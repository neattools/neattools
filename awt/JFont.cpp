#include "JFont.h"
#include "JDictionary.h"
#include "JWindow.hpp"

extern JDictionary JFontTable;
JFont JFont::standard;

char* theJFont = JFont().Register();
void JFont::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putObject(os, "name", name);
  putInteger(os, "style", style);
  putInteger(os, "size", size);
}

void JFont::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  name = *(JString*)getObject(dict, "name");
  style = getInteger(dict, "style");
  size = getInteger(dict, "size");
}

const char* JFont::className() const { return "JFont";}
int JFont::hashCode() const
{ return (name.hashCode()^style^size)&hashMask;}
JObject* JFont::clone() const { return new JFont(*this);}

int JFont::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  JFont &obj = *(JFont*)&s;
  int result = name.compareTo(obj.name);
  if (!result) {
    result = style-obj.style;
    if (!result) result = size-obj.size;
  }
  return result;
}

JFont::JFont() : name("times") { style = PLAIN; size = 12;}
JFont::JFont(const JString& _name, int _style, int _size)
  : name(_name) { style = _style; size = _size;}
JFont::~JFont() { Release();}
JString JFont::getName() { return name;}
int JFont::getStyle() { return style;}
int JFont::getSize() { return size;}
boolean JFont::isPlain() { return (style == 0);}
boolean JFont::isBold() { return (style & BOLD) != 0;}
boolean JFont::isItalic() { return (style & ITALIC) != 0;}

#if defined(WIN32)

  void JFont::Delete() { 
    DeleteObject((HFONT)hnd);
  }

  int JFont::Duplicate() {
    hnd = null;
    return (int)(*this);
  }

  JFont::operator int() {
    if (hnd) return hnd;
    JFont *dest = (JFont*)JMicroSoft::JObjectCache[*this];
    if (!dest) {
      JString *fname = (JString*)JFontTable[name.toUpperCase()];
      if (!fname) fname = &name;
      Allocate((int)CreateFont(
        -size, 0, 0, 0, 
        ((style&1) ? 700 : 400),
        ((style & 2) > 0), false, false,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH,
        (char*)*fname));
      JMicroSoft::JObjectCache.add(*this);
    } else *this = *dest;
    return hnd;
  }

#else

  #include <stdio.h>

  void* JFont::getInfo() { if (!hnd) (int)(*this); return info;}

  void JFont::Delete() { XUnloadFont(JUNIX::theDisplay, (Font)hnd);}

  int JFont::Duplicate() {
    hnd = null;
    return (int)(*this);
  }

  JFont::operator int() {
    if (hnd) return hnd;
    JFont *dest = (JFont*)JUNIX::JObjectCache[*this];
    if (!dest) {
      char buf[256];
      int count;
      char **fnames;
      static char* sweight[] = { "medium", "bold"};
      static char* sstyle[] = { "r", "i"};
      JString *fname = (JString*)JFontTable[name.toUpperCase()];
      if (!fname) fname = &name;
      sprintf(buf, "*-%s-%s-%s-normal--0-0-0-0-*-iso8859-1",
        (char*)*fname, sweight[style & 1], sstyle[(style & 2)>>1]);
      if (!(fnames = XListFonts(JUNIX::theDisplay, buf, 16, &count))) {
        sprintf(buf, "*-%s-%s-%s-normal--0-0-*-iso8859-1", 
          (char*)*fname, sweight[style & 1], sstyle[(style & 2)>>1]);
        if (!(fnames = XListFonts(JUNIX::theDisplay, buf, 16, &count))) {
          sprintf(buf, "*-%s-%s-normal--0-0-*-iso8859-1", 
            sweight[style & 1], sstyle[(style & 2)>>1]);
          if (!(fnames = XListFonts(JUNIX::theDisplay, buf, 16, &count)))
            return null;
        } 
      }
      char *ptr = fnames[0]+JString(fnames[0]).indexOf("--0-0-")+2;
      *ptr++ = 0;
      sprintf(buf, "%s%d%s", fnames[0], size, ptr);
      info = XLoadQueryFont(JUNIX::theDisplay, buf);
      Allocate((int)((XFontStruct*)info)->fid);
      JUNIX::JObjectCache.add(*this);
    } else *this = *dest;
    return hnd;
  }

#endif
