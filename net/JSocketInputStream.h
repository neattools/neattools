#if !defined( _JSocketInputStream_h )
#define _JSocketInputStream_h

#include "JDescriptor.h"
#include "JInputStream.h"
#include "JSocket.h"

class
#include "JBase.hpp"
JSocketInputStream 
  : public JDescriptor, public JInputStream {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSocketInputStream();
    JSocketInputStream(const JSocket& sock);
    ~JSocketInputStream();
    virtual JInputStream& operator>>(const JBlock &B);
    virtual JInputStream& operator>>(JString &v);
};

#endif
