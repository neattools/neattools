#if !defined( _JRMaxObj_h )
#define _JRMaxObj_h

#include "JRAddObj.h"

class JRMaxObj : public JRAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
