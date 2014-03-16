#if !defined( _JStateObj_h )
#define _JStateObj_h

#include "JANDObj.h"
#include "JCriticalSection.h"

class JStateObj : public JANDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { ENABLE, RESET, CONDITIONS};
    enum { STATE, ACTIVATES};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JStateObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
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
  protected:
    JString name;
    int state;
    int N;
    JBlock cond;
    JCriticalSection cs;
    void updateN(int _N);
    void resetBroadcast();
};

#endif
