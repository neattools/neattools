#if !defined( _JIntegerData_h )
#define _JIntegerData_h

#include "JDataType.h"

#define INT(data) ((int&)*(JIntegerData*)&data)

class
#include "JNEAT.hpp"
JIntegerData : public JDataType {
  public:
    static const int id;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JIntegerData(int& _value);
    operator int&() const;
    virtual void reset() const;
    virtual void assign(const JObject& obj) const;
  protected:
    int& value;
};

#endif
