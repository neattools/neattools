#if !defined( _JRDivideObj_h )
#define _JRDivideObj_h

#include "JRAbsObj.h"

class JRDivideObj : public JRAbsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRDivideObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    double v[2];
};

#endif
