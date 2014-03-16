#if !defined( _JScrambledStringProperty_h )
#define _JScrambledStringProperty_h

#include "JStringProperty.h"

class
#include "JNEAT.hpp"
JScrambledStringProperty : public JStringProperty {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static JString scramble(JString src);
    static JString unscramble(JString src);
    JScrambledStringProperty();
    JScrambledStringProperty(JString name, JString _value);
    virtual const char* className() const;
    virtual JObject* clone() const;
};

#endif
