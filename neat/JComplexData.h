#if !defined( _JComplexData_h )
#define _JComplexData_h

#include "bcomplex.h"
#include "JDataType.h"

#define JCOMPLEX(data) ((jcomplex&)*(JComplexData*)&data)

class
#include "JNEAT.hpp"
JComplexData : public JDataType {
  public:
    static const int id;
    static const JColor color;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JComplexData(jcomplex& _value);
    operator jcomplex&() const;
    virtual void reset() const;
    virtual void assign(const JObject& obj) const;
  protected:
    jcomplex& value;
};

#endif
