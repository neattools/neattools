#include "JMIDIFileObj.h"
#include "JWaveOutObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JRealData.h"
#include "JMIDIData.h"
#include "JSystem.h"
#include "JStringProperty.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JIOException.h"
#include "JEOFException.h"
#include "JMath.h"

class JMIDITrack : public JObject {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMIDITrack();
    JMIDITrack(JString _name);
    JMIDITrack(JBlock _buf);
    JString name;
    short channel;
    short bank;
    short program;
    short volume;
    short pan;
    short reverb;
    short chorus;
    JBlock buf;
};

#define TRACK(x) ((JMIDITrack*)x)
const char* JMIDITrack::className() const { return "JMIDITrack";}
JObject* JMIDITrack::clone() const { return new JMIDITrack(*this);}

JMIDITrack::JMIDITrack() {
  channel = bank = program = reverb = chorus = 0;
  volume = pan = 64;
}

JMIDITrack::JMIDITrack(JString _name) {
  channel = bank = program = reverb = chorus = 0;
  volume = pan = 64;
  name = _name;
}

JMIDITrack::JMIDITrack(JBlock _buf) {
  channel = bank = program = reverb = chorus = 0;
  volume = pan = 64;
  buf = _buf;
}

char* theJMIDIFileObj = JMIDIFileObj().Register();
const char* JMIDIFileObj::className() const { return "JMIDIFileObj";}
JObject* JMIDIFileObj::clone() const { return new JMIDIFileObj(*this);}

JMIDIFileObj::JMIDIFileObj() { 
  nTrack = 1;
  updateN(nTrack, false);
  id = -1;
  ticksPerQuarterNote = 0;
  isRMID = false;
  type = "*.mid";
  filename = composit(prefix, sequence);
  tempo = 12000;
}

/* Required by GCC */
JMIDIFileObj::JMIDIFileObj(const JMIDIFileObj& obj) { *this=obj;}
JMIDIFileObj::~JMIDIFileObj() { 
  close();
}

int getInt(JInputStream& is) {
  int val;
  uchar *ptr = (uchar*)&val;
  is >> JBlock(val);
  return (ptr[0]<<24)+(ptr[1]<<16)+(ptr[2]<<8)+ptr[3];
}

short getShort(JInputStream& is) {
  short val;
  uchar *ptr = (uchar*)&val;
  is >> JBlock(val);
  return (ptr[0]<<8)+ptr[1];
}

void putInt(JOutputStream& os, int val) {
  int ov;
  uchar *ptr = (uchar*)&ov;
  ptr[3] = val & 0xFF;
  ptr[2] = (val>>8) & 0xFF;
  ptr[1] = (val>>16) & 0xFF;
  ptr[0] = (val>>24) & 0xFF;
  os << JBlock(ov);
}

void putShort(JOutputStream& os, short val) {
  short ov;
  uchar *ptr = (uchar*)&ov;
  ptr[1] = val & 0xFF;
  ptr[0] = (val>>8) & 0xFF;
  os << JBlock(ov);
}

