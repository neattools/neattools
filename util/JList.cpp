#include "JList.h"
#include "JInteger.h"

class JCell : public JObject {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JCell(const JObject& o, JCell* n = null);
    JCell(const JCell& c);
    virtual ~JCell();
    JCell& operator=(const JCell& c);
    JObject* obj;
    JCell* next;
};

#define CELL(x) ((JCell*)x)
char* theJList = JList().Register();

const char* JCell::className() const { return "JCell";}
JObject* JCell::clone() const { return new JCell(*this);}
JCell::JCell(const JObject& o, JCell* n): obj(o.clone()) { next = n;}
JCell::JCell(const JCell& c) { *this=c;}
JCell::~JCell() { DelPObj(obj);}

JCell& JCell::operator=(const JCell& c) {
  obj = c.obj->clone();
  next = c.next;
  return *this;
}

void DoWriteJList(const JObject* obj, void** arg) { 
  JObject::putObject(*(JOutputStream*)arg[0], 
    JInteger::toJString(--(*(int*)arg[1])), *(JObject*)obj);
}

void JList::writeContent(JOutputStream& os) {
  int sz = size();
  void* arg[] = { &os, &sz};
  JObject::writeContent(os);
  putInteger(os, "size", sz);
  forEach(DoWriteJList, arg);
}

void JList::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  int sz = getInteger(dict, "size");
  JObject *obj;
  *this = JList();
  for (int i=0; i<sz; i++) {
    obj = getObject(dict, JInteger::toJString(i));
    if (obj) add(*obj);
  }
}

const char* JList::className() const { return "JList";}
JObject* JList::clone() const { return new JList(*this);}
void JList::forEach(iterFuncType func, void** arg) const {
  JCell *c = CELL(hnd), *np;
  while (c) {
    np = c->next;
    c->obj->forEach(func, arg);
    c = np;
  }
}

JObject* JList::firstThat(condFuncType func, void** arg) const {
  JCell *c = CELL(hnd), *np;
  while (c) {
    np = c->next;
    if (c->obj->firstThat(func, arg))
      return c->obj;
    c = np;
  }
  return null;
}

void JList::Delete() { 
  JCell* c = CELL(hnd), *np;
  while (c) {
    np = c->next;
    delete c;
    c = np;
  }
}

int JList::Duplicate() { 
  JCell* c = (JCell*)CELL(hnd)->clone();
  int nhnd = (int)c;
  while (c) {
    if (c->next)
      c->next = (JCell*)c->next->clone();
    c = c->next;
  }
  return nhnd;
}

int JList::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  JList &a = *(JList*)&s;
  if (hnd == a.hnd) return 0;
  if (size() != a.size()) return size()-a.size();
  JCell* c = CELL(hnd);
  JCell* d = CELL(a.hnd);
  while (c) {
    if (*c->obj != *d->obj) 
      return (c->obj)->compareTo(*d->obj);
    c = c->next;
    d = d->next;
  }
  return 0;
}

JList::JList() {}
JList::JList(const JObject& o)
{ Allocate((int)new JCell(o));}
JList::~JList() { Release();}

JObject* JList::swap(const JObject& o1, const JObject& o2) {
  if (!hnd) return false;
  JCell *c = CELL(hnd);
  JCell *c1 = null, *c2 = null;
  while (c) {
    if (*c->obj == o1) c1 = c;
    else if (*c->obj == o2) c2 = c;
    c = c->next;
  }
  if (c1 && c2) {
    JObject *temp = c1->obj;
    c1->obj = c2->obj;
    c2->obj = temp;
    return temp;
  }
  return null;
}

JObject* JList::add(const JObject& o) {
  if (hnd) {
    hnd = (int)new JCell(o, CELL(hnd));
  } else Allocate((int)new JCell(o));
  return CELL(hnd)->obj;
}

JObject* JList::replace(const JObject& o, const JObject& no) {
  JCell *c = CELL(hnd);
  while (c) {
    if (*c->obj == o) {
      delete c->obj;
      c->obj = no.clone();
      return c->obj;
    }
    c = c->next;
  }
  return null;
}

JObject* JList::del(const JObject& o) {
  if (!hnd) return false;
  JCell *c = CELL(hnd);
  if (*c->obj == o) {
    c = CELL(hnd);
    hnd = (int)c->next;
    delete c;
    return c;
  }
  JCell *pc = c;
  c = c->next;
  while (c) {
    if (*c->obj == o) {
      pc->next = c->next;
      delete c;
      return c;
    }
    c = (pc=c)->next;
  }
  return null;
}

JObject* JList::del(int index) {
  if (!hnd) return false;
  JCell *c = CELL(hnd);
  if (!index) {
    c = CELL(hnd);
    hnd = (int)c->next;
    delete c;
    return c;
  }
  JCell *pc = c;
  c = c->next;
  while (c) {
    if (!--index) {
      pc->next = c->next;
      delete c;
      return c;
    }
    c = (pc=c)->next;
  }
  return null;
}

boolean DoIndexOf(const JObject* obj, void** arg) { 
  ++*(int*)arg[1]; 
  if (*obj != *(JObject*)arg[2]) return false;
  *(int*)arg[0] = *(int*)arg[1];
  return true;
}

int JList::indexOf(const JObject& o) {
  int index = -1, count = -1;
  void* arg[] = { &index, &count, (void*)&o};
  *firstThat(DoIndexOf, arg);
  return index;
}

boolean DoHas(const JObject* obj, void** arg)
{ return *obj == *(JObject*)arg;}

JObject* JList::operator[](const JObject& o)
{ return firstThat(DoHas, (void**)&o);}

boolean DoIndexHas(const JObject* obj, void** arg)
{ return --(*(int*)arg) < 0;}

JObject* JList::operator[](int index)
{ return firstThat(DoIndexHas, (void**)&index);}

JObject* JList::first()
{ return (hnd) ? CELL(hnd)->obj : null;}

boolean JList::isEmpty() { return (hnd == null);}

void DoSize(const JObject*, void** arg) { ++(*(int*)arg);}

int JList::size() const {
  int sz = 0;
  forEach(DoSize, (void**)&sz);
  return sz;
}

void JList::reset(int index) { ptr = CELL(hnd);}
JObject* JList::current() { return (ptr) ? CELL(ptr)->obj : null;}
void JList::next() { ptr = CELL(ptr)->next;}

