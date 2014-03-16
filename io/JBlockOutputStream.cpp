#include "JBlockOutputStream.h"

char* theJBlockOutputStream = JBlockOutputStream().Register();
const char* JBlockOutputStream::className() const { return "JBlockOutputStream";}
JObject* JBlockOutputStream::clone() const { return new JBlockOutputStream(*this);}
JBlockOutputStream::JBlockOutputStream() : out(null) { pos = 0;}
JBlockOutputStream::JBlockOutputStream(JBlock &_out) : out(&_out) { pos = 0;}
JBlockOutputStream::~JBlockOutputStream() { close();}

void JBlockOutputStream::connect(JBlock &_out) {
  if (out) close(); 
  out = &_out; 
  pos = 0;
}

void JBlockOutputStream::close() { if (out) out->setSize(pos);}

JOutputStream& JBlockOutputStream::operator<<(const JBlock &B) {
  int sz = B.size();
  if (pos+sz > out->size())
    out->grow(max(pos+sz, out->size() << 1));
  JBlock(sz, ((char*)*out)+pos).copy(B);
  pos+=sz;
  return *this;
}

