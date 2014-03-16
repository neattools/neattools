#if !defined( _JRGreaterThanObj_h )
#define _JRGreaterThanObj_h

#include "JNOTObj.h"

class JRGreaterThanObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRGreaterThanObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    double v[2];
};

#endif
