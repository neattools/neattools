#if !defined( _JBytesData_h )
#define _JBytesData_h

#include "JBlockData.h"

class
#include "JNEAT.hpp"
JBytesData : public JBlockData {
  public:
    static const int id;
    static const JColor color;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    JBytesData(JBlock& _value);
};

#endif
