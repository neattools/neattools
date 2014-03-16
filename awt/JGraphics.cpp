#include "JMath.h"
#include "JGraphics.h"
#include "JComponent.h"
#include "JImage.h"
#include "JWindow.hpp"
#include <string.h>

char* theJGraphics = JGraphics().Register();
const char* JGraphics::className() const { return "JGraphics";}
JObject* JGraphics::clone() const { return new JGraphics(*this);}

JGraphics::JGraphics() { lstyle = SOLID_LINE;}
JGraphics::JGraphics(int handle, boolean ref) :
  JReference(handle, ref) {
  hwnd = -1;
  lstyle = SOLID_LINE;
}

JGraphics::~JGraphics() { Release();}

JGraphics::operator int() const { return hnd;}

void JGraphics::setClipJRect(JRect rect)
{ setClipRect(rect.x, rect.y, rect.width, rect.height);}

JRegion JGraphics::scrollJArea(JRect rect, int dx, int dy)
{ return scrollArea(rect.x, rect.y, rect.width, rect.height, dx, dy);}
JRegion JGraphics::copyJArea(JRect rect, int dx, int dy)
{ return copyArea(rect.x, rect.y, rect.width, rect.height, dx, dy);}
void JGraphics::fillJRect(JRect rect)
{ fillRect(rect.x, rect.y, rect.width, rect.height);}
void JGraphics::drawJRect(JRect rect)
{ drawRect(rect.x, rect.y, rect.width, rect.height);}
void JGraphics::drawJPixel(JPoint pt)
{ drawPixel(pt.x, pt.y);}
void JGraphics::drawJLine(JPoint p1, JPoint p2)
{ drawLine(p1.x, p1.y, p2.x, p2.y);}
void JGraphics::fillJOval(JRect rect)
{ fillOval(rect.x, rect.y, rect.width, rect.height);}
void JGraphics::drawJOval(JRect rect)
{ drawOval(rect.x, rect.y, rect.width, rect.height);}
void JGraphics::fillJArc(JRect rect, int start, int end)
{ fillArc(rect.x, rect.y, rect.width, rect.height, start, end);}
void JGraphics::drawJArc(JRect rect, int start, int end)
{ drawArc(rect.x, rect.y, rect.width, rect.height, start, end);}
void JGraphics::fill3DJRect(JRect rect, int depth)
{ fill3DRect(rect.x, rect.y, rect.width, rect.height, depth);}
void JGraphics::draw3DJRect(JRect rect, int depth)
{ draw3DRect(rect.x, rect.y, rect.width, rect.height, depth);}
void JGraphics::draw3DJTriangle(JRect rect, int depth, int type)
{ draw3DTriangle(rect.x, rect.y, rect.width, rect.height, depth, type);}



