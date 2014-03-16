#if !defined( _JBDelObj_h )
#define _JBDelObj_h

#include "JBAddObj.h"

class JBDelObj : public JBAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_DATA, IN_FROM, IN_TO, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JBDelObj();
    virtual boolean inputAllowed(int n);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    JBlock block;
    int from, to;
    void putResult();
};

#endif
