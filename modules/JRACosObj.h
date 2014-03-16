#if !defined( _JRACosObj_h )
#define _JRACosObj_h

#include "JRAbsObj.h"

class JRACosObj : public JRAbsObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
