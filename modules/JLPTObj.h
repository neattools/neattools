#if !defined( _JLPTObj_h )
#define _JLPTObj_h

#include "JAddObj.h"
#include "JThread.h"

class JLPTObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { INPUT, ENABLED, SAMPLING, CONTROL, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JLPTObj(int _port = 0);
    boolean isValid();
    virtual void reset();
    virtual void open();
    virtual void close();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void addButton(JComponent *panel);
  protected:
    int id, port, clock, enabled;
    boolean connected;
};

#endif
