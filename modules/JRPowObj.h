#if !defined( _JRPowObj_h )
#define _JRPowObj_h

#include "JRDivideObj.h"

class JRPowObj : public JRDivideObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
