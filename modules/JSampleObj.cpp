#include "JSampleObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"

char* theJSampleObj = JSampleObj().Register();
void JSampleObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "N", N);
}

void JSampleObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  N = getInteger(dict, "N");
  N = max(1, min(512, N));
  igm = N+IN_LAST;
  ogm = N;
}

const char* JSampleObj::className() const { return "JSampleObj";}
JObject* JSampleObj::clone() const { return new JSampleObj(*this);}

JSampleObj::JSampleObj() {
  N = 1;
  igm = N+IN_LAST;
  ogm = N;
  control = 0;
  typeCounter = valueCounter = 0;
}

void JSampleObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/5;
  int by = (h-dy*2)/2;
  int kx = max(3, w/15);
  int sx = kx/2;
  int my = h/2;
  int mx = w/2;
  g.drawLine(x+bx, y+my, x+bx+dx, y+my);
  g.drawLine(x+bx+dx*2, y+my, x+bx+dx*3, y+my);
  g.fillOval(x+bx+dx-sx, y+my-sx, kx, kx);
  g.fillOval(x+bx+dx*2-sx, y+my-sx, kx, kx);
  g.drawLine(x+bx+dx, y+by+dy*2, x+mx, y+by+dy*2);
  g.drawLine(x+mx, y+by+dy*2, x+mx, y+by);
  g.drawLine(x+mx, y+by, x+bx+dx*2, y+by);
}

void JSampleObj::access(int n, JLinkObj& link, const JDataType& data) { 
  if (control) {
    JLinkObj* prev = (JLinkObj*)inputSet(n+IN_LAST).first();
    if (prev) {
      if (!valueCounter++) 
        prev->access(data);
      valueCounter--;
    }
  }
}

int JSampleObj::inputType(int n) {
  if ((n-=IN_LAST) < 0) return JIntegerData::id;
  return outputType(n);
}

int JSampleObj::outputType(int n) { 
  int type = JDataType::last;
  JLinkObj* link = (JLinkObj*)inputSet(n+IN_LAST).first();
  if (link) {
    if (!typeCounter++)
      type = link->from->outputType(link->fn);
    typeCounter--;
  }
  if (type == JDataType::last) {
    link = (JLinkObj*)outputSet(n).first();
    if (link) {
      if (!typeCounter++)
        type = link->to->inputType(link->tn);
      typeCounter--;
    }
  }
  return type;
}

boolean JSampleObj::inputAllowed(int n)
{ return (boolean)((n == IN_CONTROL) ? true : !inputSet(n).last());}

JString JSampleObj::inputTag(int n) {
  if (n < IN_LAST) {
    char* tag[] = {"N(1-512)", "control(logical)"};
    return tag[n];
  }
  return JString("in-")+JInteger::toJString(n-IN_LAST);
}

JString JSampleObj::outputTag(int n) 
{ return JString("out-")+JInteger::toJString(n);}

JFRect JSampleObj::inputArea(int n) {
  if (n<IN_LAST) return topArea(n, 0, IN_LAST);
  return leftArea(n, IN_LAST, N, 0, 1);
}

JFRect JSampleObj::outputArea(int n)
{ return rightArea(n, 0, N, 0, 1);}

int JSampleObj::inputFace(int n) 
{ return (n<IN_LAST) ? TOP : LEFT;}

JFPoint JSampleObj::inputPoint(int n, JLinkObj& link) {
  if (n<IN_LAST) return topPoint(n, link, 0, IN_LAST);
  return leftPoint(n, link, IN_LAST, N, 0, 1);
}

JFPoint JSampleObj::outputPoint(int n, JLinkObj& link) 
{ return rightPoint(n, link, 0, N, 0, 1);}

void JSampleObj::engine(int n, JLinkObj& link) {
  if (n == IN_N) {
    int _N;
    link.access(JIntegerData(_N));
    updateN(_N);
  } else if (n == IN_CONTROL) {
    int oldv = control;
    link.access(JIntegerData(control));
    control = (control != 0);
    if (control != oldv) {
      if (control) {
	for (int i=0; i<N; i++)
          broadcast(i);
	control = false;
      }
    }
  }
}

JArray JSampleObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("N", N, 1, 512));
  return properties;
}

boolean JSampleObj::updateProperty(JProperty& prop) {
  if (JModuleObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value);
    return true;
  }
  return false;
}

void JSampleObj::updateN(int _N) {
  int oldv = N;
  JFRect rect = calculateInputUpdate();
  rect |= calculateOutputUpdate();
  N = max(1, min(512, _N));
  if (N != oldv) {
    igm = N+IN_LAST;
    ogm = N;
    rect |= calculateInputUpdate();
    rect |= calculateOutputUpdate();
    repaintView(rect);
  }
}