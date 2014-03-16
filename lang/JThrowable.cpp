#include "JThrowable.h"

const char* JThrowable::className() const { return "JThrowable";}
JThrowable::JThrowable() { detailMessage = EMPTY;}
JThrowable::JThrowable(JString message) { detailMessage = message;}
JString JThrowable::getMessage() const { return detailMessage;}
