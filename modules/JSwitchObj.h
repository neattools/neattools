#if !defined( _JSwitchObj_h )
#define _JSwitchObj_h

#include "JBtnObj.h"

class JSwitchObj : public JBtnObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSwitchObj::JSwitchObj();
    virtual boolean mouseDown(JEvent& e, double x, double y);
    virtual boolean mouseUp(JEvent& e, double x, double y);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    boolean depressOnly;
};

#endif
