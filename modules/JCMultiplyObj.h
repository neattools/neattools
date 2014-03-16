#if !defined( _JCMultiplyObj_h )
#define _JCMultiplyObj_h

#include "JCAddObj.h"

class JCMultiplyObj : public JCAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
