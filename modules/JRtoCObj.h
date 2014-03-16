#if !defined( _JRtoCObj_h )
#define _JRtoCObj_h

#include "JCAddObj.h"

class JRtoCObj : public JCAddObj {
  protected:
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRtoCObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    double iv[2];
};

#endif
