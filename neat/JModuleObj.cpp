#include "JPObject.h"
#include "JModuleObj.h"
#include "JModuleButton.h"
#include "JLinkObj.h"
#include "JComponent.h"
#include "JMath.h"
#include "JThread.h"
#include "JIntegerData.h"
#include "JPropertyBox.h"
#include "JColorProperty.h"

int JModuleObj::depth = 2;
int JModuleObj::depth2 = 4;
int JModuleObj::limit = 0xFFFF;
void JModuleObj::writeContent(JOutputStream& os) {
  JViewObj::writeContent(os);
  putObject(os, "moduleColor", moduleColor);
}

void JModuleObj::readContent(JDictionary& dict) {
  JViewObj::readContent(dict);
  JObject *obj = getObject(dict, "moduleColor");
  if (obj) moduleColor = *(JColor*)obj;
}

const char* JModuleObj::className() const { return "JModuleObj";}
JObject* JModuleObj::clone() const { return new JModuleObj(*this);}

JModuleObj::JModuleObj() {
  igm = 0;
  ogm = 1;
  igSize = ogSize = 0;
  eventMask = 0;
  moduleColor = JColor::cyan.darker();
}

void JModuleObj::addEvent(int mask) { eventMask |= mask;}
void JModuleObj::removeEvent(int mask) { eventMask &= ~mask;}
int JModuleObj::getEventMask() { return eventMask;}
JRegion JModuleObj::getJRegion() { return region;}
JRect JModuleObj::getIExtent(double dx, double dy, double scale) {
  int ix = JMath::round((x+dx)*scale);
  int iy = JMath::round((y+dy)*scale);
  int iw = max(1, JMath::round((x+width+dx)*scale)-ix);
  int ih = max(1, JMath::round((y+height+dy)*scale)-iy);
  return JRect(ix, iy, iw, ih);
}

int JModuleObj::inputGroupMax() { return igm;}
int JModuleObj::outputGroupMax() { return ogm;}

JFocusSet& JModuleObj::inputSet(int n) {
  if (n >= igSize) {
    JFocusSet fset;
    inputGroup.grow(igSize=n+1, fset);
  }
  return *(JFocusSet*)inputGroup[n];
}

JFocusSet& JModuleObj::outputSet(int n) { 
  if (n >= ogSize) {
    JFocusSet fset;
    outputGroup.grow(ogSize=n+1, fset);
  }
  return *(JFocusSet*)outputGroup[n];
}

JString JModuleObj::inputTagType(int n) {
  int type = inputType(n);
  if (type < JDataType::last)
    return inputTag(n)+"<"+JDataType::tag[type]+">";
  return inputTag(n)+"<polymorph>";
}

JString JModuleObj::outputTagType(int n) { 
  int type = outputType(n);
  if (type < JDataType::last)
    return outputTag(n)+"<"+JDataType::tag[type]+">";
  return outputTag(n)+"<polymorph>";
}

JString JModuleObj::inputTag(int n) { 
  char* tag[] = { "input", "enable(logical)"};
  return tag[n];
}

JString JModuleObj::outputTag(int n)
{ return "output";}

void DoModuleRemove(const JObject* obj, void** arg)
{ ((JLinkObj*)obj)->remove();}

void JModuleObj::remove() {
  int i;
  for (i=0; i<igSize; i++) 
    inputSet(i).forEachChild(DoModuleRemove);
  for (i=0; i<ogSize; i++) 
    outputSet(i).forEachChild(DoModuleRemove);
  JViewObj::remove();
}

void DoModuleUpdate(const JObject* obj, void** arg)
{ *(JFRect*)arg |= ((JViewObj*)obj)->calculateExtent();}

JFRect JModuleObj::calculateUpdate() {
  int i;
  JFRect rect = calculateExtent();
  for (i=0; i<igSize; i++) 
    inputSet(i).forEachChild(DoModuleUpdate, (void**)&rect);
  for (i=0; i<ogSize; i++) 
    outputSet(i).forEachChild(DoModuleUpdate, (void**)&rect);
  return rect;
}

JFRect JModuleObj::calculateInputUpdate(int n) {
  JFRect rect;
  if (n < 0) {
    for (int i=0; i<igSize; i++)
      inputSet(i).forEachChild(DoModuleUpdate, (void**)&rect);
  } else inputSet(n).forEachChild(DoModuleUpdate, (void**)&rect);
  return rect;
}

JFRect JModuleObj::calculateOutputUpdate(int n) {
  JFRect rect;
  if (n < 0) {
    for (int i=0; i<ogm; i++)
      outputSet(i).forEachChild(DoModuleUpdate, (void**)&rect);
  } else outputSet(n).forEachChild(DoModuleUpdate, (void**)&rect);
  return rect;
}

