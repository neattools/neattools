#include "JScrambledStringProperty.h"
#include "JInteger.h"
#include "JInputBox.h"

char* sdata = "1938238172";

JString JScrambledStringProperty::scramble(JString src) {
  int len = src.length();
  if (len == 0) return src;
  int i, N = ((len+1)/10+1)*10;
  char *buf = new char[N+1];
  unsigned char ch = 0;
  for (i=0; i<N; i++) {
    if (i <= len) 
      buf[i] = (ch = (((src[i]^sdata[i%10])+ch)&127))+128;
    else buf[i] = (ch = (((0^sdata[i%10])+ch)&127))+128;
  }
  buf[0] = ((buf[0]-128+ch)&127)+128;
  buf[i] = 0;
  return JString(buf, JString::needDel);
}

JString JScrambledStringProperty::unscramble(JString src) {
  int N = src.length();
  if (N == 0) return src;
  char *buf = new char[N+1];
  int i = N-1;
  unsigned char ch = (src[i]-128);
  src[0] = ((src[0]-128-ch)&127)+128;
  buf[i] = 0;
  ch = 0;
  for (i=0; i<N; i++) {
     buf[i] = ((src[i]-128-ch)^sdata[i%10])&127;
     ch = src[i]-128;
  }
  return JString(buf, JString::needDel);
}

char* theJScrambledStringProperty = JScrambledStringProperty().Register();

void JScrambledStringProperty::writeContent(JOutputStream& os) {
  JProperty::writeContent(os);
  putString(os, "value", scramble(value));
}

void JScrambledStringProperty::readContent(JDictionary& dict) {
  JProperty::readContent(dict);
  value = unscramble(getString(dict, "value"));
}

JScrambledStringProperty::JScrambledStringProperty() {}
JScrambledStringProperty::JScrambledStringProperty(JString name, JString _value) 
  : JStringProperty(name, _value) {}

const char* JScrambledStringProperty::className() const { return "JScrambledStringProperty";}
JObject* JScrambledStringProperty::clone() const { return new JScrambledStringProperty(*this);}

