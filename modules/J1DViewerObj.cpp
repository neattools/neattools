#include "J1DViewerObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JColorData.h"
#include "JLinkObj.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"

char* theJ1DViewerObj = J1DViewerObj().Register();
void J1DViewerObj::writeContent(JOutputStream& os) {
  J1DMeterObj::writeContent(os);
  putInteger(os, "bufSize", bufSize);
  putInteger(os, "id", id);
}

void J1DViewerObj::readContent(JDictionary& dict) {
  J1DMeterObj::readContent(dict);
  id = getInteger(dict, "id");
  bufSize = getInteger(dict, "bufSize");
  bufSize = max(2048, min(16384, bufSize));
  initialize();
}

const char* J1DViewerObj::className() const { return "J1DViewerObj";}
JObject* J1DViewerObj::clone() const { return new J1DViewerObj(*this);}

J1DViewerObj::J1DViewerObj(int _type) 
  :J1DMeterObj(_type) { 
  igm = IN_LAST;
  color = JColor::yellow; 
  bkgnd = JColor(0, 64, 0); 
  sequence = oldValue = 0;
  tail = head = 0;
  data = null;
  bufSize = 1024;
  valid = false;
  headBase = head;
  ovBase = 0;
  id = LINE;
}

void J1DViewerObj::startup() { initialize();}

void J1DViewerObj::drawFrame(JGraphics g, JRect rect) {
  if ((rect.width > depth2) && (rect.height > depth2)) {
    g.draw3DJRect(rect, depth);
    g.setJColor((id == LINE) ? bkgnd : JColor::black);
    g.fillJRect(rect.shrinkBy(depth, depth));
    g.setJColor(color.darker());
    if (type == HORIZONTAL) {
      int delta = 20, x, kx, ky;
      int x1 = rect.x;
      int x2 = rect.x+rect.width+1;
      int ym = rect.y+rect.height/2;
      int dy = rect.height/4;
      for (x=x1+1, kx=0; x<x2; x+=delta, kx++) {
	if (!(kx % 8)) ky = dy;
	else if (!(kx % 4)) ky = dy/2;
	else ky = dy/4;
        g.drawLine(x, ym-ky, x, ym+ky+1);
      }
      g.drawLine(x1, ym, x2, ym);
    } else {
      int delta = 20, y, kx, ky;
      int y1 = rect.y;
      int y2 = rect.y+rect.height+1;
      int xm = rect.x+rect.width/2;
      int dx = rect.width/4;
      for (y=y1+1, ky=0; y<y2; y+=delta, ky++) {
	if (!(ky % 8)) kx = dx;
	else if (!(ky % 4)) kx = dx/2;
	else kx = dx/4;
        g.drawLine(xm-kx, y, xm+kx+1, y);
      }
      g.drawLine(xm, y1, xm, y2);
    }
  } else {
    g.setJColor(bkgnd);
    g.fillJRect(rect);
  }
}

JColor getMappedColor(int x) {
  if (x > 510) return JColor::red;
  if (x < 0) return JColor::blue;
  if (x < 256) return JColor(0, x, 255-x);
  return JColor(x-256, 511-x, 0);
}

void J1DViewerObj::drawLine(JGraphics g, JRect rect, 
  int& head, int& sequence, int& oldValue) {
  int val = data[head];
  head = (head+1)%bufSize;
  sequence++;
  val = min(val, mask);
  switch (id) {
    case COLORMAP:
      g.setXORMode(getMappedColor(val*510/mask));
      if (type == HORIZONTAL) {
        g.fillRect(rect.x+sequence-1, rect.y,
          1, rect.height);
      } else {
        g.fillRect(rect.x, rect.y+sequence-1,
          rect.width, 1);
      }
      g.setPaintMode();
      break;
    case INTENSITY:
      g.setXORMode(JColor(
        val*color.getRed()/mask,
        val*color.getGreen()/mask,
        val*color.getBlue()/mask));
      if (type == HORIZONTAL) {
        g.fillRect(rect.x+sequence-1, rect.y,
          1, rect.height);
      } else {
        g.fillRect(rect.x, rect.y+sequence-1,
          rect.width, 1);
      }
      g.setPaintMode();
      break;
    case BAR:
      g.setXORMode(color);
      if (type == HORIZONTAL) {
        int dy = val*(rect.height-1)/mask;
        g.fillRect(rect.x+sequence-1, 
          rect.y+rect.height-dy, 1, dy);
      } else {
        g.fillRect(rect.x, rect.y+sequence-1,
          val*(rect.width-1)/mask, 1);
      }
      g.setPaintMode();
      break;
    case COLORMAPBAR:
      g.setXORMode(getMappedColor(val*510/mask));
      if (type == HORIZONTAL) {
        int dy = val*(rect.height-1)/mask;
        g.fillRect(rect.x+sequence-1, 
          rect.y+rect.height-dy, 1, dy);
      } else {
        g.fillRect(rect.x, rect.y+sequence-1,
          val*(rect.width-1)/mask, 1);
      }
      g.setPaintMode();
      break;
    case INTENSITYBAR:
      g.setXORMode(JColor(
        val*color.getRed()/mask,
        val*color.getGreen()/mask,
        val*color.getBlue()/mask));
      if (type == HORIZONTAL) {
        int dy = val*(rect.height-1)/mask;
        g.fillRect(rect.x+sequence-1, 
          rect.y+rect.height-dy, 1, dy);
      } else {
        g.fillRect(rect.x, rect.y+sequence-1,
          val*(rect.width-1)/mask, 1);
      }
      g.setPaintMode();
      break;
    default:
      if (type == HORIZONTAL) {
        g.drawLine(rect.x+sequence-1, 
          rect.y+rect.height-1-
          oldValue*(rect.height-1)/mask,
          rect.x+sequence,
          rect.y+rect.height-1-
          val*(rect.height-1)/mask);
      } else {
        g.drawLine(rect.x+
          oldValue*(rect.width-1)/mask,
          rect.y+sequence-1,
          rect.x+
          val*(rect.width-1)/mask,
          rect.y+sequence);
      }
  }
  oldValue = val;
}

