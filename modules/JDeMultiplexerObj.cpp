#include "JDeMultiplexerObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JMath.h"
#if defined(WIN32)
  #include <windows.h>
#endif

char* theJDeMultiplexerObj = JDeMultiplexerObj().Register();
void JDeMultiplexerObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "N", N);
  putInteger(os, "select", select);
  putInteger(os, "sendResetEvent", sendResetEvent);
}

void JDeMultiplexerObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  N = getInteger(dict, "N");
  N = max(2, min(512, N));
  select = getInteger(dict, "select");
  sendResetEvent = getInteger(dict, "sendResetEvent", true);
  ogm = N;
}

const char* JDeMultiplexerObj::className() const { return "JDeMultiplexerObj";}
JObject* JDeMultiplexerObj::clone() const { return new JDeMultiplexerObj(*this);}

JDeMultiplexerObj::JDeMultiplexerObj() {
  N = 2;
  select = 0;
  ogm = N;
  igm = IN_LAST;
  typeCounter = valueCounter = 0;
  sendResetEvent = true;
}

void JDeMultiplexerObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("DeMux"), rect);
}

void JDeMultiplexerObj::access(int n, JLinkObj& link, const JDataType& data) {
  if (n == select) {
    JLinkObj* prev = (JLinkObj*)inputSet(0).first();
    if (prev) {
      if (!valueCounter++) 
        prev->access(data);
      valueCounter--;
    } else data.reset();
  } else data.reset();
}

int JDeMultiplexerObj::inputType(int n) {
  if (!n) return outputType(n);
  return JIntegerData::id;
}

int JDeMultiplexerObj::outputType(int n) { 
  int i;
  int type = JDataType::last;
  JLinkObj* link = (JLinkObj*)inputSet(0).first();
  if (link) {
    if (!typeCounter++)
      type = link->from->outputType(link->fn);
    typeCounter--;
  }
  if (type == JDataType::last) {
    link = null;
    for (i=0; (i<ogm) && !link; i++)
      link = (JLinkObj*)outputSet(i).first();
    if (link) {
      if (!typeCounter++)
        type = link->to->inputType(link->tn);
      typeCounter--;
    }
  }
  return type;
}

boolean JDeMultiplexerObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JDeMultiplexerObj::inputTag(int n) {
  char* tag[] = {"input", "N(2-512)", "select"};
  return JString(tag[n]);
}

JString JDeMultiplexerObj::outputTag(int n) {
  return JString("out-")+JInteger::toJString(n);
}

JFRect JDeMultiplexerObj::inputArea(int n) {
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, IN_LAST-1);
}

JFRect JDeMultiplexerObj::outputArea(int n) 
{ return rightArea(n, 0, N, 0, 1);}

JFPoint JDeMultiplexerObj::inputPoint(int n, JLinkObj& link) {
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, IN_LAST-1);
}

JFPoint JDeMultiplexerObj::outputPoint(int n, JLinkObj& link) 
{ return rightPoint(n, link, 0, N, 0, 1);}

void JDeMultiplexerObj::engine(int n, JLinkObj& link) {
  if (n == IN_N) {
    int _N;
    link.access(JIntegerData(_N));
    updateN(_N);
  } else if (n == IN_SELECT) {
    int _select;
    link.access(JIntegerData(_select));
    updateSelect(_select);
  } else broadcast(select);
}

JArray JDeMultiplexerObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("N", N, 2, 512));
  properties.append(JIntegerProperty("select", select, 0, N-1));
  properties.append(JIntegerListProperty("sendResetEvent", sendResetEvent, 
    JIntegerListProperty::booleanTag));
  return properties;
}

boolean JDeMultiplexerObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("select")) {
    updateSelect(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("sendResetEvent")) {
    sendResetEvent = ((JIntegerListProperty*)&prop)->value;
    return true;
  }
  return false;
}

void JDeMultiplexerObj::updateN(int _N) {
  int oldv = N;
  JFRect rect = calculateOutputUpdate();
  N = max(2, min(512, _N));
  if (N != oldv) {
    ogm = N;
    updateSelect(JMath::imod(select, N));
    rect |= calculateOutputUpdate();
    repaintView(rect);
  }
}

void JDeMultiplexerObj::updateSelect(int _select) {
  int oldv = select;
  select = JMath::imod(_select, N);
  if (select != oldv) {
    if (sendResetEvent) broadcast(oldv);
    broadcast(select);
  }
}

