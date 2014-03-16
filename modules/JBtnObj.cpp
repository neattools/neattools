#include "JBtnObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JStringProperty.h"
#include "JIntegerListProperty.h"

char* theJBtnObj = JBtnObj().Register();
void JBtnObj::writeContent(JOutputStream& os) {
  JNBitsObj::writeContent(os);
  putObject(os, "label", label);
  putInteger(os, "type", type);
}

void JBtnObj::readContent(JDictionary& dict) {
  JNBitsObj::readContent(dict);
  JObject *obj = getObject(dict, "label");
  if (obj) label = *(JString*)obj;
  type = getInteger(dict, "type");
}

const char* JBtnObj::className() const { return "JBtnObj";}
JObject* JBtnObj::clone() const { return new JBtnObj(*this);}
char* btnTypeTag[] = { "RECT", "LEFT", "RIGHT", "UP", "DOWN", null};

JBtnObj::JBtnObj() { 
  color = JColor::black;
  bkgnd = JColor::cyan.darker();
  igm = 3;
  type = TYPE_RECT;
  eventMask = MOUSE_MASK;
  mousePressed = false;
}

void JBtnObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  g.setJColor(moduleColor);
  g.draw3DJRect(getIExtent(dx, dy, scale), depth);
  update(g, dx, dy, rgn, scale);
}

void JBtnObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale), thumb;
  JRegion frgn(rect.shrinkBy(depth, depth));
  if ((rect.width > 0) && (rect.height > 0)) {
    g.setJColor(bkgnd);
    g.fillJRect(rect);
    thumb = rect.shrink(depth, depth);
    if ((thumb.width > 0) && (thumb.height > 0)) {
      switch (type) {
        case TYPE_RECT:
          g.draw3DJRect(thumb, ((value) ? -depth : depth));
          break;
        case TYPE_LEFT:
        case TYPE_RIGHT:
        case TYPE_UP:
        case TYPE_DOWN:
          g.draw3DJTriangle(thumb, 
            ((value) ? -depth : depth), type-1);
          break;
      }
      if (label.length()) {
        g.setJColor(color);
        drawText(g, label, thumb.shrink(depth, depth));
      }
    }
  }
}

boolean JBtnObj::mouseDown(JEvent& e, double x, double y) {
  if (e.modifiers & JEvent::LBUTTON) {
    if (inside(x, y)) {
      if (e.id == JEvent::MOUSE_DOWN) {
        mousePressed = true;
        setValue(mask);
      }
    }
  }
  return true;
}

boolean JBtnObj::mouseUp(JEvent& e, double x, double y) {
  if ((e.modifiers & JEvent::LBUTTON) && mousePressed) {
    mousePressed = false;
    setValue(0);
  }
  return true;
}

void JBtnObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int iv = value;
    link.access(JIntegerData(iv));
    setValue((iv) ? mask : 0);
  } else processColor(n, link);
}

boolean JBtnObj::setLabel(JString _label) {
  if (_label != label) {
    label = _label;
    repaint();
    return true;
  }
  return false;
}

JArray JBtnObj::getProperties() {
  JArray properties = JNBitsObj::getProperties();
  properties.append(JStringProperty("label", label));
  properties.append(JIntegerListProperty("type", type, btnTypeTag));
  return properties;
}

boolean JBtnObj::updateProperty(JProperty& prop) {
  if (JNBitsObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("label")) {
    setLabel(((JStringProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("type")) {
    type = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  }
  return false;
}

