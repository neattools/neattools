#include "JMIDIObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JMIDIData.h"
#include <memory.h>

char* theJMIDIObj = JMIDIObj().Register();
int JMIDIObj::MAX_PROGRAM = 127;
int JMIDIObj::MAX_DAMPER = 1;

const char* JMIDIObj::className() const { return "JMIDIObj";}
JObject* JMIDIObj::clone() const { return new JMIDIObj(*this);}

JMIDIObj::JMIDIObj() { 
  igm = INPUT_LAST;
  ogm = INPUT_LAST;
  channel = 0;
  int midValue = matchNB(0x8000, 16);
  for (int i=0; i<MAX_CHANNEL; i++) {
    program[i] = 0;
    volume[i] = 64;
    pan[i] = 64;
    damper[i] = 0;
    channel_pressure[i] = 64;
    pitch[i] = 16384;
    program[i] = 0;
    memset(sw[i], 0, MAX_NOTE);
  }
  memset(v, 0, INPUT_LAST*sizeof(int));
  v[VOLUME] = 64;
  v[PAN] = 64;
  v[PITCH] = 16384;
}

void JMIDIObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, "MIDI", rect);
}

char* drumTag[] = {
  "Acoustic Bass Drum",
  "Bass Drum 1",
  "Side Stick",
  "Acoustic Snare",
  "Hand Clap",
  "Electric Snare",
  "Low Floor Tom",
  "Closed Hi-Hat",
  "High Floor Tom",
  "Pedal Hi-Hat",
  "Low Tom",
  "Open Hi-Hat",
  "Low-Mid Tom",
  "Hi-Mid Tom",
  "Crash Cymbal 1",
  "High Tom",
  "Ride Cymbal 1",
  "Chinese Cymbal",
  "Ride Bell",
  "Tambourine",
  "Splash Cymbal",
  "Cowbell",
  "Crash Cymbal 2",
  "Vibraslap",
  "Ride Cymbal 2",
  "Hi Bongo",
  "Low Bongo",
  "Mute Hi Conga",
  "Open Hi Conga",
  "Low Conga",
  "High Timbale",
  "Low Timbale",
  "High Agogo",
  "Low Agogo",
  "Cabasa",
  "Maracas",
  "Short Whistle",
  "Long Whistle",
  "Short Guiro",
  "Long Guiro",
  "Claves",
  "Hi Wood Block",
  "Low Wood Block",
  "Mute Cuica",
  "Open Cuica",
  "Mute Triangle",
  "Open Triangle"
};

JString JMIDIObj::ioTag(int n) {
  if (n < MIDI) {
    if (channel != 9) {
      char* ntag[] = {"C", "C#", "D", "D#", "E", "F",
        "F#", "G", "G#", "A", "A#", "B"};
      return JString("Octave[")+
        JInteger::toJString(n/12)+
        "]"+ntag[n%12]+"-Note#"+
        JInteger::toJString(n)+NBTag();
    } else {
      if ((34 < n) && (n < 82))
        return JString(drumTag[n-35])+"-Note#"+
          JInteger::toJString(n)+NBTag();
      return JString("Note#")+
	JInteger::toJString(n)+NBTag();
    }
  }
  char* tag[] = { "midi", "channel(0-15)", "channel_pressure",
    "program(0-127)", "volume", "pan", "damper", "pitch"};
  if ((n == MIDI) || (n == CHANNEL) || (n == PROGRAM))
    return JString(tag[n-MIDI]);
  return JString(tag[n-MIDI])+NBTag();
}

JString JMIDIObj::inputTag(int n) { return ioTag(n)+"-in";}
JString JMIDIObj::outputTag(int n) { return ioTag(n)+"-out";}

int JMIDIObj::inputType(int n) 
{ return (n == MIDI) ? JMIDIData::id : JIntegerData::id;}
int JMIDIObj::outputType(int n) 
{ return (n == MIDI) ? JMIDIData::id : JIntegerData::id;}
void JMIDIObj::access(int n, JLinkObj& link, const JDataType& data) { 
  switch (n) {
    case MIDI:
    case CHANNEL:
    case PROGRAM:
      INT(data) = v[n];
      break;
    case PITCH:
      INT(data) = matchNB(v[n], 14);
      break;
    default:
      INT(data) = matchNB(v[n], 7);
      break;
  }
}

boolean JMIDIObj::inputAllowed(int n) { return true;}
boolean JMIDIObj::outputAllowed(int n) { return true;}

JFRect JMIDIObj::inputArea(int n) {
  if (n == MIDI) return topArea(n, MIDI, 1);
  if (n > MIDI) return leftArea(n, 1, INPUT_LAST, 0, 1);
  return leftArea(n, 0, INPUT_LAST, 0, 1);
}

JFRect JMIDIObj::outputArea(int n) {
  if (n == MIDI) return bottomArea(n, MIDI, 1);
  if (n > MIDI) return rightArea(n, 1, INPUT_LAST, 0, 1);
  return rightArea(n, 0, INPUT_LAST, 0, 1);
}

int JMIDIObj::inputFace(int n) 
{ return (n == MIDI) ? TOP : LEFT;}

int JMIDIObj::outputFace(int n) 
{ return (n == MIDI) ? BOTTOM : RIGHT;}

JFPoint JMIDIObj::inputPoint(int n, JLinkObj& link) { 
  if (n == MIDI) return topPoint(n, link, MIDI, 1);
  if (n > MIDI) return leftPoint(n, link, 1, INPUT_LAST, 0, 1);
  return leftPoint(n, link, 0, INPUT_LAST, 0, 1);
}

