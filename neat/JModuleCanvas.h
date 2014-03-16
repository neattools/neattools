#if !defined( _JModuleCanvas_h )
#define _JModuleCanvas_h

#include "JCanvas.h"
#include "JModuleObj.h"

class
#include "JNEAT.hpp"
JModuleCanvas : public JCanvas {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JModuleCanvas* create(JComponent* p, JModuleObj* obj);
    JModuleCanvas();
    virtual void startup();
    virtual void paint(JGraphics g);
    JModuleObj *pmodule;
};

#endif
