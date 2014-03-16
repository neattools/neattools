#if !defined( _JIOException_h )
#define _JIOException_h

#include "JException.h"

class
#include "JBase.hpp"
JIOException : public JException {
  public:
    virtual const char* className() const;
    JIOException();
    JIOException(JString message);
};

#endif

