#include "JProcessCreateException.h"

const char* JProcessCreateException::className() const { return "JThreadCreateException";}
JProcessCreateException::JProcessCreateException() {}
JProcessCreateException::JProcessCreateException(JString message) : JRuntimeException(message) {}
