#include "JTailObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JStringData.h"
#include "JFile.h"
#include "JFileProperty.h"
#include "JIOException.h"
#include "JEOFException.h"

/* Register itself into the NeatTools System */
char* theJTailObj = JTailObj().Register();

/* Write the current Module state into OutputStream */
void JTailObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os); // Base Class Action
  putObject(os, "filename", filename);
}

/* Reconstruct the current Module state from Dictionary */
void JTailObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict); // Base Class Action
  JObject *obj = getObject(dict, "filename");
  if (obj) filename = *(JString*)obj;
  check(); // Check if module is in valid state
}

/* Name of the Class */
const char* JTailObj::className() const { return "JTailObj";}
/* Object Clone Override */
JObject* JTailObj::clone() const { return new JTailObj(*this);}

/* Construct Object and initialize variables */
JTailObj::JTailObj() {
  igm = 1;
  ogm = 1;
  isOpened = false;
  type = "*.*";
  filename = "untitle.txt";
  data = "";
  check();
}

int JTailObj::inputType(int n) { 
  return JIntegerData::id;
}

int JTailObj::outputType(int n) {
  return JStringData::id;
} 

void JTailObj::access(int n, JLinkObj& link, const JDataType& _data) { 
  _data.assign(data);
}

int JTailObj::inputFace(int n) { return TOP;}

boolean JTailObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JTailObj::inputTag(int n) {
  return "sample_clock(logical)";
}

JString JTailObj::outputTag(int n) {
  return "tail-string";
}

JFRect JTailObj::inputArea(int n) { return topArea(n, 0, igm);}
JFPoint JTailObj::inputPoint(int n, JLinkObj& link) { return topPoint(n, link, 0, igm);}

void JTailObj::draw(JGraphics g, int x, int y, int w, int h) {
  if (!isOpened) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, "Tail", rect1);
  drawText(g, filename, rect2);
}

void JTailObj::engine(int n, JLinkObj& link) {
  if (n == 0) {
    int clock = null;
    link.access(JIntegerData(clock));
    if (clock != 0) {
      int len = fis.available();
      if (len > 0) {
        JBlock buf(len, 0);
        fis >> buf;
        data =JString(buf);
        broadcast(0);
      }  
    }
  }
}

JArray JTailObj::getProperties() {
  JArray properties = JAddObj::getProperties(); // Base class Action
  properties.append(JFileProperty("filename", filename, type));
  return properties;
}

boolean JTailObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true; 
  if (prop.getName() == JString("filename")) {
    filename = ((JFileProperty*)&prop)->value;
    check();
    repaint();
    return true;
  }
  return false;
}

boolean JTailObj::check() {
  boolean result = false;
  isOpened = false;
  try {
    fis.open(filename); // Open the Data File
    int avail = fis.available();
    if (avail > 0) fis.skip(avail);
    result = true;
    isOpened = true;
  } catch (JIOException* e) {
    delete e;
    result = false;
  }
  return result;
}

