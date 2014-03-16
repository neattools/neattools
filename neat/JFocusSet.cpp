#include "JFocusSet.h"
#include "JLinkObj.h"
#include "JObjectPtr.h"

char* theJFocusSet = JFocusSet().Register();
const char* JFocusSet::className() const { return "JFocusSet";}
JObject* JFocusSet::clone() const { return new JFocusSet(*this);}
JFocusSet::JFocusSet() {}

void JFocusSet::remove() {
  JViewSet::remove();
  delAll();
}

JViewObj* JFocusSet::extract(JObject* obj) 
{ return (JViewObj*)OPTR(obj);}

extern void DoUngroup(const JObject* obj, void** arg);

void JFocusSet::ungroup(JViewSet& np, JFocusSet& set) {
  void* arg[] = {&np, &set};
  forEachChild(DoUngroup, arg);
}

JViewObj* JFocusSet::add(JViewObj& obj) 
{ children.append(JObjectPtr(&obj)); return &obj;}
void JFocusSet::del(JViewObj& obj) { children.del(JObjectPtr(&obj));}
JViewObj* JFocusSet::operator[](JViewObj& obj)
{ return extract(children[obj]);}
JViewObj* JFocusSet::operator[](int index)
{ return extract(children[index]);}
JViewObj* JFocusSet::first()
{ return extract(children.first());}
JViewObj* JFocusSet::last() 
{ return extract(children.last());}

void DoToFront(const JObject* obj, void** arg) 
{ ((JViewObj*)obj)->toFront();}

void JFocusSet::toFront() 
{ forEachChild(DoToFront);}

boolean DoToBack(const JObject* obj, void** arg) 
{ ((JViewObj*)obj)->toBack(); return false;}

void JFocusSet::toBack()
{ lastChildThat(DoToBack);}

void JFocusSet::toggle(JViewObj& newObj) {
  if ((*this)[newObj]) del(newObj);
  else add(newObj);
}

void DoToggle(const JObject* obj, void** arg) 
{ ((JFocusSet*)arg)->toggle(*(JViewObj*)obj);}

void JFocusSet::toggle(JFocusSet& newSet) {
  newSet.forEachChild(DoToggle, (void**)this);
}

void DoFocusDuplicate(const JObject* obj, void** arg)
{ ((JFocusSet*)arg[2])->add(*((JViewObj*)obj)->duplicate((JViewSet*)arg[0], (JDictionary*)arg[1]));}

void DoLinkRebuild(const JObject* obj, void** arg) { 
  JLinkObj *link = (JLinkObj*)obj;
  JDictionary &dict = *(JDictionary*)arg;
  JPObject *fp = (JPObject*)dict[JPObject(link->from)];
  JPObject *tp = (JPObject*)dict[JPObject(link->to)];
  if (fp && tp) {
    link = (JLinkObj*)link->duplicate();
    link->from = (JModuleObj*)(JObject*)(*fp);
    link->to = (JModuleObj*)(JObject*)(*tp);
    link->addSelf();
  }
}

JViewObj* JFocusSet::duplicateFocus(JViewSet& linkSet, JViewSet* _parent) {
  JFocusSet newSet;
  JDictionary dict(101);
  void* arg[] = { _parent, &dict, &newSet};
  forEachChild(DoFocusDuplicate, arg);
  linkSet.forEachChild(DoLinkRebuild, (void**)&dict);
  newSet.reshape(*this);
  *this = newSet;
  return null;
}
