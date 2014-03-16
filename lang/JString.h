#if !defined( _JString_h )
#define _JString_h

#include "JReference.h"

class
#include "JBase.hpp"
JString : public JReference {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
    virtual void Delete();
    virtual int Duplicate();
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JString();
    JString(const char* s, int ref=false);
    JString(const class JBlock& B);
    virtual ~JString();
    operator char*() const;
    char& operator[](int index) const;
    JString  operator()(int begin) const;
    JString  operator()(int begin, int end) const;
    JString& operator+=(const JString& s);
    JString  operator+ (const JString& s) const;
    JString& operator+=(char* str);
    JString  operator+ (char* str) const;
    JString  operator+ (const char* str) const;
    JString& operator+=(char val);
    JString  operator+ (char val) const;
    JString& operator+=(int val);
    JString  operator+ (int val) const;
    JString& operator+=(float val);
    JString  operator+ (float val) const;
    JString& operator+=(double val);
    JString  operator+ (double val) const;
    boolean operator==(const JString& s) const;
    boolean operator!=(const JString& s) const;
    boolean operator>=(const JString& s) const;
    boolean operator<=(const JString& s) const;
    boolean operator> (const JString& s) const;
    boolean operator< (const JString& s) const;
    boolean operator==(char* str) const;
    boolean operator!=(char* str) const;
    boolean operator>=(char* str) const;
    boolean operator<=(char* str) const;
    boolean operator> (char* str) const;
    boolean operator< (char* str) const;
    boolean operator==(const char* str) const;
    boolean operator!=(const char* str) const;
    boolean operator>=(const char* str) const;
    boolean operator<=(const char* str) const;
    boolean operator> (const char* str) const;
    boolean operator< (const char* str) const;
    int length() const;
    boolean equalsIgnoreCase(char* s) const;
    int compareIgnoreCaseTo(char* s) const;
    JString toLowerCase() const;
    JString toUpperCase() const;
    JString trim() const;
    JString insertAt(char ch, int index) const;
    JString insertAt(char* s, int index) const;
    JString insertAt(const JString& s, int index) const;
    int indexOf(char ch, int fromIndex = 0) const;
    int indexOf(char* s, int fromIndex = 0) const;
    int indexOf(const JString& s, int fromIndex = 0) const;
    int lastIndexOf(char ch, int fromIndex = -1) const;
    int lastIndexOf(char* s, int fromIndex = -1) const;
    int lastIndexOf(const JString& s, int fromIndex = -1) const;
    JString token(char* seps, int& index) const;
};

#endif
