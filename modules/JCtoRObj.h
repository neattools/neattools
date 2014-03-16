#if !defined( _JCtoRObj_h )
#define _JCtoRObj_h

#include "JCAddObj.h"

class JCtoRObj : public JCAddObj {
  protected:
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JCtoRObj();
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual int outputType(int n);
    virtual JString outputTag(int n);
    virtual int outputFace(int n);
    virtual JFRect outputArea(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
  protected:
    double v[2];
};

#endif
