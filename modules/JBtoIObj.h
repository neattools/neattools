#if !defined( _JBtoIObj_h )
#define _JBtoIObj_h

#include "JAddObj.h"

class JBtoIObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBtoIObj();
    virtual int inputType(int n);
    virtual JString outputTag(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
