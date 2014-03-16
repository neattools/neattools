#if !defined( _JNTLFileObj_h )
#define _JNTLFileObj_h

#include "JAddObj.h"

class JNTLFileObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JNTLFileObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual int inputFace(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean check();
  protected:
    int enabled;
    boolean needSave, valid;
    JString fname, type;
};

#endif
