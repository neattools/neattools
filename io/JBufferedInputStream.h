#if !defined( _JBufferedInputStream_h )
#define _JBufferedInputStream_h

#include "JFilterInputStream.h"
#include "JBlock.h"

class
#include "JBase.hpp"
JBufferedInputStream : public JFilterInputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBufferedInputStream();
    JBufferedInputStream(JInputStream &_in);
    virtual JInputStream& operator>>(const JBlock &B);
    virtual JInputStream& operator>>(JString &v);
    virtual long skip(long n);
    virtual int available();
    virtual void mark(int readLimit);
    virtual void reset();
    virtual boolean markSupported();
  private:
    JBlock buf;
    int count;
    int pos;
    int markpos;
    int marklimit;
    void fill();
    virtual void initialize();
};

#endif
