#include "JLineObj.h"
#include "JFocusSet.h"

char* theJLineObj = JLineObj().Register();
void JLineObj::writeContent(JOutputStream& os) {
  JViewObj::writeContent(os);
  putObject(os, "sp", sp);
  putObject(os, "ep", ep);
}

void JLineObj::readContent(JDictionary& dict) {
  JViewObj::readContent(dict);
  sp = *(JFPoint*)getObject(dict, "sp");
  ep = *(JFPoint*)getObject(dict, "ep");
}

const char* JLineObj::className() const { return "JLineObj";}
JObject* JLineObj::clone() const { return new JLineObj(*this);}
int JLineObj::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  int result = sp.compareTo(((JLineObj*)&s)->sp);
  if (!result) result = ep.compareTo(((JLineObj*)&s)->ep);
  return result;
}

JLineObj::JLineObj() {}

JLineObj::JLineObj(JFPoint& _sp, JFPoint& _ep)
  : sp(_sp), ep(_ep) 
{ reshape(JFRect(sp, ep).grow(delta, delta));}

double JLineObj::getDistance(JFPoint pt) {
  double dx = (ep.x-sp.x);
  double dy = (ep.y-sp.y);
  double dr = (dx*dx+dy*dy);
  if (dr > delta) {
    double t = ((pt.x-sp.x)*dx+(pt.y-sp.y)*dy)/dr;
    if (t < 0.0) return sp.distance(pt);
    else if (t > 1.0) return ep.distance(pt);
    JFPoint kp(t*dx+sp.x, t*dy+sp.y);
    return kp.distance(pt);
  }
  return sp.distance(pt);
}

void JLineObj::nearest(double _x, double _y, double& dmin, JViewObj*& dest) {
  double d = getDistance(JFPoint(_x, _y));
  if (!dest || (d <= dmin)) {
    dmin = d;
    dest = this;
  }
}

void JLineObj::touch(JFRect& r, class JFocusSet& set) {
  JFPoint cp = r.center();
  if (getDistance(cp) <= cp.distance(r)) 
    set.add(*this);
}

void JLineObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  g.drawJLine(getIPoint(sp, dx, dy, scale), 
    getIPoint(ep, dx, dy, scale));

}

JFPoint& JLineObj::translate(double dx, double dy) {
  JViewObj::translate(dx, dy);
  sp.translate(dx, dy);
  ep.translate(dx, dy);
  return *this;
}

void JLineObj::rescale(JFRect& info, double wscale, double hscale) {
  JViewObj::rescale(info, wscale, hscale);
  transform(sp, info, wscale, hscale);
  transform(ep, info, wscale, hscale);
}

