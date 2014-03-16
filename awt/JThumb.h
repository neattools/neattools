#if !defined( _JThumb_h )
#define _JThumb_h

#include "JPushButton.h"

class
#include "JAWT.hpp"
JThumb : public JPushButton {
  public:
    enum { HORIZONTAL, VERTICAL};
    enum { THUMB, PAGE_DOWN, PAGE_UP};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JThumb* create(JComponent *p);
    JThumb();
    int getType();
    boolean setType(int _type);
    int getValue();
    boolean setValue(int _value);
    boolean setValue(int _value, int _section,
      int _minimum, int _maximum, boolean frepaint);
    void moveThumb(int delta);
    virtual void paint(JGraphics g);
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
    virtual boolean mouseDrag(JEvent& e, int x, int y);
  protected:
    int type;	  /* HORIZONAL/VERTICAL */
    int value;    /* Current Value */
    int section;  /* Current Visible Section */
    int minimum;  /* Minimum Value */
    int maximum;  /* Maximum Value */
    int range;    /* Maximum-Minimum */
    int area;     /* Current Pressed Area */
    int offset;   /* Thumb Offset */
    int length;   /* Thumb Length */
    int mofs;     /* Mouse pressed Offset */
    void checkValue();
    boolean setThumb();
};

#endif
