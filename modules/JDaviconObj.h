#if !defined( _JDaviconObj_h )
#define _JDaviconObj_h

#include "JANDObj.h"

class JDaviconObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static double EMGFactor;
    static double EMGConstant;
    static double PPGFactor;
    static double PPGConstant;
    static double TRFactor;
    static double TRConstant;
    static double TSFactor;
    static double TSConstant;
    static double SCLFactor;
    static double SCLConstant;
    static double SCRFactor;
    static double SCRConstant;
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDaviconObj();
    ~JDaviconObj();
    virtual void reset();
    virtual void open();
    virtual void close();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual int inputFace(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFRect outputArea(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    boolean valid, connected;
    int enabled;
    int id, port;
    double v[8];
    virtual int sample(int channel);
    virtual boolean check();
};

#endif
