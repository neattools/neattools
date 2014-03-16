#include "JFileArray.h"
#include "JBlock.h"
#include "JIOException.h"
#include "JEOFException.h"

/*
'FARY', sz, cap, posFree, eof,
ptr[0..cap-1],
cell[0..]

allocated cell = [? or index, sz, data]
free cell = [next, sz, ???]

posFree: point to the first free cell or eof
eof: point to the end of file.
*/

char* theJFileArray = JFileArray().Register();

#define ISZ ((int)sizeof(int))
#define ISZ2 (ISZ+ISZ)

const char* JFileArray::className() const { return "JFileArray";}
JObject* JFileArray::clone() const { return new JFileArray(*this);}

int JFileArray::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  JFileArray &a = *(JFileArray*)&s;
  return fio.compareTo(a.fio);
}

JFileArray::JFileArray() 
{ sz = cap = posFree = eof = 0; readOnly = true;}

JFileArray::JFileArray(JString fname, boolean _readOnly) 
{ open(fname, _readOnly);}

JFileArray::~JFileArray() { close();}

void JFileArray::open(JString fname, boolean _readOnly) { 
  sz = cap = posFree = eof = 0;
  posTable = ((char*)&pad)-header;
  readOnly = _readOnly;
  try {
    if (!readOnly) {
      fio.open(fname);
      fin.open((int)fio);
    } else fin.open(fname);
    fin >> JBlock(posTable, header);
    if (JString(JBlock(ISZ, header)) == "FARY") return;
  } catch (JEOFException* e) {
    delete e;
  } catch (JIOException* e) {
    delete e;
  }
  if (!readOnly) {
    fio.close();
    fio.open(fname);
    fin.open((int)fio);
    JBlock(ISZ, header).copy(JBlock(ISZ, "FARY"));
    sz = cap = 0;
    posFree = eof = posTable;
    fio << JBlock(posTable, header);
  } else fin.close();
}

void JFileArray::close() {
  if (!eof) return;
  updateHeader();
  if (!readOnly) fio.close();
  else fin.close();
  sz = cap = eof = 0; 
  readOnly = true;
}

void JFileArray::updateHeader() {
  if (!eof || readOnly) return;
  fio.seek(0);
  fio << JBlock(posTable, header);
}

int JFileArray::size() const { return sz;}

int JFileArray::setSize(int ns) {
  if (readOnly) return sz;
  if (ns < sz) {
    for (int i=ns; i<sz; i++) 
      free(i);
    sz = ns;
  }
  ensureCapacity(ns);
  return (sz = ns);
}

boolean JFileArray::isValid() { return (int)fin != 0;}
boolean JFileArray::isEmpty() { return !sz;}
boolean JFileArray::isReadOnly() { return readOnly;}

void JFileArray::set(int index, const JBlock& data) {
  if (readOnly) return;
  if (index >= sz) return;
  int ds = data.size();
  if (!ds) {
    free(index);
    return;
  }
  int pos = posTable+index*ISZ;
  int ptr = getFInt(pos);
  if (ptr) {
    if (ds == getFInt(ptr+ISZ)) {
      putFBlock(ptr+ISZ2, data);      
      return;
    }
    free(index);
  }
  if (posFree < eof) {
    int fs, prev, next;
    prev = 0;
    ptr = next = posFree;
    do {
      next = getFInt(ptr);
      fs = getFInt(ptr+ISZ);
      if ((fs == ds) || (fs > ds+ISZ2)) {
	int delta = fs-ds-ISZ2;
	int nptr = ptr+ISZ2+delta;
	putFInt(pos, nptr);
	putFData(nptr, index, data);
	if (fs == ds) {
          if (ptr == posFree) posFree = next;
          else putFInt(prev, next);
	} else putFInt(ptr+ISZ, delta);
	return;
      }
      prev = ptr;
      ptr = next;
    } while (ptr < eof);
    putFInt(prev, eof+=ISZ2+ds);
  } else {
    ptr = eof;
    eof += ISZ2+ds;
    posFree = eof;
  }
  putFInt(pos, ptr);
  putFData(ptr, index, data);
}

JBlock JFileArray::get(int index) {
  if (index >= sz) return JBlock();
  int ptr = getFInt(posTable+index*ISZ);
  if (ptr) return getFBlock(ptr);
  return JBlock();
}

