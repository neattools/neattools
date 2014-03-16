#if !defined( _JSKeyboardObj_h )
#define _JSKeyboardObj_h

#include "JSAddObj.h"

class JSKeyboardObj : public JSAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSKeyboardObj();
    virtual boolean inputAllowed(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual boolean globalKeyDown(JEvent& e, int key);
    virtual boolean globalKeyUp(JEvent& e, int key);
  protected:
    char ks[2];
};

#endif