void J1DViewerObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect frect = getIExtent(dx, dy, scale);
  JRect rect = frect.shrink(depth, depth);
  g.setJColor(moduleColor);
  drawFrame(g, frect);
  int psequence = 0;
  int ptail = tail;
  int phead = headBase;
  int poldValue = ovBase;
  g.setJRegion(rgn & rect);
  g.setJColor(color);
  while (phead != ptail)
    drawLine(g, rect, phead, psequence, poldValue);
}

void J1DViewerObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  if (head == tail) {
    paint(g, dx, dy, rgn, scale);
    return;
  }
  JRect frect = getIExtent(dx, dy, scale);
  JRect rect = frect.shrink(depth, depth);
  if ((rect.width > 0) && (rect.height > 0)) {
    int size = (type == HORIZONTAL) ? rect.width : rect.height;
    g.setJRegion(rgn & rect);
    g.setJColor(color);
    while (head != tail) {
      if ((sequence > size) || (sequence < 0)) {
        sequence = 0;
	g.setJRegion(rgn);
	g.setJColor(moduleColor);
	drawFrame(g, frect);
	g.setJRegion(rgn & rect);
	g.setJColor(color);
	headBase = head;
	ovBase = oldValue;
      }
      drawLine(g, rect, head, sequence, oldValue);
    }
  }
}

int J1DViewerObj::inputType(int n) { 
  switch (n) {
    case COLOR:
    case BACKGROUND:
      return JColorData::id;
  }
  return JIntegerData::id;
}

JString J1DViewerObj::inputTag(int n) {
  char* tag[] = { "input", "color", "background", "sync"};
  return tag[n];
}

JFRect J1DViewerObj::outputArea(int n) { 
  if (type == VERTICAL)
    return bottomArea(n, 0, 1, 0, 1);
  return rightArea(n, 0, 1, 0, 1);
}

int J1DViewerObj::outputFace(int n) 
{ return (type == VERTICAL) ? BOTTOM : RIGHT;}

JFPoint J1DViewerObj::outputPoint(int n, JLinkObj& link) { 
  if (type == VERTICAL)
    return JFPoint(x+link.pos*width, y+height);
  return JFPoint(x+width, y+(1.0-link.pos)*height);
}

double J1DViewerObj::outputPos(int n, JFPoint opt) { 
  if (type == VERTICAL)
    return (opt.x-x)/width;
  return (y+height-opt.y)/height;
}

void J1DViewerObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case INPUT: {
      int iv = value;
      link.access(JIntegerData(iv));
      setValue(iv);
      break;
    }
    case COLOR:
    case BACKGROUND:
      processColor(n, link);
      break;
    case SYNC: {
      int iv;
      link.access(JIntegerData(iv));
      if (iv) sequence = -1;
      break;
    }
  }
}

boolean J1DViewerObj::setValue(int _value) {
  int next = (tail+1)%bufSize;
  if (next == head)
    head = (head+1)%bufSize;
  oValue = value;
  data[tail] = value = _value;
  tail = next;
  condBroadcast(0);
  repaint();
  return true;
}

JArray J1DViewerObj::getProperties() {
  JArray properties = J1DMeterObj::getProperties();
  char* idTag[] = {"Line", "Color", "Intensity", 
    "Bar", "ColorBar", "IntensityBar", null};
  properties.append(JIntegerListProperty("id", id, idTag));
  properties.append(JIntegerProperty("bufSize", bufSize, 2048, 16384));
  return properties;
}

boolean J1DViewerObj::updateProperty(JProperty& prop) {
  if (J1DMeterObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("id")) {
    id = ((JIntegerListProperty*)&prop)->value;
    repaintView(*this);
    return true;
  } else if (prop.getName() == JString("bufSize")) {
    bufSize = ((JIntegerProperty*)&prop)->value;
    initialize();
    return true;
  }
  return false;
}

void J1DViewerObj::initialize() {
  tail = head = 0;
  sequence = oldValue = 0;
  headBase = head;
  buf = JBlock(bufSize*sizeof(int), 0);
  data = (int*)(char*)buf;
}

void J1DViewerObj::addButton(JComponent* panel) { 
  addModuleButton(panel, J1DViewerObj(HORIZONTAL));
  addModuleButton(panel, J1DViewerObj(VERTICAL));
}
