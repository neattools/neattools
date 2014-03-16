#if !defined( _JGraphics_h )
#define _JGraphics_h

#include "JReference.h"
#include "JFont.h"
#include "JColor.h"
#include "JRect.h"
#include "JRegion.h"

#if defined(WIN32)
  class
  #include "JAWT.hpp"
  JPen : public JReference {
    protected:
      virtual void Delete();
      virtual int Duplicate();
    public:
      virtual const char* className() const;
      virtual JObject* clone() const;
      JPen();
      JPen(int handle, boolean ref=false);
      JPen(JColor c, int style, int width = 0);
      ~JPen();
      operator int() const;
  };

  class
  #include "JAWT.hpp"
  JBrush : public JReference {
    protected:
      virtual void Delete();
      virtual int Duplicate();
    public:
      virtual const char* className() const;
      virtual JObject* clone() const;
      JBrush();
      JBrush(int handle, boolean ref=false);
      JBrush(JColor c);
      ~JBrush();
      operator int() const;
  };

#endif

class
#include "JAWT.hpp"
JGraphics : public JReference {
  public:
    enum { SOLID_LINE, DASH_LINE};
    enum { LEFT, RIGHT, UP, DOWN};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JGraphics();
    JGraphics(int handle, boolean ref = true);
    JGraphics(int handle, class JComponent& jc, boolean ref = true);
    JGraphics(int handle, class JImage& ji, boolean ref = true);
    virtual ~JGraphics();
    operator int() const;
    void translate(int x, int y);
    void setLineStyle(int _lstyle);
    void setJColor(JColor c);
    JColor getJColor();
    void setJFont(JFont f);
    JFont getJFont();
    void setPaintMode();
    void setXORMode(JColor c);
    JRect getClipJRect();
    void setClipJRect(JRect rect);
    void setClipRect(int x, int y, int width, int height);
    void setJRegion(JRegion rgn);
    JRegion scrollJArea(JRect rect, int dx, int dy);
    JRegion scrollArea(int x, int y, int width, int height, int dx, int dy);
    JRegion copyJArea(JRect rect, int dx, int dy);
    JRegion copyArea(int x, int y, int width, int height, int dx, int dy);
    void drawJPixel(JPoint pt);
    void drawPixel(int x, int y);
    void drawJLine(JPoint p1, JPoint p2);
    void drawLine(int x1, int y1, int x2, int y2);
    void fillJRect(JRect rect);
    void fillRect(int x, int y, int width, int height);
    void drawJRect(JRect rect);
    void drawRect(int x, int y, int width, int height);
    void fillJOval(JRect rect);
    void fillOval(int x, int y, int width, int height);
    void drawJOval(JRect rect);
    void drawOval(int x, int y, int width, int height);
    void fillJArc(JRect rect, int start, int end);
    void fillArc(int x, int y, int width, int height, int start, int end);
    void drawJArc(JRect rect, int start, int end);
    void drawArc(int x, int y, int width, int height, int start, int end);
    void fillPolygon(int *xs, int *ys, int nPoints);
    void drawPolygon(int *xs, int *ys, int nPoints);
    void draw3DJRect(JRect rect, int depth);
    void draw3DRect(int x, int y, int width, int height, int depth);
    void fill3DJRect(JRect rect, int depth);
    void fill3DRect(int x, int y, int width, int height, int depth);
    void draw3DJTriangle(JRect rect, int depth, int type);
    void draw3DTriangle(int x, int y, int width, int height, int depth, int type);
    void drawJString(JString s, int x, int y);
    void drawJImage(class JImage b, int x, int y);
    void drawJImage(class JImage b, int x, int y, int w, int h);
  protected:
    int hwnd;
    int lstyle;
    JPoint ofs;
    JFont font;
    JRect clip;
    JRect limit;
#if defined(WIN32)
    JPen forePen;
    JBrush foreBrush;
    static JBrush nullBrush;
#endif
    virtual void Delete();
    virtual int Duplicate();
};

#endif