JFPoint JMIDIObj::outputPoint(int n, JLinkObj& link) { 
  if (n == MIDI) return bottomPoint(n, link, MIDI, 1);
  if (n > MIDI) return rightPoint(n, link, 1, INPUT_LAST, 0, 1);
  return rightPoint(n, link, 0, INPUT_LAST, 0, 1);
}

void JMIDIObj::shortMsg(char status, char b1, char b2) {
  char msg[4] = { status, b1, b2, 0};
  v[MIDI] = *(int*)msg;
  broadcast(MIDI);
}

void JMIDIObj::shortMsg(int midi) {
  uchar* msg = (uchar*)&midi;
  int type = msg[0]/16;
  int n = msg[0]%16;
  char b1 = msg[1];
  char b2 = msg[2];
  if (n != v[CHANNEL]) {
    v[CHANNEL] = n;
    broadcast(CHANNEL);
  }
  switch (type) {
    case 0x8: // NOTE_OFF
      v[b1] = 0;
      broadcast(b1);
      break;
    case 0x9: // NOTE_ON
      v[b1] = b2;
      broadcast(b1);
      break;
    case 0xA: // NOTE_PRESSURE
      v[b1] = b2;
      broadcast(b1);
      break;
    case 0xB: // CONTROL
      switch (b1) {
        case 7 : // VOLUME
	  v[VOLUME] = b2;
	  broadcast(VOLUME);
	  break;
	case 10: // PAN
	  v[PAN] = b2;
	  broadcast(PAN);
	  break;
	case 64: // DAMPER
	  v[DAMPER] = (b2 != 0) ? 127 : 0;
	  broadcast(DAMPER);
	  break;
      }
      break;
    case 0xC: // PROGRAM
      v[PROGRAM] = b1;
      broadcast(PROGRAM);
      break;
    case 0xD: // CHANNEL_PRESSURE
      v[CHANNEL_PRESSURE] = b1;
      broadcast(CHANNEL_PRESSURE);
      break;
    case 0xE: // PITCH
      v[PITCH] = b1+(b2<<7);
      broadcast(PITCH);
      break;
  }
}

void JMIDIObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case MIDI: {
      int iv;
      link.access(JIntegerData(iv));
      shortMsg(iv);
      break;
    }
    case CHANNEL: {
      link.access(JIntegerData(channel));
      channel = min(max(channel, 0), MAX_CHANNEL-1);
      break;
    }
    case PROGRAM: {
      int oldprog = program[channel];
      int newprog;
      link.access(JIntegerData(newprog));
      newprog = min(max(newprog, 0), MAX_PROGRAM);
      if (newprog != oldprog) {
	shortMsg((char)(0xC0+channel),
	  program[channel] = (char)newprog);
      }
      break;
    }
    case VOLUME: {
      int oldvol = volume[channel];
      int newvol;
      link.access(JIntegerData(newvol));
      newvol = matchBack(newvol & mask, 7);
      if (newvol != oldvol) {
	volume[channel] = newvol;
	shortMsg((char)(0xB0+channel),
	  7, (char)newvol);
      }
      break;
    }
    case PAN: {
      int oldpan = pan[channel];
      int newpan;
      link.access(JIntegerData(newpan));
      newpan = matchBack(newpan & mask, 7);
      if (newpan != oldpan) {
	pan[channel] = newpan;
	shortMsg((char)(0xB0+channel),
	  10, (char)newpan);
      }
      break;
    }
    case DAMPER: {
      int olddam = damper[channel];
      int newdam;
      link.access(JIntegerData(newdam));
      newdam = (newdam != 0);
      if (newdam != olddam) {
	damper[channel] = (char)newdam;
	shortMsg((char)(0xB0+channel),
	  64, (char)(newdam*127));
      }
      break;
    }
    case CHANNEL_PRESSURE: {
      int oldcp = channel_pressure[channel];
      int newcp;
      link.access(JIntegerData(newcp));
      newcp = matchBack(newcp & mask, 7);
      if (newcp != oldcp) {
	if (newcp == 0) newcp = 1;
	channel_pressure[channel] = newcp;
	shortMsg((char)(0xD0+channel), (char)newcp);
      }
      break;
    }
    case PITCH: {
      int oldpitch = pitch[channel];
      int newpitch;
      link.access(JIntegerData(newpitch));
      newpitch = matchBack(newpitch & mask, 14);
      if (newpitch != oldpitch) {
	if (newpitch == 0) newpitch = 1;
	pitch[channel] = newpitch;
	shortMsg((char)(0xE0+channel),
	  (char)(newpitch & 0x7F), (char)(newpitch >> 7));
      }
      break;
    }
    default: {
      char oldsw = sw[channel][n];
      int newsw;
      link.access(JIntegerData(newsw));
      newsw = matchBack(newsw & mask, 7);
      if (newsw != oldsw) {
	sw[channel][n] = (char)newsw;
	if (oldsw > 0) {
	  if (newsw > 0) // NOTE_PRESSURE
	    shortMsg((char)(0xA0+channel),
	      (char)n, newsw);
	  else  // NOTE_OFF
	    shortMsg((char)(0x80+channel),
	      (char)n, oldsw);
	} else { // NOTE_ON
	  shortMsg((char)(0x90+channel),
	    (char)n, newsw);
	}
      }
    }
  }
}

