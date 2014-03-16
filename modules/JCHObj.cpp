#include "JCHObj.h"
#include "JBytesData.h"
#include "JInteger.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JLinkObj.h"

char* theJCHObj = JCHObj().Register();
void JCHObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putInteger(os, "channel", channel);
  putInteger(os, "separator", separator);
  putInteger(os, "counter", counter);
  putInteger(os, "inverse", inverse);
  putInteger(os, "factor", factor);
}

void JCHObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  channel = getInteger(dict, "channel");
  separator = getInteger(dict, "separator");
  counter = getInteger(dict, "counter");
  inverse = getInteger(dict, "inverse");
  factor = getInteger(dict, "factor");
  factor = max(1, min(256, factor));
}

const char* JCHObj::className() const { return "JCHObj";}
JObject* JCHObj::clone() const { return new JCHObj(*this);}

JCHObj::JCHObj(int _channel) {
  channel = _channel;
  separator = 255; 
  factor = 16;
  counter = 0;
  sequence = 0;
  inverse = false;
}

void JCHObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    g.drawLine(rect.x+depth2, 
      rect.y+depth2+depth2, 
      rect.x+kw+1, rect.y+depth2+depth2);
    if (!inverse)
      g.drawLine(rect.x+depth2+depth2, 
        rect.y+depth2, 
        rect.x+depth2+depth2, rect.y+kw+1);
  }
  if (channel == -1) {
    int dx = w/5;
    int bx = (w-dx*3)/2;
    int dy = h/3;
    int by = (h-dy)/2;
    int xx[] = { x+bx, x+bx+dx, x+bx+dx, 
      x+bx+dx*2, x+bx+dx*2, x+bx+dx*3};
    int yy[] = { y+by+dy, y+by+dy, y+by, 
      y+by, y+by+dy, y+by+dy};
    g.drawPolygon(xx, yy, 6);
  } else drawText(g, JString("Ch")+JInteger::toJString(channel), rect);
}

JString JCHObj::inputTag(int n) { return "input";}
int JCHObj::inputType(int n) { return JBytesData::id;}

void JCHObj::processByte(int v) {
  if (v == separator) sequence++;
  if (sequence%factor) return;
  if (channel == -1) {
    if (v == separator) {
      value = (inverse) ? 0 : mask;
      broadcast(0);
    } else {
      if (value != 0) {
        value = (inverse) ? mask : 0;
        broadcast(0);
      }
    }
  } else {
    if (v == separator) {
      counter = 0;
    } else if (counter++ == channel) {
      v = matchNB(v, 8);
      if (inverse) 
	value = mask-v;
      else value = v;
      broadcast(0);
    }
  }
  sequence = 0;
}

void JCHObj::engine(int n, JLinkObj& link) {
  JBlock block;
  link.access(JBlockData(block));
  int size = block.size();
  for (int i=0; i<size; i++)
    processByte((uchar)block[i]);
}

JArray JCHObj::getProperties() {
  JArray properties = JNOTObj::getProperties();
  properties.append(JIntegerProperty("channel", channel, -1, 4));
  properties.append(JIntegerProperty("factor", factor, 1, 256));
  properties.append(JIntegerListProperty("inverse", inverse, 
    JIntegerListProperty::booleanTag));
  return properties;
}

boolean JCHObj::updateProperty(JProperty& prop) {
  if (JNOTObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("channel")) {
    channel = ((JIntegerProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("factor")) {
    factor = ((JIntegerProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("inverse")) {
    inverse = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  }
  return false;
}

void JCHObj::addButton(JComponent* panel) { 
  addModuleButton(panel, JCHObj(0));
  addModuleButton(panel, JCHObj(1));
  addModuleButton(panel, JCHObj(2));
  addModuleButton(panel, JCHObj(3));
  addModuleButton(panel, JCHObj(-1));
}
