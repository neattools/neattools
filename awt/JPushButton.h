#if !defined( _JPushButton_h )
#define _JPushButton_h

#include "JButton.h"

class
#include "JAWT.hpp"
JPushButton : public JButton {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JPushButton* create(JComponent* p, JString text);
    JPushButton();
    boolean getAutoRepeat();
    boolean setAutoRepeat(boolean _repeat);
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
  protected:
    boolean autoRepeat;
};

#endif
