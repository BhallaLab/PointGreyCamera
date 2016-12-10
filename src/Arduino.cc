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
}  /* -----  end of method Arduino::~Arduino  (destructor)  ----- */


