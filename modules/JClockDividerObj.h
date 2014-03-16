#if !defined( _JClockDividerObj_h )
#define _JClockDividerObj_h

#include "JANDObj.h"

class JClockDividerObj : public JANDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_DATA, IN_N, IN_RESET, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JClockDividerObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int N;
    int ivalue, reset;
    void updateN(int _N);
    void updateValue(int _value);
};

#endif
