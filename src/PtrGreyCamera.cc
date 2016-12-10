/*
 * =====================================================================================
 *
 *       Filename:  Camera.cc
 *
 *    Description:  PtrGreyCamera client.
 *
 *        Version:  1.0
 *        Created:  Saturday 10 December 2016 11:47:34  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#include "PtrGreyCamera.hh"

#include <boost/log/trivial.hpp>

PtrGreyCamera::PtrGreyCamera( )
{
    BOOST_LOG_TRIVIAL( info ) << "Initializing camera client";

    // Retrieve singleton reference to system object
    system_ = System::GetInstance();
    if( system_->IsInUse( ) )
    {
        BOOST_LOG_TRIVIAL( warning ) << 
            "PtrGreyCamera is already in use. Reattach and continue";
        return;
    }

    // Retrieve list of cameras from the system
    cameras_ = system_->GetCameras();

    unsigned int numPtrGreyCameras = cameras_.GetSize();

    BOOST_LOG_TRIVIAL( info ) << "Number of cameras detected: " 
        << numPtrGreyCameras << endl << endl;

    // Finish if there are no cameras
    if (numPtrGreyCameras == 0)
    {
        // Clear camera list before releasing system_
        cameras_.Clear();

        // Release system_
        system_->ReleaseInstance();
        BOOST_LOG_TRIVIAL( info ) << "Not enough cameras! Existing ..." << endl;
        return;
    }

    // Since there are enough camera lets initialize socket to write ar
    // frames.

    camera_ = cameras_.GetByIndex( 0 );

#if 0
    // Configure camera here.
    // configure_camera( pCam );
    //result = RunSinglePtrGreyCamera( );

    camera_ = nullptr;
    // Clear camera list before releasing system_
    cameras__.Clear();

    // Release system_
    //system_->ReleaseInstance();
    std::BOOST_LOG_TRIVIAL( info ) << "All done" << std::endl;
#endif 

}

PtrGreyCamera::~PtrGreyCamera( )
{
    BOOST_LOG_TRIVIAL( warning ) << "Camera client existing... ";
}

int PtrGreyCamera::AcquireImages(  )
{

}

void PtrGreyCamera::run( )
{

}

#if 0
    signal( SIGINT, sig_handler );
    int result = 0;
    try
    {

        auto startTime = system_clock::now();

#if 1
        CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode");
        if (!IsAvailable(ptrAcquisitionMode) || !IsWritable(ptrAcquisitionMode))
        {
            BOOST_LOG_TRIVIAL( info ) << "Unable to set acquisition mode to continuous " 
                << " (enum retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Retrieve entry node from enumeration node
        CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
        if (!IsAvailable(ptrAcquisitionModeContinuous) || !IsReadable(ptrAcquisitionModeContinuous))
        {
            BOOST_LOG_TRIVIAL( info ) << "Unable to set acquisition mode to continuous " << 
                " (entry retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Retrieve integer value from entry node
        int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();

        // Set integer value from entry node as new value of enumeration node
        ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);
        BOOST_LOG_TRIVIAL( info ) << "Acquisition mode set to continuous..." << endl;

        // Change the acquition frame rate.

#else
        // This section does not work.
        CEnumerationPtr pAcquisitionMode = nodeMap.GetNode( "AcquisitionMode" );
        pAcquisitionMode->SetIntValue( AcquisitionMode_MultiFrame );
        CIntegerPtr pAcquitionFrameCount = nodeMap.GetNode( "AcquisitionBurstFrameCount" );
        pAcquitionFrameCount->SetValue( 3 );
        BOOST_LOG_TRIVIAL( info ) << "Frame per fetch " << pAcquitionFrameCount->GetValue( ) << endl;
#endif

        pCam->BeginAcquisition();

        gcstring deviceSerialNumber("");
        CStringPtr ptrStringSerial = nodeMapTLDevice.GetNode("DeviceSerialNumber");
        if (IsAvailable(ptrStringSerial) && IsReadable(ptrStringSerial))
        {
            deviceSerialNumber = ptrStringSerial->GetValue();
            BOOST_LOG_TRIVIAL( info ) << "Device serial number retrieved " << deviceSerialNumber 
                << endl;
        }


        char notification[100] = "running ..";
        while( true )
        {

            try
            {
                ImagePtr pResultImage = pCam->GetNextImage();
                //BOOST_LOG_TRIVIAL( info ) << "Pixal format: " << pResultImage->GetPixelFormatName( ) << endl;

                if ( pResultImage->IsIncomplete() ) /* Image is incomplete. */
                {
                    BOOST_LOG_TRIVIAL( info ) << "[WARN] Image incomplete with image status " << 
                        pResultImage->GetImageStatus() << " ..." << endl;
                }
                else
                {
                    size_t width = pResultImage->GetWidth();
                    size_t height = pResultImage->GetHeight();
                    size_t size = pResultImage->GetBufferSize( );
                    total_frames_ += 1;
                    //BOOST_LOG_TRIVIAL( info ) << "H: "<< height << " W: " << width << " S: " << size << endl;
                    // Convert the image to Monochorme, 8 bits (1 byte) and send
                    // the output.
                    //auto img = pResultImage->Convert( PixelFormat_Mono8 );
                    write_data( pResultImage->GetData( ), width, height );

                    // Compure FPS after every 100 frames.
                    if( total_frames_ % 100 == 0 )
                    {
                        duration<double> elapsedSecs = system_clock::now( ) - startTime;
                        fps_ = ( float ) total_frames_ / elapsedSecs.count( );
                        BOOST_LOG_TRIVIAL( info ) << "Running FPS : " << fps_ << endl;
                    }
                }
            }
            catch( runtime_error& e )
            {
                BOOST_LOG_TRIVIAL( info ) << "User pressed Ctrl+c" << endl;
                break;
            }
            catch (Spinnaker::Exception &e)
            {
                BOOST_LOG_TRIVIAL( info ) << "Error: " << e.what() << endl;
                result = -1;
            }
        }
        pCam->EndAcquisition();
    }
    catch (Spinnaker::Exception &e)
    {
        BOOST_LOG_TRIVIAL( info ) << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// This function prints the device information of the camera from the transport
// layer; please see NodeMapInfo example for more in-depth comments on printing
// device information from the nodemap.
int PtrGreyCamera::PrintDeviceInfo(INodeMap & nodeMap)
{
    int result = 0;

    BOOST_LOG_TRIVIAL( info ) << endl << "*** DEVICE INFORMATION ***" << endl << endl;

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
                BOOST_LOG_TRIVIAL( info ) << pfeatureNode->GetName() << " : ";
                CValuePtr pValue = (CValuePtr)pfeatureNode;
                BOOST_LOG_TRIVIAL( info ) << (IsReadable(pValue) ? pValue->ToString() : "Node not readable");
                BOOST_LOG_TRIVIAL( info ) << endl;
            }

        }
        else
        {
            BOOST_LOG_TRIVIAL( info ) << "Device control information not available." << endl;
        }
    }
    catch (Spinnaker::Exception &e)
    {
        BOOST_LOG_TRIVIAL( info ) << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// This function acts as the body of the example; please see NodeMapInfo example
// for more in-depth comments on setting up cameras.
int PtrGreyCamera::RunSinglePtrGreyCamera(PtrGreyCameraPtr pCam, int socket)
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

        // Set width, height
        CIntegerPtr width = nodeMap.GetNode("Width");
        width->SetValue( FRAME_WIDTH );

        CIntegerPtr height = nodeMap.GetNode("Height");
        height->SetValue( FRAME_HEIGHT );

        // Set frame rate manually.
        CBooleanPtr pAcquisitionManualFrameRate = nodeMap.GetNode( "AcquisitionFrameRateEnable" );
        pAcquisitionManualFrameRate->SetValue( true );

        CFloatPtr ptrAcquisitionFrameRate = nodeMap.GetNode("AcquisitionFrameRate");

        try {
            BOOST_LOG_TRIVIAL( info ) << "Trying to set frame rate to " << EXPECTED_FPS << endl;
            ptrAcquisitionFrameRate->SetValue( EXPECTED_FPS );
        }
        catch ( std::exception & e )
        {
            BOOST_LOG_TRIVIAL( info ) << "Failed to set frame rate. Using default ... " << endl;
            BOOST_LOG_TRIVIAL( info ) << "\tError was " << e.what( ) << endl;
        }

        if (!IsAvailable(ptrAcquisitionFrameRate) || !IsReadable(ptrAcquisitionFrameRate)) 
            BOOST_LOG_TRIVIAL( info ) << "Unable to retrieve frame rate. " << endl << endl;
        else
        {
            fps_ = static_cast<float>(ptrAcquisitionFrameRate->GetValue());
            BOOST_LOG_TRIVIAL( info ) << "[INFO] Expected frame set to " << fps_ << endl;
        }

        // Switch off auto-exposure and set it manually.
        CEnumerationPtr ptrExposureAuto = nodeMap.GetNode("ExposureAuto");
        if (!IsAvailable(ptrExposureAuto) || !IsWritable(ptrExposureAuto))
        {
            BOOST_LOG_TRIVIAL( info ) << "Unable to disable automatic exposure (node retrieval). Aborting..." << endl << endl;
            return -1;
        }

        CEnumEntryPtr ptrExposureAutoOff = ptrExposureAuto->GetEntryByName("Off");
        if (!IsAvailable(ptrExposureAutoOff) || !IsReadable(ptrExposureAutoOff))
        {
            BOOST_LOG_TRIVIAL( info ) << "Unable to disable automatic exposure (enum entry retrieval). Aborting..." << endl << endl;
            return -1;
        }

        ptrExposureAuto->SetIntValue(ptrExposureAutoOff->GetValue());
        BOOST_LOG_TRIVIAL( info ) << "Automatic exposure disabled..." << endl;
        CFloatPtr ptrExposureTime = nodeMap.GetNode("ExposureTime");
        if (!IsAvailable(ptrExposureTime) || !IsWritable(ptrExposureTime))
        {
            BOOST_LOG_TRIVIAL( info ) << "Unable to set exposure time. Aborting..." << endl << endl;
            return -1;
        }

        // Ensure desired exposure time does not exceed the maximum
        const double exposureTimeMax = ptrExposureTime->GetMax();

        ptrExposureTime->SetValue( EXPOSURE_TIME_IN_US );
        BOOST_LOG_TRIVIAL( info ) << "Exposure time set to " << ptrExposureTime->GetValue( ) << " us..." << endl << endl;

#if 1
        // Turn of automatic gain
        CEnumerationPtr ptrGainAuto = nodeMap.GetNode("GainAuto");
        if (!IsAvailable(ptrGainAuto) || !IsWritable(ptrGainAuto))
        {
            BOOST_LOG_TRIVIAL( info ) << "Unable to disable automatic gain (node retrieval). Aborting..." << endl << endl;
            return -1;
        }
        CEnumEntryPtr ptrGainAutoOff = ptrGainAuto->GetEntryByName("Off");
        if (!IsAvailable(ptrGainAutoOff) || !IsReadable(ptrGainAutoOff))
        {
            BOOST_LOG_TRIVIAL( info ) << "Unable to disable automatic gain (enum entry retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Set gain; gain recorded in decibels
        CFloatPtr ptrGain = nodeMap.GetNode("Gain");
        if (!IsAvailable(ptrGain) || !IsWritable(ptrGain))
        {
            BOOST_LOG_TRIVIAL( info ) << "[WARN] Unable to set gain (node retrieval). Using default ..." << endl;
        }
        else
        {
            double gainMax = ptrGain->GetMax();
            double gainToSet = ptrGain->GetMin( );
            ptrGain->SetValue(gainToSet);
        }

#endif

        /*-----------------------------------------------------------------------------
         *  IMAGE ACQUISITION
         *-----------------------------------------------------------------------------*/
        result = AcquireImages(pCam, nodeMap, nodeMapTLDevice, socket );

        // Reset settings.
        ResetExposure( nodeMap );

        // Deinitialize camera
        pCam->DeInit();
    }
    catch (Spinnaker::Exception &e)
    {
        BOOST_LOG_TRIVIAL( info ) << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

#endif

