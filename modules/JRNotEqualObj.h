#if !defined( _JRNotEqualObj_h )
#define _JRNotEqualObj_h

#include "JRGreaterThanObj.h"

class JRNotEqualObj : public JRGreaterThanObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
