#if !defined( _JSocketException_h )
#define _JSocketException_h

#include "JIOException.h"

class
#include "JBase.hpp"
JSocketException : public JIOException {
  public:
    virtual const char* className() const;
    JSocketException();
    JSocketException(JString message);
};

#endif