int JMIDIFileObj::getNextEvent(JBlock& buf, int track, 
  uchar& status, int& pos, int& dt) {
  if (pos >= buf.size()) return -1;
  int result = null;
  uchar b, n;
  uchar* d = (uchar*)&result;
  uchar* ptr = (uchar*)(char*)buf;
  dt = 0;
  do {
    b = ptr[pos++];
    dt = (dt<<7)+(b&0x7F);
  } while (b&0x80);
  b = ptr[pos++];
  if (b == 0xFF) {
    b = ptr[pos++];
    n = ptr[pos++];
    switch (b) {
      case 0x0: { // Sequence Number
	break;
      }
      case 0x01: { // Text
	break;
      }
      case 0x02: { // CopyRight
        break;
      }
      case 0x03: { // Track Name
	TRACK(data[track])->name = 
	  JString(JBlock(n, (char*)(ptr+pos)));
	break;
      }
      case 0x04: { // Instrument Name
	break;
      }
      case 0x20: { // MIDI Channel
	break;
      }
      case 0x21: { // MIDI Port
	break;
      }
      case 0x2F: { // End Of Track
	result = -1;
	break;
      }
      case 0x51: { // Set Tempo
        usPerQuarterNote = (ptr[pos]<<16)+(ptr[pos+1]<<8)+ptr[pos+2];
	setTempo();
	break;
      }
      case 0x58: { // Time Signature
	clicksPerMeasure = ptr[pos];
	clicksPerWholeNote = JMath::ipow(2, ptr[pos+1]);
	ticksPerClick = ptr[pos+2];
	break;
      }
      case 0x59: { // Key Signature
	char* keyTag[] = { 
	  "bC", "bG", "bD", "bA", "bE", "bB" , "F", 
	  "C", "G", "D", "A", "E", "B", "#F", "#C"};
	keySignature = JString(keyTag[uchar(ptr[pos]+7)])+" "+
	  ((ptr[pos+1]) ? "minor" : "major");
	break;
      }
      case 0x7F: { // Proprietary Event
	break;
      }
    }
    pos+=n;
  } else if (b == 0xF0) { // SYSEX
    n = ptr[pos++];
    pos+=n;
  } else if (b == 0xF7) { // SYSEX CONTINUATION
    n = ptr[pos++];
    if (n < 0xF1) pos+=n;
  } else {
    if (!(b&0x80)) {
      d[0] = b = status;
      pos--;
    } else status = d[0] = b;
    switch (b>>4) {
      case 0xF:
        break;
      case 0xC:
      case 0xD:
        d[1] = ptr[pos++];
        break;
      default:
        d[1] = ptr[pos++];
        d[2] = ptr[pos++];
    }
  }
  return result;
}

boolean JMIDIFileObj::check(boolean redraw) {
  id = -1;
  nTrack = 1;
  ticksPerQuarterNote = 0;
  count = total = 0;
#if defined(WIN32)
  try {
    fis.open(filename);
    bis.connect(fis);
    uchar status;
    int i, size, tSize;
    int p, dt, val;
    uchar *msg = (uchar*)&val;
    JBlock track;
    JBlock tag(4, 0);
    if (isRMID) {
      fis >> tag;
      if (JString(tag) != JString("RIFF")) goto ENDCHECK;
      fis >> JBlock(size);
      fis >> tag;
      if (JString(tag) != JString("RMID")) goto ENDCHECK;
      for (;;) {
        fis >> tag;
        fis >> JBlock(size);
        if (JString(tag) == JString("data")) break;
        fis.move(total);
      }
    }
    fis >> tag;
    if (JString(tag) != JString("MThd")) goto ENDCHECK;
    size = getInt(fis);
    id = getShort(fis);
    nTrack = getShort(fis);
    ticksPerQuarterNote = getShort(fis);
    clicksPerMeasure = 4;
    clicksPerWholeNote = 4;
    ticksPerClick = ticksPerQuarterNote;
    usPerQuarterNote = 500000;
    setTempo();
    updateN(nTrack, true);
    for (i=0; i<nTrack; i++) {
      fis >> tag;
      if (JString(tag) != JString("MTrk")) {
	id = -1;
	goto ENDCHECK;
      }
      tSize = getInt(fis);
      track = JBlock(tSize, 0);
      fis >> track;
      data.set(i, JMIDITrack(track));
      p = size = 0;
      while (p < tSize) {
        val = getNextEvent(track, i, status, p, dt);
        size+=dt;
	if (!size) {
	  switch (msg[0] >> 4) {
	    case 0xC:
	      TRACK(data[i])->channel = msg[0]&0xF;
	      TRACK(data[i])->program = msg[1];
	      break;
	    case 0xB:
	      switch (msg[1]) {
	        case 0: 
	          TRACK(data[i])->bank = msg[2];
		  break;
	        case 7: 
	          TRACK(data[i])->volume = msg[2];
		  break;
	        case 10: 
	          TRACK(data[i])->pan = msg[2];
		  break;
	        case 91: 
	          TRACK(data[i])->reverb = msg[2];
		  break;
	        case 93: 
	          TRACK(data[i])->chorus = msg[2];
		  break;
	      }
	      break;
	  }
	}
      }
      if (size > total) total = size;
    }
    if (id == 1)
      TRACK(data[0])->name = "*Tempo*";
    broadcast(COUNT);
    broadcast(TOTAL);
  } catch (JIOException* e) {
    id = -1;
    nTrack = 1;
    delete e;
  }
ENDCHECK:
  closeHandle();
#endif
  if (id == -1) {
    updateN(nTrack, redraw);
    return false;
  }
  return true;
}

