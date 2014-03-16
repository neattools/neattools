#if !defined( _JCOMObj_h )
#define _JCOMObj_h

#include "JAddObj.h"
#include "JThread.h"

class JCOMObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { INPUT, ENABLED, SAMPLING, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JCOMObj(int _port = 1);
    ~JCOMObj();
    virtual void reset();
    virtual void open();
    virtual void close();
    virtual void closeHandle();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access (int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual boolean inputAllowed(int n);
    virtual void engine(int n, JLinkObj& link);
    virtual void run();
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void addButton(JComponent *panel);
  protected:
    int type, port, handle;
    int speed, stopbits, databits, parity;
    int flowControl;
    int bufferSize;
    int enabled, samplingClock;
    boolean connected;
    JBlock data;
    JThread thread;
};

#endif
