#if !defined( _JAddObj_h )
#define _JAddObj_h

#include "JModuleObj.h"

class
#include "JNEAT.hpp"
JAddObj : public JModuleObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JAddObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int value;
};

#endif
