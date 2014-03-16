#if !defined( _JBtnObj_h )
#define _JBtnObj_h

#include "JNBitsObj.h"

class JBtnObj : public JNBitsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { TYPE_RECT, TYPE_LEFT, TYPE_RIGHT, TYPE_UP, TYPE_DOWN};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBtnObj();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual boolean mouseDown(JEvent& e, double x, double y);
    virtual boolean mouseUp(JEvent& e, double x, double y);
    virtual void engine(int n, JLinkObj& link);
    virtual boolean setLabel(JString _label);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    boolean mousePressed;
    int type;
    JString label;
};

#endif
