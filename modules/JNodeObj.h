#if !defined( _JNodeObj_h )
#define _JNodeObj_h

#include "JAbsObj.h"

class JNodeObj : public JAbsObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JNodeObj();
    virtual void access(int n, class JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual JString outputTag(int n);
    virtual int outputFace(int n);
    virtual JFRect outputArea(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int typeCounter;
    int valueCounter;
    int eventIndicator;
};

#endif
