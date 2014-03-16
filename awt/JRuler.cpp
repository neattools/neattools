#include "JRuler.h"
#include "JMath.h"
#include "JDouble.h"

char* theJRuler = JRuler().Register();
static int idelta = 8;
static int idiv = 8;
static int ihdiv = idiv/2;

JRuler* JRuler::create(JComponent* p, int _type) { 
  JRuler *dest = (JRuler*)createJComponent(theJRuler, p);
  dest->setType(_type);
  return dest;
}

const char* JRuler::className() const { return "JRuler";}
JObject* JRuler::clone() const { return new JRuler(*this);}
JRuler::JRuler() {
  state = CONCAVE;
  base = ratio = 5;
  setValue(0, 1, 0, 1, 75, 1.0, false);
  mouseInside = false;
}

void JRuler::checkValue() {
  if ( maximum <= minimum ) maximum = minimum+1;
  if ( section < 1 ) section = 1;
  if ( section > maximum-minimum ) section = maximum-minimum;
  if ( value > maximum-section ) value = maximum-section;
  if ( value < minimum ) value = minimum;
  if ( scale <= 0.0 ) scale = 1.0;
  dscale = scale*dpi;
  double check = dscale;
  if (check < (double)idelta) {
    while (check < (double)idelta) check*=2.0;
  } else {
    while (check/2 > (double)idelta) check/=2.0;
  }
  delta = check/dscale;
  vscale = 1.0/check;
}

int JRuler::getType() { return type;}

boolean JRuler::setType(int _type) {
  if (type == _type) return false;
  type = _type;
  return true;
}

int JRuler::getValue() { return value;}
double JRuler::getDelta() { return delta;}

boolean JRuler::setValue(int _value) {
  int oldvalue = value, dv;
  value = _value;
  checkValue();
  dv = oldvalue-value;
  if (!dv) return false;
  switch (type) {
    case HORIZONTAL:
      ScrollWindow(0, 0, width, height, dv, 0);
      break;
    case VERTICAL:
      ScrollWindow(0, 0, width, height, 0, dv);
      break;
  }
  return true;
}

boolean JRuler::setValue(int _value, int _section,
  int _minimum, int _maximum, int _dpi,
  double _scale, boolean frepaint) {
  section = _section;
  minimum = _minimum;
  maximum = _maximum;
  dpi = _dpi;
  scale = _scale;
  value = _value;
  checkValue();
  if (frepaint)
    repaint(true);
  return true;
}

void JRuler::paint(JGraphics g) {
  int s1, s2, to;
  JRect rect = g.getClipJRect();
  JColor fg = getForeground();
  JColor bg = getBackground();
  JColor dk = bg.darker();
  JColor br = bg.brighter();
  g.setJColor(bg);
  switch (type) {
    case HORIZONTAL: {
      s1 = (int)JMath::floor(vscale*(value+rect.x)/idiv)*idiv;
      s2 = (int)JMath::floor(vscale*(value+rect.x));
      to = (int)JMath::ceil(vscale*(value+rect.x+rect.width))+1;
      int i, icurrent = s1;
      double current = delta*icurrent;
      int bottom = height-2;
      int hup = height/2-1;
      int up, sup = height*4/5-1;
      g.fillRect(rect.x, 0, rect.width, height-1);
      g.setJColor(dk);
      g.drawLine(rect.x, height-1, rect.x+rect.width, height-1);
      for (; icurrent<to; current+=delta, icurrent++) {
        i = ((int)JMath::round(current*dscale))-value;
	if (!(icurrent%idiv)) {
	  JString tag = JDouble::toJString(current);
	  g.setJColor(br);
	  g.drawJString(tag, i+3, 1);
	  g.setJColor(fg);
	  g.drawJString(tag, i+2, 0);
	  up = 0;
	  if (icurrent == s1) {
	    icurrent = max(s1, s2-1);
	    current = delta*icurrent;
	  }
	} else if (!(icurrent%ihdiv)) up = hup;
	else up = sup;
        g.setJColor(fg);
	g.drawLine(i, bottom, i, up);
        g.setJColor(br);
	g.drawLine(i+1, bottom, i+1, up);
      }
      break;
    }
    case VERTICAL: {
      s1 = (int)JMath::floor(vscale*(value+rect.y)/idiv)*idiv;
      s2 = (int)JMath::ceil(vscale*(value+rect.y))-1;
      to = (int)JMath::ceil(vscale*(value+rect.y+rect.height))+1;
      int i, icurrent = s1;
      double current = delta*icurrent;
      int right = width-2;
      int hleft = width/2-1;
      int left, sleft = width*4/5-1;
      g.fillRect(0, rect.y, width-1, rect.height);
      g.setJColor(dk);
      g.drawLine(width-1, rect.y, width-1, rect.y+rect.height);
      for (; icurrent<to; current+=delta, icurrent++) {
        i = ((int)JMath::round(current*dscale))-value;
	if (!(icurrent%idiv)) {
	  JString tag = JDouble::toJString(current);
	  g.setJColor(br);
	  g.drawJString(tag, 2, i+2);
	  g.setJColor(fg);
	  g.drawJString(tag, 1, i+1);
	  left = 0;
	  if (icurrent == s1) {
	    icurrent = max(s1, s2-1);
	    current = delta*icurrent;
	  }
	} else if (!(icurrent%ihdiv)) left = hleft;
	else left = sleft;
        g.setJColor(fg);
	g.drawLine(right, i, left, i);
        g.setJColor(br);
	g.drawLine(right, i+1, left, i+1);
      }
      break;
    }
    default:
      g.fillJRect(rect);
      g.draw3DRect(4, 4, width-8, height-8, -1);
      g.setJColor(dk);
      g.drawPixel(width-1, height-1);
  }
}

boolean JRuler::mouseEnter(JEvent& e, int x, int y) {
  mouseInside = true;
  return false;
}

boolean JRuler::mouseExit(JEvent& e, int x, int y) {
  mouseInside = false;
  return false;
}

boolean JRuler::isMouseInside() { return mouseInside;}