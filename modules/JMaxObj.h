#if !defined( _JMaxObj_h )
#define _JMaxObj_h

#include "JAddObj.h"

class JMaxObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
