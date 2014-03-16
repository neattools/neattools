#if !defined( _JSPosObj_h )
#define _JSPosObj_h

#include "JAbsObj.h"
#include "JString.h"

class JSPosObj : public JAbsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSPosObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JString v[2];
};

#endif
