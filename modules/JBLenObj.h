#if !defined( _JBLenObj_h )
#define _JBLenObj_h

#include "JBtoIObj.h"

class JBLenObj : public JBtoIObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