#if defined(WIN32)

  JGraphics::JGraphics(int handle, JComponent& jc, boolean ref) :
    JReference(handle, ref) {
    RECT rect;
    hwnd = (int)jc;
    limit.width = jc.width;
    limit.height = jc.height;
    GetClipBox((HDC)hnd, &rect);
    clip = JRect(rect.left, rect.top, 
      rect.right-rect.left,
      rect.bottom-rect.top);
    lstyle = SOLID_LINE;
    SetBkMode((HDC)hnd, TRANSPARENT);
    setJFont(jc.getJFont());
  }

  JGraphics::JGraphics(int handle, JImage& ji, boolean ref) :
    JReference(handle, ref) {
    hwnd = -1;
    limit.width = ji.getWidth();
    limit.height = ji.getHeight();
    clip = limit;
    lstyle = SOLID_LINE;
    SetBkMode((HDC)hnd, TRANSPARENT);
    SelectObject((HDC)hnd, (HBITMAP)(int)ji);
  }

  void JPen::Delete() {
    DeleteObject((HPEN)hnd);
  }
  int JPen::Duplicate() {
    LOGPEN lp;
    GetObject((HPEN)hnd, sizeof(LOGPEN), &lp);
    return (int)CreatePenIndirect(&lp);
  }

  const char* JPen::className() const { return "JPen";}
  JObject* JPen::clone() const { return new JPen(*this);}
  JPen::JPen() {}
  JPen::JPen(int handle, boolean ref)
    : JReference(handle, ref) {}
  JPen::JPen(JColor c, int style, int width)
    : JReference((int)CreatePen(style, width, (int)c), true) {}
  JPen::~JPen() { Release();}
  JPen::operator int() const { return hnd;}

  void JBrush::Delete() { DeleteObject((HBRUSH)hnd);}
  int JBrush::Duplicate() {
    LOGBRUSH lb;
    GetObject((HBRUSH)hnd, sizeof(LOGBRUSH), &lb);
    return (int)CreateBrushIndirect(&lb);
  }

  const char* JBrush::className() const { return "JBrush";}
  JObject* JBrush::clone() const { return new JBrush(*this);}
  JBrush::JBrush() {}
  JBrush::JBrush(int handle, boolean ref)
    : JReference(handle, ref) {}
  JBrush::JBrush(JColor c)
    : JReference((int)CreateSolidBrush((int)c), true) {}
  JBrush::~JBrush() { Release();}
  JBrush::operator int() const { return hnd;}

  JBrush JGraphics::nullBrush((int)GetStockObject(NULL_BRUSH));

  int JGraphics::Duplicate() {
    return (hwnd == -1) ? 
      (int)CreateCompatibleDC((HDC)hnd) :
      (int)GetDC((HWND)hwnd);
  }

  void JGraphics::Delete() {
    if (hwnd == -1) DeleteDC((HDC)hnd);
    else ReleaseDC((HWND)hwnd, (HDC)hnd);
  }

  void JGraphics::translate(int x, int y) { 
    SetWindowOrgEx((HDC)hnd, x, y, null);
    clip.x += (ofs.x = x);
    clip.y += (ofs.y = y);
  }

  void JGraphics::setLineStyle(int _lstyle) {
    if (lstyle != _lstyle) {
      lstyle = _lstyle;
      forePen = JPen(getJColor(), 
	((lstyle == SOLID_LINE) ? PS_SOLID : PS_DOT));
    }
  }

  void JGraphics::setJColor(JColor c) {
    HDC hdc = (HDC)hnd;
    SetTextColor(hdc, (COLORREF)c.getRGB());
    forePen = JPen(c, 
      ((lstyle == SOLID_LINE) ? PS_SOLID : PS_DOT));
    foreBrush = JBrush(c);
  }

  JColor JGraphics::getJColor() {
    return JColor((int)GetTextColor((HDC)hnd));
  }

  void JGraphics::setJFont(JFont f) { font=f;}

  JFont JGraphics::getJFont() { return font;}

  void JGraphics::setPaintMode() {
    SetROP2((HDC)hnd, R2_COPYPEN);
  }

  void JGraphics::setXORMode(JColor c) {
    setJColor(c);
    SetROP2((HDC)hnd, R2_XORPEN);
  }

  JRect JGraphics::getClipJRect() { return clip;}

  void JGraphics::setClipRect(int x, int y, int width, int height)
  { setJRegion(JRegion(x, y, width, height));}

  void JGraphics::setJRegion(JRegion rgn) { 
    clip = (JRect)rgn;
    SelectClipRgn((HDC)hnd, (HRGN)(int)rgn);
    if (ofs.x || ofs.y)
      OffsetClipRgn((HDC)hnd, -ofs.x, -ofs.y);
  }

  JRegion JGraphics::scrollArea(int x, int y,
    int width, int height, int dx, int dy) {
    JRegion rgn;
    RECT rect = { x, y, x+width, y+height};
    ScrollDC((HDC)hnd, dx, dy, &rect, &rect, (HRGN)(int)rgn, null);
    return rgn;
  }

  JRegion JGraphics::copyArea(int x, int y,
    int width, int height, int dx, int dy) {
    if (dx < 0) {
      x+=dx;
      width-=dx;
    } else width+=dx;
    if (dy < 0) {
      y+=dy;
      height-=dy;
    } else height+=dy;
    return scrollArea(x, y, width, height, dx, dy);
  }

  void JGraphics::drawPixel(int x, int y) {
    SetPixel((HDC)hnd, x, y, GetTextColor((HDC)hnd));
  }

  /* Include the Last Point */
  void JGraphics::drawLine(int x1, int y1, int x2, int y2) {
    if (x1 > 2000) x1 = 2000;
    if (x2 > 2000) x2 = 2000;
    HDC hdc = (HDC)hnd;
    HPEN hPen = (HPEN)SelectObject(hdc, (HPEN)(int)forePen);
    POINT points[2] = {{x1, y1}, {x2, y2}};
    Polyline(hdc, points, 2);
    SelectObject(hdc, hPen);
  }

  void JGraphics::fillRect(int x, int y, int width, int height) {
    HDC hdc = (HDC)hnd;
    HBRUSH hBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)(int)foreBrush);
    PatBlt(hdc, x, y, width, height,
      (GetROP2(hdc) == R2_XORPEN) ? PATINVERT : PATCOPY);
    SelectObject(hdc, hBrush);
  }

  void JGraphics::drawRect(int x, int y, int width, int height) {
    HDC hdc = (HDC)hnd;
    HPEN hPen = (HPEN)SelectObject(hdc, (HPEN)(int)forePen);
    HBRUSH hBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)(int)nullBrush);
    Rectangle(hdc, x, y, x+width, y+height);
    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);
  }

  void JGraphics::fillOval(int x, int y, int width, int height) {
    HDC hdc = (HDC)hnd;
    HPEN hPen = (HPEN)SelectObject(hdc, (HPEN)(int)forePen);
    HBRUSH hBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)(int)foreBrush);
    Ellipse(hdc, x, y, x+width, y+height);
    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);
  }

  void JGraphics::drawOval(int x, int y, int width, int height) {
    HDC hdc = (HDC)hnd;
    HPEN hPen = (HPEN)SelectObject(hdc, (HPEN)(int)forePen);
    HBRUSH hBrush = (HBRUSH)SelectObject(hdc, (HPEN)(int)nullBrush);
    Ellipse(hdc, x, y, x+width, y+height);
    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);
  }

  void JGraphics::fillArc(int x, int y, int width, int height,
    int start, int end) {
    HDC hdc = (HDC)hnd;
    HPEN hPen = (HPEN)SelectObject(hdc, (HPEN)(int)forePen);
    HBRUSH hBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)(int)foreBrush);
    int factor = 180 << 5;
    int cx = x+width/2-1;
    int cy = y+height/2-1;
    double a1 = JMath::pi*start/factor;
    double a2 = a1+JMath::pi*end/factor;
    Pie(hdc, x, y, x+width, y+height, 
      cx+(int)(JMath::cos(a1)*width), 
      cy+(int)(JMath::sin(a1)*height), 
      cx+(int)(JMath::cos(a2)*width), 
      cy+(int)(JMath::sin(a2)*height));
    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);
  }

  void JGraphics::drawArc(int x, int y, int width, int height,
    int start, int end) {
    HDC hdc = (HDC)hnd;
    HPEN hPen = (HPEN)SelectObject(hdc, (HPEN)(int)forePen);
    int factor = 180<<6;
    int cx = x+width/2-1;
    int cy = y+height/2-1;
    double a1 = JMath::pi*start/factor;
    double a2 = a1+JMath::pi*end/factor;
    Arc(hdc, x, y, x+width, y+height, 
      cx+(int)(JMath::cos(a1)*width), 
      cy+(int)(-JMath::sin(a1)*height),
      cx+(int)(JMath::cos(a2)*width),
      cy+(int)(-JMath::sin(a2)*height));
    SelectObject(hdc, hPen);
  }

  void JGraphics::fillPolygon(int *xs, int *ys, int nPoints) {
    HDC hdc = (HDC)hnd;
    HPEN hPen = (HPEN)SelectObject(hdc, (HPEN)(int)forePen);
    HBRUSH hBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)(int)foreBrush);
    POINT *points = new POINT[nPoints];
    for (int i=nPoints; i-->0;) {
      points[i].x = xs[i];
      points[i].y = ys[i];
    }
    Polygon(hdc, points, nPoints);
    Polyline(hdc, points, nPoints);
    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);
    delete points; 
  }

  void JGraphics::drawPolygon(int *xs, int *ys, int nPoints) {
    HDC hdc = (HDC)hnd;
    HPEN hPen = (HPEN)SelectObject(hdc, (HPEN)(int)forePen);
    POINT *points = new POINT[nPoints];
    for (int i=nPoints; i-->0;) {
      points[i].x = xs[i];
      points[i].y = ys[i];
    }
    Polyline(hdc, points, nPoints);
    SelectObject(hdc, hPen);
    delete points; 
  }

  void JGraphics::drawJString(JString s, int x, int y) {
    HDC hdc = (HDC)hnd;
    HFONT hFont = (HFONT)SelectObject(hdc, (HFONT)(int)font);
    TextOut(hdc, x, y, (char*)s, s.length());
    SelectObject(hdc, hFont);
  }

  void JGraphics::drawJImage(JImage b, int x, int y) {
    JGraphics mdc = b.getJGraphics();
    BitBlt((HDC)hnd, x, y, b.getWidth(), b.getHeight(),
      (HDC)(int)mdc, 0, 0, SRCCOPY);
  }

  void JGraphics::drawJImage(JImage b, int x, int y, int w, int h) {
    JGraphics mdc = b.getJGraphics();
    StretchBlt((HDC)hnd, x, y, w, h,
      (HDC)(int)mdc, 0, 0, 
      b.getWidth(), b.getHeight(), 
      SRCCOPY);
  }

