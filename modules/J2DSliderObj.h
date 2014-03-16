#if !defined( _J2DSliderObj_h )
#define _J2DSliderObj_h

#include "JBtnObj.h"

class J2DSliderObj : public JBtnObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { XINPUT, YINPUT, COLOR, BACKGROUND, 
      XMAX, YMAX, XNEXT, YNEXT, XPREV, YPREV, XMIN, YMIN, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    J2DSliderObj();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual boolean mouseDown(JEvent& e, double x, double y);
    virtual boolean mouseDrag(JEvent& e, double x, double y);
    virtual boolean mouseUp(JEvent& e, double x, double y);
    virtual int inputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean setNValue(int n, int _value);
  protected:
    double fraction[2];
    double factor[2], oldf[2];
    int v[2], pv[2];
    int min[2], max[2], next[2], prev[2];
    boolean isNBits(int n);
    int getMin(int n);
    int getMax(int n);
};

#endif
