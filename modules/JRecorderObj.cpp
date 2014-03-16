#include "JRecorderObj.h"
#include "JConvertObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JDouble.h"
#include "JIntegerData.h"
#include "JRealData.h"
#include "JBlockData.h"
#include "JStringData.h"
#include "JSystem.h"
#include "JFile.h"
#include "JMath.h"
#include "JFileProperty.h"
#include "JDoubleProperty.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JIOException.h"
#include "JEOFException.h"
#include "JWaveOutObj.h"

/* Register itself into the NeatTools System */
char* theJRecorderObj = JRecorderObj().Register();

/* Write the current Module state into OutputStream */
void JRecorderObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os); // Base Class Action
  putObject(os, "prefix", prefix);
  putInteger(os, "repeat", repeat);
  putInteger(os, "feedback", feedback);
  putInteger(os, "sequence", sequence);
  putInteger(os, "textOutput", textOutput);
  putDouble(os, "playbackScale", playbackScale);
  putInteger(os, "N", N);
}

/* Reconstruct the current Module state from Dictionary */
void JRecorderObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict); // Base Class Action
  JObject *obj = getObject(dict, "prefix");
  if (obj) prefix = *(JString*)obj;
  repeat = getInteger(dict, "repeat");
  feedback = getInteger(dict, "feedback");
  sequence = getInteger(dict, "sequence");
  textOutput = getInteger(dict, "textOutput");
  playbackScale = getDouble(dict, "playbackScale", 1.0);
  updateN(getInteger(dict, "N"), false);
  filename = composit(prefix, sequence);
  check(false); // Check if module is in valid state
}

/* Name of the Class */
const char* JRecorderObj::className() const { return "JRecorderObj";}
/* Object Clone Override */
JObject* JRecorderObj::clone() const { return new JRecorderObj(*this);}

/* Construct Object and initialize variables */
JRecorderObj::JRecorderObj() {
  N = 0;
  updateN(1, false);
  sequence = 0;
  pos = count = total = 0;
  prefix = "untitle";
  type = "*.dat";
  filename = composit(prefix, sequence);
  recording = false;
  playing = false;
  pause = false;
  recordEnabled = false;
  playEnabled = false;
  repeat = false;
  feedback = false;
  textOutput = false;
  waveFeedback = 0;
  timeBase = pauseBase = 0;
  startPos = 16;
  playbackScale = 1.0;
}

/* GCC 2.7.2 will crash if don't have this constructor
   defined. It is not needed in VC++ */ 
JRecorderObj::JRecorderObj(const JRecorderObj& obj) { *this=obj;}

/* Close all handles and destroy object */
JRecorderObj::~JRecorderObj() { 
  close();
}

/* Startup action (Respond to System) */
void JRecorderObj::startup() 
{ if (!playing && !recording) check(true);}

/* Reset states when copy/duplicate modules */
void JRecorderObj::reset() { 
  playing = false;
  recording = false;
}

/* Start to Record Events */
void JRecorderObj::record() {
  cs.lock(); // Mutex Lock
  if (recording) { // If in recording state unlock and quit 
    cs.unlock();
    return;
  }
  close();   // Close Previous actions (like playback)
  try {
    count = total = 0;
    if (textOutput) { // If need Text Output, Open it and
      JFile tf(filename); // Write Header Line First
      tf.changeExt(".txt");
      ftos.open(tf.getPath());
      btos.connect(ftos);
      btos << JString("Time\tChannel\tType\tValue\n");
    }
    fos.open(filename); // Open Data File
    fos << JBlock(4, "DATA"); // Write Header
    fos << JBlock(total); // Write Totle ms 
    fos << JBlock(N);     // Write Number of Channel
    fos << JBlock(count); // Write Event Count 
    bos.connect(fos);   // Connect to Buffer Stream
    recording = true;   // Set Recording State
    repaint();          // Refresh Module Display
    broadcast(COUNT);   // Broadcast Events
    broadcast(TOTAL);
    pauseBase = timeBase = JSystem::currentTimeMillis();
  } catch (JIOException* e) {
    delete e;
    close();  // Close Handle when Exception happen
  }
  cs.unlock(); // Mutex Unlock
}

