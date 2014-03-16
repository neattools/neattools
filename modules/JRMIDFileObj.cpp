#include "JRMIDFileObj.h"
#include "JWaveOutObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JSystem.h"
#include "JFileProperty.h"
#include "JIntegerListProperty.h"
#include "JIOException.h"
#include "JEOFException.h"
#include "JMath.h"
#include "JWindow.hpp"

char* theJRMIDFileObj = JRMIDFileObj().Register();		   
const char* JRMIDFileObj::className() const { return "JRMIDFileObj";}
JObject* JRMIDFileObj::clone() const { return new JRMIDFileObj(*this);}

JRMIDFileObj::JRMIDFileObj() {
  isRMID = true;
  type = "*.rmi";
  filename = composit(prefix, sequence);
}

JRMIDFileObj::~JRMIDFileObj() { close();}

