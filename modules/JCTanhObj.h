#if !defined( _JCTanhObj_h )
#define _JCTanhObj_h

#include "JCSinObj.h"

class JCTanhObj : public JCSinObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
