#if !defined( _JANDObj_h )
#define _JANDObj_h

#include "JAddObj.h"

class
#include "JNEAT.hpp"
JANDObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JANDObj();
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int NB;
    int mask;
    virtual boolean updateNB(int _NB);
    JString NBTag();
    int matchNB(int v, int n);
    int matchBack(int v, int n);
};

#endif
