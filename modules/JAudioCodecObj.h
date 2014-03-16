#if !defined( _JAudioCodecObj_h )
#define _JAudioCodecObj_h

#include "JModuleObj.h"
#include "JG723.h"

class JAudioCodecObj : public JModuleObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JAudioCodecObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int encodeId;
    int encodeType;
    int samplingFactor;
    int bitRate;
    JBlock encode, decode;
    JG723State enc_state, enc_state2;
    JG723State dec_state, dec_state2;
};

#endif
