#if !defined( _JCEqualObj_h )
#define _JCEqualObj_h

#include "JNOTObj.h"
#include "bcomplex.h"

class JCEqualObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JCEqualObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    jcomplex v[2];
};

#endif
