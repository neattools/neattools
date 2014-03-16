#include "JIllegalArgumentException.h"

const char* JIllegalArgumentException::className() const { return "JIllegalArgumentException";}
JIllegalArgumentException::JIllegalArgumentException() {}
JIllegalArgumentException::JIllegalArgumentException(JString message) : JRuntimeException(message) {}
