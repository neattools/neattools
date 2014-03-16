#if !defined( _JOutputStream_h )
#define _JOutputStream_h

#include "JObject.h"

class
#include "JBase.hpp"
JOutputStream {
  public:
    virtual const char* className() const;
    virtual JOutputStream& operator<<(const class JBlock &B) = 0;
    virtual void flush();
    virtual void close();
};

#endif
