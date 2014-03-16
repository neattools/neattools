#include "JInterruptedIOException.h"

const char* JInterruptedIOException::className() const { return "JInterruptedIOException";}
JInterruptedIOException::JInterruptedIOException() {}
JInterruptedIOException::JInterruptedIOException(JString message) : JIOException(message) {}
