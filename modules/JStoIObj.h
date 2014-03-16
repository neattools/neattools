#if !defined( _JStoIObj_h )
#define _JStoIObj_h

#include "JAddObj.h"

class JStoIObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JStoIObj();
    virtual int inputType(int n);
    virtual JString outputTag(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