/* Play back events */
void JRecorderObj::play() {
  cs.lock();  // Mutex Lock
  if (playing) { // If in playing state unlock and quit
    cs.unlock();
    return;
  }
  close();  // Close Previous actions (like recording)
  try {
    if (check(true)) { // If module is valid then proceed
      pos = max(0, min(total, pos)); // Calculate the starting position
      fis.open(filename); // Open Data File
      fis.seek(startPos);
      bis.connect(fis);   // Connect to Buffer Stream
      playing = true;	  // Set Playback State
      repaint();	  // Refresh Module Display
      thread = JThread(this); // New Thread Instance
      thread.start();     // Start Thread and set Priority
      thread.setPriority(JThread::TNORM_PRIORITY+1);
    }
  } catch (JIOException* e) {
    delete e;
    close(); // Close Handle when Exception happen
  }
  cs.unlock(); // Mutex Unlock
}

/* Close File Handle */
void JRecorderObj::closeHandle() {
  try {
    bis.close();
  } catch (JIOException* e) {
    delete e;
  }
}

/* Close Current Record/Playback Action */
void JRecorderObj::close() {
  cs.lock(); // Mutex Lock
  if (recording) { // Is in recording state ?
    recording = false;
    try {
      bos.flush(); // Flush Buffer
      fos.seek(4); // Seek header
      fos << JBlock(total); // Write Totle ms
      fos.seek(12); // Seek header
      fos << JBlock(count); // Write Totle Event Count
      bos.close(); // Close File Handle
      if (textOutput) { // If need Text Output 
	btos.flush(); // Flush Text File Buffer
	btos.close(); // Close Text File Handle
      }
    } catch (JIOException* e) {
      delete e;
    }
    repaint(); // Refresh Module Display
  }
  if (playing) { // Is in playback state ?
    playing = false;
    /* Set Thread Priority to normal */
    closeHandle(); // Close Related Handle
    repaint(); // Refresh Module Display

  }
  cs.unlock(); // Unlock Mutex
}

/* Return the input type of port n */
int JRecorderObj::inputType(int n) { 
    if (n < IN_BLOCK) {
      switch (n) {
        case FILENAME:
	  return JStringData::id;
        case PLAYBACK_SCALE:
	  return JRealData::id;
      }
      return JIntegerData::id;
    }
    return JBlockData::id;
}

/* Return the output type of port n */
int JRecorderObj::outputType(int n) { return (n < OUT_BLOCK) ? JIntegerData::id : JBlockData::id;} 

/* Exchange Data of port n */
void JRecorderObj::access(int n, JLinkObj& link, const JDataType& _data) { 
  if ((OUT_BLOCK <= n) && (n-OUT_BLOCK < N))
    _data.assign(*data[n-OUT_BLOCK]);
  else INT(_data) = (!n) ? count : total;
}

/* Access control of port n */
boolean JRecorderObj::inputAllowed(int n)
{ return !inputSet(n).last();}

/* Tag String of input port n */
JString JRecorderObj::inputTag(int n) {
  if (n < IN_BLOCK) {
    if (n < IN_LAST) {
      char* tag[] = { "record(logical)", "play(logical)", 
        "pause(logical)", "filename",
        "sequence", "pos", "N(1-128)", "playbackScale", "waveFeedback"};
      return tag[n];
    }
    return "";
  }
  return JString("in-")+JInteger::toJString(n-IN_BLOCK);
}

/* Tag String of output port n */
JString JRecorderObj::outputTag(int n) {
  if (n < OUT_BLOCK) {
    if (n < OUT_LAST) {
      char* tag[] = { "count", "total"};
      return tag[n];
    }
    return "";
  }
  return JString("out-")+JInteger::toJString(n-OUT_BLOCK);
}

/* Input Area of port n */
JFRect JRecorderObj::inputArea(int n) { 
  if (n < IN_BLOCK) {
    if (n < IN_LAST) return topArea(n, 0, IN_LAST);
    return JFRect();
  }
  if (n >= IN_BLOCK+N) n = IN_BLOCK;
  return leftArea(n, IN_BLOCK, N, 0, 1);
}

/* Output Area of port n */
JFRect JRecorderObj::outputArea(int n) {
  if (n < OUT_BLOCK) {
    if (n < OUT_LAST) return bottomArea(n, 0, OUT_LAST);
    return JFRect();
  }
  if (n >= OUT_BLOCK+N) n = OUT_BLOCK;
  return rightArea(n, OUT_BLOCK, N, 0, 1);
}

/* Input Attach Edge of port n */
int JRecorderObj::inputFace(int n) {
  if (n < IN_BLOCK) return TOP;
  return LEFT;
}

