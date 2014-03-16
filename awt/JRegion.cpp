#include "JRegion.h"
#include "JWindow.hpp"

char* theJRegion = JRegion().Register();
const char* JRegion::className() const { return "JRegion";}
JObject* JRegion::clone() const { return new JRegion(*this);}
JRegion::~JRegion() { Release();}
JRegion::operator int() { return hnd;}

boolean JRegion::operator||(const JRegion& reg)
{ return !(*this | reg) == 0;}
boolean JRegion::operator&&(const JRegion& reg)
{ return !(*this & reg) == 0;}
JRegion& JRegion::operator|=(const JRegion& reg)
{ return (*this = *this | reg);}
JRegion& JRegion::operator&=(const JRegion& reg)
{ return (*this = *this & reg);}
JRegion& JRegion::operator-=(const JRegion& reg)
{ return (*this = *this - reg);}
JRegion& JRegion::operator^=(const JRegion& reg)
{ return (*this = *this ^ reg);}

#if defined(WIN32)

  void JRegion::Delete() {
    DeleteObject((HRGN)hnd);
  }

  int JRegion::Duplicate() {
    HRGN hDest = CreateRectRgn(0, 0, 0, 0);
    CombineRgn(hDest, hDest, (HRGN)hnd, RGN_COPY);
    return (int)hDest;
  }

  JRegion::JRegion() {
    Allocate((int)CreateRectRgn(0, 0, 0, 0));
  }

  JRegion::JRegion(JRect _rect) {
    rect = _rect;
    Allocate((int)CreateRectRgn(rect.x, rect.y,
      rect.x+rect.width, rect.y+rect.height));
  }

  JRegion::JRegion(int x, int y, int width, int height) 
    : rect(x, y, width, height) {
    Allocate((int)CreateRectRgn(x, y, x+width, y+height));
  }

  JRegion::JRegion(int* xs, int *ys, int nPoints) {
    POINT *points = new POINT[nPoints];
    for (int i=nPoints; i-->0;) {
      points[i].x = xs[i];
      points[i].y = ys[i];
    }
    Allocate((int)CreatePolygonRgn(points, nPoints, WINDING));
    delete points;
    rect = calculate();
  }

  boolean JRegion::operator!() 
  { return !rect.width || !rect.height;}

  JRegion JRegion::operator|(const JRegion& reg) {
    JRegion dest;
    CombineRgn((HRGN)dest.hnd, (HRGN)hnd,
      (HRGN)reg.hnd, RGN_OR);
    dest.rect = dest.calculate();
    return dest;
  }

  JRegion JRegion::operator&(const JRegion& reg) {
    JRegion dest;
    CombineRgn((HRGN)dest.hnd, (HRGN)hnd,
      (HRGN)reg.hnd, RGN_AND);
    dest.rect = dest.calculate();
    return dest;
  }

  JRegion JRegion::operator-(const JRegion& reg) {
    JRegion dest;
    CombineRgn((HRGN)dest.hnd, (HRGN)hnd,
      (HRGN)reg.hnd, RGN_DIFF);
    dest.rect = dest.calculate();
    return dest;
  }

  JRegion JRegion::operator^(const JRegion& reg) {
    JRegion dest;
    CombineRgn((HRGN)dest.hnd, (HRGN)hnd,
      (HRGN)reg.hnd, RGN_XOR);
    dest.rect = dest.calculate();
    return dest;
  }

  JRegion::operator JRect() { return rect;}

  JRect JRegion::calculate() { 
    RECT rect;
    HDC hdc = GetDC(null);
    SelectObject(hdc, (HRGN)hnd);
    GetClipBox(hdc, &rect);
    ReleaseDC(null, hdc);
    return JRect(rect.left, rect.top, 
      rect.right-rect.left,
      rect.bottom-rect.top);
  }

#else

  void JRegion::Delete() {
    XDestroyRegion((Region)hnd);
  }

  int JRegion::Duplicate() {
    Region nr = XCreateRegion();
    XUnionRegion((Region)hnd, nr, nr);
    return (int)nr;
  }

  JRegion::JRegion() {
    Allocate((int)XCreateRegion());
  }

  JRegion::JRegion(JRect _rect) {
    rect = _rect;
    XRectangle r = { rect.x, rect.y, rect.width, rect.height};
    Region nr = XCreateRegion();
    XUnionRectWithRegion(&r, nr, nr);
    Allocate((int)nr);
  }

  JRegion::JRegion(int x, int y, int width, int height) 
    : rect(x, y, width, height) {
    XRectangle r = { x, y, width, height};
    Region nr = XCreateRegion();
    XUnionRectWithRegion(&r, nr, nr);
    Allocate((int)nr);
  }

  JRegion::JRegion(int* xs, int *ys, int nPoints) {
    XPoint *points = new XPoint[nPoints];
    for (int i=nPoints; i-->0;) {
      points[i].x = xs[i];
      points[i].y = ys[i];
    }
    Allocate((int)XPolygonRegion(points, nPoints, WindingRule));
    delete points;
    rect = calculate();
  }

  boolean JRegion::operator!() { return XEmptyRegion((Region)hnd) != 0;}

  JRegion JRegion::operator|(const JRegion& reg) {
    JRegion dest;
    XUnionRegion((Region)hnd,
      (Region)reg.hnd, (Region)dest.hnd);
    dest.rect = dest.calculate();
    return dest;
  }

  JRegion JRegion::operator&(const JRegion& reg) {
    JRegion dest;
    XIntersectRegion((Region)hnd,
      (Region)reg.hnd, (Region)dest.hnd);
    dest.rect = dest.calculate();
    return dest;
  }

  JRegion JRegion::operator-(const JRegion& reg) {
    JRegion dest;
    XSubtractRegion((Region)hnd,
      (Region)reg.hnd, (Region)dest.hnd);
    dest.rect = dest.calculate();
    return dest;
  }

  JRegion JRegion::operator^(const JRegion& reg) {
    JRegion dest;
    XXorRegion((Region)hnd,
      (Region)reg.hnd, (Region)dest.hnd);
    dest.rect = dest.calculate();
    return dest;
  }

  JRegion::operator JRect() { return rect;}

  JRect JRegion::calculate() { 
    XRectangle rect;
    XClipBox((Region)hnd, &rect);
    return JRect(rect.x, rect.y, rect.width, rect.height);
  }

#endif


