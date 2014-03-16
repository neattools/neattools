#if !defined( _JConvertObj_h )
#define _JConvertObj_h

#include "JAddObj.h"
#include "JCriticalSection.h"

class JConvertObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JConvertObj();
    virtual void reset();
    virtual void startup();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JArray data;
    JCriticalSection cs;
};

#endif
