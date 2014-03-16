#if !defined( _JMouseBtnObj_h )
#define _JMouseBtnObj_h

#include "JNOTObj.h"

class JMouseBtnObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { LEFT, RIGHT, MIDDLE};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMouseBtnObj(int type = LEFT);
    virtual void startup();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual boolean globalMouseDown(JEvent& e, int x, int y);
    virtual boolean globalMouseUp(JEvent& e, int x, int y);
    virtual boolean gotFocus(JEvent& e);
    virtual boolean lostFocus(JEvent& e);
    virtual void engine(int n, JLinkObj& link);
    virtual void addButton(JComponent *panel);
  protected:
    int type;
    int tmask;
    int state;
    int focusOn;
};

#endif