/* Output Attach Edge of port n */
int JRecorderObj::outputFace(int n) {
  if (n < OUT_BLOCK) return BOTTOM;
  return RIGHT;
}

/* Input Attach Point of port n */
JFPoint JRecorderObj::inputPoint(int n, JLinkObj& link) { 
  if (n < IN_BLOCK) {
    if (n < IN_LAST) return topPoint(n, link, 0, IN_LAST);
    return JFPoint();
  }
  if (n >= IN_BLOCK+N) n = IN_BLOCK;
  return leftPoint(n, link, IN_BLOCK, N, 0, 1);
}

/* Output Attach Point of port n */
JFPoint JRecorderObj::outputPoint(int n, JLinkObj& link) {
  if (n < OUT_BLOCK) {
    if (n < OUT_LAST) return bottomPoint(n, link, 0, OUT_LAST);
    return JFPoint();
  }
  if (n >= OUT_BLOCK+N) n = OUT_BLOCK;
  return rightPoint(n, link, OUT_BLOCK, N, 0, 1);
}

/* Paint the module */
void JRecorderObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JAddObj::paint(g, dx, dy, rgn, scale); // Base Class Action
  JRect rect = getIExtent(dx, dy, scale);// Get Current Extent
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) { // If Display is large engough
    if (pause) g.setJColor(JColor::blue);        // Set the indicator color
    else if (recording) g.setJColor(JColor::red);
    else if (playing) g.setJColor(JColor::yellow);
    else g.setJColor(JColor::red.darker());      // Set the inactivate color
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2); // Draw the Indicator Rectangle
  }
}

/* Draw the module pattern */
void JRecorderObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dh = h/3;
  int dy = h/12;
  /* Calculate the Bounding box */
  JRect rect1(x, y+dy, w, dh);
  JRect rect2(x, y+h/3, w, dh);
  JRect rect3(x, y+h*2/3-dy, w, dh);
  /* Draw the Text Representation */
  drawText(g, "Rec", rect1);
  drawText(g, "Block", rect2);
  drawText(g, filename, rect3);
}

