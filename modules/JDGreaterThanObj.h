#if !defined( _JDGreaterThanObj_h )
#define _JDGreaterThanObj_h

#include "JNOTObj.h"
#include "JDate.h"

class JDGreaterThanObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDGreaterThanObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JDate v[2];
};

#endif
