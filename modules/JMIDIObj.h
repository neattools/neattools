#if !defined( _JMIDIObj_h )
#define _JMIDIObj_h

#include "JANDObj.h"

class JMIDIObj : public JANDObj {
  public:
    enum { MAX_CHANNEL = 16, MAX_NOTE = 128};
    enum { NOTE_FIRST, MIDI=128, 
      CHANNEL, CHANNEL_PRESSURE, PROGRAM, 
      VOLUME, PAN, DAMPER, PITCH, INPUT_LAST};
    static int MAX_PROGRAM;
    static int MAX_DAMPER;
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMIDIObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual JString ioTag(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual void shortMsg(char status, char b1, char b2=null);
    virtual void shortMsg(int midi);
  protected:
    int channel, v[INPUT_LAST];
    char program[MAX_CHANNEL];
    char sw[MAX_CHANNEL][MAX_NOTE];
    char damper[MAX_CHANNEL];
    int volume[MAX_CHANNEL];
    int pan[MAX_CHANNEL];
    int channel_pressure[MAX_CHANNEL];
    int pitch[MAX_CHANNEL];
};

#endif
