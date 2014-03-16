#if !defined( _JIntegerListBox_h )
#define _JIntegerListBox_h

#include "JMessageBox.h"
#include "JListBox.h"
#include "JArray.h"

class
#include "JAWT.hpp"
JIntegerListBox : public JMessageBox {
  public:
    static int create(JString text, 
      int _style, int &value, JArray tag,
      int x=-1, int y=-1);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void startup();
    virtual boolean action(JEvent& e, JObject* arg);
    virtual boolean gotFocus(JEvent& e, JObject* arg);
    virtual boolean transferArguments();
  protected:
    JListBox *tagList;
    int value;
};

#endif
