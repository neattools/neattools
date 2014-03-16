#if !defined( _JRDelayObj_h )
#define _JRDelayObj_h

#include "JRAbsObj.h"

class JRDelayObj : public JRAbsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRDelayObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    double nvalue;
};

#endif
