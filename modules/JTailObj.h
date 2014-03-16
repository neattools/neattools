#if !defined( _JTailObj_h )
#define _JTailObj_h

#include "JAddObj.h"
#include "JFileInputStream.h"

class
JTailObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JTailObj();
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean check();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputFace(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual boolean inputAllowed(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JFileInputStream fis;
    boolean isOpened;
    JString type;
    JString filename;
    JString data;
};

#endif
