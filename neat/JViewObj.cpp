#include "JPObject.h"
#include "JViewSet.h"
#include "JMath.h"
#include "JDouble.h"
#include "JInteger.h"
#include "JFocusSet.h"
#include "JPropertyBox.h"
#include "JCriticalSection.h"

char* theJViewObj = JViewObj().Register();

double JViewObj::delta = JDouble::EPSILON*100;
const char* JViewObj::className() const { return "JViewObj";}
JObject* JViewObj::clone() const { return new JViewObj(*this);}

int JViewObj::compareTo(const JObject& s) const
{ return JObject::compareTo(s);}

void JViewObj::forEachNode(iterFuncType func, void** arg) const
{ (*func)(this, arg);}
JObject* JViewObj::firstNodeThat(condFuncType func, void** arg) const
{ return ((*func)(this, arg)) ? (JObject*)this : null;}
JObject* JViewObj::lastNodeThat(condFuncType func, void** arg) const
{ return ((*func)(this, arg)) ? (JObject*)this : null;}

JViewObj::JViewObj() { parent = null;}

boolean JViewObj::needEvent(int mask)
{ return (getEventMask() & mask) != null;}
int JViewObj::getEventMask() { return null;}
JRegion JViewObj::getJRegion() { return JRegion();}

void JViewObj::toFront() 
{ parent->toLast(*this);}

void JViewObj::toBack() 
{ parent->toFirst(*this);}

void JViewObj::remove() 
{ if (parent) parent->del(*this);}

void JViewObj::startup() {}
void JViewObj::reset() {}
void JViewObj::close() {}

JFPoint JViewObj::calculateOffset() {
  JViewObj *p = parent;
  JFPoint pt = *this;
  while (p) {
    pt.x += p->x;
    pt.y += p->y;
    p = p->parent;
  }
  return pt;
}

void JViewObj::ungroup(JViewSet& np, JFocusSet& set) {
  parent->reparent(*this, np);
  set.add(*this);
}

JViewObj* JViewObj::locate(double x, double y, JViewObj*& obj)
{ return inside(x, y) ? (obj = this) : null;}

void JViewObj::nearest(double _x, double _y, double& dmin, JViewObj*& dest) {
  JFPoint cp = center();
  JFPoint pt(_x, _y);
  double d = cp.distance(pt);
  if (!dest || (d <= dmin)) {
    dmin = d;
    dest = this;
  }
}

void JViewObj::selectObj(JFRect& r, JFocusSet& set) 
{ if (r.inside(*this)) set.add(*this);}
void JViewObj::touch(JFRect& r, JFocusSet& set) 
{ if (r && *this) set.add(*this);}

JFRect JViewObj::calculateExtent() { return *this;}
JFRect JViewObj::calculateUpdate()
{ return calculateExtent();}

void JViewObj::calculateJRegion(JRegion& rgn, double dx, double dy, double scale) {}

JRect JViewObj::getIExtent(double dx, double dy, double scale) {
  int ix = JMath::round((x+dx)*scale);
  int iy = JMath::round((y+dy)*scale);
  int iw = JMath::round((x+width+dx)*scale)-ix+1;
  int ih = JMath::round((y+height+dy)*scale)-iy+1;
  return JRect(ix, iy, iw, ih);
}

JPoint JViewObj::getIPoint(JFPoint pt, double dx, double dy, double scale) {
  return JPoint(JMath::round((pt.x+dx)*scale),
    JMath::round((pt.y+dy)*scale));
}

void JViewObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {}
void JViewObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) 
{ paint(g, dx, dy, rgn, scale);}

JString JViewObj::info() {
  return JString(className()+1)+":("+
    JDouble::toJStringF(x)+","+
    JDouble::toJStringF(y)+")-("+
    JDouble::toJStringF(width)+"x"+
    JDouble::toJStringF(height)+").";
}

void JViewObj::transform(double& v, JFRect& info, double wscale, double hscale) 
{ v = (v-info.x)*wscale+info.x+info.width;}

void JViewObj::transform(JFPoint& pt, JFRect& info, double wscale, double hscale) {
  pt.x = (pt.x-info.x)*wscale+info.x+info.width;
  pt.y = (pt.y-info.y)*hscale+info.y+info.height;
}

void JViewObj::rescale(JFRect& info, double wscale, double hscale) {
  transform(*this, info, wscale, hscale);
  reshape(x, y, width*wscale, height*hscale);
}

JViewObj* JViewObj::duplicate(JViewSet* _parent, JDictionary* dict) {
  if (!_parent) _parent = parent;
  JViewObj *obj = _parent->add(*this);
  obj->reset();
  if (dict) dict->add(JPObject(this), JPObject(obj));
  return obj;
}

