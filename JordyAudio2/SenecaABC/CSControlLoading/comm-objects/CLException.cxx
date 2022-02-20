/* ------------------------------------------------------------------   */
/*      item            : CLException.cxx
        made by         : Rene' van Paassen
        date            : 020514
	category        : body file 
        description     : 
	changes         : 020514 first version
        language        : C++
*/

const static char c_id[] =
"$Id: CLException.cxx,v 1.1 2014/12/05 15:17:32 fltsim Exp $";

#define CLException_cxx
#include "CLException.hxx"
 
CLException::CLException(const CLException& e) : 
  reason(e.reason) 
{
  //
}

CLException::CLException(const char* r) : 
  reason(r) 
{
  //
}
  
CLException::~CLException() throw()
{
  //
}

const char* CLException::what() const throw()
{ 
  return reason;
}

CLException& CLException::operator= (const CLException& e) 
{
  reason = e.reason; 
  return *this;
}
