#if !defined( _JStringProperty_h )
#define _JStringProperty_h

#include "JProperty.h"

class
#include "JNEAT.hpp"
JStringProperty : public JProperty {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JStringProperty();
    JStringProperty(JString name, JString _value);
    virtual boolean edit(int x, int y);
    virtual JString toJString();
    JString value;
};

#endif
