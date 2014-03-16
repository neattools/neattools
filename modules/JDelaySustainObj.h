#if !defined( _JDelaySustainObj_h )
#define _JDelaySustainObj_h

#include "JAddObj.h"
#include "JCriticalSection.h"

class JDelaySustainObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { NONE, DELAY_MODE, SUSTAIN_MODE};
    enum { INPUT, IN_CLOCK, IN_DELAY, IN_SUSTAIN, IN_LAST};
    enum { OUTPUT, OUT_DELAY, OUT_SUSTAIN, OUT_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDelaySustainObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
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
    int iv;
    int delay, sustain, clock;
    int counter, edge, mode;
    JCriticalSection cs;
};

#endif
