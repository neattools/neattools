#include "JIOException.h"

const char* JIOException::className() const { return "JIOException";}
JIOException::JIOException() {}
JIOException::JIOException(JString message) : JException(message) {}
