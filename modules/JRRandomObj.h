#if !defined( _JRRandomObj_h )
#define _JRRandomObj_h

#include "JRAbsObj.h"

class JRRandomObj : public JRAbsObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRRandomObj();
    virtual JString inputTag(int n);
    virtual int inputType(int n);
    virtual int inputFace(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, class JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int ivalue;
};

#endif
