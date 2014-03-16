#if !defined( _JScroller_h )
#define _JScroller_h

#include "JTriangleButton.h"
#include "JThumb.h"

class
#include "JAWT.hpp"
JScroller : public JCanvas {
  public:
    enum { HORIZONTAL, VERTICAL};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JScroller* create(JComponent *p, int _type);
    JScroller();
    virtual void startup();
    virtual boolean action(JEvent& e, JObject* arg);
    int getType();
    boolean setType(int _type);
    int getValue();
    boolean setValue(int _value);
    boolean setValue(int _value, int _section, 
      int _minimum, int _maximum, boolean frepaint);
    virtual boolean needRedraw();
  protected:
    int type;
    JThumb *thumb;
    JTriangleButton *up, *down;
};

#endif
