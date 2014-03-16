#if !defined( _JBlock_h )
#define _JBlock_h

#include "JReference.h"

class
#include "JBase.hpp"
JBlock : public JReference {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
    virtual void Delete();
    virtual int Duplicate();
  public:
    static JString toJString(JBlock b);
    static JBlock parse(JString s);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JBlock();
    JBlock(int size, int pad);
    JBlock(int size, char* buf, int ref=false);
    JBlock(char &v);
    JBlock(uchar &v);
    JBlock(short &v);
    JBlock(ushort &v);
    JBlock(int &v);
    JBlock(uint &v);
    JBlock(long &v);
    JBlock(ulong &v);
    JBlock(float &v);
    JBlock(double &v);
    JBlock(const class JString &v, int ref=false);
    virtual ~JBlock();
    operator char*() const;
    char& operator[](int index) const;
    JBlock operator()(int begin) const;
    JBlock operator()(int begin, int end) const;
    JBlock& operator+=(const JBlock& b);
    JBlock  operator+ (const JBlock& b) const;
    JBlock& grow(int nSize);
    JBlock insertAt(const JBlock& b, int index) const;
    int indexOf(const JBlock& b, int fromIndex = 0) const;
    int lastIndexOf(const JBlock& b, int fromIndex = 0) const;
    void copy(const JBlock& s) const;
    int size() const;
    int setSize(int _sz) const;
  private:
    int sz;
};

#endif
