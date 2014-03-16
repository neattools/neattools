#if !defined( _JPipedStream_h )
#define _JPipedStream_h

#include "JInputStream.h"
#include "JOutputStream.h"
#include "JBlock.h"

class
#include "JBase.hpp"
JPipedStream : public JObject,
  public JInputStream, public JOutputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JPipedStream();
    virtual JInputStream& operator>>(const JBlock &B);
    virtual JInputStream& operator>>(JString &v);
    virtual long skip(long n);
    virtual int available();
    virtual JOutputStream& operator<<(const JBlock &B);
    virtual void flush();
  private:
    JBlock buf;
    int count;
    int pos;
    void fill();
};

#endif
