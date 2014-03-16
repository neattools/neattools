#if !defined( _JArray_h )
#define _JArray_h

#include "JReference.h"
#include "JList.h"

class
#include "JBase.hpp"
JArray : public JReference {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void forEach(iterFuncType, void** arg=null) const;
    virtual JObject* firstThat(condFuncType, void** arg=null) const;
    virtual JObject* lastThat(condFuncType, void** arg=null) const;
    virtual int compareTo(const JObject& s) const;
    JArray();
    JArray(int s);
    JArray(char** sa);
    JArray(JList& list);
    virtual ~JArray();
    JObject* operator[](int index) const;
    JObject* operator[](const JObject& s) const;
    JObject* set(int index, const JObject& s);
    void free(int index);
    void grow(int ns, const JObject& fill);
    int size() const;
    int setSize(int ns) const;
    int capacity() const;
    boolean isEmpty() const;
    int indexOf(const JObject& s, int index = 0) const;
    int lastIndexOf(const JObject& s, int index = -1) const;
    JObject* first();
    JObject* last();
    JObject* add(const JObject& s);
    JObject* insert(const JObject& s, int index = 0, int n=1);
    JObject* insert(int index, int n = 1);
    JObject* append(const JObject& s);
    JObject* toFirst(const JObject& s);
    JObject* toLast(const JObject& s);
    JObject* reparent(const JObject& s, JArray& np);
    void del(int index, int n = 1);
    void del(const JObject& s);
    void delAll();
    void sort();
    void swap(int a, int b);
  protected:
    virtual void Delete();
    virtual int Duplicate();
    void ensureCapacity(int minCapacity) const;
    void quickSort(int from, int to);
};

#endif
