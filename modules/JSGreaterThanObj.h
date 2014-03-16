#if !defined( _JSGreaterThanObj_h )
#define _JSGreaterThanObj_h

#include "JNOTObj.h"
#include "JString.h"

class JSGreaterThanObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSGreaterThanObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JString v[2];
};

#endif
