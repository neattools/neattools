#include "JThreadCreateException.h"

const char* JThreadCreateException::className() const { return "JThreadCreateException";}
JThreadCreateException::JThreadCreateException() {};
JThreadCreateException::JThreadCreateException(JString message) : JRuntimeException(message) {}
