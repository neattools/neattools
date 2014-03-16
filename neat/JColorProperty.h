#if !defined( _JColorProperty_h )
#define _JColorProperty_h

#include "JProperty.h"
#include "JColor.h"

class
#include "JNEAT.hpp"
JColorProperty : public JProperty {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JColorProperty();
    JColorProperty(JString name, JColor c);
    virtual boolean edit(int x, int y);
    virtual JString toJString();
    JColor color;
};

#endif
