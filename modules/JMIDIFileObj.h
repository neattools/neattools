#if !defined( _JMIDIFileObj_h )
#define _JMIDIFileObj_h

#include "JRecorderObj.h"

class JMIDIFileObj : public JRecorderObj {
  public:
    enum { TEMPO = TOTAL+1, OUT_LAST};
    static char* programTag[];
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMIDIFileObj();
    JMIDIFileObj(const JMIDIFileObj& obj);
    ~JMIDIFileObj();
    virtual void record();
    virtual void play();
    virtual void close();
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual void run();
    virtual boolean check(boolean redraw);
    virtual boolean updateN(int nN, boolean redraw);
    virtual boolean writeHeader(int _id);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    short id;
    short nTrack;
    short ticksPerQuarterNote;
    short clicksPerMeasure;
    short clicksPerWholeNote;
    short ticksPerClick;
    boolean isRMID;
    double msPerTick;
    int usPerQuarterNote;
    int tempo;
    JString keySignature;
    JArray data;
    int getNextEvent(JBlock& data, int track, 
      uchar& status, int& pos, int& dt);
    void resetDevice();
    void setTempo();
};

#endif
