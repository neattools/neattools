#if !defined( _JCDivideObj_h )
#define _JCDivideObj_h

#include "JCSubtractObj.h"

class JCDivideObj : public JCSubtractObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
