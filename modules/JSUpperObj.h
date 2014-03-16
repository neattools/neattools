#if !defined( _JSUpperObj_h )
#define _JSUpperObj_h

#include "JSAddObj.h"

class JSUpperObj : public JSAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual boolean inputAllowed(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
