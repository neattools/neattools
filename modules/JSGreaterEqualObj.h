#if !defined( _JSGreaterEqualObj_h )
#define _JSGreaterEqualObj_h

#include "JSGreaterThanObj.h"

class JSGreaterEqualObj : public JSGreaterThanObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
