#include "JClassReferenceException.h"

const char* JClassReferenceException::className() const { return "JClassReferenceException";}
JClassReferenceException::JClassReferenceException() {}
JClassReferenceException::JClassReferenceException(JString message) : JIOException(message) {}
