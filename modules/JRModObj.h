#if !defined( _JRModObj_h )
#define _JRModObj_h

#include "JRDivideObj.h"

class JRModObj : public JRDivideObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
