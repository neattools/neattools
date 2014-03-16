#include "JPoint.h"

char* theJPoint = JPoint().Register();
void JPoint::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putInteger(os, "x", x);
  putInteger(os, "y", y);
}

void JPoint::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  x = getInteger(dict, "x");
  y = getInteger(dict, "y");
}

const char* JPoint::className() const { return "JPoint";}
int JPoint::hashCode() const { return (x^(y*31))&hashMask;}
JObject* JPoint::clone() const { return new JPoint(*this);}

int JPoint::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  int result = y-((JPoint*)&s)->y;
  if (!result) result = x-((JPoint*)&s)->x;
  return result;
}

JPoint::JPoint() { x = y = 0;}

JPoint::JPoint(int _x, int _y) {
  x = _x;
  y = _y;
}

int JPoint::distance(JPoint pt)
{ return (pt.x-x)*(pt.x-x)+(pt.y-y)*(pt.y-y);}

JPoint& JPoint::move(int _x, int _y) {
  x = _x;
  y = _y;
  return *this;
}

JPoint& JPoint::translate(int dx, int dy) {
  x += dx;
  y += dy;
  return *this;
}