boolean JMIDIFileObj::writeHeader(int _id) {
  id = _id;
#if defined(WIN32)
  try {
    int size = 6;
    fos << JBlock(4, "MThd");
    putInt(fos, 6);
    putShort(fos, id);
    /*
    fos << JBlock(4, "WAVE");
    fos << JBlock(4, "fmt ");
    fos << JBlock(fmtSize);
    fos << JBlock(fmtSize, (char*)&wfx);
    fos << JBlock(4, "data");
    fos << JBlock(dataSize);
    */
  } catch (JIOException* e) {
    delete e;
    id = -1;
    repaint();
    return false;
  }
#endif
  return true;
}

void JMIDIFileObj::record() {
  /*
  cs.lock();
  if (recording) {
    cs.unlock();
    return;
  }
  close();
  id = -1;
  count = 0;
  try {
    fos.open(filename);
    if (isRMID) { // RMID
    }
    bos.connect(fos);
    recording = true;
  } catch (JIOException* e) {
    delete e;
    close();
  }
  repaint();
  cs.unlock();
  */
}

void JMIDIFileObj::play() {
  if (playing) return;
  close();
  playing = true;
  thread = JThread(this);
  thread.start();
  thread.setPriority(JThread::TMAX_PRIORITY);
  repaint();
  /*
  cs.lock();
  if (playing) {
    cs.unlock();
    return;
  }
  close();
  try {
    if (check(true)) {
      fis.open(filename);
      fis.seek(pos);
      bis.connect(fis);
      playing = true;
      thread = JThread(*(JRunnable*)this);
      thread.start();
      thread.setPriority(JThread::TMAX_PRIORITY);
    }
  } catch (JIOException* e) {
    delete e;
    close();
  }
  repaint();
  cs.unlock();
  */
}

void JMIDIFileObj::close() {

  if (playing) {
    playing = false;
    repaint();
  }
  /*
  cs.lock();
  if (recording) {
    recording = false;
    try {
      bos.flush();
      if (isRMID) {
      }
      fos.seek(4);
      fos << JBlock(size+=dataSize);
      fos.seek(pos-4);
      fos << JBlock(dataSize);
      bos.close();
    } catch (JIOException* e) {
      delete e;
    }
    repaint();
  }
  if (playing) {
    playing = false;
    closeHandle();
    repaint();
  }
  cs.unlock();
  */
}

void JMIDIFileObj::access(int n, JLinkObj& link, const JDataType& data) {
  switch (n) {
    case COUNT: 
      INT(data) = count;
      break;
    case TOTAL: 
      INT(data) = total;
      break;
    case TEMPO: 
      INT(data) = tempo;
      break;
    default:
      INT(data) = value;
  }
}

int JMIDIFileObj::inputType(int n)
{ return (n >= IN_BLOCK) ? JMIDIData::id : JRecorderObj::inputType(n);}
int JMIDIFileObj::outputType(int n)
{ return (n >= OUT_BLOCK) ? JMIDIData::id : JRecorderObj::outputType(n);}

JString JMIDIFileObj::inputTag(int n) {
  if (n >= IN_BLOCK+N) return "";
  if (n > IN_BLOCK) return TRACK(data[n-IN_BLOCK])->name;
  if (n == IN_BLOCK) return "Mixed";
  return JRecorderObj::inputTag(n);
}

JString JMIDIFileObj::outputTag(int n) {
  if (n >= OUT_BLOCK+N) return "";
  if (n > OUT_BLOCK) return TRACK(data[n-OUT_BLOCK])->name;
  if (n == OUT_BLOCK) return "Mixed";
  if (n == TEMPO) return "tempo";
  return JRecorderObj::outputTag(n);
}

