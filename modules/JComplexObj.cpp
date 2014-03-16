#include "JComplexObj.h"
#include "JLinkObj.h"
#include "JPObject.h"
#include "JInteger.h"
#include "JDouble.h"
#include "JMessageBox.h"
#include "JStringProperty.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"

char* theJComplexObj = JComplexObj().Register();
#define FACTOR 8
#define FACTOR2 16

class JPort : public JObject {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JPort();
    JPort(JString name);
    JString name;
    int valueCounter;
    int typeCounter;
};

#define PORT(x) ((JPort*)x)
const char* JPort::className() const { return "JPort";}
JObject* JPort::clone() const { return new JPort(*this);}
JPort::JPort() { valueCounter = typeCounter = 0;}
JPort::JPort(JString _name) 
{ name = _name; valueCounter = typeCounter = 0;}

void JComplexObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putString(os, "name", name);
  putInteger(os, "numOfInput", numOfInput);
  putInteger(os, "numOfLeftInput", numOfLeftInput);
  putInteger(os, "numOfOutput", numOfOutput);
  putInteger(os, "numOfRightOutput", numOfRightOutput);
  putInteger(os, "internalMode", internalMode);
  igm = ogm = numOfInput+numOfOutput;
  JString prefix;
  for (int i=0; i<igm; i++) {
    prefix = getPrefix(i);
    putString(os, prefix+"Tag", PORT(port[i])->name);
  }
}

void JComplexObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  name = getString(dict, "name");
  numOfInput = getInteger(dict, "numOfInput");
  numOfLeftInput = getInteger(dict, "numOfLeftInput");
  numOfOutput = getInteger(dict, "numOfOutput");
  numOfRightOutput = getInteger(dict, "numOfRightOutput");
  internalMode = getInteger(dict, "internalMode");
  igm = ogm = numOfInput+numOfOutput;
  JString prefix;
  port.Release();
  for (int i=0; i<igm; i++) {
    prefix = getPrefix(i);
    port.append(JPort(getString(dict, prefix+"Tag")));
  }
}

const char* JComplexObj::className() const { return "JComplexObj";}
JObject* JComplexObj::clone() const { return new JComplexObj(*this);}

JComplexObj::JComplexObj() {
  igm = 2;
  numOfInput = igm;
  numOfLeftInput = 1;
  numOfOutput = ogm;
  numOfRightOutput = ogm;
  igm = ogm = numOfInput+numOfOutput;
  port.append(JPort("input"));
  port.append(JPort("control"));
  port.append(JPort("output"));
  internalMode = true;
}

void JComplexObj::startup() { port.Dereference();}

void JComplexObj::calculateJRegion(JRegion& rgn, double dx, double dy, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  region = JRegion(rect) & rgn;
  if (internalMode) { // Need Calculate Internal Regions
    double delta = min(width, height)/FACTOR;
    JPoint pt = getIPoint(JFPoint(x+delta, y+delta), dx, dy, scale);
    region-=JRegion(rect.shrink(pt.x-rect.x, pt.y-rect.y));
  }
  rgn -= region;
}

void JComplexObj::access(int n, JLinkObj& link, const JDataType& data) { 
  int &valueCounter = PORT(port[n])->valueCounter;
  JLinkObj* prev = (JLinkObj*)inputSet(n).first();
  if (prev) {
    if (!valueCounter++) 
      prev->access(data);
    valueCounter--;
  }
}

