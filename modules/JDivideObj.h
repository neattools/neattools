#if !defined( _JDivideObj_h )
#define _JDivideObj_h

#include "JAbsObj.h"

class JDivideObj : public JAbsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDivideObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual boolean inputAllowed(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int v[2];
};

#endif
