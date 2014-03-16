#if !defined( _JInterruptedIOException_h )
#define _JInterruptedIOException_h

#include "JIOException.h"

class
#include "JBase.hpp"
JInterruptedIOException : public JIOException {
  public:
    virtual const char* className() const;
    JInterruptedIOException();
    JInterruptedIOException(JString message);
};

#endif