/* Input event service define in engine */
void JRecorderObj::engine(int n, JLinkObj& link) {
  if (n >= IN_BLOCK) { // If Data Event Coming In 
    cs.lock();  // Lock Mutex
    if (recording && !pause) { // If in Recording and not in pause mode
      try {
        long dt = JSystem::currentTimeMillis()-timeBase;
        uchar ch = (uchar)(n-IN_BLOCK+1); // The incoming channel number
	JBlock buf;
        for (int i=data.size(); i<ch; i++) // Append output data array
          data.append(JBlock());
        link.access(JBlockData(buf)); // Get the Data Block
        bos << JBlock(JInteger::toJString(dt, JDataType::convertBase))
	  +JBlock(ch)+buf; // Write Data into buffer stream
	if (feedback) { // If need feedback
	  data.set(ch, buf); // Prepare Data
	  broadcast(OUT_BLOCK+ch); // Broadcast Data
	}
        timeBase += dt;	// Calcuate the next Time Base
	total = (count += dt); // Calculate the total Time in ms
	if (textOutput) { // If Need Text Output
          JString tag = JString(buf); // Output Data in Text Format
	  btos << JInteger::toJString(count)+"\t"+
	    JInteger::toJString(ch-1)+"\t"+tag(0, 1)+"\t"+
	    JInteger(tag(1), JDataType::convertBase).toJString()+"\n";
	}
	broadcast(COUNT); // Broadcast Events
	broadcast(TOTAL);
      } catch (JIOException* e) {
        delete e;
        close();
      }
    }
    cs.unlock(); // Unlock Mutex
    return;
  }
  switch (n) {
    case RECORD: { // Handle Record Control Event
      link.access(JIntegerData(recordEnabled)); // Get Event
      if (recordEnabled) playEnabled = false; 
      if (recordEnabled && !recording) {
        close(); // Close Previous Action
        record();  // Start Recording
      } else if (!recordEnabled && recording) close();
      break;
    }
    case PLAY: { // Handle Playback Control Event
      link.access(JIntegerData(playEnabled)); // Get Event
      if (playEnabled) recordEnabled = false;
      if (playEnabled && !playing) {
        close(); // Close Previous Action
        play();  // Start Playback
      } else if (!playEnabled && playing) close();
      break;
    }
    case PAUSE: { // Handle Pause Control Event
      int oPause = pause;
      link.access(JIntegerData(pause)); // Get Event
      pause  = (pause != 0);
      if (oPause != pause) {
	if (pause) {
          /* Remember the current Pause Time base */
	  pauseBase = JSystem::currentTimeMillis();
	  if (playing) counter = 0;
	} else {
          /* Reconstruct the new Time base */
          timeBase += JSystem::currentTimeMillis()-pauseBase;
        }
	repaint();
      }
      break;
    }
    case FILENAME: { // Handle Filename String Event
      JString nPrefix;
      JString oFilename = filename;
      link.access(JStringData(filename)); // Get Event
      sequence = parseName(filename, nPrefix);
      filename = composit(nPrefix, sequence);
      if (oFilename != filename) {
        boolean oldREnabled = recordEnabled;
        boolean oldPEnabled = playEnabled;
        close(); // Close Previous Action
	prefix = nPrefix;
        /* Resume Previous Action with new File name */
        if (oldREnabled) record(); 
        else if (oldPEnabled) play();
        repaint(); // Refresh the module display
      }
      break;
    }
    case SEQUENCE: { // Handle File Sequence Event
      int oSequence = sequence;
      link.access(JIntegerData(sequence)); // Get Event
      if (oSequence != sequence) {
        boolean oldREnabled = recordEnabled;
        boolean oldPEnabled = playEnabled;
        close(); // Close Previous Action
	filename = composit(prefix, sequence);
        /* Resume Previous action with new File Sequence */
        if (oldREnabled) record();
        else if (oldPEnabled) play();
        repaint(); // Refresh the Module Display
      }
      break;
    }
    case POS: { // Handle Start Position Event
      link.access(JIntegerData(pos)); // Get Event
      pos = max(0, min(total, pos));  // Caculate Position Value
      break;
    }
    case NTRACK: { // Handle Channel Number Event
      int iv;
      link.access(JIntegerData(iv)); // Get Event
      updateN(iv, true); // Update the Channel Number
      break;
    }
    case PLAYBACK_SCALE: { 
      double iv;
      link.access(JRealData(iv)); // Get Event
      playbackScale = iv;
      break;
    }
    case WAVE_FEEDBACK: { // Handle Wave Feedback Event
      link.access(JIntegerData(waveFeedback)); // Get Event
      break;
    }
  }
}

/* Collect the module's property set */
JArray JRecorderObj::getProperties() {
  JArray properties = JAddObj::getProperties(); // Base class Action
  properties.append(JFileProperty("filename", filename, type));
  properties.append(JIntegerProperty("sequence", sequence, 0, 9999));
  properties.append(JIntegerProperty("N", N, 1, 128));
  properties.append(JIntegerListProperty("repeat", repeat, 
    JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("feedback", feedback, 
    JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("textOutput", textOutput, 
    JIntegerListProperty::booleanTag));
  properties.append(JDoubleProperty("playbackScale", playbackScale, 0.1, 10.0));
  return properties;
}

/* Modify module's property (Respond to System) */
boolean JRecorderObj::updateProperty(JProperty& prop) {
  /* Base Class Action, If Base Class already handle 
     the property then exit */
  if (JAddObj::updateProperty(prop)) return true; 
  boolean changed = false;
  boolean oldREnabled = recordEnabled;
  boolean oldPEnabled = playEnabled;
  close(); // Close Previous Action when change module state
  if (prop.getName() == JString("filename")) {
    sequence = parseName(((JFileProperty*)&prop)->value, prefix);
    filename = composit(prefix, sequence);
    check(true);
    changed = true;
  } else if (prop.getName() == JString("sequence")) {
    sequence = ((JIntegerProperty*)&prop)->value;
    filename = composit(prefix, sequence);
    changed = true;
  } else if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value, true);
    changed = true;
  } else if (prop.getName() == JString("repeat")) {
    repeat = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("feedback")) {
    feedback = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("textOutput")) {
    textOutput = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("playbackScale")) {
    playbackScale = ((JDoubleProperty*)&prop)->value;
  }
  /* Resume the previous action with new state */
  if (oldREnabled) record();
  else if (oldPEnabled) play();
  if (changed) repaint(); // Refresh Module Display
  return changed;
}

