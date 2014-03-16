#if !defined( _JORObj_h )
#define _JORObj_h

#include "JANDObj.h"

class JORObj : public JANDObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
