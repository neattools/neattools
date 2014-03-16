#include "J2DSliderObj.h"
#include "JIntegerProperty.h"
#include "JColorProperty.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JIntegerData.h"
#include "JColorData.h"

char* theJ2DSliderObj = J2DSliderObj().Register();
void J2DSliderObj::writeContent(JOutputStream& os) {
  JBtnObj::writeContent(os);
  putDouble(os, "fraction0", fraction[0]);
  putDouble(os, "fraction1", fraction[1]);
  putInteger(os, "v0", v[0]);
  putInteger(os, "v1", v[1]);
  putInteger(os, "min0", min[0]);
  putInteger(os, "min1", min[1]);
  putInteger(os, "max0", max[0]);
  putInteger(os, "max1", max[1]);
}

void J2DSliderObj::readContent(JDictionary& dict) {
  JBtnObj::readContent(dict);
  color = JColor::cyan.darker(); 
  fraction[0] = getDouble(dict, "fraction0");
  fraction[1] = getDouble(dict, "fraction1");
  pv[0] = v[0] = getInteger(dict, "v0");
  pv[1] = v[1] = getInteger(dict, "v1");
  min[0] = getInteger(dict, "min0");
  min[1] = getInteger(dict, "min1");
  max[0] = getInteger(dict, "max0");
  max[1] = getInteger(dict, "max1");
}

const char* J2DSliderObj::className() const { return "J2DSliderObj";}
JObject* J2DSliderObj::clone() const { return new J2DSliderObj(*this);}

J2DSliderObj::J2DSliderObj() { 
  igm = IN_LAST;
  ogm = 2;
  bkgnd = color = JColor::cyan.darker(); 
  v[0] = v[1] = 0;
  pv[0] = pv[1] = 0;
  min[0] = min[1] = 0;
  max[0] = max[1] = 0;
  next[0] = next[1] = 0;
  prev[0] = prev[1] = 0;
  fraction[0] = fraction[1] = 0.0; 
  factor[0] = factor[1] = 0.0; 
  oldf[0] = oldf[1] = 0.0; 
}

void J2DSliderObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  g.setJColor(moduleColor);
  if ((rect.width > depth2+2) && (rect.height > depth2+2)) {
    g.draw3DJRect(rect, depth);
    g.draw3DJRect(rect.shrink(depth, depth), -1);
  } else g.fillJRect(rect);
  update(g, dx, dy, rgn, scale);
}

void J2DSliderObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  int dt = depth2+2;
  JRect rect = getIExtent(dx, dy, scale);
  if ((rect.width > dt) && (rect.height > dt)) {
    int ov[] = { v[0], v[1]};
    JRect clip = rect, thumb;
    JRegion frgn(clip.shrinkBy(depth+1, depth+1));
    int xlen = rect.width-dt-dt;
    int ylen = rect.height-dt-dt;
    if (oldf[0] != factor[0]) {
      oldf[0] = factor[0];
      fraction[0] = (factor[0]*rect.width-dt)/xlen;
      fraction[0] = max(0.0, min(1.0, fraction[0]));
    }
    if (oldf[1] != factor[1]) {
      oldf[1] = factor[1];
      fraction[1] = (factor[1]*rect.height-dt)/ylen;
      fraction[1] = max(0.0, min(1.0, fraction[1]));
    }
    int xpos = (int)JMath::round(fraction[0]*xlen);
    int ypos = (int)JMath::round((1.0-fraction[1])*ylen);
    thumb = JRect(clip.x+xpos, clip.y+ypos, dt, dt);
    int vmin0 = getMin(0);
    int vmin1 = getMin(1);
    v[0] = (int)JMath::round(fraction[0]*(getMax(0)-vmin0)+vmin0);
    v[1] = (int)JMath::round(fraction[1]*(getMax(1)-vmin1)+vmin1);
    if (v[0] != ov[0]) broadcast(0);
    if (v[1] != ov[1]) broadcast(1);
    g.setJColor(color);
    g.fill3DJRect(thumb, depth);
    g.setJRegion((frgn & rgn)-JRegion(thumb));
    g.setJColor(bkgnd);
    g.fillJRect(clip);
    g.setJRegion(rgn);
  }
}

boolean J2DSliderObj::mouseDown(JEvent& e, double _x, double _y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = (inside(_x, _y));
  }
  return true;
}

boolean J2DSliderObj::mouseDrag(JEvent& e, double _x, double _y) {
  if (mousePressed) {
    oldf[0] = factor[0];
    oldf[1] = factor[1];
    if (width > 0.0) 
      factor[0] = (_x-x)/width;
    else factor[0] = 0.0;
    if (height > 0.0) 
      factor[1] = (y+height-_y)/height;
    else factor[1] = 0.0;
    if ((oldf[0] != factor[0]) ||
      (oldf[1] != factor[1])) {
      repaint();
    }
  }
  return true;
}

