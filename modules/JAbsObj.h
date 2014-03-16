#if !defined( _JAbsObj_h )
#define _JAbsObj_h

#include "JAddObj.h"

class JAbsObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual boolean inputAllowed(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
