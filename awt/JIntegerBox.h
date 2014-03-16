#if !defined( _JIntegerBox_h )
#define _JIntegerBox_h

#include "JInputBox.h"
#include "JScroller.h"

class
#include "JAWT.hpp"
JIntegerBox : public JInputBox {
  public:
    static int create(JString text, 
      int _style, int &value, int min, int max,
      int x=-1, int y=-1);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void startup();
    virtual boolean action(JEvent& e, JObject* arg);
    virtual boolean transferArguments();
  protected:
    JScroller *scroller;
};

#endif
