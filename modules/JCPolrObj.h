#if !defined( _JCPolrObj_h )
#define _JCPolrObj_h

#include "JCtoRObj.h"

class JCPolrObj : public JCtoRObj {
  protected:
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString outputTag(int n);
    virtual void engine(int n, JLinkObj& link);
};

#endif
