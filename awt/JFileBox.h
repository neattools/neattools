#if !defined( _JFileBox_h )
#define _JFileBox_h

#include "JInputBox.h"
#include "JListBox.h"
#include "JFile.h"

class
#include "JAWT.hpp"
JFileBox : public JInputBox {
  public:
    static int create(JString text,
      JString& data, JString type, 
      int x = -1, int y = -1);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void startup();
    virtual boolean transferArguments();
    virtual boolean action(JEvent& e, JObject* arg);
  protected:
    JListBox *fileList;
    JListBox *dirList;
    JLabel *filter;
    JFile path;
    JString type, ext;
    void updateLists();
};

#endif
