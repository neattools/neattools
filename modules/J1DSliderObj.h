#if !defined( _J1DSliderObj_h )
#define _J1DSliderObj_h

#include "JBtnObj.h"

class J1DSliderObj : public JBtnObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { HORIZONTAL, VERTICAL};
    enum { INPUT, COLOR, BACKGROUND, MAX, NEXT, PREV, MIN, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    J1DSliderObj(int _type = HORIZONTAL);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual boolean mouseDown(JEvent& e, double x, double y);
    virtual boolean mouseDrag(JEvent& e, double x, double y);
    virtual boolean mouseUp(JEvent& e, double x, double y);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual int outputFace(int n);
    virtual JFRect outputArea(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual boolean setValue(int _value);
    virtual void addButton(JComponent *panel);
  protected:
    double fraction;
    double factor, oldf;
    int min, max, next, prev;
    boolean isNBits();
    int getMin();
    int getMax();
};

#endif
