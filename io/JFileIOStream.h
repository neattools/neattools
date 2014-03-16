#if !defined( _JFileIOStream_h )
#define _JFileIOStream_h

#include "JFileInputStream.h"
#include "JOutputStream.h"

class
#include "JBase.hpp"
JFileIOStream : public JFileInputStream, public JOutputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JFileIOStream();
    JFileIOStream(const JString& name);
    virtual void open(JString name);
    virtual JOutputStream& operator<<(const JBlock &B);
    virtual void close();
    virtual boolean truncate(long size);
};

#endif
