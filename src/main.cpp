#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <error.h>
#include <chrono>
#include <exception>

#include <opencv2/highgui/highgui.hpp>
#include <boost/program_options.hpp> 
#include <boost/log/trivial.hpp>

#include "Arduino.hh"
#include "PtrGreyCamera.hh"
#include "Streamer.hpp"

#include "config.h"

using namespace std::chrono;
using namespace cv;

int socket_ = -1;

void sig_handler( int s )
{
    cout << "Got keyboard interrupt. Removing socket" << endl;
    close( socket_ );
    remove( SOCK_PATH );
    throw runtime_error( "Ctrl+C pressed" );
}

// This function returns the camera to its default state by re-enabling automatic
// exposure.
int ResetExposure(INodeMap & nodeMap)
{
        int result = 0;
        try
        {
                // 
                // Turn automatic exposure back on
                //
                // *** NOTES ***
                // Automatic exposure is turned on in order to return the camera to its 
                // default state.
                //
                CEnumerationPtr ptrExposureAuto = nodeMap.GetNode("ExposureAuto");
                if (!IsAvailable(ptrExposureAuto) || !IsWritable(ptrExposureAuto))
                {
                        cout << "Unable to enable automatic exposure (node retrieval). Non-fatal error..." << endl << endl;
                        return -1;
                }
        
                CEnumEntryPtr ptrExposureAutoContinuous = ptrExposureAuto->GetEntryByName("Continuous");
                if (!IsAvailable(ptrExposureAutoContinuous) || !IsReadable(ptrExposureAutoContinuous))
                {
                        cout << "Unable to enable automatic exposure (enum entry retrieval). Non-fatal error..." << endl << endl;
                        return -1;
                }
                ptrExposureAuto->SetIntValue(ptrExposureAutoContinuous->GetValue());
                cout << "Automatic exposure enabled..." << endl << endl;
        }
        catch (Spinnaker::Exception &e)
        {
                cout << "Error: " << e.what() << endl;
                result = -1;
        }
        return result;
}

/**
 * @brief Write data to socket.
 *
 * @param data
 * @param size
 *
 * @return 
 */
int write_data( void* data, size_t width, size_t height )
{
    // If socket_ is not set, don't try to write.
    if( socket_ == 0 )
        return 0;

    Mat img(height, width, CV_8UC1, data );
    data = img.data;

#ifdef TEST_WITH_CV
    imshow( "MyImg", img );
    waitKey( 10 );
#else
    try 
    {
        if( write( socket_, data,  width * height ) == -1 )
            throw runtime_error( strerror( errno ) );
    } 
    catch ( exception & e )
    {
        throw runtime_error( "Error in writing" );
    }
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
    cout << "[INFO] Creating socket " << SOCK_PATH << endl;
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

#if 0
void configure_camera( CameraPtr pCam )
{
    cout << "Max width: " << pCam->Width << endl;
    //cout << "Max height: " << pCam->Height.GetValue( ) << endl;
}
#endif


// Example entry point; please see Enumeration example for more in-depth
// comments on preparing and cleaning up the system.
int main(int argc, char* argv[] )
{
    // Print application build information
    cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;
    /*-----------------------------------------------------------------------------
     *  Handle program options here.
     *-----------------------------------------------------------------------------*/
    namespace po = boost::program_options;
    po::variables_map vm;

    try {
        po::options_description desc( "Arduino + Camera client" );

        desc.add_options( )
            ( "help", "produce help message" )
            ( "port", po::value<string>(), "Serial port to read from" )
            ( "name", po::value<string>(), "Name of the animal" )
            ( "session_num", po::value<int>(), "Session number" )
            ( "session_type", po::value<int>(), "Session type" )
            ;
        po::store( po::parse_command_line( argc, argv, desc), vm );
        po::notify( vm );

        if (vm.count("help") ) {
            cout << desc;
            return 0;
        }

        if ( ! (
                    vm.count( "port") && vm.count( "name" ) 
                    && vm.count( "session_num" ) && vm.count( "session_type" ) 
               )
           )
        {
            cout << "[ERROR] One or more required arguments are missing " << endl;
            cout << desc << endl;
            return 0;
        }
    } catch ( exception& e ) {
        cerr << "Error : " << e.what( ) << endl;
        return 1;
    }

    
    /*-----------------------------------------------------------------------------
     *  Step 1: Poll for serial port for sometime. If connection can not be made
     *  quit. Otherwise, we need to launch a parallel process which reads from
     *  termnal to send commands to arduino.
     *-----------------------------------------------------------------------------*/

    Arduino arduino( vm[ "port" ].as<string>(), 38400 );
    PtrGreyCamera cam( );

    return 0;
}
