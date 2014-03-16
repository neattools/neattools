#if !defined( _JMousePosObj_h )
#define _JMousePosObj_h

#include "JMouseBtnObj.h"

class JMousePosObj : public JMouseBtnObj {
  public:
    enum { XPOS, YPOS};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMousePosObj(int type = XPOS);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual boolean outputAllowed(int n);
    virtual boolean globalMouseDown(JEvent& e, int x, int y);
    virtual boolean globalMouseUp(JEvent& e, int x, int y);
    virtual boolean globalMouseMove(JEvent& e, int x, int y);
    virtual void engine(int n, JLinkObj& link);
    virtual void addButton(JComponent *panel);
};

#endif
