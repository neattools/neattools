#include "JThumb.h"

char* theJThumb = JThumb().Register();
JThumb* JThumb::create(JComponent* p) 
{ return (JThumb*)createJComponent(theJThumb, p);}

const char* JThumb::className() const { return "JThumb";}
JObject* JThumb::clone() const { return new JThumb(*this);}
JThumb::JThumb() { 
  type = HORIZONTAL; 
  base = ratio = 0; 
  area = THUMB;
  setValue(0, 1, 0, 1, false);
}

void JThumb::checkValue() {
  if ( maximum <= minimum ) maximum = minimum+1;
  if ( section < 1 ) section = 1;
  if ( section > maximum-minimum ) section = maximum-minimum;
  if ( value > maximum-section ) value = maximum-section;
  if ( value < minimum ) value = minimum;
}

boolean JThumb::setThumb() {
  boolean changed;
  int _length, _offset;
  int wRange = (type == HORIZONTAL) ? width : height;
  _length = max(depth*4, section*wRange/range);
  _offset = (value-minimum)*max(1, wRange-_length)/
  max(1, range-section);
  changed = ((offset != _offset) || (length != _length));
  offset = _offset;
  length = _length;
  return changed;
}

int JThumb::getType() { return type;}

boolean JThumb::setType(int _type) {
  if (type == _type) return false;
  type = _type;
  repaint();
  return true;
}

int JThumb::getValue() { return value;}

boolean JThumb::setValue(int _value) {
  int oldvalue = value;
  value = _value;
  checkValue();
  if (setThumb())
    repaint(true);
  return (value != oldvalue);
}

boolean JThumb::setValue(int _value, int _section,
  int _minimum, int _maximum, boolean frepaint) {
  section = _section;
  minimum = _minimum;
  maximum = _maximum;
  value = _value;
  checkValue();
  range = maximum-minimum;
  if (setThumb() && frepaint)
    repaint(true);
  return true;
}

void JThumb::moveThumb(int delta) {
  if (!delta) return;
  if (setValue(value+delta)) {
    JEvent event(this, JEvent::ACTION_EVENT);
    event.key = value;
    postJEvent(event);
  }
}

void JThumb::paint(JGraphics g) {
  setThumb();
  g.setJColor(getBackground());
  JRect thumb;
  if (type == HORIZONTAL) thumb = JRect(offset, 0, length, height);
  else thumb = JRect(0, offset, width, length);
  g.fill3DJRect(thumb, depth);
  g.setJRegion(JRegion(g.getClipJRect())-
    JRegion(thumb));
  g.fillRect(0, 0, width, height);
}

boolean JThumb::mouseDown(JEvent& e, int x, int y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = true;
  }
  if (e.modifiers & JEvent::LBUTTON) {
    if (e.id == JEvent::MOUSE_DOWN) {
      area = THUMB;
      if ( type == HORIZONTAL ) {
        if ( x < offset ) area = PAGE_UP;
        else if ( x >= offset+length ) area = PAGE_DOWN;
        else mofs = x-offset;
      } else {
        if ( y < offset ) area = PAGE_UP;
        else if ( y >= offset+length ) area = PAGE_DOWN;
        else mofs = y-offset;
      }
    }
    if (autoRepeat || (e.id == JEvent::MOUSE_DOWN)) {
      if (area == PAGE_DOWN) moveThumb(section);
      else if (area == PAGE_UP) moveThumb(-section);
    }
  }
  return true;
}

boolean JThumb::mouseUp(JEvent& e, int x, int y) {
  if (e.modifiers & JEvent::LBUTTON)
    mousePressed = false;
  return true;
}

boolean JThumb::mouseDrag(JEvent& e, int x, int y) {
  if ( !mousePressed || (area != THUMB) ) return false;
  int wRange = (type == HORIZONTAL) ? width : height;
  int kRange = max(1, range-section);
  wRange = max(1, wRange-length);
  moveThumb((((type == HORIZONTAL) ? x : y)-
    mofs-offset)*kRange/wRange);
  return true;
}
