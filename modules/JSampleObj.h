#if !defined( _JSampleObj_h )
#define _JSampleObj_h

#include "JAddObj.h"
#include "JArray.h"

class JSampleObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_N, IN_CONTROL, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSampleObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int N;
    int control;
    int typeCounter;
    int valueCounter;
    void updateN(int _N);
};

#endif
