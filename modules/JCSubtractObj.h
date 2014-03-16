#if !defined( _JCSubtractObj_h )
#define _JCSubtractObj_h

#include "JCAddObj.h"

class JCSubtractObj : public JCAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JCSubtractObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual boolean inputAllowed(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    jcomplex v[2];
};

#endif
