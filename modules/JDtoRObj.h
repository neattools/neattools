#if !defined( _JDtoRObj_h )
#define _JDtoRObj_h

#include "JRAbsObj.h"

class JDtoRObj : public JRAbsObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
};

#endif
