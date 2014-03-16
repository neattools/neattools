#include "J1DSliderObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JColorData.h"
#include "JMath.h"

char* theJ1DSliderObj = J1DSliderObj().Register();
void J1DSliderObj::writeContent(JOutputStream& os) {
  JBtnObj::writeContent(os);
  putDouble(os, "fraction", fraction);
  putInteger(os, "max", max);
  putInteger(os, "min", min);
}

void J1DSliderObj::readContent(JDictionary& dict) {
  JBtnObj::readContent(dict);
  fraction = getDouble(dict, "fraction");
  max = getInteger(dict, "max");
  min = getInteger(dict, "min");
}

const char* J1DSliderObj::className() const { return "J1DSliderObj";}
JObject* J1DSliderObj::clone() const { return new J1DSliderObj(*this);}

J1DSliderObj::J1DSliderObj(int _type) { 
  igm = IN_LAST;
  bkgnd = color = JColor::cyan.darker(); 
  type = _type;
  oldf = factor = fraction = 0.0; 
  min = max = next = prev = 0;
}

void J1DSliderObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  g.setJColor(moduleColor);
  if ((rect.width > depth2+2) && (rect.height > depth2+2)) {
    g.draw3DJRect(rect, depth);
    g.draw3DJRect(rect.shrink(depth, depth), -1);
  } else g.fillJRect(rect);
  update(g, dx, dy, rgn, scale);
}

void J1DSliderObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  int dt = depth2+2;
  JRect rect = getIExtent(dx, dy, scale);
  if ((rect.width > dt) && (rect.height > dt)) {
    int oldv = value;
    JRect clip = rect, thumb;
    JRegion frgn(clip.shrinkBy(depth+1, depth+1));
    if (type == HORIZONTAL) {
      int len = rect.width-dt-dt;
      if (oldf != factor) {
	oldf = factor;
	fraction = (factor*rect.width-dt)/len;
	fraction = max(0.0, min(1.0, fraction));
      }
      int pos = (int)JMath::round(fraction*len);
      thumb = JRect(clip.x+pos, clip.y, dt, clip.height);
    } else {
      int len = rect.height-dt-dt;
      if (oldf != factor) {
	oldf = factor;
	fraction = (factor*rect.height-dt)/len;
	fraction = max(0.0, min(1.0, fraction));
      }
      int pos = (int)JMath::round((1.0-fraction)*len);
      thumb = JRect(clip.x, clip.y+pos, clip.width, dt);
    }
    int vmin = getMin();
    value = (int)JMath::round(fraction*(getMax()-vmin)+vmin);
    if (value != oldv) broadcast(0);
    g.setJColor(color);
    g.fill3DJRect(thumb, depth);
    g.setJRegion((frgn & rgn)-JRegion(thumb));
    g.setJColor(bkgnd);
    g.fillJRect(clip);
    g.setJRegion(rgn);
  }
}

boolean J1DSliderObj::mouseDown(JEvent& e, double _x, double _y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = (inside(_x, _y));
  }
  return true;
}

boolean J1DSliderObj::mouseDrag(JEvent& e, double _x, double _y) {
  if (mousePressed) {
    oldf = factor;
    if (type == HORIZONTAL) {
      if (width > 0.0) 
	factor = (_x-x)/width;
      else fraction = 0.0;
    } else {
      if (height > 0.0) 
	factor = (y+height-_y)/height;
      else fraction = 0.0;
    }
    if (oldf != factor) repaint();
  }
  return true;
}

boolean J1DSliderObj::mouseUp(JEvent& e, double x, double y) {
  if (e.modifiers & JEvent::LBUTTON) {
    mousePressed = false;
  }
  return true;
}

JFRect J1DSliderObj::outputArea(int n) {
  if (type == HORIZONTAL) 
    return rightArea(n, 0, 1);
  return bottomArea(n, 0, 1);
}

int J1DSliderObj::inputType(int n) { 
  switch (n) {
    case COLOR:
    case BACKGROUND:
      return JColorData::id;
  }
  return JIntegerData::id;
}

JString J1DSliderObj::inputTag(int n) {
  char* tag[] = { "input", "color", "background", 
    "max", "next", "prev", "min"};
  if (!n && isNBits()) return JString(tag[0])+NBTag();
  return tag[n];
}

JString J1DSliderObj::outputTag(int n) {
  char* tag = "output";
  if (!n && isNBits()) return JString(tag)+NBTag();
  return tag;
}

int J1DSliderObj::outputFace(int n) 
{ return (type == HORIZONTAL) ? RIGHT : BOTTOM;}

JFPoint J1DSliderObj::outputPoint(int n, JLinkObj& link) { 
  if (type == HORIZONTAL) 
    return rightPoint(n, link, 0, 1);
  return bottomPoint(n, link, 0, 1);
}

void J1DSliderObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case INPUT: {
      int iv = value;
      link.access(JIntegerData(iv));
      setValue(iv);
      break;
    }
    case COLOR:
    case BACKGROUND: {
      processColor(n, link);
      break;
    }
    case MIN: {
      int ov = min;
      link.access(JIntegerData(min));
      if (min != ov)
        setValue(value);
      break;
    }
    case MAX: {
      int ov = max;
      link.access(JIntegerData(max));
      if (max != ov) setValue(value);
      break;
    }
    case NEXT: {
      int ov = next;
      link.access(JIntegerData(next));
      next = (next != 0);
      if (next && (next != ov)) 
        setValue(value+1);
      break;
    }
    case PREV: {
      int ov = prev;
      link.access(JIntegerData(prev));
      prev = (prev != 0);
      if (prev && (prev != ov)) 
        setValue(value-1);
      break;
    }
  }
}

boolean J1DSliderObj::setValue(int _value) {
  _value = max(getMin(), min(getMax(), _value));
  if (_value != value) {
    value=_value;
    int vmin = getMin();
    int range = getMax()-vmin;
    if (!range) fraction = 0;
    else fraction = double(value-vmin)/range;
    oldf = factor;
    broadcast(0);
    repaint();
    return true;
  }
  return false;
}

void J1DSliderObj::addButton(JComponent* panel) { 
  addModuleButton(panel, J1DSliderObj(HORIZONTAL));
  addModuleButton(panel, J1DSliderObj(VERTICAL));
}

boolean J1DSliderObj::isNBits() 
{ return !inputSet(MAX).last() && !inputSet(MIN).last();}
int J1DSliderObj::getMax() 
{ return (inputSet(MAX).last()) ? max : mask;}
int J1DSliderObj::getMin() 
{ return (inputSet(MIN).last()) ? min : 0;}
