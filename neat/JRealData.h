#if !defined( _JRealData_h )
#define _JRealData_h

#include "JDataType.h"

#define DOUBLE(data) ((double&)*(JRealData*)&data)

class
#include "JNEAT.hpp"
JRealData : public JDataType {
  public:
    static const int id;
    static const JColor color;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JRealData(double& _value);
    operator double&() const;
    virtual void reset() const;
    virtual void assign(const JObject& obj) const;
  protected:
    double& value;
};

#endif
