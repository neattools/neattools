#include "JMIDIChannelObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JMIDIData.h"

char* theJMIDIChannelObj = JMIDIChannelObj().Register();
const char* JMIDIChannelObj::className() const { return "JMIDIChannelObj";}
JObject* JMIDIChannelObj::clone() const { return new JMIDIChannelObj(*this);}

JMIDIChannelObj::JMIDIChannelObj() {
  igm = ogm = MIDI+1;
  for (int i=0; i<igm; i++) v[i] = 0;
}

void JMIDIChannelObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, "MDCH", rect);
}

int JMIDIChannelObj::inputType(int n) { return JMIDIData::id;}
int JMIDIChannelObj::outputType(int n) { return JMIDIData::id;}
void JMIDIChannelObj::access(int n, JLinkObj& link, const JDataType& data) { INT(data) = v[n];}

boolean JMIDIChannelObj::inputAllowed(int n) { return true;}
boolean JMIDIChannelObj::outputAllowed(int n) { return true;}

JString JMIDIChannelObj::inputTag(int n) {
  if (n == MIDI) return "midi-in";
  else if (n == MISC) return "misc-in";
  return JString("ch")+JInteger::toJString(n)+"-in";
}

JString JMIDIChannelObj::outputTag(int n) {
  if (n == MIDI) return "midi-out";
  else if (n == MISC) return "misc-out";
  return JString("ch")+JInteger::toJString(n)+"-out";
}

JFRect JMIDIChannelObj::inputArea(int n) { 
  if (n == MIDI) return topArea(n, MIDI, 1);
  return leftArea(n, 1, igm-1, 0, 1);
}

JFRect JMIDIChannelObj::outputArea(int n) { 
  if (n == MIDI) return bottomArea(n, MIDI, 1);
  return rightArea(n, 1, ogm-1, 0, 1);
}

int JMIDIChannelObj::inputFace(int n) 
{ return (n == MIDI) ? TOP : LEFT;}

int JMIDIChannelObj::outputFace(int n) 
{ return (n == MIDI) ? BOTTOM : RIGHT;}

JFPoint JMIDIChannelObj::inputPoint(int n, JLinkObj& link) { 
  if (n == MIDI) return topPoint(n, link, MIDI, 1);
  return leftPoint(n, link, 1, igm-1, 0, 1);
}

JFPoint JMIDIChannelObj::outputPoint(int n, JLinkObj& link) { 
  if (n == MIDI) return bottomPoint(n, link, MIDI, 1);
  return rightPoint(n, link, 1, ogm-1, 0, 1);
}

void JMIDIChannelObj::engine(int n, JLinkObj& link) {
  if (n == MIDI) {
    int ivalue ;
    link.access(JIntegerData(ivalue));
    uchar* msg = (uchar*)&ivalue;
    if (msg[0]>>4 == 0xF) {
      v[MISC] = ivalue;
      broadcast(MISC);
    } else {
      int channel = msg[0]%16;
      v[channel] = ivalue;
      broadcast(channel);
    }
  } else if (n == MISC) {
    link.access(JIntegerData(v[MIDI]));
    broadcast(MIDI);
  } else {
    int ivalue;
    link.access(JIntegerData(ivalue));
    uchar* msg = (uchar*)&ivalue;
    if ((msg[0]>>4) < 0xF)
      msg[0] = (msg[0]&0xF0)+n;
    v[MIDI] = ivalue;
    broadcast(MIDI);
  }
}

