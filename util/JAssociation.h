#if !defined( _JAssociation_h )
#define _JAssociation_h

#include "JObject.h"

class
#include "JBase.hpp"
JAssociation : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JAssociation();
    JAssociation(const JObject& k);
    JAssociation(const JObject& k, const JObject& v);
    JAssociation(const JAssociation& a);
    virtual ~JAssociation();
    JAssociation& operator=(const JAssociation& a);
    JObject* key() const;
    JObject* value() const;
    JObject* setKey(const JObject& k);
    JObject* setValue(const JObject& v);
  private:
    JObject* aKey;
    JObject* aValue;
};

#endif
