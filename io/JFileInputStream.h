#if !defined( _JFileInputStream_h )
#define _JFileInputStream_h

#include "JDescriptor.h"
#include "JInputStream.h"

class
#include "JBase.hpp"
JFileInputStream 
  : public JDescriptor, public JInputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JFileInputStream();
    JFileInputStream(const JString& name);
    JFileInputStream(int handle, boolean ref = false);
    ~JFileInputStream();
    virtual void open(JString name);
    virtual void open(int handle, boolean ref = false);
    virtual JInputStream& operator>>(const JBlock &B);
    virtual JInputStream& operator>>(JString &v);
    virtual long skip(long n);
    virtual int available();
    virtual void close();
    virtual void reset();
    virtual long pos();
    virtual long seek(long pos);
    virtual long move(long ofs);
  protected:
    virtual void Delete();
    virtual int Duplicate();
};

#endif
