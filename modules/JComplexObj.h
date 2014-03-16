#if !defined( _JComplexObj_h )
#define _JComplexObj_h

#include "JAddObj.h"
#include "JString.h"
#include "JCriticalSection.h"

class JComplexObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JComplexObj();
    virtual void startup();
    virtual void calculateJRegion(JRegion& rgn, double dx, double dy, double scale);
    virtual void access(int n, class JLinkObj& link, const JDataType& data);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean inputAllowed(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputAreaNo(JFPoint fpt);
    virtual int outputAreaNo(JFPoint fpt);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, class JLinkObj& link);
    virtual JFPoint outputPoint(int n, class JLinkObj& link);
    virtual JViewObj* locate(double x, double y, JViewObj*& obj);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void addLinks(JViewSet& set, JHashTable& hash);
    boolean checkEmpty();
    JString getPrefix(int i);
  protected:
    int numOfInput;
    int numOfLeftInput;
    int numOfOutput;
    int numOfRightOutput;
    JString name;
    JArray port;
    boolean internalMode;
    JCriticalSection cs;
};

#endif
