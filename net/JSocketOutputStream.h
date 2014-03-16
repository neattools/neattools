#if !defined( _JSocketOutputStream_h )
#define _JSocketOutputStream_h

#include "JOutputStream.h"
#include "JSocket.h"
#include "JDescriptor.h"

class
#include "JBase.hpp"
JSocketOutputStream
  : public JDescriptor, public JOutputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSocketOutputStream();
    JSocketOutputStream(const JSocket& sock);
    virtual JOutputStream& operator<<(const JBlock &B);
};

#endif
