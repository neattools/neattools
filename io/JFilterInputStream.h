#if !defined( _JFilterInputStream_h )
#define _JFilterInputStream_h

#include "JInputStream.h"

class
#include "JBase.hpp"
JFilterInputStream 
  : public JObject, public JInputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JFilterInputStream();
    JFilterInputStream(JInputStream &_in);
    void connect(JInputStream &_in);
    virtual JInputStream& operator>>(const JBlock &B);
    virtual JInputStream& operator>>(JString &V);
    virtual long skip(long n);
    virtual int available();
    virtual void close();
    virtual void mark(int readLimit);
    virtual void reset();
    virtual boolean markSupported();
  protected:
    JInputStream *in;
    virtual void initialize();
};

#endif