JFRect JMIDIFileObj::inputArea(int n) { 
  if (n < IN_BLOCK) {
    if (n < IN_LAST) return topArea(n, 0, IN_LAST);
    return JFRect();
  }
  return leftArea(n, IN_BLOCK, N, 0, 1);
}

JFRect JMIDIFileObj::outputArea(int n) { 
  if (n < OUT_BLOCK) {
    if (n < OUT_LAST) return bottomArea(n, 0, OUT_LAST);
    return JFRect();
  }
  return rightArea(n, OUT_BLOCK, N, 0, 1);
}

JFPoint JMIDIFileObj::inputPoint(int n, JLinkObj& link) { 
  if (n < IN_BLOCK) {
    if (n < IN_LAST) return topPoint(n, link, 0, IN_LAST);
    return JFPoint();
  }
  return leftPoint(n, link, IN_BLOCK, N, 0, 1);
}

JFPoint JMIDIFileObj::outputPoint(int n, JLinkObj& link) { 
  if (n < OUT_BLOCK) {
    if (n < OUT_LAST) return bottomPoint(n, link, 0, OUT_LAST);
    return JFPoint();
  }
  return rightPoint(n, link, OUT_BLOCK, N, 0, 1);
}

void JMIDIFileObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dh = h/3;
  int dy = h/12;
  JRect rect1(x, y+dy, w, dh);
  JRect rect2(x, y+h/3, w, dh);
  JRect rect3(x, y+h*2/3-dy, w, dh);
  if (id == -1) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  drawText(g, ((isRMID) ? "RMID" : "MIDI"), rect1);
  drawText(g, "Format", rect2);
  drawText(g, filename, rect3);
}

void JMIDIFileObj::engine(int n, JLinkObj& link) {
  if (!n) {
    /*
    cs.lock();
    if (recording) {
      int nid;
      WAVEHDR *whdr;
      JBlock idata = link.bValue();
      if (idata.size() < sizeof(WAVEHDR)) {
	cs.unlock();
	return;
      }
      idata.Dereference();
      whdr = (WAVEHDR*)(char*)idata;
      whdr->lpData = (LPSTR)(whdr+1);
      nid = max(0, min(JWaveOutObj::_LAST-1, 
        HIWORD(whdr->dwUser)));
      if (id == -1) writeHeader(nid);
      if (nid != id) {
	cs.unlock();
	close();
	return;
      }
      try {
        bos << JBlock(whdr->dwBytesRecorded, whdr->lpData);
	count = (dataSize += whdr->dwBytesRecorded);
	broadcast(COUNT);
	broadcast(TOTAL);
        if (feedback) {
	  data = link.bValue();
	  broadcast(OUT_BLOCK);
        }
	if (whdr->dwUser & JWaveOutObj::TAIL_BLOCK)
	  close();
      } catch (JIOException* e) {
        delete e;
	close();
      }
    }
    cs.unlock();
    */
  } else if (n == PLAYBACK_SCALE) {
    link.access(JRealData(playbackScale));
    playbackScale = max(0.01, min(100, playbackScale));
    if (!playing) usPerQuarterNote = 500000;
    setTempo();
  } else JRecorderObj::engine(n, link);
}

extern void segmentDelay(int interval, int&base, int& counter, boolean& cond);

void JMIDIFileObj::resetDevice() {
  uchar *msg = (uchar*)&value;
  for (int i=0; i<16; i++) {
    value = 0;
    msg[0] = 0xC0+i;
    broadcast(OUT_BLOCK);
    msg[0] = 0xB0+i;
    msg[1] = 121;
    broadcast(OUT_BLOCK);
    msg[1] = 123;
    broadcast(OUT_BLOCK);
  }
}

