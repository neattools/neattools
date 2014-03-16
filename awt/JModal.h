#if !defined( _JModal_h )
#define _JModal_h

#include "JComponent.h"

class
#include "JAWT.hpp"
JModal : public JComponent {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static int create();
    int runModal();
    void endModal(int _result);
    virtual boolean transferArguments();
    virtual boolean lostFocus(JEvent& e, JObject* arg);
};

#endif
