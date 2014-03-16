#include "JArray.h"
#include "JInteger.h"
#include "JString.h"
#include <string.h>

struct JArrayStruct {
  int capacity;
  int size;
  JObject* array[1];
};

#define ALLOC(s) ((int)(new JObject*[(s+2)]))
#define POBJ(x) (((JArrayStruct*)x)->array)
#define CAPACITY(x) (((JArrayStruct*)x)->capacity)
#define SIZE(x) (((JArrayStruct*)x)->size)
char* theJArray = JArray().Register();

void JArray::writeContent(JOutputStream& os) {
  int sz = size();
  JObject** buf = POBJ(hnd);
  JObject::writeContent(os);
  putInteger(os, "size", sz);
  for (int i=0; i<sz; i++) {
    if (buf[i])
      putObject(os, JInteger::toJString(i), *buf[i]);
  }
}

void JArray::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  int sz = getInteger(dict, "size");
  JObject *obj;
  *this = JArray(sz);
  for (int i=0; i<sz; i++) {
    obj = getObject(dict, JInteger::toJString(i));
    if (obj) set(i, *obj);
  }
}

const char* JArray::className() const { return "JArray";}
JObject* JArray::clone() const { return new JArray(*this);}
void JArray::forEach(iterFuncType func, void** arg) const {
  int sz = size();
  JObject** buf = POBJ(hnd);
  for (int i=-1; ++i<sz;)
    if (buf[i]) buf[i]->forEach(func, arg);
}

JObject* JArray::firstThat(condFuncType func, void** arg) const {
  int sz = size();
  JObject** buf = POBJ(hnd);
  for (int i=-1; ++i<sz;)
    if (buf[i] && buf[i]->firstThat(func, arg))
      return buf[i];
  return null;
}

JObject* JArray::lastThat(condFuncType func, void** arg) const {
  JObject** buf = POBJ(hnd);
  for (int i=size(); i-->0;)
    if (buf[i] && buf[i]->lastThat(func, arg))
      return buf[i];
  return null;
}

void JArray::Delete() {
  JObject** buf = POBJ(hnd);
  for (int i=size(); i-->0;)
    delete buf[i];
  delete (JObject**)hnd;
}

int JArray::Duplicate() {
  int sz = size();
  int thnd = ALLOC(sz);
  JObject** buf = POBJ(hnd);
  JObject** tmp = POBJ(thnd);
  CAPACITY(thnd) = SIZE(thnd) = sz;
  for (int i=sz; i-->0;)
    tmp[i] = DupPObj(buf[i]);
  return thnd;
}

int JArray::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  JArray &a = *(JArray*)&s;
  if (hnd == a.hnd) return 0;
  if (size() != a.size()) return size()-a.size();
  JObject** buf = POBJ(hnd);
  for (int i=size(); i-->0;) {
    if (buf[i] && a[i]) {
      if (buf[i] != a[i])
        return buf[i]->compareTo(*a[i]);
    } else if (buf[i] != a[i])
    return buf[i]-a[i];
  }
  return 0;
}

JArray::JArray() {}

JArray::JArray(int s) : 
  JReference(ALLOC(s), true) {
  CAPACITY(hnd) = SIZE(hnd) = s;
  memset(POBJ(hnd), 0, s*sizeof(JObject*));
}

JArray::JArray(char** sa) {
  for (int i=0; sa[i]; i++)
    append(JString(sa[i]));
}

void DoArraySetup(const JObject* obj, void** arg) 
{ POBJ(arg[0])[(*(int*)arg[1])++] = obj->clone();}

JArray::JArray(JList& list) {
  int sz = list.size();
  Allocate(ALLOC(sz));
  CAPACITY(hnd) = SIZE(hnd) = sz;
  void* arg[] = { (void*)hnd, &(sz = 0)};
  list.forEach(DoArraySetup, arg);
}

JArray::~JArray() { Release();}
JObject* JArray::operator[](int index) const { return POBJ(hnd)[index];}

JObject* JArray::operator[](const JObject& s) const { 
  int index = indexOf(s);
  return (index > -1) ? POBJ(hnd)[index] : null;
}

JObject* JArray::set(int index, const JObject& s) {
  JObject* &cell = POBJ(hnd)[index];
  return SetPObj(cell, &s);
}

void JArray::free(int index) {
  JObject* &cell = POBJ(hnd)[index];
  SetPObj(cell, (JObject*)null);
}

void JArray::grow(int ns, const JObject& fill) {
  if (ns <= size()) return;
  int os = size();
  setSize(ns);
  if (&fill) {
    for (int i=os; i<ns; i++)
      set(i, fill);
  }
}
int JArray::size() const { return (hnd) ? SIZE(hnd) : 0;}
int JArray::capacity() const { return (hnd) ? CAPACITY(hnd) : 0;}

int JArray::setSize(int ns) const {
  int sz = size();
  if (ns < sz) {
    JObject** buf = POBJ(hnd);
    for (int i=ns; i<sz; i++) {
      if (buf[i]) {
        DelPObj(buf[i]);
      }
    }
    if (hnd) SIZE(hnd) = ns;
  }
  ensureCapacity(ns);
  if (hnd) SIZE(hnd) = ns;
  return ns;
}

