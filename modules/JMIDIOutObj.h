#if !defined( _JMIDIOutObj_h )
#define _JMIDIOutObj_h

#include "JAddObj.h"
#include "JCriticalSection.h"

class JMIDIOutObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static int getNumDevs();
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMIDIOutObj();
    JMIDIOutObj(int _id);
    ~JMIDIOutObj();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual boolean inputAllowed(int n);
    virtual void reset();
    virtual void close();
    virtual void open();
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getDeviceTag();
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean check();
    virtual void addButton(JComponent *panel);
  protected:
    int id, mid;
    int handle, enabled;
    boolean valid;
    boolean connected;
    boolean hasPatchCaching;
    JString name;
    JCriticalSection cs;
};

#endif
