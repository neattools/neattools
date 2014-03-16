#if !defined( _JTNGObj_h )
#define _JTNGObj_h

#include "JANDObj.h"

class JTNGObj : public JANDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { MAX_CHANNEL = 32};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JTNGObj();
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
    virtual void processByte(int v);
  protected:
    int v[MAX_CHANNEL+3];
    boolean inv[MAX_CHANNEL];
    int offset;
    int factor;
    int sequence;
    int channel;
    int channelCount;
    static uchar separator;
};

#endif
