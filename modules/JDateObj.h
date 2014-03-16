#if !defined( _JDateObj_h )
#define _JDateObj_h

#include "JLabelObj.h"
#include "JDate.h"

class JDateObj : public JLabelObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { DATA, MILLIS, SECONDS, MINUTES, HOURS, DATE, MONTH, YEAR,
      IN_COLOR, IN_BKGND, IN_EDITFOCUS, IN_STRING, IN_LAST};
    enum { WDAY = YEAR+1, YDAY, DST, WEEK_TAG, MONTH_TAG, 
      OUT_NEXTFOCUS, OUT_ENTER, OUT_ESCAPE, OUT_STRING, OUT_LAST};
    enum {
      DATE_MASK = 1,
      TIME_MASK = 2,
      YEAR_MASK = 4,
      SECONDS_MASK = 8,
      WEEK_MASK = 16,
      MILLIS_MASK = 32
    };
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDateObj();
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean setDValue(JDate _date);
    virtual boolean setLabel(JString _label);
  protected:
    int v[OUT_NEXTFOCUS];
    int ov[OUT_NEXTFOCUS];
    int mode;
    JDate date;
    void updateValue();
    JString getText();
    void changeMode(int mask, boolean status);
    virtual JString getEditSet();
    virtual void processCtrlKeys(int key);
};

#endif
