#include "JColorObj.h"
#include "JColorProperty.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JColorData.h"

char* theJColorObj = JColorObj().Register();
void JColorObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putObject(os, "color", color);
}

void JColorObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  color = *(JColor*)getObject(dict, "color");
  updateValue();
}

const char* JColorObj::className() const { return "JColorObj";}
JObject* JColorObj::clone() const { return new JColorObj(*this);}

JColorObj::JColorObj(JColor _color) {
  igm = 4;
  ogm = 4;
  color = _color;
  updateValue();
}

void JColorObj::updateValue() {
  v[0] = color.getRed() << 8;
  v[1] = color.getGreen() << 8;
  v[2] = color.getBlue() << 8;
}

void JColorObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  g.setJColor(moduleColor);
  if ((rect.width > depth2) && (rect.height > depth2))
    g.draw3DJRect(rect, depth);
  update(g, dx, dy, rgn, scale);
}

void JColorObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  g.setJColor(color);
  if ((rect.width > depth2) && (rect.height > depth2)) {
    g.fillJRect(rect.shrink(depth, depth));
  } else g.fillJRect(rect);
}

int JColorObj::inputType(int n) 
{ return (!n) ? JColorData::id : JIntegerData::id;}
int JColorObj::outputType(int n) 
{ return (!n) ? JColorData::id : JIntegerData::id;}

void JColorObj::access(int n, JLinkObj& link, const JDataType& data) { 
  if (!n) data.assign(color);
  else INT(data) = v[n-1];
}

boolean JColorObj::inputAllowed(int n) {
  if (!n) {
    return !inputSet(n).last() &&
      !inputSet(1).last() &&
      !inputSet(2).last() &&
      !inputSet(3).last();
  } else {
    return !inputSet(n).last() &&
      !inputSet(0).last();
  }
}

boolean JColorObj::outputAllowed(int n) { return true;}

JString JColorObj::inputTag(int n) {
  char* tag[] = { "color-in", "red-in", "green-in", "blue-in"};
  return tag[n];
}

JString JColorObj::outputTag(int n) {
  char* tag[] = { "color-out", "red-out", "green-out", "blue-out"};
  return tag[n];
}

JFRect JColorObj::inputArea(int n) { 
  if (!n) return topArea(n, 0, 1);
  return leftArea(n, 1, 3, 0, 1);
}

JFRect JColorObj::outputArea(int n) { 
  if (!n) return bottomArea(n, 0, 1);
  return rightArea(n, 1, 3, 0, 1);
}

int JColorObj::inputFace(int n) 
{ return (!n) ? TOP : LEFT;}

int JColorObj::outputFace(int n) 
{ return (!n) ? BOTTOM : RIGHT;}

JFPoint JColorObj::inputPoint(int n, JLinkObj& link) { 
  if (!n) return topPoint(n, link, 0, 1);
  return leftPoint(n, link, 1, 3, 0, 1);
}

JFPoint JColorObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return bottomPoint(n, link, 0, 1);
  return rightPoint(n, link, 1, 3, 0, 1);
}

void JColorObj::engine(int n, JLinkObj& link) {
  if (!n) {
    JColor oldc = color;
    link.access(JColorData(color));
    if (oldc != color) {
      int i;
      int ov[3];
      for (i=0; i<3; i++)
        ov[i] = v[i];
      updateValue();
      for (i=0; i<3; i++)
        if (ov[i] != v[i])
	  broadcast(i+1);
      broadcast(0);
      repaint();
    }
  } else {
    int oldv = v[n-1];
    link.access(JIntegerData(v[n-1]));
    v[n-1] = v[n-1] & 0xFF00;
    if (oldv != v[n-1]) {
      color = JColor(v[0] >> 8, 
        v[1] >> 8, v[2] >> 8);
      broadcast(n);
      broadcast(0);
      repaint();
    }
  }
}

JArray JColorObj::getProperties() {
  JArray properties = JModuleObj::getProperties();
  properties.append(JColorProperty("color", color));
  return properties;
}

boolean JColorObj::updateProperty(JProperty& prop) {
  if (JModuleObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("color")) {
    color = ((JColorProperty*)&prop)->color;
    repaint();
  }
  return true;
}

