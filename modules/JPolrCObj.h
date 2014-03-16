#if !defined( _JPolrCObj_h )
#define _JPolrCObj_h

#include "JRtoCObj.h"

class JPolrCObj : public JRtoCObj {
  protected:
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
};

#endif
