#if !defined( _JEqualObj_h )
#define _JEqualObj_h

#include "JGreaterThanObj.h"

class JEqualObj : public JGreaterThanObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
