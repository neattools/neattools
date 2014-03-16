#include "JTextField.h"
#include "JClipboard.h"

char* theJTextField = JTextField().Register();
JTextField* JTextField::create(JComponent* p, JString text, 
  int cols, boolean password) { 
  JTextField *dest = (JTextField*)createJComponent(theJTextField, p);
  dest->setColums(cols);
  dest->setText(text);
  dest->setPasswordMode(password);
  return dest;
}

const char* JTextField::className() const { return "JTextField";}
JObject* JTextField::clone() const { return new JTextField(*this);}
JTextField::JTextField() { 
  mousePressed = false;
  focusOn = false;
  editEnabled = true;
  cursorVisible = false;
  overwriteOn = false;
  updateLock = 0;
  align = LEFT;
  state = CONCAVE;
  depth = DEPTH;
  colums = 20;
  ratio = 2*colums;
  cursor = 0;
  len = 0;
  mBegin = mEnd = 0;
}

void JTextField::setText(JString text) {
  len = text.length();
  if (len > colums)
    text = text(0, len=colums);
  if (cursor > len)
    setCursor(len);
  JLabel::setText(text);
}

void JTextField::beforePaint(JRect *rect) {
  critical.lock();
  if (!updateLock++) {
    if (editEnabled && cursorVisible) {
      showCursor(rect);
      cursorVisible--;
    }
  }
}

void JTextField::afterPaint(JRect *rect) {
  if (!--updateLock) {
    if (editEnabled && !cursorVisible) {
      showCursor(rect);
      cursorVisible++;
    }
  }
  critical.unlock();
}

boolean JTextField::mouseDown(JEvent& e, int x, int y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = true;
    beforePaint();
    cursor = mBegin = mEnd = positionToCursor(x-getBaseX(), 
      getJGraphics(), getText());
    requestFocus();
    afterPaint();
  }
  return true;
}

boolean JTextField::mouseDrag(JEvent& e, int x, int y) {
  if (mousePressed) {
    int nx = positionToCursor(x-getBaseX(), 
      getJGraphics(), getText());
    if (nx != cursor) {
      beforePaint();
      cursor = mEnd = nx;
      afterPaint();
    }
  }
  return true;
}

boolean JTextField::mouseUp(JEvent& e, int x, int y) {
  if (e.modifiers & JEvent::LBUTTON) {
    mousePressed = false;
  }
  return true;
}

