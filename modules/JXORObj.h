#if !defined( _JXORObj_h )
#define _JXORObj_h

#include "JANDObj.h"

class JXORObj : public JANDObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
