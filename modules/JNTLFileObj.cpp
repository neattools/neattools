#include "JNTLFileObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JFile.h"
#include "JIntegerData.h"
#include "JIntegerListProperty.h"
#include "JFileProperty.h"

char* theJNTLFileObj = JNTLFileObj().Register();
void JNTLFileObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "needSave", needSave);
  putString(os, "fname", fname);
}

void JNTLFileObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  needSave = getInteger(dict, "needSave");
  fname = getString(dict, "fname");
  valid = check();
}

const char* JNTLFileObj::className() const { return "JNTLFileObj";}
JObject* JNTLFileObj::clone() const { return new JNTLFileObj(*this);}
boolean JNTLFileObj::check() { return JFile(fname).exists();}

JNTLFileObj::JNTLFileObj() {
  igm = 1;
  ogm = 0;
  type = "*.ntl";
  fname = "untitle.ntl";
  enabled = valid = needSave = false;
  valid = check();
}

void JNTLFileObj::draw(JGraphics g, int x, int y, int w, int h) {
  if (!valid) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, JString("NTL"), rect1);
  drawText(g, fname, rect2);
}

boolean JNTLFileObj::inputAllowed(int n) { return !inputSet(n).last();}
int JNTLFileObj::inputFace(int n) { return TOP;}
JString JNTLFileObj::inputTag(int n) { return "enabled(logical)";}
JFRect JNTLFileObj::inputArea(int n) { return topArea(n, 0, igm);}
JFPoint JNTLFileObj::inputPoint(int n, JLinkObj& link) { return topPoint(n, link, 0, igm);}

static int executing = 0;

void JNTLFileObj::engine(int n, JLinkObj& link) {
  if (!valid) return;
  link.access(JIntegerData(enabled));
  enabled = (enabled != 0);
  if (enabled && !executing) {
    executing++;
    JComponent* pRoot = parent->getRoot();
    if (pRoot) {
      JEvent event(this, JEvent::CHILD_NOTIFY);
      event.key = EXECUTE_MODE;
      event.modifiers = needSave;
      pRoot->childNotify(event, &fname);
    }
    executing--;
  }
  repaint();
}

JArray JNTLFileObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JFileProperty("filename", fname, type));
  properties.append(JIntegerListProperty("needSave", needSave, 
    JIntegerListProperty::booleanTag));
  return properties;
}

boolean JNTLFileObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("needSave")) {
    needSave = ((JIntegerListProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("filename")) {
    fname = ((JFileProperty*)&prop)->value;
    valid = check();
    repaint();
    return true;
  }
  return false;
}

