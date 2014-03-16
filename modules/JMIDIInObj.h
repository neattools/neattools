#if !defined( _JMIDIInObj_h )
#define _JMIDIInObj_h

#include "JMIDIOutObj.h"

class JMIDIInObj : public JMIDIOutObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static int getNumDevs();
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMIDIInObj(int _id);
    ~JMIDIInObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean inputAllowed(int n);
    virtual JFRect inputArea(int n);
    virtual int inputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void close();
    virtual void open();
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getDeviceTag();
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean dataNotify(JEvent& e, void* data);
    virtual boolean auxNotify(JEvent& e, void* data);
    virtual boolean check();
    virtual void addButton(JComponent *panel);
    boolean miscEvent;
    boolean ctrlEvent;
  protected:
    int blockSize;
    JBlock data;
};

#endif
