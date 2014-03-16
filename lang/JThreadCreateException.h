#if !defined( _JThreadCreateException_h )
#define _JThreadCreateException_h

#include "JRuntimeException.h"

class
#include "JBase.hpp"
JThreadCreateException : public JRuntimeException {
  public:
    virtual const char* className() const;
    JThreadCreateException();
    JThreadCreateException(JString message);
};

#endif

