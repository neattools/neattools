#if !defined( _JMultiplyObj_h )
#define _JMultiplyObj_h

#include "JAddObj.h"

class JMultiplyObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
