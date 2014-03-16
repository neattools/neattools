#if !defined( _JDictionary_h )
#define _JDictionary_h

#include "JHashTable.h"

class
#include "JBase.hpp"
JDictionary : public JHashTable {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDictionary();
    JDictionary(int sz);
    JObject* operator[](const JObject& key);
    JObject* add(const JObject& key);
    JObject* add(const JObject& key, const JObject& val);
    JObject* del(const JObject& key);
};

#endif
