#if !defined( _JSNotEqualObj_h )
#define _JSNotEqualObj_h

#include "JSGreaterThanObj.h"

class JSNotEqualObj : public JSGreaterThanObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
