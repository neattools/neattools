#if !defined( _JModuleButton_h )
#define _JModuleButton_h

#include "JButton.h"
#include "JModuleObj.h"

class
#include "JNEAT.hpp"
JModuleButton : public JButton {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JModuleButton* create(JComponent* p, const JModuleObj& obj);
    JModuleButton();
    virtual void startup();
    virtual void destroy();
    virtual void paint(JGraphics g);
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
    JModuleObj *pmodule;
};

#endif
