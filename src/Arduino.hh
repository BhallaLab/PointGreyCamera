/*
 * =====================================================================================
 *
 *       Filename:  Arduino.hh
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Saturday 10 December 2016 10:45:52  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#ifndef  Arduino_INC
#define  Arduino_INC

#include <string>
using namespace std;

/*
 * =====================================================================================
 *        Class:  Arduino
 *  Description:  
 * =====================================================================================
 */
class Arduino
{
    public:

        Arduino ( string port, int baudrate );    

        ~Arduino( );

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

    protected:
        /* ====================  METHODS       ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */

    private:
        /* ====================  METHODS       ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */

}; /* -----  end of class Arduino  ----- */


#endif   /* ----- #ifndef Arduino_INC  ----- */
