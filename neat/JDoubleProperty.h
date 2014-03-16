#if !defined( _JDoubleProperty_h )
#define _JDoubleProperty_h

#include "JProperty.h"

class
#include "JNEAT.hpp"
JDoubleProperty : public JProperty {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JDoubleProperty();
    JDoubleProperty(JString name, double v, double minimum, double maximum);
    virtual boolean check();
    virtual boolean edit(int x, int y);
    virtual JString toJString();
    double value;
    double minimum;
    double maximum;
};

#endif
