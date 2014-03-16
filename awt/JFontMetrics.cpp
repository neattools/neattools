#include "JFontMetrics.h"
#include "JWindow.hpp"

char* theJFontMetrics = JFontMetrics().Register();
const char* JFontMetrics::className() const { return "JFontMetrics";}
int JFontMetrics::hashCode() const { return (font.hashCode()*37)&hashMask;}
JObject* JFontMetrics::clone() const { return new JFontMetrics(*this);}

int JFontMetrics::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return font.compareTo((*(JFontMetrics*)&s).font);
}

JFontMetrics::JFontMetrics() {}

#if defined(WIN32)

  JFontMetrics::JFontMetrics(JGraphics _g) {
    g = _g;
    font = g.getJFont();
    HDC hdc = (HDC)(int)g;
    TEXTMETRIC tm;
    HFONT hFont = (HFONT)SelectObject(hdc, (HFONT)(int)font);
    if (GetTextMetrics(hdc, &tm)) {
      fmHeight = tm.tmHeight;
      fmAscent = tm.tmAscent;
      fmDescent = tm.tmDescent;
      fmLeading = tm.tmExternalLeading;
      fmMaxAdvance = tm.tmMaxCharWidth;
    } else {
      fmHeight = 0;
      fmAscent = 0;
      fmDescent = 0;
    }
    SelectObject(hdc, hFont);
  }

  int JFontMetrics::charWidth(char c) {
    char str[2] = {c, '\0'};
    return stringWidth(str);
  }

  int JFontMetrics::stringWidth(char* str) {
    SIZE sz = { 0, 0};
    HDC hdc = (HDC)(int)g;
    HFONT hFont = (HFONT)SelectObject(hdc, (HFONT)(int)font);
    GetTextExtentPoint32(hdc, str, 
      JString(str).length(), &sz);
    SelectObject(hdc, hFont);
    return sz.cx;
  }

#else

  JFontMetrics::JFontMetrics(JGraphics _g) {
    g = _g;
    font = g.getJFont();;
    XFontStruct *info = (XFontStruct*)font.getInfo();
    if (info) {
      fmHeight = info->ascent+info->descent;
      fmAscent = info->ascent;
      fmDescent = info->descent;
      fmLeading = info->descent;
      fmMaxAdvance = info->max_bounds.width;
    } else {
      fmHeight = 0;
      fmAscent = 0;
      fmDescent = 0;
    }
  }

  int JFontMetrics::charWidth(char c) {
    char str[2] = {c, '\0'};
    XFontStruct *info = (XFontStruct*)font.getInfo();
    return (info) ? XTextWidth(info, str, 1) : 0;
  }

  int JFontMetrics::stringWidth(char* str) {
    XFontStruct *info = (XFontStruct*)font.getInfo();
    return (info) ? XTextWidth(info, str, JString(str).length()) : 0;
  }

#endif

JFont JFontMetrics::getFont() { return font;}
int JFontMetrics::getLeading() { return fmLeading;}
int JFontMetrics::getAscent() { return fmAscent;}
int JFontMetrics::getDescent() { return fmDescent;}
int JFontMetrics::getHeight() { return fmHeight;}
int JFontMetrics::getMaxAdvance() { return fmMaxAdvance;}
