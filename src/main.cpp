#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <error.h>
#include "Streamer.hpp"
#include <chrono>
#include <exception>
#include <opencv2/highgui/highgui.hpp>

using namespace std::chrono;

#ifdef TEST_WITH_CV2 
using namespace cv;
#endif

#define SOCK_PATH  "/tmp/socket_blinky"
#define BLOCK_SIZE  4096                        /* Block to write. */

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

int total_frames_ = 0;
int socket_ = -1;                               /* Socket descriptor */
float fps_ = 0.0;                               /* Frame per second. */

SystemPtr system_;
CameraList cam_list_;

void sig_handler( int s )
{
    cout << "Got keyboard interrupt. Removing socket" << endl;
    close( socket_ );
    throw runtime_error( "Ctrl+C pressed" );
    remove( SOCK_PATH );
}

/**
 * @brief Write data to socket.
 *
 * @param data
 * @param size
 *
 * @return 
 */
int write_data( void* data, size_t size )
{
    // If socket_ is not set, don't try to write.
    if( socket_ == 0 )
        return 0;

#if 0
    size_t nBlocks = size / BLOCK_SIZE;
    for (size_t i = 0; i < nBlocks; i++) 
    {
        void* buf = data + (i * BLOCK_SIZE);
        if( write( socket_, buf,  BLOCK_SIZE ) == -1 )
            throw runtime_error( strerror( errno ) );
    }
#else
    if( write( socket_, data,  size ) == -1 )
        throw runtime_error( strerror( errno ) );
#endif
    return 0;
}

