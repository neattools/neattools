#if !defined( _JFileProperty_h )
#define _JFileProperty_h

#include "JStringProperty.h"

class
#include "JNEAT.hpp"
JFileProperty : public JStringProperty {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JFileProperty();
    JFileProperty(JString name, JString _value, JString _type);
    virtual boolean edit(int x, int y);
  protected:
    JString type;
};

#endif
