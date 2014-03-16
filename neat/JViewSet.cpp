#include "JViewSet.h"
#include "JFocusSet.h"
#include "JLineObj.h"
#include "JInteger.h"
#include "JDouble.h"
#include "JDictionary.h"

char* theJViewSet = JViewSet().Register();
void JViewSet::writeContent(JOutputStream& os) {
  JViewObj::writeContent(os);
  putObject(os, "children", children);
}

void JViewSet::readContent(JDictionary& dict) {
  JViewObj::readContent(dict);
  children = *(JDList*)getObject(dict, "children");
}

const char* JViewSet::className() const { return "JViewSet";}

int JViewSet::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return children.compareTo(((JViewSet*)&s)->children);
}

JObject* JViewSet::clone() const { return new JViewSet(*this);}

void DoForEachNode(const JObject* obj, void** arg)
{ ((JViewObj*)obj)->forEachNode((iterFuncType)arg[0], (void**)arg[1]);}

void JViewSet::forEachNode(iterFuncType func, void** arg) const { 
  void* args[] = { func, arg};
  children.forEach(DoForEachNode, args);
}

void JViewSet::forEachChild(iterFuncType func, void** arg) const
{ children.forEach(func, arg);}

boolean DoFirstNodeThat(const JObject* obj, void** arg)
{ return ((JViewObj*)obj)->firstNodeThat((condFuncType)arg[0], (void**)arg[1]) != null;}

JObject* JViewSet::firstNodeThat(condFuncType func, void** arg) const { 
  void* args[] = { func, arg};
  return children.firstThat(DoFirstNodeThat, args);
}

JObject* JViewSet::firstChildThat(condFuncType func, void** arg) const
{ return children.firstThat(func, arg);}

boolean DoLastNodeThat(const JObject* obj, void** arg)
{ return ((JViewObj*)obj)->lastNodeThat((condFuncType)arg[0], (void**)arg[1]) != null;}

JObject* JViewSet::lastNodeThat(condFuncType func, void** arg) const { 
  void* args[] = { func, arg};
  return children.lastThat(DoLastNodeThat, args);
}

JObject* JViewSet::lastChildThat(condFuncType func, void** arg) const
{ return children.lastThat(func, arg);}

JViewSet::JViewSet(JComponent *_root) { root = _root; eventMask = 0;}
JComponent* JViewSet::getRoot() { return (parent) ? parent->getRoot() : root;}
int JViewSet::getEventMask() { return eventMask;}

void DoRemove(const JObject* obj, void** arg)
{ ((JViewObj*)obj)->remove();}

void JViewSet::remove() {
  forEachChild(DoRemove);
  JViewObj::remove();
}

void DoStartup(const JObject* obj, void** arg)
{ ((JViewObj*)obj)->startup();}

void JViewSet::startup() {
  JViewObj::startup();
  forEachChild(DoStartup);
}

void DoClose(const JObject* obj, void** arg)
{ 
  ((JViewObj*)obj)->close();
}

void JViewSet::close() {
  forEachChild(DoClose);
  JViewObj::close();
}

void JViewSet::toFirst(JViewObj& obj) 
{ children.toFirst(obj);}

void JViewSet::toLast(JViewObj& obj) 
{ children.toLast(obj);}

void JViewSet::reparent(JViewObj& obj, JViewSet& np) {
  if (obj.parent != &np) {
    children.reparent(obj, np.children);
    obj.parent = &np;
  }
}

void DoReparent(const JObject* obj, void** arg)
{ ((JViewObj*)obj)->parent->reparent(*(JViewObj*)obj, *(JViewSet*)arg);}

void JViewSet::reparent(JViewSet& np)
{ forEachChild(DoReparent, (void**)&np);}

void DoUngroup(const JObject* obj, void** arg)
{ ((JViewObj*)obj)->ungroup(*(JViewSet*)arg[0], *(JFocusSet*)arg[1]);}

void JViewSet::ungroup(JViewSet& np, JFocusSet& set) {
  if (!parent->parent) {
    void* arg[] = {&np, &set};
    forEachChild(DoUngroup, arg);
    remove();
  } else JViewObj::ungroup(np, set);  
}

JViewObj* JViewSet::add(JViewObj& obj) {
  JViewObj *last = (JViewObj*)children.append(obj);
  last->parent = this;
  return last;
}
void JViewSet::del(JViewObj& obj) { children.del(obj);}
int JViewSet::indexOf(JViewObj& obj)
{ return children.indexOf(obj);}
JViewObj* JViewSet::operator[](JViewObj& obj)
{ return (JViewObj*)children[obj];}
JViewObj* JViewSet::operator[](int index)
{ return (JViewObj*)children[index];}
JViewObj* JViewSet::first()
{ return (JViewObj*)children.first();}
JViewObj* JViewSet::last()
{ return (JViewObj*)children.last();}
int JViewSet::size() const
{ return children.size();}
void JViewSet::Dereference() { children.Dereference();}
void JViewSet::delAll() { children.Release();}
boolean JViewSet::isEmpty() { return children.isEmpty();}

