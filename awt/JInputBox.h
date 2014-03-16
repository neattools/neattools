#if !defined( _JInputBox_h )
#define _JInputBox_h

#include "JMessageBox.h"
#include "JTextField.h"

class
#include "JAWT.hpp"
JInputBox : public JMessageBox {
  public:
    static int create(JString text, int _style, JString& data, 
      int x=-1, int y=-1, boolean password=false);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void startup();
    virtual boolean transferArguments();
    virtual boolean gotFocus(JEvent& e, JObject* arg);
  protected:
    JTextField *tf;
};

#endif
