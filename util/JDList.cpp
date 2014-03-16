#include "JDList.h"

class JDCell : public JObject {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDCell(const JObject& o, JDCell* n = null);
    JDCell(const JDCell& c);
    virtual ~JDCell();
    JDCell& operator=(const JDCell& c);
    void setup(JDCell* n);
    JObject *obj;
    JDCell *next, *prev;
};

#define CELL(x) ((JDCell*)x)
char* theJDList = JDList().Register();

const char* JDCell::className() const { return "JDCell";}
JObject* JDCell::clone() const { return new JDCell(*this);}
JDCell::JDCell(const JObject& o, JDCell* n): obj(o.clone())
{ setup(n);}
JDCell::JDCell(const JDCell& c) { *this=c;}
JDCell::~JDCell() { DelPObj(obj);}

JDCell& JDCell::operator=(const JDCell& c) {
  obj = c.obj->clone();
  if (c.next != &c) {
    next = c.next;
    prev = c.prev;
  } else next = prev = this;
  return *this;
}

void JDCell::setup(JDCell *n) {
  if (n) {
    next = n;
    prev = n->prev;
    prev->next = this;
    n->prev = this;
  } else next = prev = this;
}

const char* JDList::className() const { return "JDList";}
JObject* JDList::clone() const { return new JDList(*this);}
void JDList::forEach(iterFuncType func, void** arg) const {
  if (!hnd) return;
  JDCell *c, *np = CELL(hnd);
  JDCell *last = np->prev;
  do {
    np = (c = np)->next;
    c->obj->forEach(func, arg);
  } while (c != last);
}

JObject* JDList::firstThat(condFuncType func, void** arg) const {
  if (!hnd) return null;
  JDCell *c, *np = CELL(hnd);
  JDCell *last = np->prev;
  do {
    np = (c = np)->next;
    if (c->obj->firstThat(func, arg))
      return c->obj;
  } while (c != last);
  return null;
}

JObject* JDList::lastThat(condFuncType func, void** arg) const {
  if (!hnd) return null;
  JDCell *last = CELL(hnd);
  JDCell *c, *np = last->prev;
  do {
    np = (c = np)->prev;
    if (c->obj->lastThat(func, arg))
      return c->obj;
  } while (c != last);
  return null;
}

void JDList::Delete() {
  JDCell* c = CELL(hnd), *np;
  do {
    np = c->next;
    delete c;
    c = np;
  } while ((int)c != hnd);
}

int JDList::Duplicate() { 
  JDCell* c = (JDCell*)CELL(hnd)->clone();
  int nhnd = (int)c;
  while ((int)c->next != hnd) {
    c->next = (JDCell*)c->next->clone();
    c->next->prev = c;
    c = c->next;
  }
  c->next = CELL(nhnd);
  c->next->prev = c;
  return nhnd;
}

int JDList::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  JDList &a = *(JDList*)&s;
  if (hnd == a.hnd) return 0;
  if (size() != a.size()) return size()-a.size();
  JDCell* c = CELL(hnd);
  JDCell* d = CELL(a.hnd);
  do {
    if (*c->obj != *d->obj) 
      return (c->obj)->compareTo(*d->obj);
    c = c->next;
    d = d->next;
  } while ((int)c != hnd);
  return 0;
}

JDList::JDList() {}
JDList::JDList(const JObject& o)
{ Allocate((int)new JDCell(o));}
JDList::~JDList() { Release();}

JObject* JDList::toFirst(const JObject& obj) {
  if (!hnd) return false;
  JDCell *c = CELL(hnd);
  JDCell *head = c;
  do {
    if (*c->obj == obj) {
      if (c == head) return c->obj;
      if (c->next != c) {
	c->prev->next = c->next;
	c->next->prev = c->prev;
      } else return c->obj;
      c->setup(head);
      hnd = (int)c;
      return c->obj;
    }
    c = c->next;
  } while ((int)c != hnd);
  return null;
}

JObject* JDList::toLast(const JObject& obj) {
  if (!hnd) return false;
  JDCell *c = CELL(hnd);
  JDCell *head = c;
  do {
    if (*c->obj == obj) {
      if (c == head) {
	hnd = (int)c->next;
	return c->obj;
      }
      if (c->next != c) {
	c->prev->next = c->next;
	c->next->prev = c->prev;
      } else return c->obj;
      c->setup(head);
      return c->obj;
    }
    c = c->next;
  } while ((int)c != hnd);
  return null;
}

JObject* JDList::reparent(const JObject& o, JDList& np) {
  if (!hnd) return false;
  JDCell *c = CELL(hnd);
  do {
    if (*c->obj == o) {
      if ((int)c == hnd) {
       c = CELL(hnd);
       hnd = (int)c->next;
      }
      if (c->next != c) {
	c->prev->next = c->next;
	c->next->prev = c->prev;
      } else {
        hnd = null;
        Release();
      }
      c->setup(CELL(np.hnd));
      if (!np.hnd) np.Allocate((int)c);
      return c->obj;
    }
    c = c->next;
  } while ((int)c != hnd);
  return null;
}

JObject* JDList::add(const JObject& o) {
  if (hnd) {
    hnd = (int)new JDCell(o, CELL(hnd));
  } else Allocate((int)new JDCell(o));
  return CELL(hnd)->obj;
}

JObject* JDList::append(const JObject& o) {
  if (hnd) new JDCell(o, CELL(hnd));
  else Allocate((int)new JDCell(o));
  return CELL(hnd)->prev->obj;
}

JObject* JDList::replace(const JObject& o, const JObject& no) {
  if (!hnd) return false;
  JDCell *c = CELL(hnd);
  do {
    if (*c->obj == o) {
      delete c->obj;
      c->obj = no.clone();
      return c->obj;
    }
    c = c->next;
  } while ((int)c != hnd);
  return null;
}

JObject* JDList::del(const JObject& o) {
  if (!hnd) return false;
  JDCell *c = CELL(hnd);
  do {
    if (*c->obj == o) {
      if (c->next != c) {
	if ((int)c == hnd) {
	  c = CELL(hnd);
	  hnd = (int)c->next;
	}
	c->prev->next = c->next;
	c->next->prev = c->prev;
        delete c;
      } else Release();
      return c;
    }
    c = c->next;
  } while ((int)c != hnd);
  return null;
}

JObject* JDList::del(int index) {
  if (!hnd) return false;
  JDCell *c = CELL(hnd);
  do {
    if (!index--) {
      if (c->next != c) {
	if ((int)c == hnd) {
	  c = CELL(hnd);
	  hnd = (int)c->next;
	}
	c->prev->next = c->next;
	c->next->prev = c->prev;
        delete c;
      } else Release();
      return c;
    }
    c = c->next;
  } while ((int)c != hnd);
  return null;
}

JObject* JDList::last()
{ return (hnd) ? CELL(hnd)->prev->obj : null;}

void JDList::reset(int index) { 
  if (!index) ptr = CELL(hnd);
  else ptr = (hnd) ? CELL(hnd)->prev : null;
}

JObject* JDList::current() { return (ptr) ? CELL(ptr)->obj : null;}

void JDList::next() { 
  ptr = CELL(ptr)->next;
  if (ptr == CELL(hnd)) ptr = null;
}

void JDList::prev() { 
  if (ptr == CELL(hnd)) ptr = null;
  else ptr = CELL(ptr)->prev;
}
