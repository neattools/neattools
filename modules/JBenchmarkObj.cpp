#include "JBenchmarkObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JInteger.h"
#include "JSystem.h"

char* theJBenchmarkObj = JBenchmarkObj().Register();
const char* JBenchmarkObj::className() const { return "JBenchmarkObj";}
JObject* JBenchmarkObj::clone() const { return new JBenchmarkObj(*this);}

void JBenchmarkObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Test"), rect);
}

JString JBenchmarkObj::inputTag(int n) { 
  char* tag[] = { "input", "enable(logical)"};
  return tag[n];
}

void JBenchmarkObj::engine(int n, JLinkObj& link) {
  if (!n) {
//    link.access(JIntegerData(v[0]));
  } else {
    int oldv = v[1];
    link.access(JIntegerData(v[1]));
    v[1] = (v[1] != 0);
    if ((v[1] != oldv) && !v[1]) {
      int time = JSystem::currentTimeMillis();
      for (int i=0; i<1000000; i++) 
        broadcast(0);
      time = JSystem::currentTimeMillis()-time;
      JComponent::debug(JInteger::toJString(time)+" ms");
    }
  }
}

