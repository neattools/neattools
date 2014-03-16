#if !defined( _JToggleButton_h )
#define _JToggleButton_h

#include "JButton.h"

class
#include "JAWT.hpp"
JToggleButton : public JButton {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JToggleButton* create(JComponent*p, JString text, int state);
    JToggleButton();
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
};

#endif
