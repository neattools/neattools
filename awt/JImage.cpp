#include "JImage.h"
#include "JComponent.h"
#include "JWindow.hpp"

char* theJImage = JImage().Register();
const char* JImage::className() const { return "JImage";}
JObject* JImage::clone() const { return new JImage(*this);}
JImage::JImage() { width = height = 0;}
JImage::JImage(int _width, int _height) 
{ width = _width; height = _height;}

JImage::~JImage() { Release();}
boolean JImage::isValid() { return ((int)*this) != null;}
int JImage::getWidth() { return width;}
int JImage::getHeight() { return height;}

JGraphics JImage::getJGraphics(JComponent& c) { 
  JGraphics g = getJGraphics();
  g.setClipRect(0, 0, width, height);
  g.setJFont(c.getJFont());
  return g;
}

#if defined(WIN32)

  JImage::JImage(int handle, boolean ref) : JReference(handle, ref) {
    BITMAP bmp;
    GetObject((HBITMAP)handle, sizeof(BITMAP), &bmp);
    width = bmp.bmWidth; height = bmp.bmHeight;
  }

  void JImage::Delete() { 
    DeleteObject((HBITMAP)hnd);
  }

  int JImage::Duplicate() {
    hnd = null;
    return (int)(*this);
  }

  JImage::operator int() {
    if (hnd) return hnd;
    if ((width> 0) && (height > 0)) {
      HDC hdc = GetDC(null);
      HBITMAP hb = CreateCompatibleBitmap(hdc, width, height);
      ReleaseDC(null, hdc);
      Allocate((int)hb);
    }
    return hnd;
  }

  JGraphics JImage::getJGraphics() 
  { return JGraphics((int)CreateCompatibleDC(null), *this);}

#else

  void JImage::Delete() 
  { XFreePixmap(JUNIX::theDisplay, (Pixmap)hnd);}

  int JImage::Duplicate() {
    hnd = null;
    return (int)(*this);
  }

  JImage::operator int() {
    if (hnd) return hnd;
    if ((width> 0) && (height > 0)) {
      Allocate((int)XCreatePixmap(
	JUNIX::theDisplay, 
        (Window)(int)*JComponent::theRootWindow,
	width, height, JUNIX::theVisualDepth));
    }
    return hnd;
  }

  JGraphics JImage::getJGraphics() {
    GC gc = XCreateGC(JUNIX::theDisplay, 
      (Window)(int)*this, 0, null);
    return JGraphics((int)gc, *this);
  }

#endif
