#if !defined( _JRAtan2Obj_h )
#define _JRAtan2Obj_h

#include "JRDivideObj.h"

class JRAtan2Obj : public JRDivideObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
