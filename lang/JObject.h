#if !defined(_JObject_h)
#define _JObject_h

#if defined(BC5)
#pragma option -w-par
#endif

#define null  0
#define true 1
#define false 0
#define EMPTY ""

#ifndef max
  #define max(x, y) (((x)>(y))?(x):(y))
#endif

#ifndef min
  #define min(x, y) (((x)<(y))?(x):(y))
#endif

#if defined(WIN32)
  #define DllImport __declspec(dllimport)
  #define DllExport __declspec(dllexport)
#else
  #define DllImport
  #define DllExport
#endif

typedef unsigned char  boolean;
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef void (*iterFuncType)(const class JObject*, void**);
typedef boolean (*condFuncType)(const class JObject*, void**);

class
#include "JBase.hpp"
JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static void putObject(class JOutputStream& os, char* key, JObject& obj);
    static JObject* getObject(class JDictionary& dict, char* key);
    static void putLong(class JOutputStream& os, char* key, long value);
    static long getLong(class JDictionary& dict, char* key, long defulat = 0L);
    static void putInteger(class JOutputStream& os, char* key, int value);
    static int getInteger(class JDictionary& dict, char* key, int defulat = 0);
    static void putFloat(class JOutputStream& os, char* key, float value);
    static float getFloat(class JDictionary& dict, char* key, float defulat = 0.0f);
    static void putDouble(class JOutputStream& os, char* key, double value);
    static double getDouble(class JDictionary& dict, char* key, double value = 0.0);
    static void putString(class JOutputStream& os, char* key, char* value);
    static class JString getString(class JDictionary& dict, char* key, char* value = EMPTY);
    void write(class JOutputStream& os);
    JObject* read(class JInputStream& is);
    JObject();
    virtual ~JObject();
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual boolean isWindow() const;
    virtual void forEach(iterFuncType, void** arg=null) const;
    virtual JObject* firstThat(condFuncType, void** arg=null) const;
    virtual JObject* lastThat(condFuncType, void** arg=null) const;
    virtual int compareTo(const JObject& s) const;
    virtual void run();
    boolean operator==(const JObject& s) const;
    boolean operator!=(const JObject& s) const;
    boolean operator>=(const JObject& s) const;
    boolean operator<=(const JObject& s) const;
    boolean operator> (const JObject& s) const;
    boolean operator< (const JObject& s) const;
    virtual char* Register();
    JObject* prevAddress;
    static int hashMask;
};

#define NOOBJECT  (*(JObject*)null)
#define DupPObj(x) ((x)?((x)->clone()):null)
#define SetPObj(x, y) (delete x, (*(JObject**)&x)=DupPObj(y))
#define DelPObj(x) (delete x, x = null)

#include "JInputStream.h"
#include "JOutputStream.h"

#endif
