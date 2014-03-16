#if !defined( _JAbout_h )
#define _JAbout_h

#include "JCanvas.h"

class
#include "JNEAT.hpp"
JAbout : public JCanvas {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JAbout* create();
	static JAbout* about;
    JAbout();
    virtual void startup();
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean mouseUp(JEvent& e, int x, int y);
    virtual boolean mouseExit(JEvent& e, int x, int y);
    virtual void paint(JGraphics g);
    virtual boolean gotFocus(JEvent& e, JObject* arg);
};

#endif
