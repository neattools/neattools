#if !defined( _JRtoIObj_h )
#define _JRtoIObj_h

#include "JRAbsObj.h"

class JRtoIObj : public JRAbsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int outputType(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int ival;
};

#endif
