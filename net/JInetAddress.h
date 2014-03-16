#if !defined( _JInetAddress_h )
#define _JInetAddress_h

#include "JBlock.h"
#include "JString.h"
#include "JArray.h"

class
#include "JBase.hpp"
JInetAddress : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JInetAddress();
    JInetAddress(const JString& name);
    JInetAddress(const JBlock& addr);
    operator int&() const;
    JString getHostName();
    JBlock getAddress();
    JString getAddressJString();
    static JInetAddress getByName(const JString& host);
    static JInetAddress getByAddr(const JBlock& addr);
    static JString getJStringByAddr(const JBlock& addr);
    static JBlock getAddrByJString(const JString& addr);
    static JArray getAllByName(const JString& host);
    static JInetAddress localHost;
    static short inetFamily;
    static int addrLen;
  protected:
    JString hostName;
    JBlock address;
    JInetAddress(const JString& name, const JBlock& addr);
};

#endif
