#if !defined( _JEOFException_h )
#define _JEOFException_h

#include "JIOException.h"

class
#include "JBase.hpp"
JEOFException : public JIOException {
  public:
    virtual const char* className() const;
    JEOFException();
    JEOFException(JString message);
};

#endif

