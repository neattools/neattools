#if !defined( _JRAbsObj_h )
#define _JRAbsObj_h

#include "JRAddObj.h"

class JRAbsObj : public JRAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual boolean inputAllowed(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
