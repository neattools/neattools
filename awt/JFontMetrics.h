#if !defined( _JFontMetrics_h )
#define _JFontMetrics_h

#include "JFont.h"
#include "JGraphics.h"

class
#include "JAWT.hpp"
JFontMetrics : public JObject {
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JFontMetrics();
    JFontMetrics(JGraphics _g);
    int charWidth(char c);
    int stringWidth(char* str);
    JFont getFont();
    int getLeading();
    int getAscent();
    int getDescent();
    int getHeight();
    int getMaxAdvance();
    int width, height;
  protected:
    JGraphics g;
    JFont font;
    int fmLeading, fmAscent, fmDescent;
    int fmHeight, fmMaxAdvance;
};

#endif
