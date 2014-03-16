#include "JLabelObj.h"
#include "JTextField.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JLinkObj.h"
#include "JColorData.h"
#include "JStringData.h"
#include "JStringProperty.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JColorProperty.h"
#include "JFileProperty.h"
#include "JBMPFile.h"
#include "JImage.h"
#include "JDictionary.h"

char* theJLabelObj = JLabelObj().Register();
void JLabelObj::writeContent(JOutputStream& os) {
  JLEDObj::writeContent(os);
  putObject(os, "label", label);
  putString(os, "imageFile", imageFile);
  putInteger(os, "canEdit", canEdit);
  putInteger(os, "raise", raise);
  putInteger(os, "align", align);
  putInteger(os, "hAlign", hAlign);
  putInteger(os, "fraction", fraction);
  putInteger(os, "fontId", fontId);
  putInteger(os, "fontStyleId", fontStyleId);
  putInteger(os, "echoOn", echoOn);
  putInteger(os, "drawBorder", drawBorder);
  putInteger(os, "drawBackground", drawBackground);
  putInteger(os, "useImage", useImage);
  putInteger(os, "autoScaleImage", autoScaleImage);
}

void JLabelObj::readContent(JDictionary& dict) {
  JLEDObj::readContent(dict);
  JObject *obj = getObject(dict, "label");
  if (obj) label = *(JString*)obj;
  imageFile = getString(dict, "imageFile");
  canEdit = getInteger(dict, "canEdit");
  raise = getInteger(dict, "raise");
  align = getInteger(dict, "align");
  hAlign = getInteger(dict, "hAlign");
  fraction = getInteger(dict, "fraction");
  fontId = getInteger(dict, "fontId");
  fontStyleId = getInteger(dict, "fontStyleId");
  echoOn = getInteger(dict, "echoOn");
  drawBorder = getInteger(dict, "drawBorder", true);
  drawBackground = getInteger(dict, "drawBackground", true);
  useImage = getInteger(dict, "useImage", false);
  autoScaleImage = getInteger(dict, "autoScaleImage", false);
}

const char* JLabelObj::className() const { return "JLabelObj";}
JObject* JLabelObj::clone() const { return new JLabelObj(*this);}

char* fontTag[] = {
  "courier",
  "fixed",
  "helvetica",
  "schoolbook",
  "terminal",
  "times",
  null
};

char* fontStyleTag[] = {
  "plain",
  "bold",
  "italic",
  "bold italic",
  null
};

boolean JLabelObj::overwriteOn = false;

void JLabelObj::calculateJRegion(JRegion& rgn, double dx, double dy, double scale) {
  JRect rect = getIExtent(dx, dy, scale);
  region = JRegion(getIExtent(dx, dy, scale)) & rgn;
  if (drawBorder && (rect.width > depth2) && (rect.height > depth2)) {
    rect.shrinkBy(depth, depth);
    if (!drawBackground) region -= JRegion(rect);
    rgn -= region;
  } else {
    if (drawBackground) rgn -= region;
  }
}

JLabelObj::JLabelObj()
  :JLEDObj(JColor::black, JColor::lightGray) { 
  eventMask = MOUSE_MASK | FOCUS_MASK | KEYBOARD_MASK;
  label = "A"; 
  hasEditFocus = false; 
  canEdit = false;
  focusOn = false;
  cursor = mBegin = mEnd = 0;
  needRelocate = false;
  raise = JLabel::CONCAVE;
  align = JLabel::CENTER;
  hAlign = HALIGN_AUTO;
  nextFocus = false;
  enterPressed = false;
  escapePressed = false;
  mousePressed = false;
  echoOn = false;
  fraction = 25;
  fontId = 0;
  fontStyleId = 1;
  igm = IN_LAST;
  ogm = OUT_LAST;
  dirty = false;
  drawBorder = true;
  drawBackground = true;
  type = "*.bmp";
}

void JLabelObj::startup() 
{ focusOn = parent->getRoot()->isFocusOn();}

void JLabelObj::reset() 
{ hasEditFocus = false;}

#if defined(WIN32)
  #include <windows.h>
#endif

JDictionary dict(101);