boolean JTextField::edit(int key, int modifiers, JString& text, 
  int& cursor, int colums, boolean& overwriteOn,
  int& mBegin, int& mEnd, JString set) {
  int len = text.length();
  cursor = max(0, min(len, cursor));
  if (modifiers & JEvent::CTRL_MASK) {
    boolean isCut = false;
    switch (key) {
      case JEvent::JK_a:
      case JEvent::JK_A: {
        cursor = mBegin = 0;
        mEnd = len;
        break;
      }
      case JEvent::JK_x:
      case JEvent::JK_X: {
        isCut = true;
      case JEvent::JK_c:
      case JEvent::JK_C:
        if (mBegin == mEnd) break;
        JClipboard cb;
        cb.open((int)*theMainWindow);
        if (mBegin < mEnd) {
          cb.empty();
          cb.setText(text(mBegin, mEnd));
        } else if (mEnd < mBegin) {
          cb.empty();
          cb.setText(text(mEnd, mBegin));
        }
        cb.close();
        if (isCut) {
          if (mBegin < mEnd) {
            text = text(0, mBegin)+text(mEnd);
            cursor = mBegin;
            mBegin = mEnd = 0;
          } else if (mEnd < mBegin) {
            text = text(0, mEnd)+text(mBegin);
            cursor = mEnd;
            mBegin = mEnd = 0;
          }
        }
        break;
      }
      case JEvent::JK_v:
      case JEvent::JK_V: {
        JClipboard cb;
        if (cb.isTextAvailable()) {
          JString data;
          cb.open((int)*theMainWindow);
          data = cb.getText();
          cb.close();
          char *ptr = (char*)data;
          while (*ptr >= 32) ptr++;
          *ptr = 0;
          if (mBegin < mEnd) {
            text = text(0, mBegin)+data+text(mEnd);
            cursor = mBegin+data.length();
            mBegin = mEnd = 0;
          } else if (mEnd < mBegin) {
            text = text(0, mEnd)+data+text(mBegin);
            cursor = mEnd+data.length();
            mBegin = mEnd = 0;
          } else {
            text = text(0, cursor)+data+text(cursor);
            cursor += data.length();
          }
        }
        break;
      }
    }
    return true;
  }
  switch (key) {
    case JEvent::JK_Return: 
    case JEvent::JK_Escape:
    case JEvent::JK_Tab:
      mBegin = mEnd = 0;
      return false;
    case JEvent::JK_Home:
      if (modifiers & JEvent::SHIFT_MASK) {
        if (mBegin == mEnd) mBegin = cursor;
        mEnd = cursor = 0;
      } else mBegin = mEnd = cursor = 0;
      break;
    case JEvent::JK_End:
      if (modifiers & JEvent::SHIFT_MASK) {
        if (mBegin == mEnd) mBegin = cursor;
        mEnd = cursor = len;
      } else {
        cursor = len;
        mBegin = mEnd = 0;
      }
      break;
    case JEvent::JK_Left:
      if (modifiers & JEvent::SHIFT_MASK) {
        if (mBegin == mEnd) mBegin = cursor;
        mEnd = --cursor;
      } else {
        if (mBegin != mEnd) {
          cursor = min(mBegin, mEnd);
          mBegin = mEnd = 0;
        } else cursor--;
      }
      break;
    case JEvent::JK_Right:
      if (modifiers & JEvent::SHIFT_MASK) {
        if (mBegin == mEnd) mBegin = cursor;
        mEnd = ++cursor;
      } else {
        if (mBegin != mEnd) {
          cursor = max(mBegin, mEnd);
          mBegin = mEnd = 0;
        } else cursor++;
      }
      break;
    case JEvent::JK_Insert: {
      overwriteOn = !overwriteOn;
      break;
    }
    case JEvent::JK_Delete: {
      if (mBegin < mEnd) {
        text = text(0, mBegin)+text(mEnd);
        cursor = mBegin;
        mBegin = mEnd = 0;
      } else if (mBegin > mEnd) {
        text = text(0, mEnd)+text(mBegin);
        cursor = mEnd;
        mBegin = mEnd = 0;
      } else if (cursor < len) {
        text = text(0, cursor)+text(cursor+1);
      }
      break;
    }
    case JEvent::JK_BackSpace: {
      if (mBegin < mEnd) {
        text = text(0, mBegin)+text(mEnd);
        cursor = mBegin;
        mBegin = mEnd = 0;
      } else if (mBegin > mEnd) {
        text = text(0, mEnd)+text(mBegin);
        cursor = mEnd;
        mBegin = mEnd = 0;
      }
      if (cursor > 0) {
	--cursor;
        text = text(0, cursor)+text(cursor+1);
      }
      break;
    }
    default:
      if ((JEvent::JK_space <= key) && 
        (key < JEvent::JK_ASCIILast)) {
        if (mBegin < mEnd) {
          text = text(0, mBegin)+text(mEnd);
          text = text.insertAt(key, mBegin);
          len = text.length();
          cursor = mBegin+1;
          mBegin = mEnd = 0;
          break;
        } else if (mEnd < mBegin) {
          text = text(0, mEnd)+text(mBegin);
          text = text.insertAt(key, mEnd);
          len = text.length();
          cursor = mEnd+1;
          mBegin = mEnd = 0;
          break;
        }
        if (cursor >= colums) break;
        if (set.length() && (set.indexOf((char)key) == -1)) break;
        if (overwriteOn && (cursor < len)) 
          text[cursor] = (char)key;
        else {
          text = text.insertAt(key, cursor);
          len++;
          if (len > colums) {
            text = text(0, colums);
            len = colums;
          }
        }
        cursor++;
      }
  }
  cursor = max(0, min(len, cursor));
  mBegin = max(0, min(len, mBegin));
  mEnd = max(0, min(len, mEnd));
  return true;
}