#else

  JGraphics::JGraphics(int handle, JComponent& jc, boolean ref) :
    JReference(handle, ref) {
    hwnd = (int)jc;
    limit.width = jc.width;
    limit.height = jc.height;
    clip = limit;
    lstyle = SOLID_LINE;
    XSetLineAttributes(JUNIX::theDisplay,
      (GC)hnd, 0, LineSolid, CapButt, JoinMiter);
    setJFont(jc.getJFont());
  }

  JGraphics::JGraphics(int handle, JImage& ji, boolean ref) :
    JReference(handle, ref) {
    hwnd = (int)ji;
    limit.width = ji.getWidth();
    limit.height = ji.getHeight();
    clip = limit;
    lstyle = SOLID_LINE;
    XSetLineAttributes(JUNIX::theDisplay,
      (GC)hnd, 0, LineSolid, CapButt, JoinMiter);
  }

  int JGraphics::Duplicate() {
    return (int)XCreateGC(JUNIX::theDisplay, (Window)hwnd, 0, null);
  }

  void JGraphics::Delete() {
    XFreeGC(JUNIX::theDisplay, (GC)hnd);
  }

  void JGraphics::translate(int x, int y) {
    clip.x += (ofs.x = x);
    clip.y += (ofs.y = y);
  }

  void JGraphics::setLineStyle(int _lstyle) {
    if (lstyle != _lstyle) {
      lstyle = _lstyle;
      XSetLineAttributes(JUNIX::theDisplay, 
	(GC)hnd, 0, 
	((lstyle == SOLID_LINE) ? LineSolid : LineOnOffDash),
	CapButt, JoinMiter);
    }
  }

  void JGraphics::setJColor(JColor c) {
    XSetForeground(JUNIX::theDisplay, (GC)hnd, c.getPixel());
  }

  JColor JGraphics::getJColor() {
    JColor result;
    XGCValues xgcv;
    XGetGCValues(JUNIX::theDisplay, (GC)hnd, GCForeground, &xgcv);
    result.setPixel(xgcv.foreground);
    return result;
  }

  void JGraphics::setJFont(JFont f) {
    XSetFont(JUNIX::theDisplay, (GC)hnd, (Font)(int)(font=f));
  }

  JFont JGraphics::getJFont() { return font;}

  void JGraphics::setPaintMode() {
    XSetFunction(JUNIX::theDisplay, (GC)hnd, GXcopy);
  }

  void JGraphics::setXORMode(JColor c) {
    XSetForeground(JUNIX::theDisplay, (GC)hnd, c.getPixel());
    XSetFunction(JUNIX::theDisplay, (GC)hnd, GXxor);
  }

  JRect JGraphics::getClipJRect() { return clip;}

  void JGraphics::setClipRect(int x, int y, int width, int height) 
  { setJRegion(JRegion(JRect(x, y, width, height) & limit));}

  void JGraphics::setJRegion(JRegion rgn) {
    clip = (JRect)rgn;
    XSetRegion(JUNIX::theDisplay, (GC)hnd,
      (Region)(int)rgn);
  }

  class JEventCell : public JObject {
    public:
      JEventCell(XEvent _event);
      XEvent event;
  };
          
  extern void waitGraphicsExpose(int handle);

  JRegion JGraphics::scrollArea(int x, int y,
    int width, int height, int dx, int dy) {
    if (dx < 0) {
      x-=dx;
      width+=dx;
    } else width-=dx;
    if (dy < 0) {
      y-=dy;
      height+=dy;
    } else height-=dy;
    return copyArea(x, y, width, height, dx, dy);
  }

  JRegion JGraphics::copyArea(int x, int y,
    int width, int height, int dx, int dy) {
    JRegion dest(x+dx, y+dy, width, height);
    XCopyArea(JUNIX::theDisplay, hwnd, hwnd, (GC)hnd, 
      x, y, width, height, x+dx, y+dy);
    if (dx < 0) {
      x+=dx;
      width-=dx;
    } else width+=dx;
    if (dy < 0) {
      y+=dy;
      height-=dy;
    } else height+=dy;
    waitGraphicsExpose(hwnd);
    return JRegion(x, y, width, height)-dest;
  }

  void JGraphics::drawPixel(int x, int y) {
    XDrawPoint(JUNIX::theDisplay, (Window)hwnd, (GC)hnd, 
      x, y);
  }

  void JGraphics::drawLine(int x1, int y1, int x2, int y2) {
    XDrawLine(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      x1, y1, x2, y2);
  }

  void JGraphics::fillRect(int x, int y, int width, int height) {
    XFillRectangle(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      x, y, width, height);
  }

  void JGraphics::drawRect(int x, int y, int width, int height) {
    if ((width < 1) || (height < 1)) return;
    XDrawRectangle(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      x, y, width-1, height-1);
  }

  void JGraphics::fillOval(int x, int y, int width, int height) {
    XFillArc(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      x, y, width, height, 0, 360*64);
  }

  void JGraphics::drawOval(int x, int y, int width, int height) {
    if ((width < 1) || (height < 1)) return;
    XDrawArc(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      x, y, width-1, height-1, 0, 360*64);
  }

  void JGraphics::fillArc(int x, int y, int width, int height,
    int start, int end) {
    XFillArc(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      x, y, width, height, start, end);
  }

  void JGraphics::drawArc(int x, int y, int width, int height,
    int start, int end) {
    if ((width < 1) || (height < 1)) return;
    XDrawArc(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      x, y, width-1, height-1, start, end);
  }

  void JGraphics::fillPolygon(int *xs, int *ys, int nPoints) {
    XPoint *points = new XPoint[nPoints];
    for (int i=nPoints; i-->0;) {
      points[i].x = xs[i];
      points[i].y = ys[i];
    }
    XFillPolygon(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      points, nPoints, Complex, CoordModeOrigin); 
    XDrawLines(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      points, nPoints, CoordModeOrigin);
    delete points; 
  }

  void JGraphics::drawPolygon(int *xs, int *ys, int nPoints) {
    XPoint *points = new XPoint[nPoints];
    for (int i=nPoints; i-->0;) {
      points[i].x = xs[i];
      points[i].y = ys[i];
    }
    XDrawLines(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      points, nPoints, CoordModeOrigin);
    delete points; 
  }

  void JGraphics::drawJString(JString s, int x, int y) {
    XDrawString(JUNIX::theDisplay, (Window)hwnd, (GC)hnd, 
      x, y+((XFontStruct*)font.getInfo())->ascent, 
      (char*)s, s.length());
  }

  void JGraphics::drawJImage(JImage b, int x, int y) { 
    XCopyArea(JUNIX::theDisplay, 
      (Window)(int)b, (Window)hwnd, 
      (GC)hnd, 0, 0, b.getWidth(), b.getHeight(), x, y);
  }

  void JGraphics::drawJImage(JImage b, int x, int y, int w, int h) {
/*
    XImage *src = XGetImage(JUNIX::theDisplay, 
      (Window)(int)b, 0, 0, w, h,
      AllPlanes, ZPixmap);
    XPutImage(JUNIX::theDisplay, (Window)hwnd, (GC)hnd,
      src, 0, 0, x, y, w, h);
*/
  }

