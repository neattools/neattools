#if !defined( _JBInsObj_h )
#define _JBInsObj_h

#include "JBAddObj.h"

class JBInsObj : public JBAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_DATA, IN_SRC, IN_POS, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBInsObj();
    virtual boolean inputAllowed(int n);
    virtual int inputType(int n);
    virtual int inputFace(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JBlock blk;
    JBlock src;
    int pos;
    void putResult();
};

#endif
