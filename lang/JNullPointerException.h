#if !defined( _JNullPointerException_h )
#define _JNullPointerException_h

#include "JRuntimeException.h"

class
#include "JBase.hpp"
JNullPointerException : public JRuntimeException {
  public:
    virtual const char* className() const;
    JNullPointerException();
    JNullPointerException(JString message);
};

#endif

