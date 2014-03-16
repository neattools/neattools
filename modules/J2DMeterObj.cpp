#include "J2DMeterObj.h"
#include "JIntegerProperty.h"
#include "JColorProperty.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JColorData.h"

char* theJ2DMeterObj = J2DMeterObj().Register();
void J2DMeterObj::writeContent(JOutputStream& os) {
  JNBitsObj::writeContent(os);
  putInteger(os, "v0", v[0]);
  putInteger(os, "v1", v[1]);
  putInteger(os, "ov0", ov[0]);
  putInteger(os, "ov1", ov[1]);
}

void J2DMeterObj::readContent(JDictionary& dict) {
  JNBitsObj::readContent(dict);
  pv[0] = v[0] = getInteger(dict, "v0");
  pv[1] = v[1] = getInteger(dict, "v1");
  ov[0] = getInteger(dict, "ov0");
  ov[1] = getInteger(dict, "ov1");
}

const char* J2DMeterObj::className() const { return "J2DMeterObj";}
JObject* J2DMeterObj::clone() const { return new J2DMeterObj(*this);}

J2DMeterObj::J2DMeterObj() { 
  igm = 4;
  ogm = 2;
  color = JColor::yellow.darker(); 
  bkgnd = JColor::cyan.darker(); 
  pv[0] = pv[1] = v[0] = v[1] = ov[0] = ov[1] = 0;
}

void J2DMeterObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  g.setJColor(moduleColor);
  if ((rect.width > depth2+2) && (rect.height > depth2+2)) {
    g.draw3DJRect(rect, depth);
    g.draw3DJRect(rect.shrink(depth, depth), -1);
  } else g.fillJRect(rect);
  update(g, dx, dy, rgn, scale);
}

void J2DMeterObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  if ((rect.width > depth2+2) && (rect.height > depth2+2)) {
    int dt = depth2+depth;
    JRect clip = rect, thumb;
    JRegion frgn(clip.shrinkBy(depth+1, depth+1));
    g.setJColor(bkgnd);
    g.fillJRect(clip);
    v[0] = max(0, min(mask, v[0]));
    v[1] = max(0, min(mask, v[1]));
    int xpos = v[0]*(rect.width-depth2-dt-2)/mask;
    int ypos = (mask-v[1])*(rect.height-depth2-dt-2)/mask;
    thumb = JRect(clip.x+xpos, clip.y+ypos, dt, dt);
    g.setJColor(color);
    g.fill3DJRect(thumb, depth);
    g.setJRegion((frgn & rgn)-JRegion(thumb));
    g.setJColor(bkgnd);
    g.fillJRect(clip);
    g.setJRegion(rgn);
  }
}

boolean J2DMeterObj::cond(int n, JLinkObj& link) { 
  double pos = link.pos*mask;
  return (ov[n] > pos) != (v[n] > pos);
}

int J2DMeterObj::inputType(int n) 
{ return (n<2) ? JIntegerData::id : JColorData::id;}
void J2DMeterObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = (v[n] > (link.pos*mask)) ? mask : 0;}

JString J2DMeterObj::inputTag(int n) { 
  char* tag[] = { "x-in", "y-in", "color", "background"};
  if (n < 2) return JString(tag[n])+NBTag();
  return tag[n];
}

JString J2DMeterObj::outputTag(int n) { 
  char* tag[] = { "x-out", "y-out"};
  return JString(tag[n])+NBTag();
}

boolean J2DMeterObj::inputAllowed(int n)
{ return (boolean)((n < 2) ? true : !inputSet(n).last());}

JFRect J2DMeterObj::inputArea(int n) { 
  if (n<2) return leftArea(n, 0, 2);
  return topArea(n, 2, 2);
}

JFRect J2DMeterObj::outputArea(int n) { 
  if (!n) return bottomArea(n, 0, 1, 0, 1);
  return rightArea(n, 1, 1, 0, 1);
}

int J2DMeterObj::inputFace(int n) 
{ return (n<2) ? LEFT : TOP;}
int J2DMeterObj::outputFace(int n) 
{ return (!n) ? BOTTOM : RIGHT;}

JFPoint J2DMeterObj::inputPoint(int n, JLinkObj& link) { 
  if (n < 2) return leftPoint(n, link, 0, 2);
  return topPoint(n, link, 2, 2);
}

JFPoint J2DMeterObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return JFPoint(x+link.pos*width, y+height);
  return JFPoint(x+width, y+(1.0-link.pos)*height);
}

double J2DMeterObj::outputPos(int n, JFPoint opt) { 
  if (!n) return (opt.x-x)/width;
  return (y+height-opt.y)/height;
}

void J2DMeterObj::engine(int n, JLinkObj& link) {
  if (n < 2) {
    int iv = v[n];
    link.access(JIntegerData(iv));
    setNValue(n, iv);
  } else processColor(n, link, -1);
}

JArray J2DMeterObj::getProperties() {
  JArray properties = JNBitsObj::getProperties();
  properties.append(JIntegerProperty("vx", v[0], 0, mask));
  properties.append(JIntegerProperty("vy", v[1], 0, mask));
  properties.append(JColorProperty("color", color));
  properties.append(JColorProperty("bkgnd", bkgnd));
  return properties;
}

boolean J2DMeterObj::updateProperty(JProperty& prop) {
  if (JNBitsObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("vx")) {
    setNValue(0, ((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("vy")) {
    setNValue(1, ((JIntegerProperty*)&prop)->value);
    return true;
  }
  return false;
}

boolean J2DMeterObj::setNValue(int n, int _value) {
  _value = max(0, min(mask, _value));
  if (_value != v[n]) {
    ov[n] = v[n];
    v[n] = _value;
    condBroadcast(n);
    repaint();
    return true;
  }
  return false;
}