void JFileArray::free(int index) {
  if (readOnly) return;
  if (index >= sz) return;
  int pos = posTable+index*ISZ, next;
  int ptr = getFInt(pos);
  if (ptr) {
    if (ptr < posFree) {
      next = posFree;
      posFree = ptr;
      putFInt(ptr, next);
      checkMerge(ptr, next);
    } else {
      int prev = posFree;
      do {
        next = getFInt(prev);
        if (next > ptr) {
          putFInt(prev, ptr);
          putFInt(ptr, next);
          checkMerge(ptr, next);
          checkMerge(prev, ptr);
	  break;
	}
	prev = next;
      } while (next != eof);
    }
    putFInt(pos, 0);
  }
}

void JFileArray::add(const JBlock& data) { insert(data);}
void JFileArray::append(const JBlock& data) { insert(data, sz);}
void JFileArray::insert(const JBlock& data, int index, int n) {
  if (readOnly) return;
  insert(index, n);
  int sz = index+n;
  for (int i=index; i<sz; i++)
    set(i, data);
}

void JFileArray::insert(int index, int n) {
  if (readOnly) return;
  if (index >= sz) {
    setSize(sz+n);
    return;
  }
  setSize(sz+n);
  int src = posTable+index*ISZ;
  int delta = ISZ*n;
  fmove(src+delta, src, (sz-index-n)*ISZ);
  fset(src, 0, delta);
}

void JFileArray::del(int index, int n) {
  if (readOnly) return;
  if (index+n > sz) return;
  int i;
  for (i=0; i<n; i++) free(index+i);
  int delta = n*ISZ;
  int ds = (sz-index-n)*ISZ;
  int dest = posTable+index*ISZ;
  fmove(dest, dest+delta, ds);
  fset(dest+ds, 0, delta);
  setSize(sz-=n);
}

void JFileArray::delAll() { setSize(0);}
void JFileArray::swap(int a, int b) {
  if (readOnly) return;
  if ((a >= sz) || (b >= sz)) return;
  int pa = posTable+a*ISZ;
  int pb = posTable+b*ISZ;
  int temp = getFInt(pa);
  putFInt(pa, getFInt(pb));
  putFInt(pb, temp);
}

void JFileArray::compact() {
  if (readOnly) return;
  int pos = posTable+cap*ISZ;
  if (pos < eof) {
    int i, ptr;
    int p = posTable;
    for (i=0; i<sz; i++, p+=ISZ) {
      ptr = getFInt(p);
      if (ptr) putFInt(ptr, i);
    } // Fill Cell with Index
    int cpos = pos;
    int next, dSize, delta;
    do {
      next = getFInt(cpos);
      if (next >= pos) {
        delta = getFInt(cpos+ISZ)+ISZ2;
        cpos += delta;
        while ((cpos < eof) &&
          ((i=getFInt(cpos)) < pos)) {
          dSize = getFInt(cpos+ISZ)+ISZ2;
          fmove(posFree, cpos, dSize);
          putFInt(posTable+i*ISZ, posFree);
          cpos += dSize;
          posFree += dSize;
        }
        putFInt(posFree, next);
        putFInt(posFree+ISZ, delta-ISZ2);
        checkMerge(posFree, cpos);
        cpos = posFree;
      } else cpos += getFInt(cpos+ISZ)+ISZ2;
    } while (cpos < eof);
  }
}

int JFileArray::capacity() const { return cap;}

int JFileArray::setCapacity(int nc) {
  if (readOnly) return cap;
  int pos = posTable+cap*ISZ; 
  int npos = posTable+nc*ISZ; 
  if (nc > cap) {
    if (pos < eof) {
      int i, ptr, delta;
      int cpos = pos;
      int p = posTable;
      for (i=0; i<sz; i++, p+=ISZ) {
        ptr = getFInt(p);
	if (ptr) putFInt(ptr, i);
      } // Fill Cell with Index
      do {
	if (cpos == posFree) {
	  delta=getFInt(posFree+ISZ)+ISZ2;
	  posFree = getFInt(posFree);
	} else delta=relocate(getFInt(cpos))+ISZ2;
	cpos+=delta;
      } while ((cpos != npos) && (cpos <= npos+ISZ2));
      if (cpos != npos) {
	putFInt(npos, posFree);
	putFInt(npos+ISZ, cpos-npos-ISZ2);
	posFree = npos;
      }
    } else posFree = eof = npos;
    fset(pos, 0, npos-pos);
  } else if (nc < cap) {
    if (pos == eof) {
      posFree = eof = npos;
      fio.truncate(eof);
    } else {
      if (pos-npos > ISZ2) {
	putFInt(npos, posFree);
	putFInt(npos+ISZ, pos-npos-ISZ2);
	checkMerge(npos, posFree);
	posFree = npos;
      } else nc = cap;
    }
  }
  return (cap = nc);
}

