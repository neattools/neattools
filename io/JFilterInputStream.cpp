#include "JFilterInputStream.h"
#include "JString.h"
#include "JBlock.h"

char* theJFilterInputStream = JFilterInputStream().Register();
const char* JFilterInputStream::className() const { return "JFilterInputStream";}
JObject* JFilterInputStream::clone() const { return new JFilterInputStream(*this);}
JFilterInputStream::JFilterInputStream() : in(null) {}
JFilterInputStream::JFilterInputStream(JInputStream &_in) : in(&_in) {}
void JFilterInputStream::connect(JInputStream &_in) { initialize(); in = &_in;}
JInputStream& JFilterInputStream::operator>>(const JBlock &B) { (*in) >> B; return *this;}
JInputStream& JFilterInputStream::operator>>(JString &v) 
{ return JInputStream::operator>>(v);}
long JFilterInputStream::skip(long n) { return in->skip(n);}
int JFilterInputStream::available() { return in->available();}
void JFilterInputStream::close() { if (in) in->close();}
void JFilterInputStream::mark(int readLimit) { in->mark(readLimit);}
void JFilterInputStream::reset() { in->reset();}
boolean JFilterInputStream::markSupported() { return in->markSupported();}
void JFilterInputStream::initialize() {}

