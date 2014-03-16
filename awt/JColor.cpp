#include "JColor.h"
#include "JMath.h"
#include "JNullPointerException.h"
#include "JWindow.hpp"

JColor JColor::white(255, 255, 255);
JColor JColor::lightGray(192, 192, 192);
JColor JColor::gray(128, 128, 128);
JColor JColor::darkGray(64, 64, 64);
JColor JColor::black(0, 0, 0);
JColor JColor::red(255, 0, 0);
JColor JColor::pink(255, 175, 175);
JColor JColor::orange(255, 200, 0);
JColor JColor::yellow(255, 255, 0);
JColor JColor::green(0, 255, 0);
JColor JColor::magenta(255, 0, 255);
JColor JColor::cyan(0, 255, 255);
JColor JColor::blue(0, 0, 255);
double JColor::FACTOR = 0.70711;

char* theJColor = JColor().Register();
void JColor::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putInteger(os, "value", value);
}

void JColor::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value = getInteger(dict, "value");
}

const char* JColor::className() const { return "JColor";}
int JColor::hashCode() const { return hashMask & value;}
JObject* JColor::clone() const { return new JColor(*this);}
int JColor::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return value - (*(JColor*)&s).value;
}

JColor::JColor() { value = -1;}
JColor::JColor(int rgb, int a) 
{ value = ((a&0xFF)<<24)|rgb;}
JColor::JColor(int r, int g, int b, int a) 
{ value = (((a&0xFF)<<24)|((b&0xFF)<<16)|((g&0xFF)<<8)|(r&0xFF));}
JColor::JColor(float r, float g, float b, float a) 
{ *this = JColor((int)(r*255), (int)(g*255), (int)(b*255), (int)(a*255));}

int JColor::getAlpha() { return (value>>24)&0xFF;}
int JColor::getRed() { return value&0xFF;}
int JColor::getGreen() { return (value>>8)&0xFF;}
int JColor::getBlue() { return (value>>16)&0xFF;}
int JColor::getRGB() { return value;}
JColor JColor::brighter() {
  double f = 1.0/FACTOR;
  return JColor(min((int)(getRed()*f), 255),
    min((int)(getGreen()*f), 255),
    min((int)(getBlue()*f), 255));
}

JColor JColor::darker() {
  return JColor(max((int)(getRed()*FACTOR), 0),
    max((int)(getGreen()*FACTOR), 0),
    max((int)(getBlue() *FACTOR), 0));
}

int JColor::HSBtoRGB(float hue, float saturation, float brightness) {
  int r = 0, g = 0, b = 0;
  if (saturation == 0) {
    r = g = b = (int)(brightness * 255);
  } else {
    double h = hue * 6.0;
    double f = h - JMath::floor(h);
    double p = brightness*(1.0 - saturation);
    double q = brightness*(1.0 - saturation * f);
    double t = brightness*(1.0 - (saturation * (1.0 - f)));
    switch ((int)h) {
      case 0:
  	r = (int)(brightness * 255);
  	g = (int)(t * 255);
  	b = (int)(p * 255);
  	break;
      case 1:
  	r = (int)(q * 255);
  	g = (int)(brightness * 255);
  	b = (int)(p * 255);
  	break;
      case 2:
  	r = (int)(p * 255);
  	g = (int)(brightness * 255);
  	b = (int)(t * 255);
  	break;
      case 3:
  	r = (int)(p * 255);
  	g = (int)(q * 255);
  	b = (int)(brightness * 255);
  	break;
      case 4:
  	r = (int)(t * 255);
  	g = (int)(p * 255);
  	b = (int)(brightness * 255);
  	break;
      case 5:
  	r = (int)(brightness * 255);
  	g = (int)(p * 255);
  	b = (int)(q * 255);
  	break;
    }
  }
  return 0xff000000 | (b << 16) | (g << 8) | r;
}

float* RGBtoHSB(int r, int g, int b, float* hsbvals) {
  float hue, saturation, brightness;
  if (hsbvals == null)
    throw new JNullPointerException("hsbvals is null");
  int cmax = max(r, g);
  if (b > cmax) cmax = b;
  int cmin = min(r, g);
  if (b < cmin) cmin = b;
  brightness = ((float)cmax)/255.0f;
  if (cmax) saturation = ((float)(cmax-cmin))/((float)cmax);
  else saturation = 0.0f;
  if (!saturation) hue = 0.0f;
  else {
    float redc = ((float)(cmax-r))/((float)(cmax-cmin));
    float greenc = ((float)(cmax-g))/((float)(cmax-cmin));
    float bluec = ((float)(cmax-b))/((float)(cmax-cmin));
    if (r == cmax) hue = bluec - greenc;
    else if (g == cmax) hue = 2.0f + redc - bluec;
    else hue = 4.0f + greenc - redc;
    hue = hue / 6.0f;
    if (hue < 0) hue = hue + 1.0f;
  }
  hsbvals[0] = hue;
  hsbvals[1] = saturation;
  hsbvals[2] = brightness;
  return hsbvals;
}

JColor JColor::getHSBJColor(float h, float s, float b) {
  return JColor(HSBtoRGB(h, s, b));
}

#if defined (WIN32)

  JColor::operator int() { return value;}

#else

  JColor::~JColor() { Release();}
  JColor::operator int() { return getPixel();}

  void JColor::Delete() {
    unsigned long pixels[] = { hnd}; 
    XFreeColors(JUNIX::theDisplay, JUNIX::theColormap, pixels, 1, 0);
  }

  int JColor::Duplicate() {
    hnd = -1;
    return getPixel();
  }

  int& JColor::getPixel() {
    if (hnd > -1) return hnd;
    JColor *dest = (JColor*)JUNIX::JObjectCache[*this];
    if (!dest) {
      XColor color;
      color.red = getRed() << 8;
      color.green = getGreen() << 8;
      color.blue = getBlue() << 8;
      if (!XAllocColor(JUNIX::theDisplay, JUNIX::theColormap, &color)) 
        color.pixel = WhitePixel(JUNIX::theDisplay, JUNIX::theScreen);
      Allocate(color.pixel);
      JUNIX::JObjectCache.add(*this);
    } else *this = *dest;
    return hnd;
  }

  void JColor::setPixel(int _pixel) {
    if (hnd == _pixel) return;
    XColor color;
    color.pixel = _pixel;
    XQueryColor(JUNIX::theDisplay, JUNIX::theColormap, &color);
    value = JColor(color.red >> 8, color.green >> 8, 
      color.blue >> 8).getRGB();
    Release();
  }

#endif

