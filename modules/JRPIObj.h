#if !defined( _JRPIObj_h )
#define _JRPIObj_h

#include "JRAddObj.h"

class JRPIObj : public JRAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRPIObj();
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
};

#endif
