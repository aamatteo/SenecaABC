/* ------------------------------------------------------------------   */
/*      item            : CLException.hxx
        made by         : Rene van Paassen
        date            : 020514
	category        : header file 
        description     : 
	changes         : 020514 first version
        language        : C++
*/

#ifndef CLException_hxx
#define CLException_hxx

#ifdef CLException_cxx
static const char h_id[] =
"$Id: CLException.hxx,v 1.1 2014/12/05 15:17:32 fltsim Exp $";
#endif

#include <exception>

/** This is an exception that is thrown by control loading stuff. */
class CLException: public std::exception
{
  /** Description of this exception. */
  const char* reason;

public:
  /** Copy constructor.
      \param e   exception to be copied. */
  CLException(const CLException& e);
  
  /** Fresh constructor.
      \param reason String explaining the reason/type of this
                    exception. Make sure this is a static. */
  CLException(const char* r);
  
  /** Destructor. */
  virtual ~CLException() throw();
  
  /** Print out the reason for throwing this. */
  const char* what() const throw();
  
  /** Assignment. */
  CLException& operator= (const CLException& e); 
};

#endif
