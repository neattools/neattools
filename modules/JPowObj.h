#if !defined( _JPowObj_h )
#define _JPowObj_h

#include "JDivideObj.h"

class JPowObj : public JDivideObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
