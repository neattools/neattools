#include "J1DMeterObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"

char* theJ1DMeterObj = J1DMeterObj().Register();
void J1DMeterObj::writeContent(JOutputStream& os) {
  JNBitsObj::writeContent(os);
  putInteger(os, "oValue", oValue);
  putInteger(os, "type", type);
}

void J1DMeterObj::readContent(JDictionary& dict) {
  JNBitsObj::readContent(dict);
  oValue = getInteger(dict, "oValue");
  type = getInteger(dict, "type");
}

const char* J1DMeterObj::className() const { return "J1DMeterObj";}
JObject* J1DMeterObj::clone() const { return new J1DMeterObj(*this);}

J1DMeterObj::J1DMeterObj(int _type) { 
  igm = 3;
  color = JColor::yellow.darker(); 
  bkgnd = JColor::cyan.darker(); 
  type = _type;
  oValue = 0;
}

void J1DMeterObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  g.setJColor(moduleColor);
  if ((rect.width > depth2+2) && (rect.height > depth2+2)) {
    g.draw3DJRect(rect, depth);
    g.draw3DJRect(rect.shrink(depth, depth), -1);
  } else g.fillJRect(rect);
  update(g, dx, dy, rgn, scale);
}

void J1DMeterObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  if ((rect.width > depth2+2) && (rect.height > depth2+2)) {
    int dt = depth2+depth;
    JRect clip = rect, thumb;
    JRegion frgn(clip.shrinkBy(depth+1, depth+1));
    value = max(0, min(value, mask));
    if (type == HORIZONTAL) {
      int pos = value*(rect.width-depth2-dt-2)/mask;
      thumb = JRect(clip.x+pos, clip.y, dt, clip.height);
    } else {
      int pos = (mask-value)*(rect.height-depth2-dt-2)/mask;
      thumb = JRect(clip.x, clip.y+pos, clip.width, dt);
    }
    g.setJColor(color);
    g.fill3DJRect(thumb, depth);
    g.setJRegion((frgn & rgn)-JRegion(thumb));
    g.setJColor(bkgnd);
    g.fillJRect(clip);
    g.setJRegion(rgn);
  }
}

boolean J1DMeterObj::cond(int n, JLinkObj& link) { 
  double pos = link.pos*mask;
  return (oValue > pos) != (value > pos);
}

void J1DMeterObj::access(int n, JLinkObj& link, const JDataType& data)
{ INT(data) = (value > (link.pos*mask)) ? mask : 0;}

JFRect J1DMeterObj::outputArea(int n) { 
  if (type == HORIZONTAL) 
    return bottomArea(n, 0, 1, 0, 1);
  return rightArea(n, 0, 1, 0, 1);
}

int J1DMeterObj::outputFace(int n) 
{ return (type == HORIZONTAL) ? BOTTOM : RIGHT;}

JFPoint J1DMeterObj::outputPoint(int n, JLinkObj& link) { 
  if (type == HORIZONTAL)
    return JFPoint(x+link.pos*width, y+height);
  return JFPoint(x+width, y+(1.0-link.pos)*height);
}

double J1DMeterObj::outputPos(int n, JFPoint opt) { 
  if (type == HORIZONTAL)
    return (opt.x-x)/width;
  return (y+height-opt.y)/height;
}

void J1DMeterObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int iv = value;
    link.access(JIntegerData(iv));
    setValue(iv);
  } else processColor(n, link);
}

boolean J1DMeterObj::setValue(int _value) {
  _value = max(0, min(mask, _value));
  if (_value != value) {
    oValue = value;
    value = _value;
    condBroadcast(0);
    repaint();
    return true;
  }
  return false;
}

void J1DMeterObj::addButton(JComponent* panel) { 
  addModuleButton(panel, J1DMeterObj(HORIZONTAL));
  addModuleButton(panel, J1DMeterObj(VERTICAL));
}
