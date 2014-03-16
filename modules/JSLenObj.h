#if !defined( _JSLenObj_h )
#define _JSLenObj_h

#include "JStoIObj.h"

class JSLenObj : public JStoIObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
