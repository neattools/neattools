#if !defined( _JPushBtnObj_h )
#define _JPushBtnObj_h

#include "JBtnObj.h"

class JPushBtnObj : public JBtnObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JPushBtnObj();
    virtual boolean mouseDown(JEvent& e, double x, double y);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    boolean autoRepeat;
};

#endif
