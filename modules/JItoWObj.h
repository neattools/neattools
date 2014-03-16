#if !defined( _JItoWObj_h )
#define _JItoWObj_h

#include "JAddObj.h"

class JItoWObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JItoWObj();
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int fid;
    JBlock wave;
};

#endif
