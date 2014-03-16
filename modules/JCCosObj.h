#if !defined( _JCCosObj_h )
#define _JCCosObj_h

#include "JCSinObj.h"

class JCCosObj : public JCSinObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
