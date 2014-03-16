#if !defined( _JPulseObj_h )
#define _JPulseObj_h

#include "JNOTObj.h"

class JPulseObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JPulseObj();
    virtual JString inputTag(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int nvalue;
};

#endif