void JViewSet::addLine(double x1, double y1, double x2, double y2) {
  JFPoint p1(x1, y1);
  JFPoint p2(x2, y2);
  JLineObj l(p1, p2);
  add(l);
}

void JViewSet::addRect(double x, double y, double width, double height) {
  JFPoint p1(x, y);
  JFPoint p2(x+width, y);
  JFPoint p3(x+width, y+height);
  JFPoint p4(x, y+height);
  JLineObj l1(p1, p2);
  JLineObj l2(p2, p3);
  JLineObj l3(p3, p4);
  JLineObj l4(p4, p1);
  add(l1);
  add(l2);
  add(l3);
  add(l4);
}

void JViewSet::addJFRect(JFRect rect) 
{ addRect(rect.x, rect.y, rect.width, rect.height);}

boolean CanLocate(const JObject* obj, void** arg) {
  return (((JViewObj*)obj)->locate(*(double*)arg[0],
    *(double*)arg[1], *(JViewObj**)arg[2])) != null;
}

JViewObj* JViewSet::locate(double _x, double _y, JViewObj*& obj) {
  if (inside(_x, _y)) {
    void* arg[] = { &_x, &_y, &obj};
    return (JViewObj*)lastChildThat(CanLocate, arg);
  }
  return null;
}

void DoNearest(const JObject* obj, void** arg) {
  ((JViewObj*)obj)->nearest(*(double*)arg[0], *(double*)arg[1],
    *(double*)arg[2], *(JViewObj**)arg[3]);
}

void JViewSet::nearest(double _x, double _y, double& d, JViewObj*& dest) {
  void* arg[] = {&_x, &_y, &d, &dest};
  forEachChild(DoNearest, arg);
}

void DoLocate(const JObject* obj, void** arg) 
{ ((JViewObj*)obj)->selectObj(*(JFRect*)arg[0], *(JFocusSet*)arg[1]);}

JFocusSet JViewSet::select(JFRect& r) {
  JFocusSet set;
  if (r && *this) {
    void* arg[] = {&r, &set};
    forEachChild(DoLocate, arg);
  }
  return set;
}

void DoTouch(const JObject* obj, void** arg) 
{ ((JViewObj*)obj)->touch(*(JFRect*)arg[0], *(JFocusSet*)arg[1]);}

void JViewSet::touch(JFRect& r, JFocusSet& set) {
  if (r && *this) {
    void* arg[] = {&r, &set};
    forEachChild(DoTouch, arg);
  }
}

JViewObj* JViewSet::nearestTouch(JFRect& r) {
  JFocusSet set;
  touch(r, set);
  if (!set.isEmpty()) {
    JFPoint cp = r.center();
    JViewObj *dest = null;
    double dist;
    set.nearest(cp.x, cp.y, dist, dest);
    return dest;
  }
  return null;
}

void DoCalculateExtent(const JObject* obj, void** arg) { 
  *(JFRect*)arg[0] |= ((JViewObj*)obj)->calculateExtent();
  *(int*)arg[1] |= ((JViewObj*)obj)->getEventMask();
}

JFRect JViewSet::calculateExtent() {
  JFRect rect;
  void* arg[] = { &rect, &(eventMask=0)};
  forEachChild(DoCalculateExtent, arg);
  reshape(rect);
  return rect;
}

void DoCalculateUpdate(const JObject* obj, void** arg)
{ *(JFRect*)arg |= ((JViewObj*)obj)->calculateUpdate();}

JFRect JViewSet::calculateUpdate() {
  JFRect rect;
  forEachChild(DoCalculateUpdate, (void**)&rect);
  return rect;
}

JRegion JViewSet::getJRegion() { return region;}

void JViewSet::calculateJRegion(JRegion& rgn, double dx, double dy, double scale) {
  JViewObj *obj;
  JDList i = children;
  region = rgn;
  for (i.reset(-1); (obj=(JViewObj*)i.current()) != 0; i.prev())
    obj->calculateJRegion(rgn, dx, dy, scale);
  region -= rgn;
}

void JViewSet::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JViewObj *obj;
  JDList i = children;
  if (!rgn) return;
  for (i.reset(); (obj=(JViewObj*)i.current()) != 0; i.next()) {
    JRegion orgn = obj->getJRegion();
    JRegion crgn = rgn & orgn;
    if (!crgn == false) {
      g.setJRegion(crgn);
      obj->paint(g, dx, dy, crgn, scale);
      if (obj->isOpaque()) rgn -= orgn;
    }
  }
}

void JViewSet::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JViewObj *obj;
  JDList i = children;
  if (!rgn) return;
  for (i.reset(); (obj=(JViewObj*)i.current()) != 0; i.next()) {
    g.setJRegion(rgn);
    obj->update(g, dx, dy, rgn, scale);
  }
}

