#if !defined( _JCSinObj_h )
#define _JCSinObj_h

#include "JCAddObj.h"

class JCSinObj : public JCAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual void engine(int n, JLinkObj& link);
};

#endif
