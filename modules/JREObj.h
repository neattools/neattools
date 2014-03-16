#if !defined( _JREObj_h )
#define _JREObj_h

#include "JRPIObj.h"

class JREObj : public JRPIObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
};

#endif
