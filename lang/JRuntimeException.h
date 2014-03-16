#if !defined( _JRuntimeException_h )
#define _JRuntimeException_h

#include "JException.h"

class
#include "JBase.hpp"
JRuntimeException : public JException {
  public:
    virtual const char* className() const;
    JRuntimeException();
    JRuntimeException(JString message);
};

#endif

