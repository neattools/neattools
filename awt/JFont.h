#if !defined( _JFont_h )
#define _JFont_h

#include "JReference.h"
#include "JString.h"

class
#include "JAWT.hpp"
JFont : public JReference {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
    virtual void Delete();
    virtual int Duplicate();
  public:
    enum { PLAIN, BOLD, ITALIC, BOLD_ITALIC};
    static JFont standard;
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JFont();
    JFont(const JString& name, int style, int size);
    ~JFont();
    operator int();
#if !defined(WIN32)
    void* getInfo();
#endif
    JString getName();
    int getStyle();
    int getSize();
    boolean isPlain();
    boolean isBold();
    boolean isItalic();
  protected:
    JString name;
    int style, size;
#if !defined(WIN32)
    void *info;
#endif
};

#endif
