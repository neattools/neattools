#if !defined( _JLEDObj_h )
#define _JLEDObj_h

#include "JModuleObj.h"

class JLEDObj : public JModuleObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JLEDObj(JColor _color = JColor::red);
    JLEDObj(JColor _color, JColor _bkgnd);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual int inputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    void processColor(int n, JLinkObj& link, int delta=0);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean setValue(int _value);
  protected:
    int value;
    boolean valid;
    JColor color, bkgnd;
};

#endif
