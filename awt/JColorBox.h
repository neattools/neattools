#if !defined( _JColorBox_h )
#define _JColorBox_h

#include "JMessageBox.h"
#include "JColor.h"
#include "JScroller.h"

class
#include "JAWT.hpp"
JColorBox : public JMessageBox {
  public:
    static int create(JString text, int _style, JColor& c, 
      int x=-1, int y=-1);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual boolean action(JEvent& e, JObject* arg);
    virtual void startup();
    virtual boolean transferArguments();
  protected:
    JScroller *rs, *gs, *bs;
    JCanvas *canvas;
};

#endif