boolean J2DSliderObj::mouseUp(JEvent& e, double x, double y) {
  if (e.modifiers & JEvent::LBUTTON) {
    mousePressed = false;
  }
  return true;
}

int J2DSliderObj::inputType(int n) { 
  switch (n) {
    case COLOR:
    case BACKGROUND:
      return JColorData::id;
  }
  return JIntegerData::id;
}

void J2DSliderObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = v[n];}

JString J2DSliderObj::inputTag(int n) {
  char* tag[] = { "x-in", "y-in", "color", "background",
    "xMax", "yMax", "xNext", "yNext", "xPrev", "yPrev", "xMin", "yMin"};
  if ((n == XINPUT) && isNBits(n)) return JString(tag[n])+NBTag();
  if ((n == YINPUT) && isNBits(n)) return JString(tag[n])+NBTag();
  return tag[n];
}

JString J2DSliderObj::outputTag(int n) {
  char* tag[] = { "x-out", "y-out"};
  if ((n == XINPUT) && isNBits(n)) return JString(tag[n])+NBTag();
  if ((n == YINPUT) && isNBits(n)) return JString(tag[n])+NBTag();
  return tag[n];
}

JFRect J2DSliderObj::inputArea(int n) { 
  if (n<2) return leftArea(n, 0, 2);
  return topArea(n, 2, igm-2);
}

JFRect J2DSliderObj::outputArea(int n) {
  if (!n) return rightArea(n, 0, 1);
  return bottomArea(n, 1, 1);
}

int J2DSliderObj::inputFace(int n) 
{ return (n<2) ? LEFT : TOP;}
int J2DSliderObj::outputFace(int n) 
{ return (!n) ? RIGHT : BOTTOM;}

JFPoint J2DSliderObj::inputPoint(int n, JLinkObj& link) { 
  if (n<2) return leftPoint(n, link, 0, 2);
  return topPoint(n, link, 2, igm-2);
}

JFPoint J2DSliderObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return rightPoint(n, link, 0, 1);
  return bottomPoint(n, link, 1, 1);
}

boolean J2DSliderObj::inputAllowed(int n) 
{ return (boolean)((n < 2) ? true : !inputSet(n).last());}

void J2DSliderObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case XINPUT:
    case YINPUT: {
      int iv = v[n];
      link.access(JIntegerData(iv));
      setNValue(n, iv);
      break;
    }
    case COLOR:
    case BACKGROUND:
      processColor(n, link, -1);
      break;
    case XMAX:
    case YMAX: {
      int id = n-XMAX;
      int ov = max[id];
      link.access(JIntegerData(max[id]));
      if (max[id] != ov) setNValue(id, v[id]);
      break;
    }
    case XMIN:
    case YMIN: {
      int id = n-XMIN;
      int ov = min[id];
      link.access(JIntegerData(min[id]));
      if (min[id] != ov) setNValue(id, v[id]);
      break;
    }
    case XNEXT: 
    case YNEXT: {
      int id = n-XNEXT;
      int ov = next[id];
      link.access(JIntegerData(next[id]));
      next[id] = (next[id] != 0);
      if (next[id] && (next[id] != ov)) 
        setNValue(id, v[id]+1);
      break;
    }
    case XPREV: 
    case YPREV: {
      int id = n-XPREV;
      int ov = prev[id];
      link.access(JIntegerData(prev[id]));
      prev[id] = (prev[id] != 0);
      if (prev[id] && (prev[id] != ov)) 
        setNValue(id, v[id]-1);
      break;
    }
  }
}

JArray J2DSliderObj::getProperties() {
  JArray properties = JModuleObj::getProperties();
  properties.append(JIntegerProperty("vx", v[0], 0, getMax(0)));
  properties.append(JIntegerProperty("vy", v[1], 0, getMax(1)));
  properties.append(JColorProperty("color", color));
  properties.append(JColorProperty("bkgnd", bkgnd));
  return properties;
}

boolean J2DSliderObj::updateProperty(JProperty& prop) {
  if (JBtnObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("vx")) {
    setNValue(0, ((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("vy")) {
    setNValue(1, ((JIntegerProperty*)&prop)->value);
    return true;
  }
  return false;
}

boolean J2DSliderObj::setNValue(int n, int _value) {
  _value = max(getMin(n), min(getMax(n), _value));
  if (_value != v[n]) {
    v[n]=_value;
    int vmin = getMin(n);
    int range = getMax(n)-vmin;
    if (!range) fraction[n] = 0;
    else fraction[n] = double(_value-vmin)/range;
    broadcast(n);
    repaint();
    return true;
  }
  return false;
}

boolean J2DSliderObj::isNBits(int n) 
{ return !inputSet(XMAX+n).last() && !inputSet(XMIN+n).last();}
int J2DSliderObj::getMin(int n) 
{ return (inputSet(XMIN+n).last()) ? min[n] : 0;}
int J2DSliderObj::getMax(int n) 
{ return (inputSet(XMAX+n).last()) ? max[n] : mask;}
