#if !defined( _JProcessCreateException_h )
#define _JProcessCreateException_h

#include "JRuntimeException.h"

class
#include "JBase.hpp"
JProcessCreateException : public JRuntimeException {
  public:
    virtual const char* className() const;
    JProcessCreateException();
    JProcessCreateException(JString message);
};

#endif

