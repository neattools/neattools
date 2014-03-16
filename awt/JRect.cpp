#include "JRect.h"

char* theJRect = JRect().Register();
void JRect::writeContent(JOutputStream& os) {
  JPoint::writeContent(os);
  putInteger(os, "width", width);
  putInteger(os, "height", height);
}

void JRect::readContent(JDictionary& dict) {
  JPoint::readContent(dict);
  width = getInteger(dict, "width");
  height = getInteger(dict, "height");
}

const char* JRect::className() const { return "JRect";}
int JRect::hashCode() const
{ return (x^(y*37)^(width*43)^(height*47))&hashMask;}
JObject* JRect::clone() const { return new JRect(*this);}

int JRect::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  JRect &obj = *(JRect*)&s;
  int result = y-obj.y;
  if (!result) {
    result = x-obj.x;
    if (!result) {
      result = height-obj.height;
      if (!result) result = width-obj.width;
    }
  }
  return result;
}

JRect::JRect() { width = height = 0;}

JRect::JRect(int _width, int _height)
  : JPoint() {
  resize(_width, _height);
}

JRect::JRect(int _x, int _y, int _width, int _height)
  : JPoint(_x, _y) {
  resize(_width, _height);
}

JRect::JRect(const JPoint& p)
  : JPoint(p) {
  width = height = 0;
}

JRect::JRect(const JDimension& d)
  : JPoint() {
  resize(d.width, d.height);
}

JRect::JRect(const JPoint& p, const JDimension& d)
  : JPoint(p) {
  resize(d.width, d.height);
}

JRect::JRect(const JPoint& p1, const JPoint& p2) {
  x = min(p1.x, p2.x);
  y = min(p1.y, p2.y);
  width = max(p1.x, p2.x)-x;
  height = max(p1.y, p2.y)-y;
}

JPoint JRect::location() { return JPoint(x, y);}
JPoint JRect::center() { return JPoint(x+width/2, y+height/2);}
JDimension JRect::size() { return JDimension(width, height);}

boolean JRect::isEmpty() const { return !width || !height;}

boolean JRect::inside(int _x, int _y) {
  return (_x >= x) && ((_x - x) < width) && (_y >= y) && ((_y-y) < height);
}

boolean JRect::inside(const JRect& r) {
  return ((r.x >= x) && (r.y >= y) &&
    (r.x+r.width <= x+width) &&
    (r.y+r.height <= y+height));
}

boolean JRect::operator&&(const JRect& r) {
  return (r.x+r.width > x) && (r.y+r.height > y) &&
    (r.x < x+width) && (r.y < y+height);
}

boolean JRect::operator||(const JRect& r) {
  return ((r.x+r.width > x) || (r.x < x+width)) &&
    ((r.y+r.height > y) || (r.y < y+height));
}

JRect JRect::operator&(const JRect& r) {
  if (isEmpty() || r.isEmpty()) return JRect();
  int x1 = max(x, r.x);
  int x2 = min(x + width, r.x + r.width);
  int y1 = max(y, r.y);
  int y2 = min(y + height, r.y + r.height);
  if ((x2 <= x1) || (y2 <= y1)) return JRect();
  return JRect(x1, y1, x2 - x1, y2 - y1);
}

JRect JRect::operator|(const JRect& r) {
  if (isEmpty()) return r;
  else if (r.isEmpty()) return *this;
  int x1 = min(x, r.x);
  int x2 = max(x + width, r.x + r.width);
  int y1 = min(y, r.y);
  int y2 = max(y + height, r.y + r.height);
  return JRect(x1, y1, x2 - x1, y2 - y1);
}

JRect JRect::operator|(const JPoint& p) {
  if (isEmpty()) return *this;
  int x1 = min(x, p.x);
  int x2 = max(x + width, p.x);
  int y1 = min(y, p.y);
  int y2 = max(y + height, p.y);
  return JRect(x1, y1, x2 - x1, y2 - y1);
}

JRect& JRect::operator&=(const JRect& r) {
  if (isEmpty() || r.isEmpty()) {
    reshape(JRect());
    return *this;
  }
  int x1 = max(x, r.x);
  int x2 = min(x + width, r.x + r.width);
  int y1 = max(y, r.y);
  int y2 = min(y + height, r.y + r.height);
  if ((x2 <= x1) || (y2 <= y1)) {
    reshape(JRect());
    return *this;
  }
  reshape(x1, y1, x2 - x1, y2 - y1);
  return *this;
}

JRect& JRect::operator|=(const JRect& r) {
  if (isEmpty()) {
    reshape(r);
    return *this;
  } else if (r.isEmpty()) return *this;
  int x1 = min(x, r.x);
  int x2 = max(x + width, r.x + r.width);
  int y1 = min(y, r.y);
  int y2 = max(y + height, r.y + r.height);
  reshape(x1, y1, x2 - x1, y2 - y1);
  return *this;
}

JRect& JRect::operator|=(const JPoint& p) {
  if (isEmpty()) return *this;
  int x1 = min(x, p.x);
  int x2 = max(x + width, p.x);
  int y1 = min(y, p.y);
  int y2 = max(y + height, p.y);
  reshape(x1, y1, x2 - x1, y2 - y1);
  return *this;
}

JRect& JRect::reshape(int _x, int _y, int _width, int _height) {
  x = _x;
  y = _y;
  width = _width;
  height = _height;
  return *this;
}

JRect& JRect::reshape(JRect r) 
{ return reshape(r.x, r.y, r.width, r.height);}

JRect& JRect::resize(int _width, int _height) 
{ return reshape(x, y, _width, _height);}

JRect& JRect::resize(JDimension d) 
{ return reshape(x, y, d.width, d.height);}

JRect& JRect::normalize() {
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

JRect& JRect::growBy(int dx, int dy) 
{ return reshape(x-dx, y-dy, width+dx+dx, height+dy+dy);}

JRect& JRect::shrinkBy(int dx, int dy) 
{ return reshape(x+dx, y+dy, width-dx-dx, height-dy-dy);}

JRect JRect::grow(int dx, int dy) 
{ return JRect(x-dx, y-dy, width+dx+dx, height+dy+dy);}

JRect JRect::shrink(int dx, int dy) 
{ return JRect(x+dx, y+dy, width-dx-dx, height-dy-dy);}

