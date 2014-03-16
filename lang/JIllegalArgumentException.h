#if !defined( _JIllegalArgumentException_h )
#define _JIllegalArgumentException_h

#include "JRuntimeException.h"

class
#include "JBase.hpp"
JIllegalArgumentException : public JRuntimeException {
  public:
    virtual const char* className() const;
    JIllegalArgumentException();
    JIllegalArgumentException(JString message);
};

#endif

