#include "JGuideObj.h"
#include "JMath.h"
#include "JDouble.h"

char* theJGuideObj = JGuideObj().Register();
void JGuideObj::writeContent(JOutputStream& os) {
  JViewObj::writeContent(os);
  putInteger(os, "type", type);
}

void JGuideObj::readContent(JDictionary& dict) {
  JViewObj::readContent(dict);
  type = getInteger(dict, "type");
}


const char* JGuideObj::className() const { return "JGuideObj";}
JObject* JGuideObj::clone() const { return new JGuideObj(*this);}
int JGuideObj::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  JGuideObj& obj = *(JGuideObj*)&s;
  int result = type-obj.type;
  if (!result) {
    if (type == HORIZONTAL)
      result = cmp(y, obj.y);
    else result = cmp(x, obj.x);
  }
  return result;
}

JGuideObj::JGuideObj() { type = HORIZONTAL;}

JGuideObj::JGuideObj(int _type, double pos, 
  double vmin, double vmax) {
  type = _type;
  if (type == HORIZONTAL)
    reshape(vmin, pos, vmax-vmin, delta);
  else reshape(pos, vmin, delta, vmax-vmin);
}

#include "JInteger.h"
#include "JComponent.h"
int count = 0;

void JGuideObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  if (type == HORIZONTAL) {
    int kp = JMath::round((y+dy)*scale);
    g.drawLine(JMath::round((x+dx)*scale), kp,
      JMath::round((x+width+dx)*scale), kp);
  } else {
    int kp = JMath::round((x+dx)*scale);
    g.drawLine(kp, JMath::round((y+dy)*scale),
      kp, JMath::round((y+height+dy)*scale));
  }
}

JFPoint& JGuideObj::translate(double dx, double dy) {
  if (type == HORIZONTAL) y+=dy;
  else x+=dx;
  return *this;
}

void JGuideObj::rescale(JFRect& info, double wscale, double hscale) {
  if (type == HORIZONTAL) 
    transform(y, info, wscale, hscale);
  else transform(x, info, wscale, hscale);
}

JString JGuideObj::info() {
  if (type == HORIZONTAL) {
    return JString("Horz")+
      (className()+1)+": Y="+
      JDouble::toJStringF(y)+".";
  } else {
    return JString("Vert")+
      (className()+1)+": X="+
      JDouble::toJStringF(x)+".";
  }
}

