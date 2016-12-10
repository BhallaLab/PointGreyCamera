/*
 * =====================================================================================
 *
 *       Filename:  PtrGreyCamera.hh
 *
 *    Description:  PtrGreyCamera class.
 *
 *        Version:  1.0
 *        Created:  Saturday 10 December 2016 12:05:03  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#ifndef  PtrGreyCamera_INC
#define  PtrGreyCamera_INC


#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream> 

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

class PtrGreyCamera
{
    public:

        PtrGreyCamera();
        ~PtrGreyCamera();

        int AcquireImages( );

        void run(  );

    private:

        /* data */
        SystemPtr system_;
        CameraList cameras_;
        CameraPtr camera_;
};

#endif   /* ----- #ifndef PtrGreyCamera_INC  ----- */
