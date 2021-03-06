#if !defined( _JSEqualObj_h )
#define _JSEqualObj_h

#include "JSGreaterThanObj.h"

class JSEqualObj : public JSGreaterThanObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
