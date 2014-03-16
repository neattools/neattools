#if !defined( _JDataType_h )
#define _JDataType_h

#include "JString.h"
#include "JArray.h"
#include "JColor.h"

class
#include "JNEAT.hpp"
JDataType : public JObject {
  public:
    static JString str;
    static JString bstr;
    static char* tag[];
    static const int id;
    static const JColor color;
    static int last;
    static int convertBase;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual void reset() const = 0;
    virtual void assign(const JObject& obj) const = 0;
    static JArray getDataArray();
    static JObject* create(int id, class JLinkObj& link);
    static JObject* create(int id, const JBlock& item);
    static JObject* createTag(int &id, const JBlock& item);
    static JBlock toBlock(int id, const JObject& obj);
    static JBlock toTagBlock(int id, const JObject& obj);
};

#endif
