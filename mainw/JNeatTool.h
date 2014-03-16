#if !defined( _JNeatTool_h )
#define _JNeatTool_h

#include "JWindow.h"
#include "JView.h"

class JNeatTool : public JWindow {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JNeatTool();
    virtual void startup();
    virtual void destroy();
    virtual void activate();
    virtual void deactivate();
    virtual void layoutMinimized();
    virtual void layoutRestored();
    virtual boolean handleJEvent(JEvent& e);
    virtual boolean gotFocus(JEvent& e, JObject* arg);
  protected:
    JView *view;
};

#endif
