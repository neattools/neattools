#if !defined( _JRRoundObj_h )
#define _JRRoundObj_h

#include "JRAbsObj.h"

class JRRoundObj : public JRAbsObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
