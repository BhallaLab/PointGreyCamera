/*
 * =====================================================================================
 *
 *       Filename:  Arduino.cc
 *
 *    Description:  Arduino class.
 *
 *        Version:  1.0
 *        Created:  Saturday 10 December 2016 10:54:54  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#include "Arduino.hh"
#include <boost/log/trivial.hpp>
#include "serial/serial.h"


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Arduino
 *      Method:  Arduino
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Arduino::Arduino ( string name, int port )
{
    BOOST_LOG_TRIVIAL( trace ) << "Connecting to arduino" ;
    pSerial_ = new serial::Serial( name, port,  serial::Timeout::simpleTimeout( 1000 ) );
    if( pSerial_->isOpen( ) )
        BOOST_LOG_TRIVIAL ( info ) << "Serial port is open ..";
    else
        BOOST_LOG_TRIVIAL ( warning ) << "Could not open serial port ..";
}  /* -----  end of method Arduino::Arduino  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Arduino
 *      Method:  ~Arduino
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Arduino::~Arduino ()
{
    BOOST_LOG_TRIVIAL ( info ) << " Arduino said bye bye .." ;
    if( pSerial_ )
        delete pSerial_;
}  /* -----  end of method Arduino::~Arduino  (destructor)  ----- */


