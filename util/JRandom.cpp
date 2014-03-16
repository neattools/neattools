#include "JRandom.h"
#include "JSystem.h"

long JRandom::multiplier = 0x7F123463;
long JRandom::addend = 0xB;

char* theJRandom = JRandom().Register();
const char* JRandom::className() const { return "JRandom";}
int JRandom::hashCode() const { return seed;}
JObject* JRandom::clone() const { return new JRandom(*this);}
int JRandom::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return seed - ((JRandom*)&s)->seed;
}

JRandom::JRandom() { setSeed(JSystem::currentTimeMillis());}
JRandom::JRandom(long _seed) { setSeed(_seed);}
void JRandom::setSeed(long _seed) { seed = (_seed^multiplier)&hashMask;}
int JRandom::next() { return (int)(seed = (seed*multiplier+addend)&hashMask);}
int JRandom::nextInt(int mask) { return next()%mask;}
float JRandom::nextFloat() { return (float(next()))/hashMask;}
double JRandom::nextDouble() { return (double(next()))/hashMask;}

