#if !defined( _JBtoSObj_h )
#define _JBtoSObj_h

#include "JSAddObj.h"

class JBtoSObj : public JSAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBtoSObj();
    virtual int inputType(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