boolean JLabelObj::fillImage(JGraphics g, JRect rect) {
#if defined(WIN32)
  if (!useImage || (imageFile.length() == 0)) return false;
  JBMPFile* bmpFile = (JBMPFile*)dict[imageFile];
  if (bmpFile == null) {
    JBMPFile bmp;
    int result = bmp.load(imageFile);
    if (result != JBMPFile::SUCCESS) return false;
    (JBMPFile*)dict.add(imageFile, bmp);
    bmpFile = (JBMPFile*)dict[imageFile];
    if (bmpFile == null) return false;
  }
  char* bits;
  HBITMAP hbmp = CreateDIBSection((HDC)(int)g,
    (BITMAPINFO*)&bmpFile->bmpInfo, DIB_RGB_COLORS, 
    (void**)&bits, null, null);
  if (hbmp == null) return false;
  JBlock(bmpFile->data.size(), bits).copy(bmpFile->data);
  JImage image((int)hbmp);
  int width = bmpFile->width;
  int height = bmpFile->height;
  if (!autoScaleImage) {
    for (int x=0; x<rect.width; x+=width)
    for (int y=0; y<rect.height; y+=height) {
      g.drawJImage(image, rect.x+x, rect.y+y);
    }
  } else g.drawJImage(image, rect.x, rect.y, 
    rect.width, rect.height);
  return true;
#else
  return false;
#endif
}

void JLabelObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  g.setJColor(moduleColor);
  JRect rect = getIExtent(dx, dy, scale);
  JRegion region = JRegion(rect);
  g.setJRegion(JRegion(rect) | rgn);
  if (drawBorder && (rect.width > depth2) && (rect.height > depth2)) {
    g.draw3DJRect(rect, depth);
    rect.shrinkBy(depth, depth);
    if (!drawBackground) region -= JRegion(rect);
    rgn -= region;
  } else {
    if (drawBackground) rgn -= region;
  }
  update(g, dx, dy, rgn, scale);
}

void JLabelObj::update(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JRect rect = getIExtent(dx, dy, scale), srect;
  g.setJRegion(JRegion(rect) | rgn);
  g.setJColor(bkgnd);
  if (drawBorder && (rect.width > depth2) && (rect.height > depth2)) {
    rect.shrinkBy(depth, depth);
    if (drawBackground) 
      if (!fillImage(g, rect)) g.fillJRect(rect);
  } else if (drawBackground) {
      if (!fillImage(g, rect)) g.fillJRect(rect);
  }
  int delta = 0;
  JFont font;
  if (hAlign == HALIGN_FRACTION) {
    if (fraction) {
      delta = rect.height*fraction/200;
      rect.shrinkBy(0, delta);
    }
    do {
      delta += depth;
      font = JFont(fontTag[fontId], fontStyleId, rect.height-delta);
      g.setJFont(font);
      JFontMetrics fm(g);
      if (fm.getHeight() <= rect.height) break;
    } while (rect.height > delta);
  } else {
    int factor = 0, sh;
    int len = label.length();
    len = (max(1, len)+5)/6*6;
    align = JLabel::CENTER;
    JFont font;
    do {
      delta = rect.height*factor/200;
      sh = rect.height-delta*2-depth;
      font = JFont("courier", fontStyleId, sh);
      g.setJFont(font);
      JFontMetrics fm(g);
      if (len*fm.charWidth('0') <= rect.width) break;
      factor += 10;
    } while (factor < 100);
    rect.shrinkBy(0, delta);
  }
  srect = JLabel::formatText(g, label, rect, 
    color, bkgnd, raise, align);
  if (canEdit && hasEditFocus) {
    int len = srect.height;
    if (len < label.length()) {
      label = label(0, len);
      cursor = min(len, cursor);
    }
    if (needRelocate) {
      JPoint pt = getIPoint(JFPoint(xpos, y), dx, dy, scale);
      int ncursor = JTextField::positionToCursor(pt.x-srect.x, g, label);
      if (needRelocate < 2) mBegin = mEnd = ncursor;
      mEnd = cursor = ncursor;
      needRelocate = false;
    }
    int pos = JTextField::cursorToPosition(cursor, g, label);
    int ww = (overwriteOn) ? depth+1 : depth2+1;
    if (mBegin != mEnd) {
      int pos1 = JTextField::cursorToPosition(mBegin, g, label);
      int pos2 = JTextField::cursorToPosition(mEnd, g, label);
      int start = min(pos1, pos2);
      int width = max(pos1, pos2)-start;
      g.setXORMode(JColor::cyan.darker());
      if (focusOn) g.fillRect(srect.x+start, rect.y, width, rect.height);
      else g.drawRect(srect.x+start, rect.y, width, rect.height);
    }
    g.setXORMode(JColor::white);
    if (focusOn)
      g.fillRect(srect.x+pos, rect.y, ww, rect.height);
    else g.drawRect(srect.x+pos, rect.y, ww, rect.height);
    g.setPaintMode();
  }
}

int JLabelObj::inputType(int n) { 
  switch (n) {
    case IN_DATA: 
    case IN_IMAGEFILE:
      return JStringData::id;
    case IN_COLOR:
    case IN_BKGND: 
      return JColorData::id;
  }
  return JIntegerData::id;
}

