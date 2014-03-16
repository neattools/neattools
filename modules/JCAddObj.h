#if !defined( _JCAddObj_h )
#define _JCAddObj_h

#include "JModuleObj.h"
#include "bcomplex.h"

class JCAddObj : public JModuleObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JCAddObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    jcomplex value;
};

#endif
