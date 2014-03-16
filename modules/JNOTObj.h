#if !defined( _JNOTObj_h )
#define _JNOTObj_h

#include "JANDObj.h"

class JNOTObj : public JANDObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual boolean inputAllowed(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