#endif

void JGraphics::draw3DRect(int x, int y, int width, int height, 
  int depth) {
  if (!depth) return;
  boolean raise = (depth > 0);
  int delta = (raise ? depth : -depth)-1;
  if ((delta >= width/2) || (delta >=height/2)) {
    delta = min(width/2, height/2);
    if (!delta) return;
  }
  JColor c = getJColor();
  int right = x+width-1;
  int bottom = y+height-1;
  int xu[] = { x, right, right-delta, x+delta, x};
  int xl[] = { x, x, x+delta, x+delta, x};
  int xd[] = { x, right, right-delta, x+delta, x};
  int xr[] = { right, right, right-delta, right-delta, right};
  int yu[] = { y, y, y+delta, y+delta, y};
  int yl[] = { y, bottom, bottom-delta, y+delta, y};
  int yd[] = { bottom, bottom, bottom-delta, bottom-delta, bottom};
  int yr[] = { y, bottom, bottom-delta, y+delta, y};
  JColor bright = c.brighter();
  JColor dark = c.darker();
  setJColor(raise ? bright : dark);
  fillPolygon(xu, yu, 5);
  setJColor(raise ? dark : bright);
  fillPolygon(xd, yd, 5);
  fillPolygon(xr, yr, 5);
  setJColor(raise ? bright : dark);
  fillPolygon(xl, yl, 5);
  setJColor(c);
}

