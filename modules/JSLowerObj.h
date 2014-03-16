#if !defined( _JSLowerObj_h )
#define _JSLowerObj_h

#include "JSAddObj.h"

class JSLowerObj : public JSAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual boolean inputAllowed(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