void JArray::ensureCapacity(int minCapacity) const {
  int oldCapacity = capacity();
  if ((minCapacity > oldCapacity) ||
      (minCapacity <= (oldCapacity-6)/4)) {
    int newCapacity = (minCapacity > oldCapacity) ?
      max(minCapacity, (oldCapacity+1)*2) :
      (minCapacity+1)*2;
    int thnd = (int)ALLOC(newCapacity);
    JObject** tmp = POBJ(thnd);
    int sz = SIZE(thnd) = min(newCapacity, size());
    CAPACITY(thnd) = newCapacity;
    if (sz) {
      JObject** buf = POBJ(hnd);
      memcpy(tmp, buf, sz*sizeof(JObject*));
      memset(buf, 0, sz*sizeof(JObject*));
    }
    memset(tmp+sz, 0, (newCapacity-sz)*sizeof(JObject*));
    ((JArray*)this)->Allocate(thnd);
  }
}

boolean JArray::isEmpty() const { return (size() == 0);}

int JArray::indexOf(const JObject& s, int index) const {
  int sz = size();
  JObject** buf = POBJ(hnd);
  for (int i=index; i<sz; i++) 
    if (buf[i] && (*buf[i] == s)) return i;
  return -1;
}

int JArray::lastIndexOf(const JObject& s, int index) const {
  JObject** buf = POBJ(hnd);
  if (index == -1) index = size();
  for (int i=index; i-->0;) 
    if (buf[i] && (*buf[i] == s)) return i;
  return -1;
}

JObject* JArray::first() { return (size() > 0) ? POBJ(hnd)[0] : null;}
JObject* JArray::last() { return (size() > 0) ? POBJ(hnd)[size()-1] : null;}

void JArray::del(int index, int n) {
  int i, sz = size();
  if (sz < index+n) return;
  JObject** buf = POBJ(hnd);
  for (i=0; i<n; i++) DelPObj(buf[index+i]);
  memmove(buf+index, buf+index+n, 
    (sz-index-n)*sizeof(JObject*));
  memset(buf+(sz-=n), 0, n*sizeof(JObject*));
  setSize(sz);
}

void JArray::del(const JObject& s) {
  int index = indexOf(s);
  if (index > -1) del(index);
}

void JArray::delAll() { setSize(0);}

JObject* JArray::add(const JObject& s) { return insert(s);}

JObject* JArray::insert(const JObject& s, int index, int n) {
  int sz = size();
  setSize(sz+n);
  JObject** buf = POBJ(hnd);
  memmove(buf+index+n, buf+index, 
    (sz-index)*sizeof(JObject*));
  sz = index+n;
  for (int i=index; i<sz; i++) {
    buf[i] = null;
    SetPObj(buf[i], &s);
  }
  return buf[index];
}

JObject* JArray::insert(int index, int n) {
  int sz = size();
  setSize(sz+n);
  JObject** buf = POBJ(hnd);
  memmove(buf+index+n, buf+index, 
    (sz-index)*sizeof(JObject*));
  sz = index+n;
  for (int i=index; i<sz; i++) 
    buf[i] = null;
  return buf[index];
}

JObject* JArray::append(const JObject& s) {
  int sz = size();
  setSize(sz+1);
  JObject** buf = POBJ(hnd);
  return SetPObj(buf[sz], &s);
}

JObject* JArray::toFirst(const JObject& s) {
  int index = indexOf(s);
  if (index == -1) return null;
  JObject** buf = POBJ(hnd);
  if (index > 0) {
    JObject* tmp = buf[index];
    memmove(buf+1, buf,
      index*sizeof(JObject*));
    buf[0] = tmp;
    return tmp;
  }
  return buf[index];
}

JObject* JArray::toLast(const JObject& s) {
  int index = indexOf(s);
  if (index == -1) return null;
  int sz = size();
  JObject** buf = POBJ(hnd);
  if (index < sz-1) {
    JObject* tmp = buf[index];
    memmove(buf+index, buf+index+1,
      (sz-index-1)*sizeof(JObject*));
    buf[sz-1] = tmp;
    return tmp;
  }
  return buf[index];
}

JObject* JArray::reparent(const JObject& s, JArray& np) {
  int index = indexOf(s);
  if (index == -1) return false;
  JObject** buf = POBJ(hnd);
  JObject* tmp = buf[index];
  buf[index] = null;
  del(index);
  np.setSize(np.size()+1);
  POBJ(np.hnd)[np.size()-1] = tmp;
  return tmp;
}

void JArray::sort() { 
  if (size() < 2) return;
  quickSort(0, size()-1);
}

void JArray::quickSort(int from, int to) {
  int i = from, j = to;
  JObject** buf = POBJ(hnd);
  JObject* x = buf[(i+j)/2];
  do {
    while (*x > *buf[i]) i++;
    while (*buf[j] > *x) j--;
    if (i<=j) {
      JObject* temp = buf[i];
      buf[i] = buf[j];
      buf[j] = temp;
      i++; j--;
    }
  } while (i<=j);
  if (from<j) quickSort(from, j);
  if (i<to) quickSort(i, to);
}

void JArray::swap(int a, int b) {
  JObject** buf = POBJ(hnd);
  JObject* temp = buf[a];
  buf[a] = buf[b];
  buf[b] = temp;
}