void JModuleObj::calculateJRegion(JRegion& rgn, double dx, double dy, double scale) {
  region = JRegion(getIExtent(dx, dy, scale)) & rgn;
  rgn -= region;
}

JViewObj* JModuleObj::duplicate(JViewSet* _parent, JDictionary* dict) {
  JModuleObj* obj = (JModuleObj*)JViewObj::duplicate(_parent, dict);
  obj->igSize = obj->ogSize = 0;
  obj->inputGroup.Release();
  obj->outputGroup.Release();
  return obj;
}

void JModuleObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Mod"), rect);
}

void JModuleObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  g.setJColor(moduleColor);
  JRect rect = getIExtent(dx, dy, scale);
  g.fill3DRect(rect.x, rect.y, rect.width, rect.height, 2);
  g.setJColor(moduleColor.darker());
  draw(g, rect.x+3, rect.y+3, rect.width-8, rect.height-8);
  g.setJColor(moduleColor.brighter());
  draw(g, rect.x+5, rect.y+5, rect.width-8, rect.height-8);
  g.setJColor(JColor::black);
  draw(g, rect.x+4, rect.y+4, rect.width-8, rect.height-8);
}

int JModuleObj::inputType(int n) { return JIntegerData::id;}
int JModuleObj::outputType(int n) { return JIntegerData::id;}
boolean	JModuleObj::cond(int n, JLinkObj& link) { return true;}
void JModuleObj::access(int n, JLinkObj& link, const JDataType& data) {}
boolean JModuleObj::inputAllowed(int n) { return false;}
boolean JModuleObj::outputAllowed(int n) { return false;}

JFRect JModuleObj::inputArea(int n) { 
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, 1);
}

JFRect JModuleObj::outputArea(int n)
{ return rightArea(n, 0, 1);}

int JModuleObj::inputAreaNo(JFPoint fpt) { 
  for (int i=0; i<igm; i++) {
    if (inputArea(i).inside(fpt.x, fpt.y))
      return i;
  }
  return -1;
}

int JModuleObj::outputAreaNo(JFPoint fpt) { 
  for (int i=0; i<ogm; i++) {
    if (outputArea(i).inside(fpt.x, fpt.y))
      return i;
  }
  return -1;
}

int JModuleObj::inputFace(int n) { return (!n) ? LEFT : TOP;}
int JModuleObj::outputFace(int n) { return RIGHT;}
JFPoint JModuleObj::inputPoint(int n, JLinkObj& link) {
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, 1);
}
JFPoint JModuleObj::outputPoint(int n, JLinkObj& link)
{ return rightPoint(n, link, 0, 1);}
double JModuleObj::outputPos(int n, JFPoint opt) { return 0.5;}
void JModuleObj::engine(int n, JLinkObj& link) {}

void DoBroadcast(const JObject* obj, void** arg) 
{ ((JLinkObj*)obj)->engine();}

boolean JModuleObj::isBroadcasting() {
  for (int i=0; i<ogSize; i++) {
    int &broadcastCounter = *(int*)&outputSet(i).prevAddress;
    if (broadcastCounter)
      return (broadcastCounter > 0);
  }
  return false;
}

void JModuleObj::broadcast(int n) {
  JFocusSet &fs = outputSet(n);
  int &broadcastCounter = *(int*)&fs.prevAddress;
  if (broadcastCounter++ < 2)
    fs.forEachChild(DoBroadcast);
  broadcastCounter--;
}

void DoCondBroadcast(const JObject* obj, void** arg) 
{ if (((JLinkObj*)obj)->cond()) ((JLinkObj*)obj)->engine();}

void JModuleObj::condBroadcast(int n) {
  JFocusSet &fs = outputSet(n);
  int &broadcastCounter = *(int*)&fs.prevAddress;
  if (broadcastCounter++ < 2)
    fs.forEachChild(DoCondBroadcast);
  broadcastCounter--;
}

void JModuleObj::repaint() {
  if (!parent) return;
  JComponent* pRoot = parent->getRoot();
  if (pRoot) {
    JEvent event(this, JEvent::CHILD_NOTIFY);
    event.key = isOpaque() ? DIRECT_MODE : REPAINT_MODE;
    pRoot->childNotify(event, this);
  }
}

void JModuleObj::repaint(int x, int y, int w, int h) {
  JComponent* pRoot = parent->getRoot();
  if (pRoot) {
    JRect rect(x, y, w, h);
    JEvent event(this, JEvent::CHILD_NOTIFY);
    event.key = isOpaque() ? DIRECT_MODE : REPAINT_MODE;
    pRoot->childNotify(event, &rect);
  }
}

void JModuleObj::repaintView(JFRect rect, int mode) {
  JComponent* pRoot = parent->getRoot();
  if (pRoot) {
    JEvent event(this, JEvent::CHILD_NOTIFY);
    event.key = mode;
    pRoot->childNotify(event, &rect);
  }
}

