#if !defined( _JListBox_h )
#define _JListBox_h

#include "JScroller.h"
#include "JArray.h"
#include "JHashTable.h"

class
#include "JAWT.hpp"
JListBox : public JCanvas {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JListBox* create(JComponent* p, boolean _multipleSelections);
    JListBox();
    virtual void startup();
    virtual void layout();
    virtual void paint(JGraphics g);
    virtual void paint(int index);
    virtual void beforePaint(JRect *rect = null);
    virtual void afterPaint(JRect *rect = null);
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean gotFocus(JEvent& e, JObject* arg);
    virtual boolean lostFocus(JEvent& e, JObject* arg);
    virtual boolean action(JEvent& e, JObject* arg);
    boolean setCursor(int _cursor);
    int getCursor();
    boolean setBase(int _base);
    int getBase();
    boolean allowMultipleSelections();
    boolean setMultipleSelections(boolean sw);
    void addItem(JString item);
    void addItem(JString item, int index);
    void clear();
    int countItems();
    void delItem(int position, int n=1);
    void deselect(int index);
    JString getItem(int index);
    int getRows();
    int getSelectedIndex();
    JArray getSelectedIndexes();
    JString getSelectedItem();
    JArray getSelectedItems();
    boolean isSelected(int index);
    void makeVisible(int index);
    void replaceItem(JString newValue, int index);
    void select(int index);
    void resetScroller();
    void sort();
  protected:
    int section, base, d, d2, adjust;
    boolean multipleSelections;
    JScroller *scroller;
    JArray content;
    boolean mousePressed;
    boolean focusOn;
    boolean cursorVisible;
    int updateLock;
    int cursor, current;
    virtual void showCursor(JRect *rect);
    int getBaseH();
    int cursorToPosition(int _cursor);
    int positionToCursor(int _pos);
};

#endif
