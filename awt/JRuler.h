#if !defined( _JRuler_h )
#define _JRuler_h

#include "JCanvas.h"
#include "JImage.h"

class
#include "JAWT.hpp"
JRuler : public JCanvas {
  public:
    enum { HORIZONTAL, VERTICAL, CORNER};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JRuler* create(JComponent *p, int _type);
    JRuler();
    virtual boolean mouseEnter(JEvent& e, int x, int y);
    virtual boolean mouseExit(JEvent& e, int x, int y);
    virtual void paint(JGraphics g);
    int getType();
    boolean setType(int _type);
    int getValue();
    double getDelta();
    boolean setValue(int _value);
    boolean setValue(int _value, int _section,
      int _minimum, int _maximum, int _dpi, 
      double _scale, boolean frepaint);
    boolean isMouseInside();
  protected:
    boolean mouseInside;
    int type;
    int value;    /* Current Value */
    int section;  /* Current Visible Section */
    int minimum;  /* Minimum Value */
    int maximum;  /* Maximum Value */
    double scale, dscale;
    double delta, vscale;
    int dpi;
    void checkValue();
};

#endif
