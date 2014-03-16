#if !defined( _JAvgFilterObj_h )
#define _JAvgFilterObj_h

#include "JAddObj.h"

class JAvgFilterObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JAvgFilterObj();
    virtual void startup();
    virtual boolean inputAllowed(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int N, sum;
    int head, tail;
    JBlock buf;
    int* data;
    void initialize();
};

#endif
