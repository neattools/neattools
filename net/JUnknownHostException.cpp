#include "JUnknownHostException.h"

const char* JUnknownHostException::className() const { return "JUnknownHostException";}
JUnknownHostException::JUnknownHostException() {}
JUnknownHostException::JUnknownHostException(JString message) : JIOException(message) {}

