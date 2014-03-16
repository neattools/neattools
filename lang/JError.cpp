#include "JError.h"

const char* JError::className() const { return "JError";}
JError::JError() {}
JError::JError(JString message) : JThrowable(message) {}
