#if !defined( _JUnknownHostException_h )
#define _JUnknownHostException_h

#include "JIOException.h"

class
#include "JBase.hpp"
JUnknownHostException : public JIOException {
  public:
    virtual const char* className() const;
    JUnknownHostException();
    JUnknownHostException(JString message);
};

#endif

