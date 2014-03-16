#if !defined( _JMessageBox_h )
#define _JMessageBox_h

#include "JModal.h"
#include "JButton.h"

class
#include "JAWT.hpp"
JMessageBox : public JModal {
  public:
    enum { 
      BTN_OK = 2,
      BTN_OKCANCEL = 3,
      BTN_YESNO = 12,
      BTN_YESNOCANCEL = 13
    };
    static int create(JString text, int _style, 
      int x = -1, int y = -1);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void startup();
    JMessageBox();
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean action(JEvent& e, JObject* arg);
    void setLocation(int xx, int yy, int ww, int hh);
    JButton *ok, *cancel, *yes, *no;
    JCanvas *cPanel, *uPanel;
};

#endif