JRect JModuleObj::queryExtent() {
  JComponent* pRoot = parent->getRoot();
  JRect result;
  if (pRoot) {
    JEvent event(this, JEvent::CHILD_NOTIFY);
    event.key = EXTENT_MODE;
    pRoot->childNotify(event, &result);
  }
  return result;
}

JPoint JModuleObj::queryJPoint(double x, double y) {
  JComponent* pRoot = parent->getRoot();
  JPoint result;
  if (pRoot) {
    JFPoint fpt(x, y);
    JEvent event(this, JEvent::CHILD_NOTIFY, &fpt);
    event.key = JPOINT_MODE;
    pRoot->childNotify(event, &result);
  }
  return result;
}

JColor JModuleObj::getModuleColor() { return moduleColor;}

void JModuleObj::addInput(int n, JLinkObj& link)
{ if (inputAllowed(n)) inputSet(n).add(link);}
void JModuleObj::delInput(int n, JLinkObj& link)
{ inputSet(n).del(link);}
void JModuleObj::delAllInput(int n) { 
  if (n == -1) {
    for (int i=0; i<igSize; i++)
      inputSet(i).delAll();
  } else inputSet(n).delAll();
}

void JModuleObj::addOutput(int n, JLinkObj& link)
{ if (outputAllowed(n)) outputSet(n).add(link);}
void JModuleObj::delOutput(int n, JLinkObj& link)
{ outputSet(n).del(link);}
void JModuleObj::delAllOutput(int n) {
  if (n == -1) {
    for (int i=0; i<ogm; i++)
      outputSet(i).delAll();
  } else outputSet(n).delAll();
}

void JModuleObj::drawText(JGraphics g, JString text, JRect rect) {
  int len = text.length();
  if (!len) return;
  int factor = 0, sh, sw, delta;
  len = (len+5)/6*6;
  do {
    delta = rect.height*factor/100;
    sh = rect.height-delta;
    JFont tmp("courier", JFont::BOLD, sh);
    g.setJFont(tmp);
    JFontMetrics fm(g);
    sw = fm.stringWidth(text);
    sh = fm.getHeight();
    if (len*fm.charWidth('0') <= rect.width) break;
    factor += 5;
  } while (factor < 100);
  rect.shrinkBy(0, delta/2);
  g.drawJString(text, rect.x+(rect.width-sw)/2, 
    rect.y+(rect.height-sh)/2);
/*
  int fsize = min(rect.width*3/((len+5)/6*10),
    rect.height*3/4);
  if (fsize > 5) {
    JFont font("helvetica", JFont::BOLD, fsize);
    g.setJFont(font);
    JFontMetrics fm(g);
    int sw = fm.stringWidth(text);
    while (sw > rect.width-depth2) {
      text = text(0, --len);
      sw = fm.stringWidth(text);
      if (!len) break;
    }
    if (len) {
      int by = rect.y+(rect.height-fm.getHeight())/2;
      int bx = rect.x+(rect.width-sw)/2;
      g.drawJString(text, bx, by);
    }
  }
*/
}

JArray JModuleObj::getProperties() { 
  JArray properties;
  properties.append(JColorProperty("moduleColor", moduleColor));
  return properties;
}

boolean JModuleObj::updateProperty(JProperty& prop) { 
  if (prop.getName() == JString("moduleColor")) {
    moduleColor = ((JColorProperty*)&prop)->color;
    repaintView(*this);
    return true;
  }
  return false;
}

boolean JModuleObj::propertyDialog(int x, int y) {
  int select = 0;
  JArray properties = getProperties();
  if (!properties.size()) {
    JMessageBox::create(JString("No Editable Properties in ")
      +(className()+1), JMessageBox::BTN_OK, x, y);
    return false;
  }
  while (JPropertyBox::create(
    JString("Module Properties of ")+(className()+1),
    properties, select, x, y, this) == JMessageBox::OK) {
    JProperty &prop = *(JProperty*)properties[select];
    if (prop.edit(x, y)) {
      updateProperty(prop);
      properties = getProperties();
    }
  }
  return true;
}

void JModuleObj::addButton(JComponent* panel) 
{ panel->add(*JModuleButton::create(panel->getParent(), *this));}

void JModuleObj::addModuleButton(JComponent* panel, const JModuleObj& obj) 
{ panel->add(*JModuleButton::create(panel->getParent(), obj));}

DllExport void DoAddModuleLinks(const JObject* obj, void** arg) {
  JHashTable &hash = *(JHashTable*)arg[1];
  if (!hash[JPObject(obj)]) {
    hash.add(JPObject(obj));
    ((JViewSet*)arg[0])->add(*(JLinkObj*)obj);
  }
}

