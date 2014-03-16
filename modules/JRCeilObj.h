#if !defined( _JRCeilObj_h )
#define _JRCeilObj_h

#include "JRAbsObj.h"

class JRCeilObj : public JRAbsObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
