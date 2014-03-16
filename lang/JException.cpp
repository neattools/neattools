#include "JException.h"

const char* JException::className() const { return "JException";}
JException::JException() {}
JException::JException(JString message) : JThrowable(message) {}
