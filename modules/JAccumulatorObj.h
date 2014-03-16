#if !defined( _JAccumulatorObj_h )
#define _JAccumulatorObj_h

#include "JDivideObj.h"

class JAccumulatorObj : public JDivideObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
};

#endif
