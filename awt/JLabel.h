#if !defined( _JLabel_h )
#define _JLabel_h

#include "JCanvas.h"
#include "JRect.h"

class
#include "JAWT.hpp"
JLabel : public JCanvas {
  public:
    enum { LEFT, CENTER, RIGHT, AUTO = CONVEX+1};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JLabel* create(JComponent* p, JString text, boolean password = false);
    static JRect formatText(JGraphics g, JString text, 
      JRect rect, JColor color, JColor bkgnd, 
      int raise = CONVEX, int align = LEFT);
    JLabel();
    int getAlign();
    int getRaise();
    boolean setAlign(int _align);
    boolean setRaise(int _raise);
    boolean setScale(int _scale);
    boolean setScaleTotal(int _scaleTotal);
    void setPasswordMode(boolean mode);
    virtual void paint(JGraphics g);
    virtual boolean needRedraw();
  protected:
    int align;
    int raise;
    int scale;
    int scaleTotal;
    boolean passwordMode;
};

#endif
