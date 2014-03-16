#if !defined( _JClipboard_h )
#define _JClipboard_h

#include "JBlock.h"
#include "JString.h"

class
#include "JAWT.hpp"
JClipboard : public JObject {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    void open(int handle);
    void close();
    void empty();
    boolean isAvailable(int type);
    boolean setData(int type, JBlock& data);
    JBlock getData(int type);
    boolean isTextAvailable();
    boolean setText(JString data);
    JString getText();
};

#endif