void JFileArray::ensureCapacity(int minCapacity) {
  int oldCapacity = capacity();
  if ((minCapacity > oldCapacity) ||
      (minCapacity <= (oldCapacity-6)/4)) {
    int newCapacity = (minCapacity > oldCapacity) ?
      max(minCapacity, (oldCapacity+1)*2) :
      (minCapacity+1)*2;
    setCapacity(newCapacity);
  }
}

int JFileArray::relocate(int index) {
  int pos = posTable+index*ISZ;
  int ptr = getFInt(pos);
  if (!ptr) return 0;
  JBlock data = getFBlock(ptr);
  int ds = data.size();
  if (posFree < eof) {
    int prev = ptr = posFree;
    do {
      prev = ptr;
      ptr = getFInt(ptr);
    } while (ptr < eof);
    putFInt(prev, eof+=ISZ2+ds);
  } else {
    ptr = eof;
    eof += ISZ2+ds;
    posFree = eof;
  }
  putFInt(pos, ptr);
  putFData(ptr, index, data);
  return ds;
}

int JFileArray::getFInt(int pos) {
  int v;
  fin.seek(pos);
  fin >> JBlock(v);
  return v;
}

void JFileArray::putFInt(int pos, int v) {
  fio.seek(pos);
  fio << JBlock(v);
}

JBlock JFileArray::getFBlock(int pos, int ds) {
  JBlock data(ds, 0);
  fin.seek(pos);
  fin >> data;
  return data;
}

JBlock JFileArray::getFBlock(int pos) {
  JBlock data(getFInt(pos+ISZ), 0);
  fin.seek(pos+ISZ2);
  fin >> data;
  return data;
}

void JFileArray::putFBlock(int pos, JBlock data) {
  fio.seek(pos);
  fio << data;
}

void JFileArray::putFData(int pos, int index, JBlock data) {
  fio.seek(pos);
  int ds = data.size();
  fio << JBlock(index)+JBlock(ds)+data;
}

boolean JFileArray::checkMerge(int p1, int p2) {
  int sz1 = getFInt(p1+ISZ);
  if (p1+sz1+ISZ2 == p2) {
    if (p2 != eof) {
      putFInt(p1, getFInt(p2));
      putFInt(p1+ISZ, sz1+getFInt(p2+ISZ)+ISZ2);
    } else fio.truncate(eof = p1);
    return true;
  }
  return false;
}

#define MAXFMOVE 32768
void JFileArray::fmove(int dest, int src, int size) {
  if (size < MAXFMOVE) {
    if (!size) return;
    JBlock data(size, 0);
    fio.seek(src);
    fio >> data;
    fio.seek(dest);
    fio << data;
  } else {
    int delta, count;
    JBlock data(MAXFMOVE, 0);
    if (dest > src) {
      count = size;
      while (size) {
        delta = min(MAXFMOVE, size);
	data.setSize(delta);
	count -= delta;
        fio.seek(src+count);
        fio >> data;
        fio.seek(dest+count);
        fio << data;
        size -= delta;
      }
    } else {
      count = 0;
      while (size) {
        delta = min(MAXFMOVE, size);
	data.setSize(delta);
        fio.seek(src+count);
        fio >> data;
        fio.seek(dest+count);
        fio << data;
        size -= delta;
	count += delta;
      }
    }
  }
}

void JFileArray::fset(int pos, int fill, int size) {
  if (size < MAXFMOVE) {
    if (!size) return;
    fio.seek(pos);
    fio << JBlock(size, fill);
  } else {
    int delta;
    JBlock data(MAXFMOVE, fill);
    fio.seek(pos);
    while (size) {
      delta = min(MAXFMOVE, size);
      data.setSize(delta);
      fio << data;
      size -= delta;
    }
  }
}
