#if !defined( _JRCalibrateObj_h )
#define _JRCalibrateObj_h

#include "JANDObj.h"

class JRCalibrateObj : public JANDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { INPUT, CALIBRATE, LOWER, UPPER, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRCalibrateObj();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    double ivalue;
    int feedback;
    double lower, upper;
    double lowerLimit, upperLimit;
    int calibrating;
    int fraction;
    double decalibrate;
    void calculateLimits();
};

#endif