int create_socket( bool waitfor_client = true )
{
    int s, s2, len;
    struct sockaddr_un local, remote;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    
    remove(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }


    // There is no point continuing if there is not one to read the data.
    while( true )
    {
        if( ! waitfor_client )
            return 0;
        int done, n;
        cout << "Waiting for a connection..." << endl;
        socklen_t t = sizeof(remote);
        if( (s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1 )
        {
            perror("accept");
            exit(1);
        }

        cout << "Connected." << endl;
        break;
    }

    // Assign to global value.
    socket_ = s2;
    return s2;
}

void show_image( void* data, size_t width, size_t height )
{
    Mat img(height, width, CV_8UC1, data );
    //imshow( "MyImg", img );
    //waitKey( 10 );
}

int AcquireImages(CameraPtr pCam, INodeMap & nodeMap , INodeMap & nodeMapTLDevice , int socket )
{
    signal( SIGINT, sig_handler );
    int result = 0;
    try
    {

        auto startTime = system_clock::now();

        CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode");
        if (!IsAvailable(ptrAcquisitionMode) || !IsWritable(ptrAcquisitionMode))
        {
            cout << "Unable to set acquisition mode to continuous " 
                << " (enum retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Retrieve entry node from enumeration node
        CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
        if (!IsAvailable(ptrAcquisitionModeContinuous) || !IsReadable(ptrAcquisitionModeContinuous))
        {
            cout << "Unable to set acquisition mode to continuous " << 
                " (entry retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Retrieve integer value from entry node
        int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();

        // Set integer value from entry node as new value of enumeration node
        ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);
        cout << "Acquisition mode set to continuous..." << endl;

        pCam->BeginAcquisition();

        gcstring deviceSerialNumber("");
        CStringPtr ptrStringSerial = nodeMapTLDevice.GetNode("DeviceSerialNumber");
        if (IsAvailable(ptrStringSerial) && IsReadable(ptrStringSerial))
        {
            deviceSerialNumber = ptrStringSerial->GetValue();
            cout << "Device serial number retrieved " << deviceSerialNumber 
                << endl;
        }

        while( true )
        {
            try
            {
                ImagePtr pResultImage = pCam->GetNextImage();
                //cout << "Pixal format: " << pResultImage->GetPixelFormatName( ) << endl;

                if ( pResultImage->IsIncomplete() ) /* Image is incomplete. */
                {
                    cout << "[WARN] Image incomplete with image status " << 
                        pResultImage->GetImageStatus() << " ..." << endl;
                }
                else
                {
                    size_t width = pResultImage->GetWidth();
                    size_t height = pResultImage->GetHeight();
                    size_t size = pResultImage->GetBufferSize( );
                    total_frames_ += 1;
                    //cout << "H: "<< height << " W: " << width << " S: " << size << endl;
                    // Convert the image to Monochorme, 8 bits (1 byte) and send
                    // the output.
                    //auto img = pResultImage->Convert( PixelFormat_Mono8 );

#ifdef TEST_WITH_CV2
                    show_image( pResultImage->GetData( ), width, height );
#else
                    write_data( img, size);
#endif
                    if( total_frames_ % 100 == 0 )
                    {
                        duration<double> elapsedSecs = system_clock::now( ) - startTime;
                        double fps = ( float ) total_frames_ / elapsedSecs.count( );
                        cout << "Running FPS : " << fps << endl;
                    }
                }
            }
            catch( runtime_error& e )
            {
                cout << "User pressed Ctrl+c" << endl;
                break;
            }
            catch (Spinnaker::Exception &e)
            {
                cout << "Error: " << e.what() << endl;
                result = -1;
            }
        }
        pCam->EndAcquisition();
    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// This function prints the device information of the camera from the transport
// layer; please see NodeMapInfo example for more in-depth comments on printing
// device information from the nodemap.
int PrintDeviceInfo(INodeMap & nodeMap)
{
    int result = 0;

    cout << endl << "*** DEVICE INFORMATION ***" << endl << endl;

    try
    {
        FeatureList_t features;
        CCategoryPtr category = nodeMap.GetNode("DeviceInformation");
        if (IsAvailable(category) && IsReadable(category))
        {
            category->GetFeatures(features);

            FeatureList_t::const_iterator it;
            for (it = features.begin(); it != features.end(); ++it)
            {
                CNodePtr pfeatureNode = *it;
                cout << pfeatureNode->GetName() << " : ";
                CValuePtr pValue = (CValuePtr)pfeatureNode;
                cout << (IsReadable(pValue) ? pValue->ToString() : "Node not readable");
                cout << endl;
            }

        }
        else
        {
            cout << "Device control information not available." << endl;
        }
    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// This function acts as the body of the example; please see NodeMapInfo example
// for more in-depth comments on setting up cameras.
int RunSingleCamera(CameraPtr pCam, int socket)
{
    int result = 0;

    try
    {
        // Retrieve TL device nodemap and print device information
        INodeMap & nodeMapTLDevice = pCam->GetTLDeviceNodeMap();

        result = PrintDeviceInfo(nodeMapTLDevice);

        // Initialize camera
        pCam->Init();

        // Retrieve GenICam nodemap
        INodeMap & nodeMap = pCam->GetNodeMap();

        CFloatPtr ptrAcquisitionFrameRate = nodeMap.GetNode("AcquisitionFrameRate");
        if (!IsAvailable(ptrAcquisitionFrameRate) || 
                !IsReadable(ptrAcquisitionFrameRate)) 
            cout << "Unable to retrieve frame rate. " << endl << endl;
        else
        {
            fps_ = static_cast<float>(ptrAcquisitionFrameRate->GetValue());
            cout << "Frame rate is " << fps_ << endl;
        }

        result = AcquireImages(pCam, nodeMap, nodeMapTLDevice, socket );

        // Deinitialize camera
        pCam->DeInit();
    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// Example entry point; please see Enumeration example for more in-depth
// comments on preparing and cleaning up the system.
int main(int /*argc*/, char** /*argv*/)
{
    // Create socket 
    socket_ = create_socket( false );

    int result = 0;

    // Print application build information
    cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

    // Retrieve singleton reference to system object
    system_ = System::GetInstance();
    if( system_->IsInUse( ) )
    {
        cout << "Warn: Camera is already in use. Reattach and continue";
        exit( -1 );
    }

    // Retrieve list of cameras from the system
    cam_list_ = system_->GetCameras();

    unsigned int numCameras = cam_list_.GetSize();

    cout << "Number of cameras detected: " << numCameras << endl << endl;

    // Finish if there are no cameras
    if (numCameras == 0)
    {
        // Clear camera list before releasing system_
        cam_list_.Clear();

        // Release system_
        system_->ReleaseInstance();

        cout << "Not enough cameras!" << endl;
        cout << "Done! Press Enter to exit..." << endl;
        getchar();

        return -1;
    }

    CameraPtr pCam = NULL;

    pCam = cam_list_.GetByIndex( 0 );
    result = RunSingleCamera(pCam, socket_);

    pCam = NULL;
    // Clear camera list before releasing system_
    cam_list_.Clear();

    // Release system_
    system_->ReleaseInstance();
    std::cout << "All done" << std::endl;

    if( socket_ > 0 )
        close( socket_ );

    return 0;
}