int JComplexObj::inputType(int n) {
  int type = JDataType::last;
  int &typeCounter = PORT(port[n])->typeCounter;
  JLinkObj* link = (JLinkObj*)inputSet(n).first();
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

int JComplexObj::outputType(int n) { return inputType(n);}

JString JComplexObj::inputTag(int n) {
  if (n < numOfInput) return PORT(port[n])->name;
  if (n < numOfInput+numOfOutput) 
    return PORT(port[n])->name+"(inner)";
  return "None";
}

JString JComplexObj::outputTag(int n) {
  if (n < numOfInput) return PORT(port[n])->name+"(inner)";
  if (n < numOfInput+numOfOutput) return PORT(port[n])->name;
  return "None";
}

boolean JComplexObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JFRect JComplexObj::inputArea(int n) {
  JFRect rect;
  int factor = (internalMode) ? FACTOR2 : FACTOR;
  if (n < numOfLeftInput) {
    rect = leftArea(n, 0, numOfLeftInput, 0.25, 0.5, factor);
  } else if (n < numOfInput)  {
    rect = topArea(n, numOfLeftInput, 
      numOfInput-numOfLeftInput, 0.25, 0.5, factor);
  } else if (n < numOfInput+numOfRightOutput) {
    rect = rightArea(n, 
      numOfInput, numOfRightOutput, 0.25, 0.5, factor);
    rect.x -= min(width, height)/factor;
  } else {
    rect = bottomArea(n, 
      numOfInput+numOfRightOutput, 
      numOfOutput-numOfRightOutput, 0.25, 0.5, factor);
    rect.y -= min(width, height)/factor;
  }
  return rect;
}

JFRect JComplexObj::outputArea(int n) {
  JFRect rect;
  int factor = (internalMode) ? FACTOR2 : FACTOR;
  if (n < numOfLeftInput) {
    rect = leftArea(n, 0, numOfLeftInput, 0.25, 0.5, factor);
    rect.x += min(width, height)/factor;
  } else if (n < numOfInput) {
    rect = topArea(n, numOfLeftInput, 
      numOfInput-numOfLeftInput, 0.25, 0.5, factor);
    rect.y += min(width, height)/factor;
  } else if (n < numOfInput+numOfRightOutput) {
    rect = rightArea(n, 
      numOfInput, numOfRightOutput, 0.25, 0.5, factor);
  } else {
    rect = bottomArea(n, 
      numOfInput+numOfRightOutput, 
      numOfOutput-numOfRightOutput, 0.25, 0.5, factor);
  }
  return rect;
}

int JComplexObj::inputAreaNo(JFPoint fpt) { 
  if (internalMode) // Need All InputArea
    return JAddObj::inputAreaNo(fpt);
  for (int i=0; i<numOfInput; i++) {
    if (inputArea(i).inside(fpt.x, fpt.y))
      return i;
  }
  return -1;
}

int JComplexObj::outputAreaNo(JFPoint fpt) { 
  if (internalMode) // Need All InputArea
    return JAddObj::outputAreaNo(fpt);
  for (int i=numOfInput; i<ogm; i++) {
    if (outputArea(i).inside(fpt.x, fpt.y))
      return i;
  }
  return -1;
}

int JComplexObj::inputFace(int n) {
  if (n < numOfLeftInput) return LEFT;
  if (n < numOfInput) return TOP;
  if (n < numOfInput+numOfRightOutput) return LEFT;
  return TOP;
}

int JComplexObj::outputFace(int n) {
  if (n < numOfLeftInput) return RIGHT;
  if (n < numOfInput) return BOTTOM;
  if (n < numOfInput+numOfRightOutput) return RIGHT;
  return BOTTOM;
}

JFPoint JComplexObj::inputPoint(int n, class JLinkObj& link) {
  JFPoint pt;
  if (n < numOfLeftInput) {
    pt = leftPoint(n, link, 0, numOfLeftInput);
  } else if (n < numOfInput)  {
    pt = topPoint(n, link, numOfLeftInput, 
      numOfInput-numOfLeftInput);
  } else if (n < numOfInput+numOfRightOutput) {
    pt = leftPoint(n, link, 
      numOfInput, numOfRightOutput);
    pt.x = x+width-min(width, height)/FACTOR;
  } else {
    pt = topPoint(n, link, 
      numOfInput+numOfRightOutput, 
      numOfOutput-numOfRightOutput);
    pt.y = y+height-min(width, height)/FACTOR;
  }
  return pt;
}

JFPoint JComplexObj::outputPoint(int n, class JLinkObj& link) {
  JFPoint pt;
  if (n < numOfLeftInput) {
    pt = rightPoint(n, link, 0, numOfLeftInput);
    pt.x = x+min(width, height)/FACTOR;
  } else if (n < numOfInput) {
    pt = bottomPoint(n, link, numOfLeftInput, 
      numOfInput-numOfLeftInput);
    pt.y = y+min(width, height)/FACTOR;
  } else if (n < numOfInput+numOfRightOutput) {
    pt = rightPoint(n, link, 
      numOfInput, numOfRightOutput);
  } else {
    pt = bottomPoint(n, link, 
      numOfInput+numOfRightOutput, 
      numOfOutput-numOfRightOutput);
  }
  return pt;
}

JViewObj* JComplexObj::locate(double x, double y, JViewObj*& obj) { 
  if (internalMode) {
    double delta = min(width, height)/FACTOR;
    return inside(x, y) && !shrink(delta, delta).inside(x, y) ? 
      (obj = this) : null;
  }
  return JAddObj::locate(x, y, obj);
}

void JComplexObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  g.setJColor(moduleColor);
  JRect rect = getIExtent(dx, dy, scale);
  if (internalMode) {
    double delta = min(width, height)/FACTOR;
    JPoint pt = getIPoint(JFPoint(x+delta, y+delta), dx, dy, scale);
    JRect inner = rect.shrink(pt.x-rect.x, pt.y-rect.y);
    g.setJRegion(rgn-=JRegion(inner));
    g.fill3DRect(rect.x, rect.y, rect.width, rect.height, depth);
    g.draw3DJRect(inner.grow(depth, depth), -depth);
  } else {
    g.fill3DRect(rect.x, rect.y, rect.width, rect.height, depth);
    g.setJColor(moduleColor.darker());
    draw(g, rect.x+3, rect.y+3, rect.width-8, rect.height-8);
    g.setJColor(moduleColor.brighter());
    draw(g, rect.x+5, rect.y+5, rect.width-8, rect.height-8);
    g.setJColor(JColor::black);
    draw(g, rect.x+4, rect.y+4, rect.width-8, rect.height-8);
  }
}

void JComplexObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  if (name.length())
    drawText(g, name, rect);
  else drawText(g, "Cplx", rect);
}

void JComplexObj::engine(int n, JLinkObj& link) 
{ broadcast(n);}

JArray JComplexObj::getProperties() {
  JString prefix;
  JArray properties = JAddObj::getProperties();
  properties.append(JStringProperty("name", name));
  properties.append(JIntegerListProperty("internalMode", internalMode, JIntegerListProperty::booleanTag));
  if (internalMode) {
    properties.append(JIntegerProperty("numOfLeftInput", numOfLeftInput, 0, 512));
    properties.append(JIntegerProperty("numOfTopInput", numOfInput-numOfLeftInput, 0, 512));
    properties.append(JIntegerProperty("numOfRightOutput", numOfRightOutput, 0, 512));
    properties.append(JIntegerProperty("numOfBottomOutput", numOfOutput-numOfRightOutput, 0, 512));
    for (int i=0; i<igm; i++) {
      prefix = getPrefix(i);
      properties.append(
        JStringProperty(prefix+" tag", 
        PORT(port[i])->name));
    }
  }
  return properties;
}

boolean JComplexObj::checkEmpty() {
  int i;
  for (i=0; i<igSize; i++)
    if (!inputSet(i).isEmpty()) return false;
  for (i=0; i<ogSize; i++)
    if (!outputSet(i).isEmpty()) return false;
  return true;
}

