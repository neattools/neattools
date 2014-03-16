#if !defined( _JProperty_h )
#define _JProperty_h

#include "JString.h"

class
#include "JNEAT.hpp"
JProperty : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual int compareTo(const JObject& s) const;
    JProperty();
    JProperty(JString name);
    JString getName();
    boolean isDirty();
    virtual boolean check();
    virtual boolean edit(int x, int y) = 0;
    virtual JString toJString() = 0;
    JString name;
    boolean dirty;
};

#endif
