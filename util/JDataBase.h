#if !defined( _JDataBase_h )
#define _JDataBase_h

#include "JArray.h"
#include "JString.h"
#include "JDictionary.h"
#include "JFileArray.h"

class
#include "JBase.hpp"
JDataField : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JDataField();
    JDataField(JString name, JString type, int id);
    JString getName();
    JString getType();
    int getId();
    int current;
  protected:
    JString name;
    JString type;
    int id;
};

class
#include "JBase.hpp"
JDataBase : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static int convertBase;
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JDataBase();
    JDataBase(JString fname, boolean _readOnly = false);
    ~JDataBase();
    void open(JString fname, boolean _readOnly = false);
    void close();
    void updateHeader();
    int getNumOfField() const;
    int getNextId();
    int getSortId();
    int getSortFieldIndex();
    void setSortId(int sid);
    void setSortFieldIndex(int fid);
    boolean hasField(const JDataField& field);
    JDataField* getField(int index);
    JDataField* getFieldById(int id);
    void setField(int index, const JDataField& field);
    void addField(const JDataField& field);
    void appendField(const JDataField& field);
    void insertField(const JDataField& field, int index = 0);
    void delField(int index, int n=1);
    void delAllField();
    void swapField(int a, int b);
    int size() const;
    int setSize(int ns);
    boolean isValid();
    boolean isEmpty();
    boolean isReadOnly();
    void set(int index, const JArray& data);
    JArray get(int index);
    void add(const JArray& data);
    void append(const JArray& data);
    void insert(const JArray& data, int index=0);
    void insert(int index, int n=1);
    void del(int index, int n=1);
    void delAll();
    void swap(int a, int b);
    void compact();
  protected:
    JFileArray fa;
    JString header;
    int numOfField;
    int currentId;
    int sortId;
    boolean valid;
    JArray fields;
    JDictionary dict;
    void updateFieldDict();
};

#endif
