#include "JRuntimeException.h"

const char* JRuntimeException::className() const { return "JRuntimeException";}
JRuntimeException::JRuntimeException() {}
JRuntimeException::JRuntimeException(JString message) : JException(message) {}

