#include "JLEDObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JColorData.h"
#include "JIntegerProperty.h"
#include "JColorProperty.h"

char* theJLEDObj = JLEDObj().Register();
void JLEDObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putObject(os, "color", color);
  putObject(os, "bkgnd", bkgnd);
  putInteger(os, "value", value);
}

void JLEDObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  JObject *obj = getObject(dict, "color");
  if (obj) color = *(JColor*)obj;
  obj = getObject(dict, "bkgnd");
  if (obj) bkgnd = *(JColor*)obj;
  value = getInteger(dict, "value");
}

const char* JLEDObj::className() const { return "JLEDObj";}
JObject* JLEDObj::clone() const { return new JLEDObj(*this);}

JLEDObj::JLEDObj(JColor _color) { 
  igm = 3;
  value = 0; 
  color = _color;
  bkgnd = color.darker();
}

JLEDObj::JLEDObj(JColor _color, JColor _bkgnd) { 
  igm = 3;
  value = 0; 
  color = _color;
  bkgnd = _bkgnd;
}

void JLEDObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  g.setJColor(moduleColor);
  if ((rect.width > depth2) && (rect.height > depth2))
    g.draw3DJRect(rect, depth);
  update(g, dx, dy, rgn, scale);
}

void JLEDObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  if (value == 0) g.setJColor(bkgnd);
  else g.setJColor(color);
  if ((rect.width > depth2) && (rect.height > depth2)) {
    g.fillJRect(rect.shrink(depth, depth));
  } else g.fillJRect(rect);
}

int JLEDObj::inputType(int n) 
{ return (!n) ? JIntegerData::id : JColorData::id;}
void JLEDObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = value;}
boolean JLEDObj::inputAllowed(int n)
{ return (boolean)((!n) ? true : !inputSet(n).last());}
boolean JLEDObj::outputAllowed(int n) { return true;}
JString JLEDObj::inputTag(int n) {
  char* tag[] = { "input", "color", "background"};
  return tag[n];
}

JFRect JLEDObj::inputArea(int n) { 
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, igm-1);
}

JFPoint JLEDObj::inputPoint(int n, JLinkObj& link) { 
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, igm-1);
}

void JLEDObj::processColor(int n, JLinkObj& link, int delta) {
  if (n+delta == 1) {
    JColor oldc = color;
    link.access(JColorData(color));
    if (oldc != color) repaint();
  } else if (n+delta == 2) {
    JColor oldc = bkgnd;
    link.access(JColorData(bkgnd));
    if (oldc != bkgnd) repaint();
  }
}

void JLEDObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int iv = value;
    link.access(JIntegerData(iv));
    setValue(iv);
  } else processColor(n, link);
}

JArray JLEDObj::getProperties() {
  JArray properties = JModuleObj::getProperties();
  properties.append(JIntegerProperty("value", value, -limit-1, limit));
  properties.append(JColorProperty("color", color));
  properties.append(JColorProperty("bkgnd", bkgnd));
  return properties;
}

boolean JLEDObj::updateProperty(JProperty& prop) {
  if (JModuleObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("value")) {
    setValue(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("color")) {
    color = ((JColorProperty*)&prop)->color;
    repaintView(*this);
    return true;
  } else if (prop.getName() == JString("bkgnd")) {
    bkgnd = ((JColorProperty*)&prop)->color;
    repaintView(*this);
    return true;
  }
  return false;
}

boolean JLEDObj::setValue(int _value) {
  if (_value != value) {
    value = _value;
    broadcast(0);
    repaint();
    return true;
  }
  return false;
}