boolean JComplexObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("name")) {
    name = ((JStringProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("internalMode")) {
    internalMode = ((JIntegerListProperty*)&prop)->value;
    repaintView(*this, REGION_MODE);
    return true;
  } else if (prop.getName() == JString("numOfLeftInput")) {
    if (!checkEmpty()) {
      JMessageBox::create("Disconnect all links before change number of ports !", 
        JMessageBox::BTN_OK);
      return true;
    }
    int delta, oldN = numOfLeftInput;
    numOfLeftInput = ((JIntegerProperty*)&prop)->value;
    delta = numOfLeftInput-oldN;
    if (!delta) return true;
    if (delta < 0) port.del(numOfLeftInput, -delta);
    else port.insert(JPort("None"), oldN, delta);
    numOfInput += delta;
    igm = ogm = numOfInput+numOfOutput;
    return true;
  } else if (prop.getName() == JString("numOfTopInput")) {
    if (!checkEmpty()) {
      JMessageBox::create("Disconnect all links before change number of ports !", 
        JMessageBox::BTN_OK);
      return true;
    }
    int delta, oldN = numOfInput;
    numOfInput = numOfLeftInput+((JIntegerProperty*)&prop)->value;
    delta = numOfInput-oldN;
    if (!delta) return true;
    if (delta < 0) port.del(numOfInput, -delta);
    else port.insert(JPort("None"), oldN, delta);
    igm = ogm = numOfInput+numOfOutput;
    return true;
  } else if (prop.getName() == JString("numOfRightOutput")) {
    if (!checkEmpty()) {
      JMessageBox::create("Disconnect all links before change number of ports !", 
        JMessageBox::BTN_OK);
      return true;
    }
    int delta, oldN = numOfRightOutput;
    numOfRightOutput = ((JIntegerProperty*)&prop)->value;
    delta = numOfRightOutput-oldN;
    if (!delta) return true;
    if (delta < 0) port.del(numOfRightOutput, -delta);
    else port.insert(JPort("None"), oldN, delta);
    numOfOutput += delta;
    igm = ogm = numOfInput+numOfOutput;
    return true;
  } else if (prop.getName() == JString("numOfBottomOutput")) {
    if (!checkEmpty()) {
      JMessageBox::create("Disconnect all links before change number of ports !", 
        JMessageBox::BTN_OK);
      return true;
    }
    int delta, oldN = numOfOutput;
    numOfOutput = numOfRightOutput+((JIntegerProperty*)&prop)->value;
    delta = numOfOutput-oldN;
    if (!delta) return true;
    if (delta < 0) port.del(numOfOutput, -delta);
    else port.insert(JPort("None"), oldN, delta);
    igm = ogm = numOfInput+numOfOutput;
    return true;
  }
  JString prefix;
  for (int i=0; i<igm; i++) {
    prefix = getPrefix(i);
    if (prop.getName() == prefix+" tag") {
      PORT(port[i])->name = ((JStringProperty*)&prop)->value;
      return true;
    }
  }
  return false;
}

DllImport void DoAddModuleLinks(const JObject* obj, void** arg);

void JComplexObj::addLinks(JViewSet& set, JHashTable& hash) {
  if (internalMode) {
    JAddObj::addLinks(set, hash);
    return;
  }
  int i;
  void* arg[] = {&set, &hash};
  for (i=0; i<numOfInput; i++) 
    inputSet(i).forEachChild(DoAddModuleLinks, arg);
  for (i=numOfInput; i<ogm; i++) 
    outputSet(i).forEachChild(DoAddModuleLinks, arg);
}

JString JComplexObj::getPrefix(int i) {
  if (i < numOfLeftInput)
    return JString("left-")+JInteger::toJString(i);
  else if (i < numOfInput)
    return JString("top-")+JInteger::toJString(i-numOfLeftInput);
  else if (i < numOfInput+numOfRightOutput) 
    return JString("right-")+JInteger::toJString(i-numOfInput);
  return JString("bottom-")+JInteger::toJString(i-numOfInput-numOfRightOutput);
}

