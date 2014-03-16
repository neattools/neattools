#include "JFRect.h"
#include "JMath.h"

char* theJFRect = JFRect().Register();
void JFRect::writeContent(JOutputStream& os) {
  JFPoint::writeContent(os);
  putDouble(os, "width", width);
  putDouble(os, "height", height);
}

void JFRect::readContent(JDictionary& dict) {
  JFPoint::readContent(dict);
  width = getDouble(dict, "width");
  height = getDouble(dict, "height");
}

const char* JFRect::className() const { return "JFRect";}
JObject* JFRect::clone() const { return new JFRect(*this);}

int JFRect::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  JFRect &obj = *(JFRect*)&s;
  int result = cmp(y, obj.y);
  if (!result) result = cmp(x, obj.x);
  if (!result) result = cmp(height, obj.height);
  if (!result) result = cmp(width, obj.width);
  return result;
}

JFRect::JFRect() { width = height = 0.0;}

JFRect::JFRect(double _width, double _height)
  : JFPoint() {
  resize(_width, _height);
}

JFRect::JFRect(double _x, double _y, double _width, double _height)
  : JFPoint(_x, _y) {
  resize(_width, _height);
}

JFRect::JFRect(const JFPoint& p)
  : JFPoint(p) {
  width = height = 0.0;
}

JFRect::JFRect(const JFDimension& d)
  : JFPoint() {
  resize(d.width, d.height);
}

JFRect::JFRect(const JFPoint& p, const JFDimension& d)
  : JFPoint(p) {
  resize(d.width, d.height);
}

JFRect::JFRect(const JFPoint& p1, const JFPoint& p2) {
  x = min(p1.x, p2.x);
  y = min(p1.y, p2.y);
  width = max(p1.x, p2.x)-x;
  height = max(p1.y, p2.y)-y;
}

JFPoint JFRect::location() { return JFPoint(x, y);}
JFPoint JFRect::center() { return JFPoint(x+width/2, y+height/2);}
JFDimension JFRect::size() { return JFDimension(width, height);}

boolean JFRect::isEmpty() const { return (width == 0.0) || (height == 0.0);}

boolean JFRect::inside(double _x, double _y) {
  return (_x >= x) && ((_x - x) < width) && (_y >= y) && ((_y-y) < height);
}

boolean JFRect::inside(const JFRect& r) {
  return ((r.x >= x) && (r.y >= y) &&
    (r.x+r.width <= x+width) &&
    (r.y+r.height <= y+height));
}

boolean JFRect::operator&&(const JFRect& r) {
  return (r.x + r.width >= x) && (r.y + r.height >= y) &&
    (r.x <= x + width) && (r.y <= y + height);
}

boolean JFRect::operator||(const JFRect& r) {
  return ((r.x + r.width >= x) || (r.x <= x + width)) &&
    ((r.y + r.height >= y) || (r.y <= y + height));
}

JFRect JFRect::operator&(const JFRect& r) {
  if (isEmpty() || r.isEmpty()) return JFRect();
  double x1 = max(x, r.x);
  double x2 = min(x + width, r.x + r.width);
  double y1 = max(y, r.y);
  double y2 = min(y + height, r.y + r.height);
  if ((x2 <= x1) || (y2 <= y1)) return JFRect();
  return JFRect(x1, y1, x2 - x1, y2 - y1);
}

JFRect JFRect::operator|(const JFRect& r) {
  if (isEmpty()) return r;
  else if (r.isEmpty()) return *this;
  double x1 = min(x, r.x);
  double x2 = max(x + width, r.x + r.width);
  double y1 = min(y, r.y);
  double y2 = max(y + height, r.y + r.height);
  return JFRect(x1, y1, x2 - x1, y2 - y1);
}

JFRect JFRect::operator|(const JFPoint& p) {
  if (isEmpty()) return *this;
  double x1 = min(x, p.x);
  double x2 = max(x + width, p.x);
  double y1 = min(y, p.y);
  double y2 = max(y + height, p.y);
  return JFRect(x1, y1, x2 - x1, y2 - y1);
}

JFRect& JFRect::operator&=(const JFRect& r) {
  if (isEmpty() || r.isEmpty()) {
    reshape(JFRect());
    return *this;
  }
  double x1 = max(x, r.x);
  double x2 = min(x + width, r.x + r.width);
  double y1 = max(y, r.y);
  double y2 = min(y + height, r.y + r.height);
  if ((x2 <= x1) || (y2 <= y1)) {
    reshape(JFRect());
    return *this;
  }
  reshape(x1, y1, x2 - x1, y2 - y1);
  return *this;
}

JFRect& JFRect::operator|=(const JFRect& r) {
  if (isEmpty()) {
    reshape(r);
    return *this;
  } else if (r.isEmpty()) return *this;
  double x1 = min(x, r.x);
  double x2 = max(x + width, r.x + r.width);
  double y1 = min(y, r.y);
  double y2 = max(y + height, r.y + r.height);
  reshape(x1, y1, x2 - x1, y2 - y1);
  return *this;
}

JFRect& JFRect::operator|=(const JFPoint& p) {
  if (isEmpty()) return *this;
  double x1 = min(x, p.x);
  double x2 = max(x + width, p.x);
  double y1 = min(y, p.y);
  double y2 = max(y + height, p.y);
  reshape(x1, y1, x2 - x1, y2 - y1);
  return *this;
}

JFRect& JFRect::reshape(double _x, double _y, double _width, double _height) {
  x = _x;
  y = _y;
  width = _width;
  height = _height;
  return *this;
}

JFRect& JFRect::reshape(JFRect r) 
{ return reshape(r.x, r.y, r.width, r.height);}

JFRect& JFRect::resize(double _width, double _height)
{ return reshape(x, y, _width, _height);}

JFRect& JFRect::resize(JFDimension d)
{ return reshape(x, y, d.width, d.height);}

JFRect& JFRect::normalize() {
  if (width < 0) {
    x+=width;
    width = -width;
  }
  if (height < 0) {
    y+=height;
    height = -height;
  }
  return *this;
}

JFRect& JFRect::growBy(double dx, double dy)
{ return reshape(x-dx, y-dy, width+dx+dx, height+dy+dy);}

JFRect& JFRect::shrinkBy(double dx, double dy) 
{ return reshape(x+dx, y+dy, width-dx-dx, height-dy-dy);}

JFRect JFRect::grow(double dx, double dy)
{ return JFRect(x-dx, y-dy, width+dx+dx, height+dy+dy);}

JFRect JFRect::shrink(double dx, double dy) 
{ return JFRect(x+dx, y+dy, width-dx-dx, height-dy-dy);}

