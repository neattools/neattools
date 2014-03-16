#if !defined( _JTNG4Obj_h )
#define _JTNG4Obj_h

#include "JTNG3Obj.h"
#include "JCriticalSection.h"

class JTNG4Obj : public JTNG3Obj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_COM, IN_A1, IN_A2, IN_A3, IN_A4, 
	  IN_B, IN_C, IN_D, IN_BCONFIG, IN_CCONFIG, 
	  IN_DCONFIG, IN_CLOCK, IN_LAST};
    enum { OUT_SYNC, OUT_CLOCK, OUT_COM, OUT_DATA};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JTNG4Obj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual int inputFace(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void engine(int n, JLinkObj& link);
  protected:
    char vi[32];
    int osepCount;
    uchar oseparators[2];
	boolean exclusive;
    JBlock buf;
    JCriticalSection cs;
    int extraInputCount;
    void procCOM(uchar code);
};

#endif
