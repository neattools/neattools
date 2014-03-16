#if !defined( _JPanel_h )
#define _JPanel_h

#include "JScroller.h"

class
#include "JAWT.hpp"
JPanel : public JComponent {
  public:
    enum { NOSCROLL, VSCROLL, HSCROLL, HVSCROLL};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JPanel* create(JComponent *p, 
      JComponent *item, int type = VSCROLL);
    JPanel();
    virtual void layout();
    virtual JDimension preferredSize();
    virtual JDimension minimumSize();
    virtual boolean action(JEvent& e, JObject* arg);
  protected:
    int type;
    int xOfs, yOfs;
    JComponent *item, *client;
    JScroller *vscroll;
    JScroller *hscroll;
    JDimension getItemPreferredSize();
    JDimension getItemMinimumSize();
};

#endif
