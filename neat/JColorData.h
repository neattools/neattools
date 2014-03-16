#if !defined( _JColorData_h )
#define _JColorData_h

#include "JDataType.h"
#include "JColor.h"

#define JCOLOR(data) ((JColor&)*(JColorData*)&data)

class
#include "JNEAT.hpp"
JColorData : public JDataType {
  public:
    static const int id;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& obj) const;
    JColorData(JColor& _value);
    operator JColor&() const;
    virtual void reset() const; 
    virtual void assign(const JObject& obj) const;
  protected:
    JColor& value;
};

#endif
