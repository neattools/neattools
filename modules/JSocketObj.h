#if !defined( _JSocketObj_h )
#define _JSocketObj_h

#include "JAddObj.h"
#include "JSocket.h"
#include "JSocketInputStream.h"
#include "JSocketOutputStream.h"
#include "JThread.h"
#include "JCriticalSection.h"

class JSocketObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JSocketObj();
    JSocketObj(const JSocketObj& obj);
    virtual ~JSocketObj();
    virtual void reset();
    virtual void open();
    virtual void close();
    virtual void openSocket();
    virtual boolean connectSocket();
    virtual void closeSocket();
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual void run();
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    void processInputStream();
    void updateN(int nN, boolean redraw);
    int isConnected();
    void setConnected(int v);
    void incConnected();
  protected:
    JSocket socket;
    JSocketInputStream sis;
    JSocketOutputStream sos;
    JString address;
    int port, N, enabled;
    uchar ssequence;
    uchar rsequence;
    boolean connected;
    JThread thread;
    JArray data;
    JCriticalSection cs;
};

#endif
