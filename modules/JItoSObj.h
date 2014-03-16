#if !defined( _JItoSObj_h )
#define _JItoSObj_h

#include "JAddObj.h"

class JItoSObj : public JAddObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JItoSObj();
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual void engine(int n, JLinkObj& link);
  protected:
    char s[2];
};

#endif
