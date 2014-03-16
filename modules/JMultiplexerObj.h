#if !defined( _JMultiplexerObj_h )
#define _JMultiplexerObj_h

#include "JAddObj.h"

class JMultiplexerObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { IN_N, IN_SELECT, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMultiplexerObj();
    virtual void access(int n, class JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual int inputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int N;
    int select;
    int typeCounter;
    int valueCounter;
    void updateN(int _N);
    void updateSelect(int _select);
};

#endif
