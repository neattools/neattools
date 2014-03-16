#if !defined( _JTNG3Obj_h )
#define _JTNG3Obj_h

#include "JTNGObj.h"

class JTNG3Obj : public JTNGObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JTNG3Obj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void processByte(int v);
  protected:
    int sepCount;
    uchar separators[2];
};

#endif
