#if !defined( _JKeyboardObj_h )
#define _JKeyboardObj_h

#include "JNOTObj.h"

class JKeyboardObj : public JNOTObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JKeyboardObj(int id = 0);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual void engine(int, JLinkObj& link);
    virtual boolean globalKeyDown(JEvent& e, int key);
    virtual boolean globalKeyUp(JEvent& e, int key);
    virtual void addButton(JComponent *panel);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int state;
    int id;
    int jKey, vKey;
    boolean needShift;
    JString name;
};

#endif
