#if !defined( _JFileArray_h )
#define _JFileArray_h

#include "JObject.h"
#include "JFileIOStream.h"

class
#include "JBase.hpp"
JFileArray : public JObject {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JFileArray();
    JFileArray(JString fname, boolean _readOnly = false);
    ~JFileArray();
    void open(JString fname, boolean _readOnly = false);
    void close();
    void updateHeader();
    int size() const;
    int setSize(int ns);
    boolean isValid();
    boolean isEmpty();
    boolean isReadOnly();
    void set(int index, const JBlock& data);
    JBlock get(int index);
    void free(int index);
    void add(const JBlock& data);
    void append(const JBlock& data);
    void insert(const JBlock& data, int index=0, int n=1);
    void insert(int index, int n=1);
    void del(int index, int n=1);
    void delAll();
    void swap(int a, int b);
    void compact();
  protected:
    char header[4];
    int sz, cap, posFree, eof, pad;
    int posTable;
    boolean readOnly;
    JFileIOStream fio;
    JFileInputStream fin;
    int capacity() const;
    int setCapacity(int nc);
    void ensureCapacity(int minCapacity);
    int getFInt(int pos);
    void putFInt(int pos, int v);
    JBlock getFBlock(int pos);
    JBlock getFBlock(int pos, int ds);
    void putFBlock(int pos, JBlock data);
    void putFData(int pos, int index, JBlock data);
    boolean checkMerge(int p1, int p2);
    int relocate(int index);
    void fmove(int dest, int src, int size);
    void fset(int pos, int fill, int size);
};

#endif