int JLabelObj::outputType(int n) { 
  if (n == OUT_DATA) return JStringData::id;
  return JIntegerData::id;
}

JString JLabelObj::inputTag(int n) {
  char* tag[] = { "input", "color", "background", 
    "editFocus(logical)", "clear(logical)", "imageFile(String)"};
  return tag[n];
}

JString JLabelObj::outputTag(int n) {
  char* tag[] = { "output", "nextFocus(logical)", 
    "enterKey(logical)", "escapeKey(logical)"};
  return tag[n];
}

JFRect JLabelObj::inputArea(int n) {
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, igm-1);
}

JFRect JLabelObj::outputArea(int n) { 
  if (!n) return rightArea(n, 0, 1);
  return bottomArea(n, 1, ogm-1);
}

int JLabelObj::outputFace(int n) 
{ return (!n) ? RIGHT : BOTTOM;}

JFPoint JLabelObj::inputPoint(int n, JLinkObj& link) { 
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, igm-1);
}

JFPoint JLabelObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return rightPoint(n, link, 0, 1);
  return bottomPoint(n, link, 1, ogm-1);
}

void JLabelObj::access(int n, JLinkObj& link, const JDataType& data) { 
  switch (n) {
    case OUT_DATA : 
      JSTRING(data) = label;
      break;
    case OUT_NEXTFOCUS:
      INT(data) = nextFocus;
      break;
    case OUT_ENTER:
      INT(data) = enterPressed;
      break;
    case OUT_ESCAPE:
      INT(data) = escapePressed;
      break;
  }
}

void JLabelObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      JString iv = label;
      link.access(JStringData(iv));
      if (iv == label) break;
      if (canEdit && hasEditFocus) {
        int i, sz = label.length();
        for (i=0; (i<sz) && (label[i] == iv[i]); i++);
        cursor = mBegin = i;
        mEnd = iv.length();
        setLabel(iv);
      } else setLabel(iv);
      break;
    }
    case IN_COLOR:
    case IN_BKGND: {
      processColor(n, link);
      break;
    }
    case IN_EDITFOCUS: {
      int iv;
      link.access(JIntegerData(iv));
      if (iv != 0) {
        if (!canEdit) {
          nextFocus = true;
          broadcast(OUT_NEXTFOCUS);
          nextFocus = false;
          broadcast(OUT_NEXTFOCUS);
        } else requestEditFocus();
      }
      break;
    }
    case IN_CLEAR: {
      int iv;
      link.access(JIntegerData(iv));
      if (iv != 0) {
        cursor = 0;
        setLabel("");
      }
      break;
    }
    case IN_IMAGEFILE: {
      JString iv = label;
      link.access(JStringData(iv));
      if (iv == imageFile) break;
      imageFile = iv;
      if (useImage) repaint();
      break;
    }
  }
}

char* raiseTag[] = { "CONCAVE", "PLAIN", "CONVEX", null};
char* alignTag[] = { "LEFT", "CENTER", "RIGHT", null};
char* hAlignTag[] = { "AUTO", "FRACTION", null};

