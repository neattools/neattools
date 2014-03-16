#include "JBackgroundObj.h"
#include "JColorProperty.h"
#include "JIntegerListProperty.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JColorData.h"

char* theJBackgroundObj = JBackgroundObj().Register();
void JBackgroundObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putObject(os, "color", color);
  putObject(os, "textColor", textColor);
  putInteger(os, "drawBorder", drawBorder);
  putInteger(os, "drawBackground", drawBackground);
  putString(os, "text", text);
}

void JBackgroundObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  JObject *obj;
  obj = getObject(dict, "color");
  if (obj) color = *(JColor*)obj;
  obj = getObject(dict, "textColor");
  if (obj) textColor = *(JColor*)obj;
  drawBorder = getInteger(dict, "drawBorder");
  drawBackground = getInteger(dict, "drawBackground");
  text = getString(dict, "text");
}

const char* JBackgroundObj::className() const { return "JBackgroundObj";}
JObject* JBackgroundObj::clone() const { return new JBackgroundObj(*this);}

JBackgroundObj::JBackgroundObj(JColor _color) {
  igm = 0;
  ogm = 0;
  color = _color;
  drawBorder = false;
}

void JBackgroundObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  if (drawBorder && (rect.width > depth2) && (rect.height > depth2)) {
    g.setJColor(moduleColor);
    g.draw3DJRect(rect, depth);
  }
  update(g, dx, dy, rgn, scale);
}

void JBackgroundObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  g.setJColor(color);
  if (drawBorder && (rect.width > depth2) && (rect.height > depth2)) {
    g.fillJRect(rect.shrink(depth, depth));
  } else g.fillJRect(rect);
}

JArray JBackgroundObj::getProperties() {
  JArray properties = JModuleObj::getProperties();
  properties.append(JColorProperty("color", color));
  properties.append(JIntegerListProperty("drawBorder", drawBorder,
    JIntegerListProperty::booleanTag));
  return properties;
}

boolean JBackgroundObj::updateProperty(JProperty& prop) {
  if (JModuleObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("color")) {
    color = ((JColorProperty*)&prop)->color;
    repaintView(*this);
  } else if (prop.getName() == JString("drawBorder")) {
    drawBorder = ((JIntegerListProperty*)&prop)->value;
    repaintView(*this);
  }
  return true;
}

