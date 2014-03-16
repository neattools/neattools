#if !defined( _JRealObj_h )
#define _JRealObj_h

#include "JLabelObj.h"

class JRealObj : public JLabelObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_DATA, IN_COLOR, IN_BKGND, IN_EDITFOCUS, IN_STRING, IN_LAST};
    enum { OUT_DATA, OUT_NEXTFOCUS, OUT_ENTER, OUT_ESCAPE, OUT_STRING, OUT_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRealObj();
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean setRValue(double _rval);
    virtual boolean setLabel(JString _label);
  protected:
    int w, f;
    double rval;
    virtual JString getEditSet();
};

#endif