void JMIDIFileObj::run() {
  int i, delay, counter, base;
  int *p = new int[N];
  int *dt = new int[N];
  int *val = new int[N];
  uchar *status = new uchar[N];
  int delta;
  int start;
  double ms;
REPEAT:
  ms = 0;
  start = base = JSystem::currentTimeMillis();
  count = 0;
  broadcast(COUNT);
  for (i=0; i<N; i++) {
    p[i] = 0;
    dt[i] = 0;
    val[i] = 0;
  }
  while (playing && (count < total)) {
    delta = 0x7FFFFFFF;
    for (i=0; i<N; i++) {
      if (val[i] == -1) continue;
      if (!dt[i])
        val[i] = getNextEvent(
	  TRACK(data[i])->buf, 
	  i, status[i], p[i], dt[i]);
      if (dt[i] < delta) delta = dt[i];
    }
    if (delta) {
      if (pos <= count) {
        ms += msPerTick*delta;
        delay = JMath::round(ms)+start-base;
        segmentDelay(delay, base, counter, playing);
      } else if (pos < count+delta) {
        start = base = JSystem::currentTimeMillis();
        ms = msPerTick*(pos-count);
        delay = JMath::round(ms)+start-base;
        segmentDelay(delay, base, counter, playing);
      }
      count+=delta;
      broadcast(COUNT);
    }
    for (i=0; i<N; i++) {
      if (val[i] == -1) continue;
      dt[i] -= delta;
      if (!dt[i] && val[i]) {
        value = val[i];
	if (pos > count) {
	  uchar *msg = (uchar*)&value;
	  int type = (msg[0] >> 4);
	  if ((type != 0x9) && (type != 0xA)) {
	    broadcast(OUT_BLOCK);
	    if (id && i) broadcast(OUT_BLOCK+i);
	  }
	} else {
	  broadcast(OUT_BLOCK);
          if (id && i) broadcast(OUT_BLOCK+i);
	}
      }
    }
  }
  resetDevice();
  if (playing && repeat && (count >= total))
    goto REPEAT;
  delete p;
  delete dt;
  delete val;
  delete status;
  if (playing) {
    playing = false;
    repaint();
  }
}

JArray JMIDIFileObj::getProperties() {
  JArray properties = JRecorderObj::getProperties();
  if (id != -1) {
    for (int i=0; i<N; i++) {
      JString prefix = JString("track-")+
        JInteger::toJString(i)+" ";
      properties.append(JStringProperty(
        prefix+"Name", TRACK(data[i])->name));
      properties.append(JIntegerProperty(
        prefix+"Channel", TRACK(data[i])->channel, 0, 15));
      properties.append(JIntegerProperty(
        prefix+"Bank", TRACK(data[i])->bank, 0, 127));
      properties.append(JIntegerListProperty(
        prefix+"Program", TRACK(data[i])->program, programTag));
      properties.append(JIntegerProperty(
        prefix+"Volume", TRACK(data[i])->volume, 0, 127));
      properties.append(JIntegerProperty(
        prefix+"Pan", TRACK(data[i])->pan, 0, 127));
      properties.append(JIntegerProperty(
        prefix+"Reverb", TRACK(data[i])->reverb, 0, 127));
      properties.append(JIntegerProperty(
        prefix+"Chorus", TRACK(data[i])->chorus, 0, 127));
    }
  }
  return properties;
}

boolean JMIDIFileObj::updateProperty(JProperty& prop) {
  if (JRecorderObj::updateProperty(prop)) return true;
  boolean changed = false;
  boolean oldREnabled = recordEnabled;
  boolean oldPEnabled = playEnabled;
  close();
  if (prop.getName() == JString("N")) {
    int nN = ((JIntegerProperty*)&prop)->value;
    int oN = N;
    JRecorderObj::updateN(nN, true);
    if (N > oN) {
      for (int i=oN; i<N; i++) {
	data.append(JMIDITrack(JString("track-")+
	  JInteger::toJString(i)));
      }
    } else data.setSize(N);
    changed = true;
  }
  if (oldREnabled) record();
  else if (oldPEnabled) play();
  if (changed) repaint();
  return changed;
}

boolean JMIDIFileObj::updateN(int nN, boolean redraw) {
  boolean result = JRecorderObj::updateN(nN, redraw);
  data = JArray();
  for (int i=0; i<N; i++) {
    data.append(JMIDITrack(JString("track-")+
      JInteger::toJString(i)));
  }
  return result;
}

void JMIDIFileObj::setTempo() {
  int oldTempo = tempo;
  msPerTick = double(usPerQuarterNote)/
    (playbackScale*ticksPerQuarterNote*1000);
  tempo = JMath::round(6.0E9*playbackScale/usPerQuarterNote);
  if (tempo != oldTempo) broadcast(TEMPO);
}

