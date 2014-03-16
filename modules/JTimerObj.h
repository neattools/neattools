#if !defined( _JTimerObj_h )
#define _JTimerObj_h

#include "JANDObj.h"
#include "JThread.h"
#include "JCriticalSection.h"

class JTimerObj : public JANDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_ENABLED, IN_INTERVAL, IN_LAST};
    enum { OUTPUT, OUT_INTERVAL, OUT_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JTimerObj(int _delay = 1000);
    ~JTimerObj();
    void updateTime();
    virtual void run();
    virtual void startup();
    virtual void reset();
    virtual void open();
    virtual void close();
    virtual boolean inputAllowed(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void addButton(JComponent *panel);
  protected:
    boolean connected;
    int delay, counter, base, enabled, priority;
    JThread thread;
    void setDelay(int _delay);
};

#endif