void JModuleObj::addLinks(JViewSet& set, JHashTable& hash) {
  int i;
  void* arg[] = {&set, &hash};
  for (i=0; i<igSize; i++) 
    inputSet(i).forEachChild(DoAddModuleLinks, arg);
  for (i=0; i<ogSize; i++) 
    outputSet(i).forEachChild(DoAddModuleLinks, arg);
}

void DoAddInputModules(const JObject* obj, void** arg) {
  JHashTable &hash = *(JHashTable*)arg[1];
  if (!hash[JPObject(obj)]) {
    hash.add(JPObject(obj));
    JLinkObj *link = (JLinkObj*)obj;
    if (!hash[JPObject(link->from)]) {
      hash.add(JPObject(link->from));
      ((JViewSet*)arg[0])->add(*link->from);
    }
  }
}

void DoAddOutputModules(const JObject* obj, void** arg) {
  JHashTable &hash = *(JHashTable*)arg[1];
  if (!hash[JPObject(obj)]) {
    hash.add(JPObject(obj));
    JLinkObj *link = (JLinkObj*)obj;
    if (!hash[JPObject(link->to)]) {
      hash.add(JPObject(link->to));
      ((JViewSet*)arg[0])->add(*link->to);
    }
  }
}

void JModuleObj::addConnectedModules(JViewSet& set, JHashTable& hash) {
  int i;
  void* arg[] = {&set, &hash};
  for (i=0; i<igSize; i++) 
    inputSet(i).forEachChild(DoAddInputModules, arg);
  for (i=0; i<ogSize; i++) 
    outputSet(i).forEachChild(DoAddOutputModules, arg);
}

boolean JModuleObj::isOpaque() { return true;}
boolean JModuleObj::gotEditFocus(JEvent& e) { return false;}
boolean JModuleObj::lostEditFocus(JEvent& e) { return true;}

boolean JModuleObj::requestEditFocus() { 
  JComponent* pRoot = parent->getRoot();
  if (pRoot) {
    JEvent event(this, JEvent::CHILD_NOTIFY);
    event.key = REQUEST_MODE;
    pRoot->childNotify(event, event.arg);
  }
  return true;
}

JFPoint JModuleObj::topPoint(int n, JLinkObj& link, int start, int N, 
  double from, double delta) {
  double fraction = 0.5;
  int index = inputSet(n).indexOf(link);
  if (index >= 0)
    fraction = double(index+1)/(inputSet(n).size()+1);
  return JFPoint(x+(from+delta*(fraction+min(N-1, n-start))/N)*width, y);
}

JFPoint JModuleObj::bottomPoint(int n, JLinkObj& link, int start, int N, 
  double from, double delta) {
  double fraction = 0.5;
  int index = outputSet(n).indexOf(link);
  if (index >= 0)
    fraction = double(index+1)/(outputSet(n).size()+1);
  return JFPoint(x+(from+delta*(fraction+min(N-1, n-start))/N)*width, y+height);
}

JFPoint JModuleObj::leftPoint(int n, JLinkObj& link, int start, int N, 
  double from, double delta) {
  double fraction = 0.5;
  int index = inputSet(n).indexOf(link);
  if (index >= 0)
    fraction = double(index+1)/(inputSet(n).size()+1);
  return JFPoint(x, 
    y+(from+delta*(fraction+min(N-1, n-start))/N)*height);
}

JFPoint JModuleObj::rightPoint(int n, JLinkObj& link, int start, int N,
  double from, double delta) {
  double fraction = 0.5;
  int index = outputSet(n).indexOf(link);
  if (index >= 0) 
    fraction = double(index+1)/(outputSet(n).size()+1);
  return JFPoint(x+width, 
    y+(from+delta*(fraction+min(N-1, n-start))/N)*height);
}

JFRect JModuleObj::topArea(int n, int start, int N, 
  double from, double delta, int factor) { 
  return JFRect(x+(from+min(N-1, n-start)*delta/N)*width, 
    y, delta*width/N, 
    min(width, height)/factor);
}

JFRect JModuleObj::bottomArea(int n, int start, int N, 
  double from, double delta, int factor) { 
  double dxy = min(width, height)/factor;
  return JFRect(x+(from+min(N-1, n-start)*delta/N)*width, 
    y+height-dxy, delta*width/N, dxy);
}

JFRect JModuleObj::leftArea(int n, int start, int N, 
  double from, double delta, int factor) { 
  return JFRect(x, 
    y+(from+min(N-1, n-start)*delta/N)*height, 
    min(width, height)/factor, 
    delta*height/N);
}

JFRect JModuleObj::rightArea(int n, int start, int N, 
  double from, double delta, int factor) { 
  double dxy = min(width, height)/factor;
  return JFRect(x+width-dxy, 
    y+(from+min(N-1, n-start)*delta/N)*height, 
    dxy, delta*height/N);
}