JArray JLabelObj::getProperties() {
  JArray properties = JModuleObj::getProperties();
  properties.append(JStringProperty("label", label));
  properties.append(JColorProperty("color", color));
  properties.append(JColorProperty("bkgnd", bkgnd));
  properties.append(JIntegerListProperty("canEdit", canEdit,
    JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("raiseMode", raise,
    raiseTag));
  properties.append(JIntegerListProperty("hAlignMode", hAlign,
    hAlignTag));
  if (hAlign == HALIGN_FRACTION) {
    properties.append(JIntegerProperty("fraction", fraction,
      0, 98));
    properties.append(JIntegerListProperty("alignMode", align,
      alignTag));
    properties.append(JIntegerListProperty("fontId", fontId,
      fontTag));
  }
  properties.append(JIntegerListProperty("fontStyleId", fontStyleId,
    fontStyleTag));
  properties.append(JIntegerListProperty("echoOn", echoOn,
    JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("drawBorder", drawBorder,
    JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("drawBackground", drawBackground,
    JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("useImage", useImage,
    JIntegerListProperty::booleanTag));
  if (useImage) {
    properties.append(JIntegerListProperty("autoScaleImage", autoScaleImage,
      JIntegerListProperty::booleanTag));
  }
  properties.append(JFileProperty("imageFile", imageFile, type));
  return properties;
}

boolean JLabelObj::updateProperty(JProperty& prop) {
  if (JModuleObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("label")) {
    setLabel(((JStringProperty*)&prop)->value);
    return true;
  } if (prop.getName() == JString("imageFile")) {
    imageFile = ((JFileProperty*)&prop)->value;
    if (useImage) repaint();
    return true;
  } else if (prop.getName() == JString("color")) {
    color = ((JColorProperty*)&prop)->color;
    repaint();
    return true;
  } else if (prop.getName() == JString("bkgnd")) {
    bkgnd = ((JColorProperty*)&prop)->color;
    repaint();
    return true;
  } else if (prop.getName() == JString("canEdit")) {
    canEdit = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("raiseMode")) {
    raise = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("alignMode")) {
    align = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("hAlignMode")) {
    hAlign = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("fontId")) {
    fontId = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("fontStyleId")) {
    fontStyleId = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("fraction")) {
    fraction = ((JIntegerProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("echoOn")) {
    echoOn = ((JIntegerProperty*)&prop)->value;
    if (echoOn) setLabel(label);
    return true;
  } else if (prop.getName() == JString("drawBorder")) {
    drawBorder = ((JIntegerProperty*)&prop)->value;
    repaintView(*this, REGION_MODE);
    return true;
  } else if (prop.getName() == JString("drawBackground")) {
    drawBackground = ((JIntegerProperty*)&prop)->value;
    repaintView(*this, REGION_MODE);
    return true;
  } else if (prop.getName() == JString("useImage")) {
    useImage = ((JIntegerProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("autoScaleImage")) {
    autoScaleImage = ((JIntegerProperty*)&prop)->value;
    repaint();
    return true;
  }
  return false;
}

boolean JLabelObj::mouseDown(JEvent& e, double x, double y) {
  if (canEdit && hasEditFocus &&
    (e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = true;
    needRelocate = true;
    xpos = x;
    repaint();
  }
  return true;
}

boolean JLabelObj::mouseDrag(JEvent& e, double x, double y) {
  if (mousePressed) {
    needRelocate = 2;
    xpos = x;
    repaint();
  }
  return true;
}

boolean JLabelObj::mouseUp(JEvent& e, double x, double y) {
  if (e.modifiers & JEvent::LBUTTON) {
    mousePressed = false;
  }
  return true;
}

boolean JLabelObj::keyDown(JEvent& e, int key) {
  if (canEdit && hasEditFocus) {
    JString nLabel = label;
    int oCursor = cursor;
    int oMBegin = mBegin;
    int oMEnd = mEnd;
    int oOverwriteOn = overwriteOn;
    if (JTextField::edit(key, e.modifiers, nLabel, cursor, 512, 
      overwriteOn, mBegin, mEnd)) {
      dirty = (nLabel != label);
      if (dirty) {
        if (echoOn) {
          if (setLabel(nLabel)) return true;
        } else label = nLabel;
        repaint();
      } else if ((oCursor != cursor) ||
        (oOverwriteOn != overwriteOn) ||
        (oMBegin != mBegin) || (oMEnd != mEnd)) {
        repaint();
      }
    } else processCtrlKeys(key);
  }
  return true;
}

void JLabelObj::processCtrlKeys(int key) {
  switch (key) {
    case JEvent::JK_Return:
      enterPressed = true;
      broadcast(OUT_ENTER);
      setLabel(label);
      enterPressed = false;
      broadcast(OUT_ENTER);
      break;
    case JEvent::JK_Escape:
      escapePressed = true;
      broadcast(OUT_ESCAPE);
      setLabel(label);
      escapePressed = false;
      broadcast(OUT_ESCAPE);
      break;
    case JEvent::JK_Tab:
      nextFocus = true;
      broadcast(OUT_NEXTFOCUS);
      setLabel(label);
      nextFocus = false;
      broadcast(OUT_NEXTFOCUS);
      break;
  }
}

boolean JLabelObj::gotFocus(JEvent& e) {
  focusOn = true;
  if (hasEditFocus && canEdit)
    repaint();
  return true;
}

boolean JLabelObj::lostFocus(JEvent& e) {
  focusOn = false;
  if (hasEditFocus && canEdit)
    repaint();
  return true;
}

boolean JLabelObj::gotEditFocus(JEvent& e) { 
  if (canEdit) {
    hasEditFocus = true;
    if (canEdit) {
      mBegin = cursor = 0;
      mEnd = label.length();
      repaint();
    }
    return true;
  }
  return false;
}

boolean JLabelObj::lostEditFocus(JEvent& e) { 
  hasEditFocus = false;
  if (canEdit) {
    setLabel(label);
    repaint();
  }
  return true;
}

boolean JLabelObj::setLabel(JString _label) {
  if (dirty || _label != label) {
    dirty = false;
    label = _label;
    broadcast(0);
    repaint();
    return true;
  }
  return false;
}

JString JLabelObj::getEditSet() { return "";}
