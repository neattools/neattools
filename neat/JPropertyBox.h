#if !defined( _JPropertyBox_h )
#define _JPropertyBox_h

#include "JMessageBox.h"
#include "JListBox.h"
#include "JProperty.h"
#include "JModuleCanvas.h"

class
#include "JNEAT.hpp"
JPropertyBox : public JMessageBox {
  public:
    static int create(JString text,
      JArray properties, int& select, 
      int x, int y, JModuleObj *obj);
    static int create(JString text,
      JArray properties, int& select,
      int x, int y);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void startup();
    virtual boolean transferArguments();
    virtual boolean gotFocus(JEvent& e, JObject* arg);
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean action(JEvent& e, JObject* arg);
  protected:
    JListBox *pList;
    JModuleCanvas *mc;
    int select;
};

#endif
