#if !defined( _JNBitsObj_h )
#define _JNBitsObj_h

#include "JLEDObj.h"

class JNBitsObj : public JLEDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JNBitsObj();
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
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