boolean JTextField::keyDown(JEvent& e, int key) {
  JString text = getText();
  JString oldText = text;
  int oCursor = cursor;
  int oMBegin = mBegin;
  int oMEnd = mEnd;
  int oOverwriteOn = overwriteOn;
  beforePaint();
  int result = edit(key, e.modifiers, text, cursor, colums, 
    overwriteOn, mBegin, mEnd);
  if (text == oldText) {
    if ((oCursor != cursor) ||
      (oOverwriteOn != overwriteOn) ||
      (oMBegin != mBegin) || (oMEnd != mEnd)) {
      repaint();
    }
  } else setText(text);
  afterPaint();
  return result;
}

boolean JTextField::gotFocus(JEvent& e, JObject* arg) {
  if (e.target == this) {
    beforePaint();
    focusOn = true;
    afterPaint();
  }
  return false;
}

boolean JTextField::lostFocus(JEvent& e, JObject* arg) {
  if (e.target == this) {
    beforePaint();
    focusOn = false;
    afterPaint();
  }
  return false;
}

boolean JTextField::setCursor(int _cursor) {
  _cursor = max(0, min(len, _cursor));
  if (cursor == _cursor) return false;
  beforePaint();
  cursor = _cursor;
  afterPaint();
  return true;
}

int JTextField::getColums() { return colums;}

boolean JTextField::setColums(int cols) {
  if (colums == cols) return false;
  colums = cols;
  ratio = 2*colums;
  repaint();
  return true;
}

int JTextField::getCursor() { return cursor;}

boolean JTextField::setEditEnabled(boolean mode) {
  if (mode == editEnabled) return false;
  editEnabled = mode;
  repaint();
  return true;
}

boolean JTextField::getEditEnabled() { return editEnabled;}

int JTextField::cursorToPosition(int _cursor, JGraphics g, JString text) {
  int pos = 0;
  int len = text.length();
  if (len && (_cursor > 0)) {
    JFontMetrics fm(g);
    _cursor = min(len, _cursor);
    pos = fm.stringWidth(text(0, _cursor));
  } 
  return pos;
}

int JTextField::positionToCursor(int _pos, JGraphics g, JString text) {
  int c = 0;
  int len = text.length();
  if (len && (_pos > 0)) {
    JFontMetrics fm(g);
    for (; c < len; c++) {
      if (_pos < fm.stringWidth(text(0, c+1)))
	break;
    }
  } 
  return c;
}

int JTextField::getBaseX() {
  JFontMetrics fm(getJGraphics());
  int sw = fm.stringWidth(getText());
  switch (align) {
    case LEFT:
      return depth+depth;
    case RIGHT:
      return width-sw-depth-depth;
    default:
      return (width-sw)/2;
  }
}

void JTextField::showCursor(JRect *rect) {
  JGraphics g = getJGraphics();
  JFontMetrics fm(g);
  int sh = fm.getHeight();
  int dx = getBaseX();
  int dy = (height-sh)/2;
  int pos = cursorToPosition(cursor, g, getText());
  int ww = (overwriteOn) ? depth+1 : depth+depth+1;
  if (mBegin != mEnd) {
    int pos1 = cursorToPosition(mBegin, g, getText());
    int pos2 = cursorToPosition(mEnd, g, getText());
    int start = min(pos1, pos2);
    int width = max(pos1, pos2)-start;
    g.setXORMode(JColor::cyan.darker());
    if (focusOn) g.fillRect(dx+start, dy, width, sh);
    else g.drawRect(dx+start, dy, width, sh);
  }
  g.setXORMode(JColor::white);
  if (focusOn) g.fillRect(dx+pos, dy, ww, sh);
  else g.drawRect(dx+pos, dy, ww, sh);
}
