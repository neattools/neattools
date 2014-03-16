#if !defined( _JBPosObj_h )
#define _JBPosObj_h

#include "JAbsObj.h"
#include "JBlock.h"

class JBPosObj : public JAbsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBPosObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JBlock v[2];
};

#endif
