#if !defined( _JFileOutputStream_h )
#define _JFileOutputStream_h

#include "JOutputStream.h"
#include "JDescriptor.h"

class
#include "JBase.hpp"
JFileOutputStream 
  : public JDescriptor, public JOutputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JFileOutputStream();
    JFileOutputStream(const JString& name);
    JFileOutputStream(int handle, boolean ref = false);
    ~JFileOutputStream();
    virtual void open(JString name);
    virtual void open(int handle, boolean ref = false);
    virtual JOutputStream& operator<<(const JBlock &B);
    virtual void close();
    virtual long pos();
    virtual long seek(long pos);
    virtual long move(long ofs);
  protected:
    virtual void Delete();
    virtual int Duplicate();
};

#endif
