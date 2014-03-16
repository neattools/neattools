#include "JTimerObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JLinkObj.h"
#include "JSystem.h"

#if defined(WIN32)
  #include <windows.h>
#endif

char* priorityTag[] = {
  "TimeCritical",
  "Highest",
  "AboveNormal",
  "Normal",
  "BelowNormal",
  "Lowest",
  "Idle",
  null
};

int priorityVal[] = {
  JThread::TMAX_PRIORITY,
  JThread::TNORM_PRIORITY+2,
  JThread::TNORM_PRIORITY+1,
  JThread::TNORM_PRIORITY,
  JThread::TNORM_PRIORITY-1,
  JThread::TNORM_PRIORITY-2,
  JThread::TMIN_PRIORITY
};

char* theJTimerObj = JTimerObj().Register();
void JTimerObj::writeContent(JOutputStream& os) {
  JANDObj::writeContent(os);
  putInteger(os, "delay", delay);
  putInteger(os, "priority", priority);
}

void JTimerObj::readContent(JDictionary& dict) {
  JANDObj::readContent(dict);
  delay = getInteger(dict, "delay");
  priority = getInteger(dict, "priority", 3);
}

const char* JTimerObj::className() const { return "JTimerObj";}
JObject* JTimerObj::clone() const { return new JTimerObj(*this);}

JTimerObj::JTimerObj(int _delay) {
  connected = false;
  enabled = true;
  delay = _delay;
  igm = IN_LAST;
  ogm = OUT_LAST;
  priority = 3;
}

JTimerObj::~JTimerObj() { 
  close();
}

DllImport void segmentDelay(int interval, int&base, int& counter, boolean& cond);

void JTimerObj::run() {
  connected = true;
  repaint();
  base = JSystem::currentTimeMillis();
  while (connected) {
    segmentDelay(delay, base, counter, connected);
    if (!connected) break;
    value = mask;
    broadcast(0);
    if (!connected) break;
    value = 0;
    broadcast(0);
  }
}

void JTimerObj::startup() 
{ if (enabled) open();}

void JTimerObj::reset() 
{ connected = false;}

void JTimerObj::open() {
  value = 0;
  thread = JThread(this);
  thread.start();
  thread.setPriority(priorityVal[priority]);
}

void JTimerObj::close() {
  if (!connected) return;
  enabled = false;
  connected = false;
  repaint();
  value = 0;
}

void JTimerObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JAddObj::paint(g, dx, dy, rgn, scale);
  JRect rect = getIExtent(dx, dy, scale);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    if (connected) g.setJColor(JColor::red);
    else g.setJColor(JColor::red.darker());
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2);
  }
}

void JTimerObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, "Timer", rect1);
  drawText(g, JInteger::toJString(delay)+"ms", rect2);
}

boolean JTimerObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JTimerObj::access(int n, JLinkObj& link, const JDataType& data) {
  if (n == OUT_INTERVAL) INT(data) = delay;
  else INT(data) = value;
}

JString JTimerObj::inputTag(int n) {
  char* tag[] = { "enabled(logical)", "interval"};
  return tag[n];
}

JString JTimerObj::outputTag(int n) {
  char* tag[] = { "output", "interval"};
  if (!n) return JString(tag[0])+NBTag();
  return tag[n];
}

JFRect JTimerObj::inputArea(int n) { 
  return topArea(n, 0, IN_LAST);
}

JFRect JTimerObj::outputArea(int n) { 
  if (!n) return rightArea(n, 0, 1);
  return bottomArea(n, 1, OUT_LAST-1);
}

int JTimerObj::inputFace(int n) { 
  return TOP;
}

int JTimerObj::outputFace(int n) { 
  if (!n) return RIGHT;
  return BOTTOM;
}

JFPoint JTimerObj::inputPoint(int n, JLinkObj& link) { 
  return topPoint(n, link, 0, IN_LAST);
}

JFPoint JTimerObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return rightPoint(n, link, 0, 1);
  return bottomPoint(n, link, 1, OUT_LAST-1);
}

void JTimerObj::engine(int n, JLinkObj& link) {
  if (n == IN_INTERVAL) {
    int newDelay = delay;
    link.access(JIntegerData(newDelay));
    setDelay(max(10, min(limit, newDelay)));
  } else if (n == IN_ENABLED) {
    int oldEnabled = enabled;
    link.access(JIntegerData(enabled));
    enabled = (enabled != 0);
    if (enabled != oldEnabled) {
      if (enabled) open();
      else close();
    }
  }
}

JArray JTimerObj::getProperties() {
  JArray properties = JANDObj::getProperties();
  properties.append(JIntegerProperty("delay", delay, 1, limit));
  properties.append(JIntegerListProperty("priority", priority, priorityTag));
  return properties;
}

boolean JTimerObj::updateProperty(JProperty& prop) {
  if (JANDObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("delay")) {
    setDelay(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("priority")) {
    priority = ((JIntegerListProperty*)&prop)->value;
    return true;
  }
  return false;
}

void JTimerObj::addButton(JComponent* panel) { 
  addModuleButton(panel, JTimerObj(10));
  addModuleButton(panel, JTimerObj(20));
  addModuleButton(panel, JTimerObj(50));
  addModuleButton(panel, JTimerObj(100));
  addModuleButton(panel, JTimerObj(200));
  addModuleButton(panel, JTimerObj(500));
  addModuleButton(panel, JTimerObj(1000));
}

void JTimerObj::setDelay(int _delay) {
  _delay = max(1, min(_delay, limit));
  if (delay != _delay) {
    delay = _delay;
    base -= counter;
    counter = 0;
    repaint();
    broadcast(OUT_INTERVAL);
  }
}
