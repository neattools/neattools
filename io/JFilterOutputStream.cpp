#include "JFilterOutputStream.h"

char* theJFilterOutputStream = JFilterOutputStream().Register();
const char* JFilterOutputStream::className() const { return "JFilterOutputStream";}
JObject* JFilterOutputStream::clone() const { return new JFilterOutputStream(*this);}
JFilterOutputStream::JFilterOutputStream() : out(null) {}
JFilterOutputStream::JFilterOutputStream(JOutputStream &_out) : out(&_out) {}
void JFilterOutputStream::connect(JOutputStream &_out) { initialize(); out = &_out;}
JOutputStream& JFilterOutputStream::operator<<(const JBlock &B) { (*out) << B; return *this;}
void JFilterOutputStream::flush() { if (out) out->flush();}
void JFilterOutputStream::close() { if (out) out->close();}
void JFilterOutputStream::initialize() {}

