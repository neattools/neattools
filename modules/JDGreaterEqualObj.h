#if !defined( _JDGreaterEqualObj_h )
#define _JDGreaterEqualObj_h

#include "JDGreaterThanObj.h"

class JDGreaterEqualObj : public JDGreaterThanObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
