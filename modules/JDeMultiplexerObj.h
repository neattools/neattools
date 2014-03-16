#if !defined( _JDeMultiplexerObj_h )
#define _JDeMultiplexerObj_h

#include "JAddObj.h"

class JDeMultiplexerObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_INPUT, IN_N, IN_SELECT, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDeMultiplexerObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int N;
    int select;
    int typeCounter;
    int valueCounter;
    boolean sendResetEvent;
    void updateN(int _N);
    void updateSelect(int _select);
};

#endif
