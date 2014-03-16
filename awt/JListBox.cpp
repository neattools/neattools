#include "JListBox.h"
#include "JAssociation.h"
#include "JInteger.h"
#include "JBorderLayout.h"

char* theJListBox = JListBox().Register();
JListBox* JListBox::create(JComponent* p, boolean _multipleSelections) {
  JListBox *dest = (JListBox*)createJComponent(theJListBox, p);
  dest->setMultipleSelections(_multipleSelections);
  return dest;
}

void JListBox::startup() {
  JBorderLayout border;
  scroller = JScroller::create(this, JScroller::VERTICAL);
  setLayout(border);
  add(JBorderLayout::EAST, *scroller);
}

void JListBox::layout() {
  resetScroller();
  JCanvas::layout();
}

void JListBox::paint(JGraphics g) {
  int dx = d2+d2, dy;
  int th = getBaseH();
  int ns = section;
  JString text;
  JFontMetrics fm(g);
  JRect clip = g.getClipJRect();
  JRect frame = JRect(0, 0, width-scroller->width, height);
  JRegion rgn(clip &= frame);
  JColor color = getForeground();
  JColor bkgnd = getBackground();
  JColor light = bkgnd.brighter();
  clip &= frame.shrink(d, d);
  if (base+ns > content.size())
    ns = content.size()-base;
  for (int i=0; i<ns; i++) {
    dy = i*th+d2;
    JRect cell(d2, dy, width-scroller->width-d2*2, th-d);
    JRect area = cell & clip;
    JRect inner = cell.shrink(d, d) & clip;
    if (area.isEmpty()) continue;
    JAssociation &obj = *(JAssociation*)content[i+base];
    text = *(JString*)obj.key();
    g.setClipJRect(cell & clip);
    g.setJColor(bkgnd);
    if (!(int)*(JInteger*)obj.value()) {
      g.fill3DJRect(cell, d);
      g.setJColor(light);
      g.setClipJRect(inner);
      g.drawJString(text, dx+1, dy+1);
    } else {
      g.fill3DJRect(cell, -d);
      g.setJColor(light);
      g.setClipJRect(inner);
      g.drawJString(text, dx-1, dy-1);
    }
    g.setJColor(color);
    g.drawJString(text, dx, dy);
    rgn -= JRegion(area);
  }
  g.setJRegion(rgn);
  g.setJColor(bkgnd);
  g.fill3DJRect(frame, -d);
}

void JListBox::paint(int index) {
  int th = getBaseH();
  int dy = (index-base)*th+d2;
  int ns = section;
  if (base+ns > content.size())
    ns = content.size()-base;
  if ((index < base) || (index >= base+ns)) return;
  repaint(d2, dy, width-scroller->width-d2-d2, th, true);
}

const char* JListBox::className() const { return "JListBox";}
JObject* JListBox::clone() const { return new JListBox(*this);}

JListBox::JListBox() { 
  multipleSelections = false;
  d = 1;
  d2 = d+d;
  section = 1;
  adjust = 0;
  mousePressed = false;
  focusOn = false;
  cursorVisible = false;
  depth = 0;
  updateLock = 0;
  state = CONCAVE;
  base = 0;
  cursor = 0;
  current = -1;
}

void JListBox::beforePaint(JRect *rect) {
  if (!updateLock++) {
    if (focusOn && cursorVisible) {
      showCursor(rect);
      cursorVisible--;
    }
  }
}

void JListBox::afterPaint(JRect *rect) {
  if (!--updateLock) {
    if (focusOn && !cursorVisible) {
      showCursor(rect);
      cursorVisible++;
    }
  }
}


boolean JListBox::mouseDown(JEvent& e, int x, int y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    if (e.modifiers & JEvent::DBCLK_MASK) {
      JEvent event(this, JEvent::ACTION_EVENT);
      event.key = -1;
      postJEvent(event);
      return true;
    }
    mousePressed = true;
    requestFocus();
    setCursor(positionToCursor(y));
    select(cursor);
  }
  return true;
}

