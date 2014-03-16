#if !defined( _JRCosObj_h )
#define _JRCosObj_h

#include "JRAbsObj.h"

class JRCosObj : public JRAbsObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
