#if !defined( _JEncoderObj_h )
#define _JEncoderObj_h

#include "JAddObj.h"

class JEncoderObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JEncoderObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual int inputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int N;
    void updateN(int _N);
};

#endif
