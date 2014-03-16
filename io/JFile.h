#if !defined( _JFile_h )
#define _JFile_h

#include "JObject.h"
#include "JString.h"
#include "JArray.h"

class
#include "JBase.hpp"
JFile : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { 
      LA_FILE = 1,
      LA_DIRECTORY = 2,
      LA_DRIVE = 4,
      LA_ALL = 7,
      LA_SORT = 8};
    static JString separator;
    static JFile workDir;
    static JString check(JString path);
    static JString trimPath(JString path);
    static JString getCurrentDirectory();
    static boolean setCurrentDirectory(JString cwd);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int hashCode() const;
    virtual int compareTo(const JObject& s) const;
    JFile();
    JFile(const JString& _path);
    JFile(const JString& _path, const JString& name);
    JFile(JFile& dir, const JString& name);
    JString getPath();
    JString getReal();
    JString getName();
    JString getParent();
    JFile& changeExt(JString ext);
    boolean exists();
    boolean canWrite();
    boolean canRead();
    boolean canReadWrite();
    boolean isFile();
    boolean isDirectory();
    long lastAccessed();
    long lastCreated();
    long lastModified();
    long length();
    boolean makeDir();
    boolean makeDirs();
    boolean renameTo(JFile dest);
    boolean remove();
    boolean removeDir();
    boolean isRoot();
    JArray list(int attr, const JString& type = "*");
  protected:
    JString path;
    JString real;
    boolean match(JString name, JString type);
};

#endif
