#if !defined( _JSubtractObj_h )
#define _JSubtractObj_h

#include "JDivideObj.h"

class JSubtractObj : public JDivideObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
