#if !defined( _JInputStream_h )
#define _JInputStream_h

#include "JObject.h"

class
#include "JBase.hpp"
JInputStream {
  public:
    virtual const char* className() const;
    virtual JInputStream& operator>>(const class JBlock &B) = 0;
    virtual JInputStream& operator>>(class JString &v);
    virtual long skip(long n);
    virtual int available();
    virtual void mark(int readLimit);
    virtual void close();
    virtual void reset();
    virtual boolean markSupported();
};

#endif
