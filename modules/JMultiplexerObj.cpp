#include "JMultiplexerObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JMath.h"
#if defined(WIN32)
  #include <windows.h>
#endif

char* theJMultiplexerObj = JMultiplexerObj().Register();
void JMultiplexerObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "N", N);
  putInteger(os, "select", select);
}

void JMultiplexerObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  N = getInteger(dict, "N");
  N = max(2, min(512, N));
  select = getInteger(dict, "select");
  igm = N+IN_LAST;
}

const char* JMultiplexerObj::className() const { return "JMultiplexerObj";}
JObject* JMultiplexerObj::clone() const { return new JMultiplexerObj(*this);}

JMultiplexerObj::JMultiplexerObj() {
  N = 2;
  select = 0;
  igm = N+IN_LAST;
  typeCounter = valueCounter = 0;
}

void JMultiplexerObj::access(int n, JLinkObj& link, const JDataType& data) { 
  JLinkObj* prev = (JLinkObj*)inputSet(select+IN_LAST).first();
  if (prev) {
    if (!valueCounter++) 
      prev->access(data);
    valueCounter--;
  } else data.reset();
}

int JMultiplexerObj::inputType(int n) {
  if ((n-=IN_LAST) < 0) return JIntegerData::id;
  return outputType(n);
}

int JMultiplexerObj::outputType(int n) { 
  int i;
  int type = JDataType::last;
  JLinkObj* link = null;
  for (i=0; (i<N) && !link; i++)
    link = (JLinkObj*)inputSet(i+IN_LAST).first();
  if (link) {
    if (!typeCounter++)
      type = link->from->outputType(link->fn);
    typeCounter--;
  }
  if (type == JDataType::last) {
    link = (JLinkObj*)outputSet(0).first();
    if (link) {
      if (!typeCounter++)
        type = link->to->inputType(link->tn);
      typeCounter--;
    }
  }
  return type;
}

void JMultiplexerObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Mux"), rect);
}

boolean JMultiplexerObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JMultiplexerObj::inputTag(int n) {
  if (n < IN_LAST) {
    char* tag[] = { "N(2-512)", "select"};
    return tag[n];
  }
  return JString("in-")+JInteger::toJString(n-IN_LAST);
}

JFRect JMultiplexerObj::inputArea(int n) {
  if (n<IN_LAST) return topArea(n, 0, IN_LAST);
  return leftArea(n, IN_LAST, N, 0, 1);
}

int JMultiplexerObj::inputFace(int n)
{ return (n<IN_LAST) ? TOP : LEFT;}

JFPoint JMultiplexerObj::inputPoint(int n, JLinkObj& link) {
  if (n<IN_LAST) return topPoint(n, link, 0, IN_LAST);
  return leftPoint(n, link, IN_LAST, N, 0, 1);
}

void JMultiplexerObj::engine(int n, JLinkObj& link) {
  if (n == IN_N) {
    int _N = N;
    link.access(JIntegerData(_N));
    updateN(_N);
  } else if (n == IN_SELECT) {
    int _select;
    link.access(JIntegerData(_select));
    updateSelect(_select);
  } else if (n == select+IN_LAST) broadcast(0);
}

JArray JMultiplexerObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("N", N, 2, 512));
  properties.append(JIntegerProperty("select", select, 0, N-1));
  return properties;
}

boolean JMultiplexerObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("select")) {
    updateSelect(((JIntegerProperty*)&prop)->value);
    return true;
  }
  return false;
}

void JMultiplexerObj::updateN(int _N) {
  int oldv = N;
  JFRect rect = calculateInputUpdate();
  N = max(2, min(512, _N));
  if (N != oldv) {
    igm = N+IN_LAST;
    updateSelect(JMath::imod(select, N));
    rect |= calculateInputUpdate();
    repaintView(rect);
  }
}

void JMultiplexerObj::updateSelect(int _select) {
  int oldv = select;
  select = JMath::imod(_select, N);
  if (select != oldv) broadcast(0);
}

