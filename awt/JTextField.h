#if !defined( _JTextField_h )
#define _JTextField_h

#include "JLabel.h"
#include "JCriticalSection.h"

class
#include "JAWT.hpp"
JTextField : public JLabel {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JTextField* create(JComponent* p, JString text, int cols = 512, boolean password = false);
    static boolean edit(int key, int modifiers, JString& text, 
      int& cursor, int colums, boolean& overwriteOn,
      int& mBegin, int& mEnd,
      JString set = "");
    static int cursorToPosition(int _cursor, JGraphics g, JString text);
    static int positionToCursor(int _pos, JGraphics g, JString text);
    JTextField();
    virtual void setText(JString text);
    virtual void beforePaint(JRect *rect = null);
    virtual void afterPaint(JRect *rect = null);
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseDrag(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean gotFocus(JEvent& e, JObject* arg);
    virtual boolean lostFocus(JEvent& e, JObject* arg);
    boolean setCursor(int _cursor);
    int getCursor();
    boolean setColums(int _cols);
    int getColums();
    boolean setEditEnabled(boolean mode);
    boolean getEditEnabled();
  protected:
    boolean overwriteOn;
    boolean mousePressed;
    boolean focusOn;
    boolean editEnabled;
    boolean cursorVisible;
    JCriticalSection critical;
    int updateLock;
    int colums;
    int cursor;
    int len;
    int mBegin, mEnd;
    virtual void showCursor(JRect *rect);
    int getBaseX();
};

#endif
