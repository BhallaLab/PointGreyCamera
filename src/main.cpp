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

using namespace std::chrono;

#define SOCK_PATH  "/tmp/socket_blinky"
#define BLOCK_SIZE  4096                        /* Block to write. */

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

int total_frames_ = 0;
float fps_ = 0.0;                               /* Frame per second. */

void sig_handler( int s )
{
    cout << "Got keyboard interrupt. Removing socket" << endl;
    remove( SOCK_PATH );
    exit( 1 );
}

int write_data( int socket, void* data, size_t size )
{
    size_t nBlocks = size / BLOCK_SIZE;
    for (size_t i = 0; i < nBlocks; i++) 
    {
        void* buf = data + (i * BLOCK_SIZE);
        if( write( socket, buf,  BLOCK_SIZE ) == -1 )
        {
            cout << "Failed to write to socket" << endl;
            cout << "\tError was: " << strerror( errno ) << endl;
            return -1;
        }
    }
    return 0;
}

int create_socket( )
{
    signal( SIGINT, sig_handler );
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
    return s2;

}

int AcquireImages(CameraPtr pCam, INodeMap & nodeMap , INodeMap & nodeMapTLDevice , int socket )
{
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
        //cout << "Acquisition mode set to continuous..." << endl;

        pCam->BeginAcquisition();

        gcstring deviceSerialNumber("");
        CStringPtr ptrStringSerial = nodeMapTLDevice.GetNode("DeviceSerialNumber");
        if (IsAvailable(ptrStringSerial) && IsReadable(ptrStringSerial))
            deviceSerialNumber = ptrStringSerial->GetValue();

        while( true )
        //for (unsigned int imageCnt = 0; imageCnt < numFrames; imageCnt++)
        {
            try
            {
                ImagePtr pResultImage = pCam->GetNextImage();
                if (! pResultImage->IsIncomplete() )
                {
                    size_t width = pResultImage->GetWidth();
                    size_t height = pResultImage->GetHeight();
                    //cout << "Width : " << width << " height : "<< height << endl;
                    size_t size = width * height;
                    total_frames_ += 1;
                    write_data( socket, pResultImage->GetData( ), size);
                    if( total_frames_ % 100 == 0 )
                    {
                        duration<double> elapsedSecs = system_clock::now( ) - startTime;
                        double fps = ( float ) total_frames_ / elapsedSecs.count( );
                        cout << "Running FPS : " << fps << endl;
                    }
                }
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

        //auto start = system_clock::now( );
        //int nFrames = floor( fps_ );
        result = AcquireImages(pCam, nodeMap, nodeMapTLDevice, socket );
        //duration<double> elapsedSecs = system_clock::now( ) - start;
        //double fps = ( float ) total_frames_ / elapsedSecs.count( );
        //cout << "FPS : " << fps << endl;

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
    int client = create_socket( );

    int result = 0;

    // Print application build information
    cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

    // Retrieve singleton reference to system object
    SystemPtr system = System::GetInstance();

    // Retrieve list of cameras from the system
    CameraList camList = system->GetCameras();

    unsigned int numCameras = camList.GetSize();

    cout << "Number of cameras detected: " << numCameras << endl << endl;

    // Finish if there are no cameras
    if (numCameras == 0)
    {
        // Clear camera list before releasing system
        camList.Clear();

        // Release system
        system->ReleaseInstance();

        cout << "Not enough cameras!" << endl;
        cout << "Done! Press Enter to exit..." << endl;
        getchar();

        return -1;
    }

    CameraPtr pCam = NULL;

    pCam = camList.GetByIndex( 0 );
    result = RunSingleCamera(pCam, client);

    pCam = NULL;
    // Clear camera list before releasing system
    camList.Clear();

    // Release system
    system->ReleaseInstance();
    std::cout << "All done" << std::endl;
    return 0;
}
