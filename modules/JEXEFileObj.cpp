#include "JEXEFileObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JFile.h"
#include "JIntegerData.h"
#include "JIntegerListProperty.h"
#include "JStringProperty.h"
#include "JFileProperty.h"

char* theJEXEFileObj = JEXEFileObj().Register();
void JEXEFileObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putString(os, "fname", fname);
  putString(os, "params", params);
}

void JEXEFileObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  fname = getString(dict, "fname");
  params = getString(dict, "params");
  valid = check();
}

const char* JEXEFileObj::className() const { return "JEXEFileObj";}
JObject* JEXEFileObj::clone() const { return new JEXEFileObj(*this);}
boolean JEXEFileObj::check() { return JFile(fname).exists();}

JEXEFileObj::JEXEFileObj() {
  igm = 1;
  ogm = 0;
  type = "*.exe";
  fname = "untitle.exe";
  params = "";
  enabled = valid = false;
  valid = check();
}

void JEXEFileObj::draw(JGraphics g, int x, int y, int w, int h) {
  if (!valid) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, JString("EXE"), rect1);
  drawText(g, fname, rect2);
}

boolean JEXEFileObj::inputAllowed(int n) { return !inputSet(n).last();}
int JEXEFileObj::inputFace(int n) { return TOP;}
JString JEXEFileObj::inputTag(int n) { return "enabled(logical)";}
JFRect JEXEFileObj::inputArea(int n) { return topArea(n, 0, igm);}
JFPoint JEXEFileObj::inputPoint(int n, JLinkObj& link) { return topPoint(n, link, 0, igm);}

#if defined(WIN32)
  #include <windows.h>
#endif

void JEXEFileObj::engine(int n, JLinkObj& link) {
  if (!valid) return;
  int ov = enabled;
  link.access(JIntegerData(enabled));
  enabled = (enabled != 0);
  if (!enabled && (enabled != ov)) {
#if defined(WIN32)
    JFile file(fname);
    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEONFEEDBACK;
    sinfo.wShowWindow = SW_SHOW;
    CreateProcess(null, 
      JString("\"")+fname+"\" "+params,
      null, null, false, 
      NORMAL_PRIORITY_CLASS,
      null, file.getParent(), &sinfo, &pinfo);
#endif    
  }
}

JArray JEXEFileObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JFileProperty("filename", fname, type));
  properties.append(JStringProperty("parameters", params));
  return properties;
}

boolean JEXEFileObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("filename")) {
    fname = ((JFileProperty*)&prop)->value;
    valid = check();
    repaint();
    return true;
  } else if (prop.getName() == JString("parameters")) {
    params = ((JStringProperty*)&prop)->value;
    return true;
  }
  return false;
}

