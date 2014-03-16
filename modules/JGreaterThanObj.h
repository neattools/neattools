#if !defined( _JGreaterThanObj_h )
#define _JGreaterThanObj_h

#include "JNOTObj.h"

class JGreaterThanObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JGreaterThanObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int v[2];
};

#endif
