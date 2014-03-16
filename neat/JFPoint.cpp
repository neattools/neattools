#include "JFPoint.h"
#include "JMath.h"

char* theJFPoint = JFPoint().Register();
void JFPoint::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putDouble(os, "x", x);
  putDouble(os, "y", y);
}

void JFPoint::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  x = getDouble(dict, "x");
  y = getDouble(dict, "y");
}

const char* JFPoint::className() const { return "JFPoint";}
JObject* JFPoint::clone() const { return new JFPoint(*this);}

int JFPoint::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  JFPoint& obj = *(JFPoint*)&s;
  int result = cmp(y, obj.y);
  if (!result) result = cmp(x, obj.x);
  return result;
}

JFPoint::JFPoint() { x = y = 0.0;}

JFPoint::JFPoint(double _x, double _y) {
  x = _x;
  y = _y;
}

double JFPoint::distance(JFPoint pt)
{ return (pt.x-x)*(pt.x-x)+(pt.y-y)*(pt.y-y);}

JFPoint& JFPoint::move(double _x, double _y) {
  x = _x;
  y = _y;
  return *this;
}

JFPoint& JFPoint::translate(double dx, double dy) {
  x += dx;
  y += dy;
  return *this;
}
