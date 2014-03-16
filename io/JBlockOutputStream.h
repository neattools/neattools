#if !defined( _JBlockOutputStream_h )
#define _JBlockOutputStream_h

#include "JOutputStream.h"
#include "JBlock.h"

class
#include "JBase.hpp"
JBlockOutputStream
  : public JObject, public JOutputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBlockOutputStream();
    JBlockOutputStream(JBlock &_out);
    ~JBlockOutputStream();
    void connect(JBlock &_in);
    virtual void close();
    virtual JOutputStream& operator<<(const JBlock &B);
  protected:
    JBlock *out;
    int pos;
};

#endif
