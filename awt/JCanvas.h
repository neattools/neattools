#if !defined( _JCanvas_h )
#define _JCanvas_h

#include "JComponent.h"

class
#include "JAWT.hpp"
JCanvas : public JComponent {
  public:
    enum { CONCAVE, PLAIN, CONVEX, DEPTH = 2};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JCanvas* create(JComponent *p);
    JCanvas();
    virtual void setText(JString text);
    int getState();
    int getBState();
    int getDepth();
    int getBase();
    int getRatio();
    boolean setState(int _state);
    boolean setBState(int _bool);
    boolean setDepth(int _depth);
    boolean setBaseRatio(int _base, int _ratio);
    void setJInsets(JInsets _setting);
    virtual JInsets insets();
    virtual JDimension preferredSize();
    virtual JDimension minimumSize();
    virtual boolean needRedraw();
    virtual void paint(JGraphics g);
  protected:
    int state;
    int depth;
    int base, ratio;
    JInsets setting;
};

#endif
