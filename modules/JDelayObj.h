#if !defined( _JDelayObj_h )
#define _JDelayObj_h

#include "JAbsObj.h"

class JDelayObj : public JAbsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDelayObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int nvalue;
};

#endif