char* JMIDIFileObj::programTag[] = {
  "Acoustic Grand", // PIANO
  "Bright Acoustic",
  "Electric Grand",
  "Honky-Tonk",
  "Electric Piano 1",
  "Electric Piano 2",
  "Harpsichord",
  "Clavinet",		  
  "Celesta",		  // CHROMATIC PERCUSSION
  "Glocknspiel",
  "Music Box",
  "Vibraphone",
  "Marimba",
  "Xylophone",
  "Tubular Bells",
  "Dulcimer",
  "Drawbar Organ",	  // ORGAN
  "Percussive Organ",
  "Rock Organ",
  "Chrch Organ",
  "Reed Organ",
  "Accordian",
  "Harmonica",
  "Tango Accordian",
  "Nylon String Guitar",  // GUITAR
  "Steel String Guitar",
  "Electric Jazz Guitar",
  "Electric Clean Guitar",
  "Electric Muted Guitar",
  "Overdriven Guitar",
  "Distortion Guitar",
  "Guitar Harmonics",
  "Acoustic Bass",	  // BASS
  "Electric Bass(finger)",
  "Electric Bass(pick)",
  "Fretless Bass",
  "Slap Bass 1",
  "Slap Bass2",
  "Synth Bass 1",
  "Synth Bass 2",
  "Violin",		  // SOLO STRINGS
  "Viola",
  "Cello",
  "Contrabass",
  "Tremolo Strings",
  "Pizzicato Strings",
  "Orchestral Strings",
  "Timpani",
  "String Ensemble 1",    // ENSEMBLE
  "String Ensemble 2",
  "Synth Strings 1",
  "Synth Strings 2",
  "Choir Aahs",
  "Voice Oohs",
  "Synth Voice",
  "Orchestra Hit",
  "Trumpet",		  // BRASS
  "Trombone",
  "Tuba",
  "Muted Trumpet",
  "French Horn",
  "Brass Section",
  "Synth Brass 1",
  "Synth Brass 2",
  "Soprano Sax",	  // REED
  "Alto Sax",
  "Tenor Sax",
  "Baritone Sax",
  "Oboe",
  "English Horn",
  "Bassoon",
  "Clarinet",
  "Piccolo",		  // PIPE
  "Flute",
  "Recorder",
  "Pan Flute",
  "Blown Bottle",
  "Shakuhachi",
  "Whistle",
  "Ocarina",
  "Lead 1(Square)",	  // SYNTH LEAD
  "Lead 2(sawtooth)",
  "Lead 3(caliope)",
  "Lead 4(chiff)",
  "Lead 5(charang)",
  "Lead 6(voic)",
  "Lead 7(fifths)",
  "Lead 8(bass+lead)",
  "Pad 1(new age)",	  // SYNTH PAD
  "Pad 2(warm)",
  "Pad 3(polysynth)",
  "Pad 4(choir)",
  "Pad 5(bowed)",
  "Pad 6(metallic)",
  "Pad 7(halo)",
  "Pad 8(sweep)",
  "FX 1(rain)",		  // SYNTH EFFECTS
  "FX 2(soundtrack)",
  "FX 3(crystal)",
  "FX 4(atmosphere)",
  "FX 5(brightness)",
  "FX 6(goblins)",
  "FX 7(echoes)",
  "FX 8(sci-fi)",
  "Sitar",		  // ETHNIC
  "Banjo",
  "Shamisen",
  "Koto",
  "Kalimba",
  "Bagpipe",
  "Fiddle",
  "Shanai",
  "Tinkle Bell",	  // PERCUSSIVE
  "Agogo",
  "Steel Drums",
  "Woodblock",
  "Taiko Drum",
  "Melodic Tom",
  "Synth Drum",
  "Reverse Cymbal",
  "Guitar Fret Noise",	  // SOUND EFFECTS
  "Breath Noise",
  "Seashore",
  "Bird Tweet",
  "Telephone Ring",
  "Helicopter",
  "Applause",
  "Gunshot",
  null
};

