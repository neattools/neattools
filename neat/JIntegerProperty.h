#if !defined( _JIntegerProperty_h )
#define _JIntegerProperty_h

#include "JProperty.h"

class
#include "JNEAT.hpp"
JIntegerProperty : public JProperty {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JIntegerProperty();
    JIntegerProperty(JString name, int v, int min, int max);
    virtual boolean check();
    virtual boolean edit(int x, int y);
    virtual JString toJString();
    int value;
    int minimum;
    int maximum;
};

#endif
