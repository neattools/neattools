#if !defined( _JSSubObj_h )
#define _JSSubObj_h

#include "JSAddObj.h"

class JSSubObj : public JSAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_DATA, IN_BEGIN, IN_END, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSSubObj();
    virtual boolean inputAllowed(int n);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JString str;
    int begin, end;
    void putResult();
};

#endif
