#if !defined( _JControlObj_h )
#define _JControlObj_h

#include "JSampleObj.h"

class JControlObj : public JSampleObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
