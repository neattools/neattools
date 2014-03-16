#if !defined( _JWtoIObj_h )
#define _JWtoIObj_h

#include "JAddObj.h"

class JWtoIObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JWtoIObj();
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual JString outputTag(int n);
    virtual JFRect outputArea(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int right;
    int samplingFactor;
};

#endif
