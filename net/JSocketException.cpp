#include "JSocketException.h"

const char* JSocketException::className() const { return "JSocketException";}
JSocketException::JSocketException() {}
JSocketException::JSocketException(JString message) : JIOException(message) {}
