#if !defined( _JRandomObj_h )
#define _JRandomObj_h

#include "JNOTObj.h"

class JRandomObj : public JNOTObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRandomObj();
    virtual JString inputTag(int n);
    virtual int inputFace(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, class JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int ivalue;
};

#endif
