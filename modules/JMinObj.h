#if !defined( _JMinObj_h )
#define _JMinObj_h

#include "JAddObj.h"

class JMinObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
