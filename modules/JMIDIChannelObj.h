#if !defined( _JMIDIChannelObj_h )
#define _JMIDIChannelObj_h

#include "JAddObj.h"

class JMIDIChannelObj : public JAddObj {
  public:
    enum { CH_FIRST, MISC = 16, MIDI};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMIDIChannelObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
  protected:
    int v[18];
};

#endif