void JViewObj::duplicateCheck(JDictionary& dict) {}
void JViewObj::fixParent(JViewSet* _parent) { parent = _parent;}
void JViewObj::fixPointer(JDictionary& dict) 
{ dict.add(JInteger((int)prevAddress), JPObject(this));}
void JViewObj::toHash(JHashTable& hash) 
{ hash.add(JPObject(this));}

boolean JViewObj::handleJEvent(JEvent& e) {
  switch (e.id) {
    case JEvent::GLOBAL_KEY_PRESS:
    case JEvent::GLOBAL_KEY_ACTION:
      if (!needEvent(GLOBAL_KEYBOARD_MASK)) break;
      return globalKeyDown(e, e.key);
    case JEvent::GLOBAL_KEY_RELEASE:
      if (!needEvent(GLOBAL_KEYBOARD_MASK)) break;
      return globalKeyUp(e, e.key);
    case JEvent::GLOBAL_MOUSE_MOVE:
      if (!needEvent(GLOBAL_MOUSE_MASK)) break;
      return globalMouseMove(e, e.x, e.y);
    case JEvent::GLOBAL_MOUSE_DOWN:
    case JEvent::GLOBAL_MOUSE_ACTION:
      if (!needEvent(GLOBAL_MOUSE_MASK)) break;
      return globalMouseDown(e, e.x, e.y);
    case JEvent::GLOBAL_MOUSE_UP:
      if (!needEvent(GLOBAL_MOUSE_MASK)) break;
      return globalMouseUp(e, e.x, e.y);
    case JEvent::KEY_PRESS:
    case JEvent::KEY_ACTION:
      if (!needEvent(KEYBOARD_MASK)) break;
      return keyDown(e, e.key);
    case JEvent::KEY_RELEASE:
      if (!needEvent(KEYBOARD_MASK)) break;
      return keyUp(e, e.key);
    case JEvent::GOT_FOCUS:
      if (!needEvent(FOCUS_MASK)) break;
      return gotFocus(e);
    case JEvent::LOST_FOCUS:
      if (!needEvent(FOCUS_MASK)) break;
      return lostFocus(e);
    case JEvent::MIXER_LINE_NOTIFY:
      if (!needEvent(MIXER_MASK)) break;
      return mixerLineNotify(e, e.key, e.modifiers);
    case JEvent::MIXER_CONTROL_NOTIFY:
      if (!needEvent(MIXER_MASK)) break;
      return mixerControlNotify(e, e.key, e.modifiers);
  }
  return false;
}

JArray JViewObj::getProperties() 
{ return JArray();}

boolean JViewObj::updateProperty(JProperty& prop) 
{ return false;}

boolean JViewObj::propertyDialog(int x, int y) { 
  int select = 0;
  JArray properties = getProperties();
  if (!properties.size()) return false;
  while (JPropertyBox::create(
    JString("Properties of ")+(className()+1),
    properties, select, x, y) == JMessageBox::OK) {
    JProperty &prop = *(JProperty*)properties[select];
    if (prop.edit(x, y)) {
      updateProperty(prop);
      properties = getProperties();
    }
  }
  return true;
}

boolean JViewObj::isOpaque() { return false;}
boolean JViewObj::mouseDown(JEvent& e, double x, double y) { return false;}
boolean JViewObj::mouseMove(JEvent& e, double x, double y) { return false;}
boolean JViewObj::mouseDrag(JEvent& e, double x, double y) { return false;}
boolean JViewObj::mouseUp(JEvent& e, double x, double y) { return false;}
boolean JViewObj::keyDown(JEvent& e, int key) { return false;}
boolean JViewObj::keyUp(JEvent& e, int key) { return false;}
boolean JViewObj::globalMouseDown(JEvent& e, int x, int y) { return false;}
boolean JViewObj::globalMouseMove(JEvent& e, int x, int y) { return false;}
boolean JViewObj::globalMouseUp(JEvent& e, int x, int y) { return false;}
boolean JViewObj::globalKeyDown(JEvent& e, int key) { return false;}
boolean JViewObj::globalKeyUp(JEvent& e, int key) { return false;}
boolean JViewObj::gotFocus(JEvent& e) { return false;}
boolean JViewObj::lostFocus(JEvent& e) { return false;}
boolean JViewObj::mixerLineNotify(JEvent& e, int mid, int lid) { return false;}
boolean JViewObj::mixerControlNotify(JEvent& e, int mid, int cid) { return false;}
boolean JViewObj::dataNotify(JEvent& e, void* data) { return false;}
boolean JViewObj::auxNotify(JEvent& e, void* data) { return false;}
