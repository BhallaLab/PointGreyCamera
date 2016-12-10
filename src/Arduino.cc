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
#include <boost/asio/serial_port.hpp>

namespace asio = boost::asio;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Arduino
 *      Method:  Arduino
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Arduino::Arduino ( string port, int baudrate )
{
    BOOST_LOG_TRIVIAL( trace ) << "Connecting to arduino" ;
    asio::io_service io;
    pSerial_ = unique_ptr<asio::serial_port>( new asio::serial_port( io ) );
    pSerial_->open( port );
    pSerial_->set_option( asio::serial_port_base::baud_rate( baudrate ) );

    if( pSerial_->is_open( ) )
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
    if( pSerial_->is_open( ) )
        pSerial_->close( );
}  /* -----  end of method Arduino::~Arduino  (destructor)  ----- */

/**
 * @brief Check if arduino is sending valid output.
 */
void Arduino::check( )
{
    
}
