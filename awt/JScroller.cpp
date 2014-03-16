#include "JScroller.h"
#include "JBorderLayout.h"

char* theJScroller = JScroller().Register();
JScroller* JScroller::create(JComponent* p, int _type) { 
  JScroller *dest = (JScroller*)createJComponent(theJScroller, p);
  dest->setType(_type);
  return dest;
}

const char* JScroller::className() const { return "JScroller";}
JObject* JScroller::clone() const { return new JScroller(*this);}
JScroller::JScroller() { 
  state = CONCAVE; 
  depth = base = ratio = 1;
}

void JScroller::startup() {
  JBorderLayout border;
  type = HORIZONTAL;
  setLayout(border);
  up = JTriangleButton::create(this);
  down = JTriangleButton::create(this);
  add(JBorderLayout::CENTER, 
    *(thumb = JThumb::create(this)));
  setType(VERTICAL);
}

boolean JScroller::action(JEvent& e, JObject* arg) {
  if (e.target == up) {
    thumb->moveThumb(-1);
    return true;
  } else if (e.target == down) {
    thumb->moveThumb(1);
    return true;
  } else if (e.target == thumb) {
    e.target = this;
  }
  return false;
}

int JScroller::getType() { return type;}

boolean JScroller::setType(int _type) {
  if (type == _type) return false;
  type = _type;
  thumb->setType(type);
  if (type == HORIZONTAL) {
    up->setType(JTriangleButton::LEFT);
    down->setType(JTriangleButton::RIGHT);
    add(JBorderLayout::WEST, *up);
    add(JBorderLayout::EAST, *down);
  } else {
    up->setType(JTriangleButton::UP);
    down->setType(JTriangleButton::DOWN);
    add(JBorderLayout::NORTH, *up);
    add(JBorderLayout::SOUTH, *down);
  }
  return true;
}

int JScroller::getValue() { return thumb->getValue();}
boolean JScroller::setValue(int _value)
{ return thumb->setValue(_value);}
boolean JScroller::setValue(int _value, int _section,
  int _minimum, int _maximum, boolean frepaint) 
{ return thumb->setValue(_value, _section, _minimum, _maximum, frepaint);}
boolean JScroller::needRedraw() { return true;}
