#if !defined( _JArithmeticException_h )
#define _JArithmeticException_h

#include "JRuntimeException.h"

class
#include "JBase.hpp"
JArithmeticException : public JRuntimeException {
  public:
    virtual const char* className() const;
    JArithmeticException();
    JArithmeticException(JString message);
};

#endif

