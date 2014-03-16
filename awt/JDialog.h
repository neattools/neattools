#if !defined( _JDialog_h )
#define _JDialog_h

#include "JComponent.h"

class
#include "JAWT.hpp"
JDialog : public JComponent {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JDialog* create(boolean widthSysMenu = true);
    JDialog();
    virtual void destroy();
    virtual boolean mouseEnter(JEvent& e, int x, int y);
    virtual boolean mouseExit(JEvent& e, int x, int y);
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
    virtual boolean mouseDrag(JEvent& e, int x, int y);
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean action(JEvent& e, JObject* arg);
  protected:
    boolean mousePressed;
};

#endif
