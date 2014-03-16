#if !defined( _JRTanObj_h )
#define _JRTanObj_h

#include "JRAbsObj.h"

class JRTanObj : public JRAbsObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
