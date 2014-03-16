#if !defined( _JDataBaseObj_h )
#define _JDataBaseObj_h

#include "JAddObj.h"
#include "JDataBase.h"

class JDataBaseObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { INDEX, SEARCH, CONDITION, LOCATE, READONLY, UPDATE, INSERT, 
      APPEND, DELETE, DELETEALL, COMPACT, IN_LAST, IN_BLOCK = 15};
    enum { CURRENT_INDEX, TOTAL, OUT_LAST, OUT_BLOCK = 5};
    static int convertBase;
    virtual const char* className() const;
    virtual JObject* clone() const;
    JDataBaseObj();
    JDataBaseObj(const JDataBaseObj& obj);
    ~JDataBaseObj();
    virtual void startup();
    virtual void reset();
    virtual void close();
    int getFieldType(int n);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean check();
    virtual int search(JObject *obj, int fid, int from, int to);
    virtual int searchFirst(JObject *obj, int fid, int from, int to);
    virtual void sort(int fid);
  protected:
    int index, total, N;
    boolean valid;
    int condition, locate, readOnly;
    int update, insert, append; 
    int del, delAll, compact;
    JString filename;
    JString type;
    JArray data, iBuf;
    JDataBase dbf;
    JArray prepareData(JArray& data);
    void updateData();
    JArray fetchData(int index);
    boolean locateData(int index, boolean force = false);
    void insertBlank();
    JArray getFieldTag();
    boolean hasFieldConnected(int index = -1);
};

#endif
