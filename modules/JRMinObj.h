#if !defined( _JRMinObj_h )
#define _JRMinObj_h

#include "JRAddObj.h"

class JRMinObj : public JRAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
