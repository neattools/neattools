#if !defined( _JItoBObj_h )
#define _JItoBObj_h

#include "JAddObj.h"

class JItoBObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JItoBObj();
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual void engine(int n, JLinkObj& link);
  protected:
    char b;
};

#endif
