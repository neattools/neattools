#include "JNullPointerException.h"

const char* JNullPointerException::className() const { return "JNullPointerException";}
JNullPointerException::JNullPointerException() {}
JNullPointerException::JNullPointerException(JString message) : JRuntimeException(message) {}
