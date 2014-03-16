#if !defined( _JDNotEqualObj_h )
#define _JDNotEqualObj_h

#include "JDGreaterThanObj.h"

class JDNotEqualObj : public JDGreaterThanObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