/* Check if module is valid */
boolean JRecorderObj::check(boolean redraw) {
  boolean result = false;
  count = 0;
  total = 0;
  try {
    int nN;
    fis.open(filename); // Open the Data File
    JBlock tag(4, 0);
    fis >> tag; // Read the Header
    if (JString(tag) != JString("DATA")) goto ENDCHECK;
    fis >> JBlock(total); // Read Total ms
    fis >> JBlock(nN);    // Read Channel Number
    updateN(nN, redraw);    // Update Channel Number
    result = true;
  } catch (JIOException* e) {
    delete e;
    result = false;
  }
ENDCHECK:
  close(); // Close All Action
  broadcast(COUNT);
  broadcast(TOTAL);
  return result;
}

/* Update the channel number */
boolean JRecorderObj::updateN(int nN, boolean redraw) {
  nN = max(1, min(128, nN)); // Get Safe Range
  if (N != nN) {
    JFRect rect;
    if (redraw) { // Calculate the Previous Update Area
      rect = calculateInputUpdate();
      rect |= calculateOutputUpdate();
    }
    N = nN; 
    ogm = N+OUT_BLOCK; // Set the Input/Output Number
    igm = N+IN_BLOCK;
    for (int i=data.size(); i<N; i++) // Append output data array
      data.append(JBlock());
    if (redraw) { // Calculate the required Update Area
      rect |= calculateInputUpdate();
      rect |= calculateOutputUpdate();
//      repaintView(rect); // Request System for Update
    }
    return true;
  }
  return false;
}

/* Composit the Prefix and Sequence into Filename Stream */
JString JRecorderObj::composit(JString prefix, int sequence) { 
  if (sequence)
    return prefix+"_"+JInteger::toJString(sequence)+type(1);
  return prefix+type(1);
}

/* Parse filename into prefix and sequence number */
int JRecorderObj::parseName(JString filename, JString& prefix) { 
  int start = filename.lastIndexOf('_');
  int end = filename.lastIndexOf('.');
  if (end == -1) end = filename.length();
  if (start > -1) {
    prefix = filename(0, start);
    return (int)JInteger(filename(start+1, end));
  } else prefix = filename(0, end);
  return 0;
}

DllImport void segmentDelay(int interval, int&base, int& counter, boolean& cond);

/* Thread Run Procedure 
   Playback the recorded event from Data File */
void JRecorderObj::run() {
  JString tag;
  int delay, ndelay;
  /* Get The Current Time Base in ms */
  int base = JSystem::currentTimeMillis();
  while (playing) {
    while (pause && playing) // Pause Loop
      JThread::sleep(100);   // Wait for Pause to release
    try {
      /* Read the Interval and Data Information */
      JString str;
      bis >> tag;
      bis >> str;
      int channel = (int)(((uchar)str[0])-1);
      JBlock buf = JBlock(str.length(), 
	((char*)str)+1, JBlock::needCopy);
      for (int i=data.size(); i<channel; i++) // Append output data array
        data.append(JBlock());
      if (JDataType::bstr.indexOf(buf[0]) > -1) {
	int ofs;
        int size = (int)JInteger(((char*)buf)+1, 
	  JDataType::convertBase); 
        ofs = buf.size();
        buf.grow(size+ofs);
	JBlock binary(size, ((char*)buf)+ofs);
        bis >> binary;
        data.set(channel, buf);
	if (binary.size() != size) break;
      } else data.set(channel, buf);
      delay = (int)JInteger(tag, JDataType::convertBase);
      ndelay = JMath::round(double(delay)/playbackScale);
      if (pos <= count) { // Normal Delay
        if (waveFeedback != JWaveOutObj::PAUSE) 
          segmentDelay(ndelay, base, counter, playing);
        broadcast(channel+OUT_BLOCK);
      } else if (pos < count+delay) { // Delay Separate by Starting Position
        if (waveFeedback != JWaveOutObj::PAUSE) 
          segmentDelay(JMath::round(double(delay-pos+count)/playbackScale), base, counter, playing);
        broadcast(channel+OUT_BLOCK);
      }
      count += delay; // Calculate the current ms
      broadcast(COUNT); // Broadcast the current ms
    } catch (JIOException *e) {
      delete e;
      /* When Exception happen stop and reset */
      if (!repeat) break;
      else {
        /* End Of File and Need Repeat */
	bis.reset();
        fis.seek(startPos);
        count = 0;
	broadcast(COUNT);
      }
    }
  }
  if (playing) { // Reset and Close Handle
    playing = false;
    closeHandle();
    repaint();
  }
}

