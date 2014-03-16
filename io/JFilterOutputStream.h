#if !defined( _JFilterOutputStream_h )
#define _JFilterOutputStream_h

#include "JOutputStream.h"

class
#include "JBase.hpp"
JFilterOutputStream
  : public JObject, public JOutputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JFilterOutputStream();
    JFilterOutputStream(JOutputStream &_out);
    void connect(JOutputStream &_out);
    virtual JOutputStream& operator<<(const JBlock &B);
    virtual void flush();
    virtual void close();
  protected:
    JOutputStream *out;
    virtual void initialize();
};

#endif
