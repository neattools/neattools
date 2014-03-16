#include "J1DMObj.h"
#include "JIntegerProperty.h"
#include "JColorProperty.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JColorData.h"

char* theJ1DMObj = J1DMObj().Register();

void J1DMObj::writeContent(JOutputStream& os) {
     JNBitsObj::writeContent(os);
     putInteger(os, "v0", v[0]);
     putInteger(os, "v1", v[1]);
     putInteger(os, "ov0", ov[0]);
     putInteger(os, "ov1", ov[1]);
}

void J1DMObj::readContent(JDictionary& dict) {
     JNBitsObj::readContent(dict);
     pv[0] = v[0] = getInteger(dict, "v0");
     pv[1] = v[1] = getInteger(dict, "v1");
     ov[0] = getInteger(dict, "ov0");
	 ov[1] = getInteger(dict, "ov1");
}

const char* J1DMObj::className() const { return "J1DMObj";}

JObject* J1DMObj::clone() const { return new J1DMObj(*this);}

J1DMObj::J1DMObj() { 
     igm = 4;
     ogm = 2;
     color = JColor::yellow.darker(); 
     bkgnd = JColor::cyan.darker(); 
     pv[0] = pv[1] = v[0] = v[1] = ov[0] = ov[1] = 0;
}

void J1DMObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
     JRect rect = getIExtent(dx, dy, scale);
     g.setJColor(moduleColor);
     if ((rect.width > depth2) && (rect.height > depth2)) {
          g.draw3DJRect(rect, depth);
          g.fillJRect(rect.shrinkBy(depth, depth));
//          g.draw3DJRect(rect.shrink(depth, depth), -1);
	 } else g.fillJRect(rect);
     update(g, dx, dy, rgn, scale);
}

void J1DMObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
     JRect frect = getIExtent(dx, dy, scale);
     JRect rect = frect.shrink(depth, depth);
     if ((rect.width > 0) && (rect.height > 0)) {
          g.setJRegion(rgn & rect);

/*  module refresh
          g.setJRegion(rgn);
		  g.setJColor(moduleColor);
		  g.draw3DJRect(rect, depth);
		  g.fillJRect(rect.shrinkBy(depth, depth));
		  g.setJRegion(rgn & rect);
		  g.setJColor(color);
*/
          v[0] = max(0, min(mask, v[0]));
          v[1] = max(0, min(mask, v[1]));
		  int xpos =  v[0]*(rect.width-depth)/mask;
          int ypos =  v[1]*(rect.height-depth)/mask;

		  g.setJColor(color);
          g.drawLine(rect.x+xpos, rect.y+ypos, rect.x+xpos+1, 
			         rect.y+ypos+1);
	 }
}

boolean J1DMObj::cond(int n, JLinkObj& link) { 
     double pos = link.pos*mask;
     return (ov[n] > pos) != (v[n] > pos);
}

int J1DMObj::inputType(int n) 
{ return (n<2) ? JIntegerData::id : JColorData::id;}

void J1DMObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = (v[n] > (link.pos*mask)) ? mask : 0;}

JString J1DMObj::inputTag(int n) { 
     char* tag[] = { "x-in", "y-in", "color", "background"};
     if (n < 2) return JString(tag[n])+NBTag();
     return tag[n];
}

JString J1DMObj::outputTag(int n) { 
     char* tag[] = { "x-out", "y-out"};
     return JString(tag[n])+NBTag();
}

boolean J1DMObj::inputAllowed(int n)
{ return (boolean)((n < 2) ? true : !inputSet(n).last());}

JFRect J1DMObj::inputArea(int n) { 
    if (n<2) return leftArea(n, 0, 2);
    return topArea(n, 2, 2);
}

JFRect J1DMObj::outputArea(int n) { 
    if (!n) return bottomArea(n, 0, 1, 0, 1);
    return rightArea(n, 1, 1, 0, 1);
}

int J1DMObj::inputFace(int n) 
{ return (n<2) ? LEFT : TOP;}

int J1DMObj::outputFace(int n) 
{ return (!n) ? BOTTOM : RIGHT;}

JFPoint J1DMObj::inputPoint(int n, JLinkObj& link) { 
     if (n < 2) return leftPoint(n, link, 0, 2);
     return topPoint(n, link, 2, 2);
}

JFPoint J1DMObj::outputPoint(int n, JLinkObj& link) { 
     if (!n) return JFPoint(x+link.pos*width, y+height);
     return JFPoint(x+width, y+(1.0-link.pos)*height);
}

double J1DMObj::outputPos(int n, JFPoint opt) { 
     if (!n) return (opt.x-x)/width;
	 return (y+height-opt.y)/height;
}

void J1DMObj::engine(int n, JLinkObj& link) {
     if (n < 2) {
          int iv = v[n];
          link.access(JIntegerData(iv));
          setNValue(n, iv);
	 } else processColor(n, link, -1);
}

JArray J1DMObj::getProperties() {
     JArray properties = JModuleObj::getProperties();
     properties.append(JIntegerProperty("vx", v[0], 0, mask));
     properties.append(JIntegerProperty("vy", v[1],  0, mask));
     properties.append(JColorProperty("color", color));
     properties.append(JColorProperty("bkgnd", bkgnd));
     return properties;
}

boolean J1DMObj::updateProperty(JProperty& prop) {
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

boolean J1DMObj::setNValue(int n, int _value) {
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



















