#if !defined( _JBlockInputStream_h )
#define _JBlockInputStream_h

#include "JInputStream.h"
#include "JBlock.h"

class
#include "JBase.hpp"
JBlockInputStream 
  : public JObject, public JInputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBlockInputStream();
    JBlockInputStream(JBlock &_in);
    void connect(JBlock &_in);
    virtual JInputStream& operator>>(const JBlock &B);
    virtual JInputStream& operator>>(JString &V);
    virtual long skip(long n);
    virtual int available();
    virtual void mark(int readLimit);
    virtual void reset();
    virtual boolean markSupported();
  protected:
    JBlock *in;
    int pos;
    int marklimit;
    int markpos;
};

#endif
