#if !defined( _JBufferedOutputStream_h )
#define _JBufferedOutputStream_h

#include "JFilterOutputStream.h"
#include "JBlock.h"

class
#include "JBase.hpp"
JBufferedOutputStream : public JFilterOutputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBufferedOutputStream();
    JBufferedOutputStream(JOutputStream &_out);
    ~JBufferedOutputStream();
    virtual JOutputStream& operator<<(const JBlock &B);
    virtual void flush();
  protected:
    JBlock buf;
    int count;
    virtual void initialize();
};

#endif
