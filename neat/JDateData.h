#if !defined( _JDateData_h )
#define _JDateData_h

#include "JDate.h"
#include "JDataType.h"

#define JDATE(data) ((JDate&)*(JDateData*)&data)

class
#include "JNEAT.hpp"
JDateData : public JDataType {
  public:
    static const int id;
    static const JColor color;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JDateData(JDate& _value);
    operator JDate&() const;
    virtual void reset() const;
    virtual void assign(const JObject& obj) const;
  protected:
    JDate& value;
};

#endif
