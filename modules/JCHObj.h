#if !defined( _JCHObj_h )
#define _JCHObj_h

#include "JNOTObj.h"

class JCHObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JCHObj(int _channel = -1);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JString inputTag(int n);
    virtual int inputType(int n);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void addButton(JComponent *panel);
  protected:
    void processByte(int v);
    boolean inverse;
    int channel;
    int separator;
    int factor;
    int counter;
    int sequence;
};

#endif
