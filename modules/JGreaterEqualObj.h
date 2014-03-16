#if !defined( _JGreaterEqualObj_h )
#define _JGreaterEqualObj_h

#include "JGreaterThanObj.h"

class JGreaterEqualObj : public JGreaterThanObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
