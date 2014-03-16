#if !defined( _JCNotEqualObj_h )
#define _JCNotEqualObj_h

#include "JCEqualObj.h"

class JCNotEqualObj : public JCEqualObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
