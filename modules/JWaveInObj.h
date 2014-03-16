#if !defined( _JWaveInObj_h )
#define _JWaveInObj_h

#include "JWaveOutObj.h"

class JWaveInObj : public JWaveOutObj {
  public:
    static int getNumDevs();
    virtual const char* className() const;
    virtual JObject* clone() const;
    JWaveInObj();
    JWaveInObj(int _wid, int _fid = 0);
    virtual ~JWaveInObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual JString inputTag(int n);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void close();
    virtual void open();
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getDeviceTag();
    virtual boolean dataNotify(JEvent& e, void* data);
    virtual boolean check();
    virtual void addButton(JComponent *panel);
  protected:
    long timeBase;
    JBlock data;
};

#endif
