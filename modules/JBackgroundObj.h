#if !defined( _JBackgroundObj_h )
#define _JBackgroundObj_h

#include "JModuleObj.h"

class JBackgroundObj : public JModuleObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBackgroundObj(JColor _color = JColor::black);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    JColor color;
    JColor textColor;
    JString text;
    int drawBorder;
    int drawBackground;
};

#endif