JString JViewSet::info() {
  int sz = children.size();
  if (sz != 1) {
    return JString(className()+1)+":("+
      JDouble::toJStringF(x)+","+
      JDouble::toJStringF(y)+")-("+
      JDouble::toJStringF(width)+"x"+
      JDouble::toJStringF(height)+") "+
      JInteger::toJString(sz)+" Objs.";
  } else return (*this)[0]->info();
}

void DoTranslate(const JObject* obj, void** arg) 
{ ((JViewObj*)obj)->translate(*(double*)arg[0], *(double*)arg[1]);}

JFPoint& JViewSet::translate(double dx, double dy) {
  JViewObj::translate(dx, dy);
  void* arg[] = { &dx, &dy};
  forEachChild(DoTranslate, arg);
  return *this;
}

void DoRescale(const JObject* obj, void** arg) { 
  ((JViewObj*)obj)->rescale(
    *(JFRect*)arg[0], *(double*)arg[1], *(double*)arg[2]);
}

void JViewSet::rescale(JFRect& info, double wscale, double hscale) {
  void* arg[] = { &info, &wscale, &hscale};
  forEachChild(DoRescale, arg);
  JViewObj::rescale(info, wscale, hscale);
}

void DoDuplicate(const JObject* obj, void** arg) { 
  ((JViewObj*)obj)->duplicate((JViewSet*)arg[0], (JDictionary*)arg[1]);
}

JViewObj* JViewSet::duplicate(JViewSet* _parent, JDictionary* dict) {
  JViewSet *set = (JViewSet*)JViewObj::duplicate(_parent);
  void* arg[] = { set, dict};
  set->delAll();
  forEachChild(DoDuplicate, arg);
  return set;
}

void DoFixParent(const JObject* obj, void** arg)
{((JViewObj*)obj)->fixParent((JViewSet*)arg);}

void JViewSet::fixParent(JViewSet* _parent) {
  parent = _parent;
  forEachChild(DoFixParent, (void**)this);
}

void DoFixPointer(const JObject* obj, void** arg)
{((JViewObj*)obj)->fixPointer(*(JDictionary*)arg);}

void JViewSet::fixPointer(JDictionary& dict) 
{ forEachChild(DoFixPointer, (void**)&dict);}

void DoToHash(const JObject* obj, void** arg)
{((JViewObj*)obj)->toHash(*(JHashTable*)arg);}

void JViewSet::toHash(JHashTable& hash) 
{ forEachChild(DoToHash, (void**)&hash);}

void DoHandleJEvent(const JObject* obj, void** arg)
{ ((JViewObj*)obj)->handleJEvent(*(JEvent*)arg);}

boolean JViewSet::handleJEvent(JEvent& e) {
  switch (e.id) {
    case JEvent::GLOBAL_KEY_PRESS:
    case JEvent::GLOBAL_KEY_ACTION:
    case JEvent::GLOBAL_KEY_RELEASE:
      if (!needEvent(GLOBAL_KEYBOARD_MASK)) return false;
      break;
    case JEvent::GLOBAL_MOUSE_MOVE:
    case JEvent::GLOBAL_MOUSE_DOWN:
    case JEvent::GLOBAL_MOUSE_ACTION:
    case JEvent::GLOBAL_MOUSE_UP:
      if (!needEvent(GLOBAL_MOUSE_MASK)) return false;
      break;
    case JEvent::KEY_PRESS:
    case JEvent::KEY_ACTION:
    case JEvent::KEY_RELEASE:
      if (!needEvent(KEYBOARD_MASK)) return false;
      break;
    case JEvent::GOT_FOCUS:
    case JEvent::LOST_FOCUS:
      if (!needEvent(FOCUS_MASK)) return false;
      break;
    case JEvent::MIXER_LINE_NOTIFY:
    case JEvent::MIXER_CONTROL_NOTIFY:
      if (!needEvent(MIXER_MASK)) return false;
      break;
  }
  forEachChild(DoHandleJEvent, (void**)&e);
  return true;
}

void DoGetProperties(const JObject* obj, void** arg) {
  JArray properties = ((JViewObj*)obj)->getProperties();
  JArray &collection = *(JArray*)arg[0];
  JDictionary &dict = *(JDictionary*)arg[1];
  int sz = properties.size();
  for (int i=0; i<sz; i++) {
    JProperty &prop = *(JProperty*)properties[i];
    if (!dict[prop.getName()]) {
      dict.add(prop.getName(), prop);
      collection.append(prop);
    }
  }
}

JArray JViewSet::getProperties() {
  JArray properties;
  JDictionary dict(101);
  void* arg[] = { &properties, &dict};
  forEachChild(DoGetProperties, arg);
  return properties;
}

void DoUpdateProperty(const JObject* obj, void** arg) 
{ ((JViewObj*)obj)->updateProperty(*(JProperty*)arg);}

boolean JViewSet::updateProperty(JProperty& prop) { 
  forEachChild(DoUpdateProperty, (void**)&prop);
  return false;
}

boolean JViewSet::isOpaque() { return true;}
