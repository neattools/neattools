#if !defined( _JRSubtractObj_h )
#define _JRSubtractObj_h

#include "JRDivideObj.h"

class JRSubtractObj : public JRDivideObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
