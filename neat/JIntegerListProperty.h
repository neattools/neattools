#if !defined( _JIntegerListProperty_h )
#define _JIntegerListProperty_h

#include "JProperty.h"
#include "JArray.h"

class
#include "JNEAT.hpp"
JIntegerListProperty : public JProperty {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static char* booleanTag[];
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JIntegerListProperty();
    JIntegerListProperty(JString name, int v, JArray tag);
    virtual boolean edit(int x, int y);
    virtual JString toJString();
    int value;
    JArray tag;
};

#endif
