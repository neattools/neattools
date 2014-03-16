#include "JEOFException.h"

const char* JEOFException::className() const { return "JEOFException";}
JEOFException::JEOFException() {}
JEOFException::JEOFException(JString message) : JIOException(message) {}
