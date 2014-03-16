#if !defined( _JStoBObj_h )
#define _JStoBObj_h

#include "JBAddObj.h"

class JStoBObj : public JBAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JStoBObj();
    virtual int inputType(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
