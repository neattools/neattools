#if !defined( _JOxfordObj_h )
#define _JOxfordObj_h

#include "JANDObj.h"

class JOxfordObj : public JANDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JOxfordObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect outputArea(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    void processByte(int v);
    int v[8];
    int last;
    int factor;
    int syncCount;
    int sequence;
    int channel;
    static int separator;
};

#endif
