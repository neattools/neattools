#if !defined( _JRAddObj_h )
#define _JRAddObj_h

#include "JModuleObj.h"

class JRAddObj : public JModuleObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRAddObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    double value;
};

#endif
