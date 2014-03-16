#if !defined( _JMouseObj_h )
#define _JMouseObj_h

#include "JNOTObj.h"

class JMouseObj : public JNOTObj {
  public:
    enum { XPOS, YPOS, LBTN, MBTN, RBTN, WHEEL_FORWARD, WHEEL_BACKWARD, _LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMouseObj();
    virtual void startup();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual boolean globalMouseDown(JEvent& e, int x, int y);
    virtual boolean globalMouseUp(JEvent& e, int x, int y);
    virtual boolean globalMouseMove(JEvent& e, int x, int y);
    virtual boolean globalKeyDown(JEvent& e, int key);
    virtual boolean gotFocus(JEvent& e);
    virtual boolean lostFocus(JEvent& e);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int state[_LAST];
    int focusOn;
};

#endif
