#include "JANDObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"

#if defined(_NEAT_DLL)
  DllExport
#endif
char* theJANDObj = JANDObj().Register();
void JANDObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "NB", NB);
}

void JANDObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  updateNB(NB = getInteger(dict, "NB"));
}

const char* JANDObj::className() const { return "JANDObj";}
JObject* JANDObj::clone() const { return new JANDObj(*this);}

JANDObj::JANDObj() {
  NB = 16;
  mask = 0xFFFF;
}

JString JANDObj::inputTag(int n) 
{ return JAddObj::inputTag(n)+NBTag();}

JString JANDObj::outputTag(int n)
{ return JAddObj::outputTag(n)+NBTag();}

void JANDObj::draw(JGraphics g, int x, int y, int w, int h) {
  int y2 = y+h-1;
  g.drawLine(x, y, x+(w-1)/2, y);
  g.drawLine(x, y, x, y2);
  g.drawLine(x, y2, x+(w-1)/2, y2);
  g.drawArc(x, y, w, h, -(90 << 6), 180 << 6);
}

void DoANDEngin(const JObject* obj, void** arg) { 
  int val = 0;
  ((JLinkObj*)obj)->access(JIntegerData(val));
  *(int*)arg &= val;
}

void JANDObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  inputSet(n).forEachChild(DoANDEngin, 
    (void**)&(value = mask));
  if (value != oldv)
    broadcast(0);
}

JArray JANDObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("N bit(s)", NB, 1, 32));
  return properties;
}

boolean JANDObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N bit(s)")) {
    if (updateNB(((JIntegerProperty*)&prop)->value)) 
      broadcast(0);
    return true;
  }
  return false;
}

boolean JANDObj::updateNB(int _NB) {
  if (!_NB) _NB = 16;
  _NB = max(1, min(32, _NB));
  mask = 0xFFFFFFFF >> (32-_NB);
  if (NB != _NB) {
    value = matchBack(value, _NB);
    NB = _NB;
    return true;
  }
  return false;
}

JString JANDObj::NBTag() { 
  if (NB == 1) return JString("(")+JInteger::toJString(NB)+"bit)";
  return JString("(")+JInteger::toJString(NB)+"bits)";
}

int JANDObj::matchNB(int v, int nb) {
  if (NB > nb) v <<= (NB-nb);
  else if (NB < nb) v >>= (nb-NB);
  return v;
}

int JANDObj::matchBack(int v, int nb) {
  if (NB > nb) v >>= (NB-nb);
  else if (NB < nb) v <<= (nb-NB);
  return v;
}