void JGraphics::fill3DRect(int x, int y, int width, int height, 
  int depth) {
  if (!depth) {
    fillRect(x, y, width, height);
    return;
  }
  int delta = ((depth > 0) ? depth : -depth);
  if ((delta > width/2) || (delta > height/2)) {
    delta = min(width/2, height/2);
    if (!delta) {
      fillRect(x, y, width, height);
      return;
    }
  }
  draw3DRect(x, y, width, height, depth);
  fillRect(x+delta, y+delta, 
    width-delta-delta, height-delta-delta);
}

void JGraphics::draw3DTriangle(int x, int y, int width, int height, 
  int depth, int type) {
  if (!depth) return;
  boolean raise = (depth > 0);
  int delta = (raise ? depth : -depth)-1;
  if ((delta >= width/2) || (delta >=height/2)) {
    delta = min(width/2, height/2);
    if (!delta) return;
  }
  JColor c = getJColor();
  int xm = x+width/2;
  int ym = y+height/2;
  int right = x+width-1;
  int bottom = y+height-1;
  JColor LT, RB;
  if (raise) {
    LT = c.brighter();
    RB = c.darker();
  } else {
    LT = c.darker();
    RB = c.brighter();
  }
  switch (type) {
    case LEFT: {
      int x1[] = { right, right, right-delta, right-delta, right};
      int x2[] = { x, right, right-delta, x+delta, x};
      int x3[] = { x, right, right-delta, x+delta, x};
      int y1[] = { y, bottom, bottom-delta, y+delta, y};
      int y2[] = { ym, bottom, bottom-delta, ym, ym};
      int y3[] = { ym, y, y+delta, ym, ym};
      setJColor(RB);
      fillPolygon(x1, y1, 5);
      fillPolygon(x2, y2, 5);
      setJColor(LT);
      fillPolygon(x3, y3, 5);
      break;
    }
    case RIGHT: {
      int x1[] = { right, x, x+delta, right-delta, right};
      int x2[] = { x, x+delta, x+delta, x, x};
      int x3[] = { right, x, x+delta, right-delta, right};
      int y1[] = { ym, y, y+delta, ym, ym};
      int y2[] = { y, y+delta, bottom-delta, bottom, y};
      int y3[] = { ym, bottom, bottom-delta, ym, ym};
      setJColor(LT);
      fillPolygon(x1, y1, 5);
      fillPolygon(x2, y2, 5);
      setJColor(RB);
      fillPolygon(x3, y3, 5);
      break;
    }
    case UP: {
      int x1[] = { x, right, right-delta, x+delta, x};
      int x2[] = { xm, right, right-delta, xm, xm};
      int x3[] = { xm, x, x+delta, xm, xm};
      int y1[] = { bottom, bottom, bottom-delta, bottom-delta, bottom};
      int y2[] = { y, bottom, bottom-delta, y+delta, y};
      int y3[] = { y, bottom, bottom-delta, y+delta, y};
      setJColor(RB);
      fillPolygon(x1, y1, 5);
      fillPolygon(x2, y2, 5);
      setJColor(LT);
      fillPolygon(x3, y3, 5);
      break;
    }
    case DOWN: {
      int x1[] = { x, right, right-delta, x+delta, x};
      int x2[] = { x, xm, xm, x+delta, x};
      int x3[] = { right, xm, xm, right-delta, right};
      int y1[] = { y, y, y+delta, y+delta, y};
      int y2[] = { y, bottom, bottom-delta, y+delta, y};
      int y3[] = { y, bottom, bottom-delta, y+delta, y};
      setJColor(LT);
      fillPolygon(x1, y1, 5);
      fillPolygon(x2, y2, 5);
      setJColor(RB);
      fillPolygon(x3, y3, 5);
      break;
    }
  }
  setJColor(c);
}