boolean JListBox::mouseUp(JEvent& e, int x, int y) {
  if (mousePressed && (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = false;
  }
  return true;
}

boolean JListBox::keyDown(JEvent& e, int key) {
  switch (key) {
    case JEvent::JK_Return: {
      JEvent event(this, JEvent::ACTION_EVENT);
      event.key = -1;
      postJEvent(event);
      break;
    }
    case JEvent::JK_Escape:
    case JEvent::JK_Left:
    case JEvent::JK_Right:
      return false;
    case JEvent::JK_space:
      select(cursor);
      break;
    case JEvent::JK_Home:
      setCursor(0);
      break;
    case JEvent::JK_End:
      setCursor(content.size()-1);
      break;
    case JEvent::JK_Prior:
      setCursor(cursor-max(1, section-adjust));
      break;
    case JEvent::JK_Next:
      setCursor(cursor+max(1, section-adjust));
      break;
    case JEvent::JK_Up:
      setCursor(cursor-1);
      break;
    case JEvent::JK_Down:
      setCursor(cursor+1);
      break;
  }
  return true;
}

boolean JListBox::gotFocus(JEvent& e, JObject* arg) {
  if (e.target == this) {
    beforePaint();
    focusOn = true;
    afterPaint();
  }
  return false;
}

boolean JListBox::lostFocus(JEvent& e, JObject* arg) {
  if (e.target == this) {
    beforePaint();
    focusOn = false;
    afterPaint();
  }
  return false;
}

boolean JListBox::action(JEvent& e, JObject* arg) {
  if (e.target == scroller) {
    setBase(e.key);
    return true;
  }
  return false;
}

boolean JListBox::setCursor(int _cursor) {
  _cursor = max(0, min(content.size()-1, _cursor));
  if (cursor == _cursor) return false;
  beforePaint();
  cursor = _cursor;
  makeVisible(cursor);
  afterPaint();
  return true;
}

int JListBox::getCursor() { return cursor;}

boolean JListBox::setBase(int _base) {
  _base = max(0, min(content.size()-1, _base));
  if (base == _base) return false;
  int delta = base-_base;
  updateInvalidArea();
  beforePaint();
  base = _base;
  ScrollWindow(d, d, 
    width-scroller->width-d2, height-d2, 
    0, delta*getBaseH());
  afterPaint();
  scroller->setValue(base);
  return true;
}

int JListBox::getBase() { return base;}

boolean JListBox::allowMultipleSelections() { return multipleSelections;}

boolean JListBox::setMultipleSelections(boolean sw) {
  if (sw == multipleSelections) return false;
  multipleSelections = sw;
  return true;
}

void JListBox::addItem(JString item) {
  content.append(JAssociation(item, JInteger()));
}

void JListBox::addItem(JString item, int index) {
  content.insert(JAssociation(item, JInteger()), index);
  if (index <= current) current++;
}

void JListBox::clear() {
  content.delAll();
  base = 0;
  cursor = 0;
  current = -1;
}

int JListBox::countItems() {
  return content.size();
}

void JListBox::delItem(int position, int n) {
  content.del(position, n);
  if ((current >= position) &&
    (current < position+n)) current = -1;
  else if (current >= position+n) current -= n;
}

void JListBox::deselect(int index) {
  ((JAssociation*)content[index])->setValue(JInteger(0));
}

JString JListBox::getItem(int index) {
  return *(JString*)((JAssociation*)content[index])->key();
}

int JListBox::getRows() { return section;}
int JListBox::getSelectedIndex() { return current;}

JArray JListBox::getSelectedIndexes() {
  JArray Selected;
  int size = content.size();
  for (int i=0; i<size; i++) {
    JAssociation &obj = *(JAssociation*)content[i];
    if ((int)*(JInteger*)obj.value() == 1) {
      Selected.append(JInteger(i));
    }
  }
  return Selected;
}

JString JListBox::getSelectedItem() {
  if (current > -1) {
    JAssociation &obj = *(JAssociation*)content[current];
    return *(JString*)obj.key();
  }
  return JString();
}

JArray JListBox::getSelectedItems() {
  JArray Selected;
  int size = content.size();
  for (int i=0; i<size; i++) {
    JAssociation &obj = *(JAssociation*)content[i];
    if ((int)*(JInteger*)obj.value() == 1) {
      Selected.append(*obj.key());
    }
  }
  return Selected;
}

void JListBox::makeVisible(int index) {
  if (index < base) setBase(index);
  else if (index >= base+section-adjust)
    setBase(index-section+adjust+1);
}

void JListBox::replaceItem(JString newValue, int index) {
  JAssociation &obj = *(JAssociation*)content[index];
  obj.setKey(newValue);
}

void JListBox::select(int index) {
  if (index >= content.size()) return;
  int oldcurrent = current;
  makeVisible(index);
  current = index;
  JAssociation &obj = *(JAssociation*)content[current];
  if (!multipleSelections) {
    obj.setValue(JInteger(1));
    if (current != oldcurrent) {
      if (oldcurrent != -1) {
	deselect(oldcurrent);
	paint(oldcurrent);
      }
      paint(current);
      JEvent event(this, JEvent::ACTION_EVENT, &obj);
      event.key = index;
      postJEvent(event);
    }
  } else {
    int oldValue = (int)*(JInteger*)obj.value();
    obj.setValue(JInteger(!oldValue));
    paint(current);
    JEvent event(this, JEvent::ACTION_EVENT, &obj);
    event.key = index;
    postJEvent(event);
  }
}

void JListBox::resetScroller() {
  beforePaint();
  int sz = content.size();
  adjust = (((height-d2-d) % getBaseH()) != 0);
  section = ((height-d2-d)/getBaseH())+1;
  scroller->setValue(base, section-adjust, 
    0, sz, true);
  base = min(sz, base);
  cursor = min(sz, cursor);
  afterPaint();
}

void JListBox::sort() { content.sort();}
int JListBox::cursorToPosition(int _cursor) 
{ return (_cursor-base)*getBaseH()+d;}
int JListBox::positionToCursor(int _pos) 
{ return ((_pos-d)/getBaseH())+base;}
int JListBox::getBaseH() 
{ return JFontMetrics(getJGraphics()).getHeight()+d2+d;}

void JListBox::showCursor(JRect *rect) {
  JGraphics g = getJGraphics();
  g.setXORMode(JColor::white);
  g.setLineStyle(JGraphics::DASH_LINE);
  g.drawRect(d, cursorToPosition(cursor), 
    width-scroller->width-d2, getBaseH()+d);
}

