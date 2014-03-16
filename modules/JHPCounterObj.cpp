#include "JHPCounterObj.h"
#include "JLinkObj.h"
#include "JRealData.h"
#include "JIntegerData.h"

#if defined(WIN32)
  #include <windows.h>
#endif

int JHPCounterObj::baseFrequency = 0;

char* theJHPCounterObj = JHPCounterObj().Register();
const char* JHPCounterObj::className() const { return "JHPCounterObj";}
JObject* JHPCounterObj::clone() const { return new JHPCounterObj(*this);}

JHPCounterObj::JHPCounterObj() {
  igm = IN_LAST;
  ogm = 1;
  value = 0.0;
#if defined(WIN32)
  LARGE_INTEGER li;
  if ((baseFrequency == 0) && QueryPerformanceFrequency(&li)) {
    baseFrequency = li.LowPart;
  }
  if (QueryPerformanceCounter(&li)) {
    baseCount = int64(li.LowPart, li.HighPart);
  }
#endif
}

void JHPCounterObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("HPC"), rect);
}

void JHPCounterObj::access(int n, JLinkObj& link, const JDataType& data) 
{ DOUBLE(data) = value;}

boolean JHPCounterObj::inputAllowed(int n)
{ return !inputSet(n).last();}
boolean JHPCounterObj::outputAllowed(int n)
{ return true;}

int JHPCounterObj::outputType(int n) { return JRealData::id;}

JString JHPCounterObj::inputTag(int n) {
  return "trigger(logical)";
}

JFRect JHPCounterObj::inputArea(int n) { 
  return topArea(n, 0, IN_LAST);
}

int JHPCounterObj::inputFace(int n) { 
  return TOP;
}

JFPoint JHPCounterObj::inputPoint(int n, JLinkObj& link) { 
  return topPoint(n, link, 0, IN_LAST);
}

void JHPCounterObj::engine(int n, JLinkObj& link) {
  if (n == IN_TRIGGER) {
    int iv;
    link.access(JIntegerData(iv));
    if (iv != 0) {
#if defined(WIN32)
      if (baseFrequency) {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
	int64 newCount(li.LowPart, li.HighPart);
	int64 delta = newCount-baseCount;
	value = (((double)delta.hi)*0xFFFFFFFF+delta.lo)/baseFrequency;
        baseCount = newCount;
      }
#endif

      broadcast(0);
    }
  }
}

