#include "JArithmeticException.h"

const char* JArithmeticException::className() const { return "JArithmeticException";}
JArithmeticException::JArithmeticException() {}
JArithmeticException::JArithmeticException(JString message) : JRuntimeException(message) {}
