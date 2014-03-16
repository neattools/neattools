#if !defined( _JRealProperty_h )
#define _JRealProperty_h

#include "JProperty.h"

class
#include "JNEAT.hpp"
JRealProperty : public JProperty {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JRealProperty();
    JRealProperty(JString name, double _value);
    JRealProperty(JString name, double _value, int _w, int _f);
    virtual boolean edit(int x, int y);
    virtual JString toJString();
    double value;
    int w, f;
};

#endif
