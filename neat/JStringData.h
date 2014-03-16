#if !defined( _JStringData_h )
#define _JStringData_h

#include "JDataType.h"
#include "JString.h"

#define JSTRING(data) ((JString&)*(JStringData*)&data)

class
#include "JNEAT.hpp"
JStringData : public JDataType {
  public:
    static const int id;
    static const JColor color;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JStringData(JString& _value);
    operator JString&() const;
    virtual void reset() const;
    virtual void assign(const JObject& obj) const;
  protected:
    JString& value;
};

#endif
