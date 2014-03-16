#if !defined( _JButton_h )
#define _JButton_h

#include "JLabel.h"

class
#include "JAWT.hpp"
JButton : public JLabel {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JButton* create(JComponent *p, JString text);
    JButton();
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseEnter(JEvent& e, int x, int y);
    virtual boolean mouseExit(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
  protected:
    boolean mousePressed;
};

#endif
