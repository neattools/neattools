#include "JFile.h"
#include "JIOException.h"
#include "JFile.hpp"

#if defined(WIN32)
  #include <stdlib.h>
  #include <windows.h>
  JString JFile::separator = "\\";
  #if defined(BC5)
    #include <dos.h>
  #endif
#else
  #include <dirent.h>
  #include <stdlib.h>
  JString JFile::separator = "/";
#endif

void adjustPath(char* path) {
  struct _stat_ data;
  if (!_stat_(path, &data) &&
     (data.st_mode & _S_IFDIR_)) {
    int len = JString(path).length();
    if (len && (path[len-1] != JFile::separator[0])) {
      path[len++] = JFile::separator[0];
      path[len] = 0;
    }
  }
}

#if defined(WIN32)

  char *_abspath_(char *resolved_name,
    const char *file_name, int size) {
    char* result = _fullpath(resolved_name, file_name, size);
    adjustPath(resolved_name);
    return result;
  }

#else

  char *_abspath_(char *resolved_name,
    const char *file_name, int size) {
    char* result = realpath(file_name, resolved_name);
    adjustPath(resolved_name);
    return result;
  }

#endif

char* theJFile = JFile().Register();
JFile JFile::workDir("");

void JFile::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putString(os, "path", path);
}

void JFile::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  path = getString(dict, "path");
}

const char* JFile::className() const { return "JFile";}
JObject* JFile::clone() const { return new JFile(*this);}
int JFile::hashCode() const { return path.hashCode();}
int JFile::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return path.compareTo(((JFile*)&s)->path);
}

boolean isRoot(JString path) {
  int p1 = path.indexOf(JFile::separator[0]);
  int p2 = path.lastIndexOf(JFile::separator[0]);
  return ((p2 > -1) && (p2 == p1) &&
    (p2 == path.length()-1));
}

JString JFile::trimPath(JString path) {
  int last = path.length()-1;
  int p1 = path.indexOf(JFile::separator[0]);
  int p2 = path.lastIndexOf(JFile::separator[0]);
  if ((p1 == -1) || (p1 == p2) || (p2 != last)) return path;
  return path(0, last);
}

JString JFile::getCurrentDirectory() {
  char dest[MAXPATHLEN];
  if (_getcwd_(dest, MAXPATHLEN)) {
    adjustPath(dest);
    return JString(dest, JString::needCopy);
  }
  return JString();
}

boolean JFile::setCurrentDirectory(JString cwd) 
{ return !_chdir_(trimPath(cwd));}

JString JFile::check(JString path) {
  char dest[MAXPATHLEN];
  path = path.trim();
  if (!path.length()) path = ".";
  if (_abspath_(dest, trimPath(path), MAXPATHLEN))
    return JString(dest, JString::needCopy);
  return path;
}

/* 
  important, register, and other initialization
  will require this constructor.
  avoid any statement here.
*/

JFile::JFile() {}

JFile::JFile(const JString& _path) {
  path = check(_path);
  if (path.indexOf(separator[0]) == -1)
    path = check(workDir.path+path);
  real = trimPath(path);
}

JFile::JFile(const JString& _path, const JString& name) {
  path = check(JFile(_path).path+name);
  real = trimPath(path);
}

JFile::JFile(JFile& dir, const JString& name) {
  path = check(dir.path+name);
  real = trimPath(path);
}

JString JFile::getPath() { return path;}
JString JFile::getReal() { return real;}

JString JFile::getName() {
  int index = real.lastIndexOf(separator[0]);
  if (index < 0) return real;
  else return real(index+1);
}

JString JFile::getParent() {
  int index = real.lastIndexOf(separator[0]);
  if (index < 0) return separator;
  else return real(0, index+1);
}

JFile& JFile::changeExt(JString ext) {
  int p; // eg. ext = ".txt"
  JString name = getName();
  if ((p=name.indexOf('.')) > -1) {
    name = name(0, p)+ext;
  } else name += ext;
  return (*this = JFile(getParent()+name));
}

boolean JFile::exists() { return !_access_(real, 0);}
boolean JFile::canWrite() { return !_access_(real, 2);}
boolean JFile::canRead() { return !_access_(real, 4);}
boolean JFile::canReadWrite() { return !_access_(real, 6);}

boolean JFile::isFile() {
  struct _stat_ data;
  if (!_stat_(real, &data))
    return (data.st_mode & _S_IFREG_) != null;
  return false;
}

boolean JFile::isDirectory() {
  struct _stat_ data;
  if (!_stat_(real, &data))
    return (data.st_mode & _S_IFDIR_) != null;
  return false;
}

long JFile::lastAccessed() {
  struct _stat_ data;
  if (!_stat_(real, &data))
    return (long)data.st_atime;
  return -1;
}

long JFile::lastCreated() {
  struct _stat_ data;
  if (!_stat_(real, &data))
    return (long)data.st_ctime;
  return -1;
}

long JFile::lastModified() {
  struct _stat_ data;
  if (!_stat_(real, &data))
    return (long)data.st_mtime;
  return -1;
}

long JFile::length() {
  struct _stat_ data;
  if (!_stat_(real, &data))
    return (long)data.st_size;
  return -1;
}

boolean JFile::makeDir() { 
  boolean result = !_mkdir_(real);
  if (result) *this = JFile(path);
  return result;
}

boolean JFile::makeDirs() {
  if (makeDir()) return true;
  JString parent = getParent();
  return (parent.length()) &&
    (JFile(parent).makeDirs() && makeDir());
}

boolean JFile::renameTo(JFile dest)
{ return !rename(real, dest.real);}
boolean JFile::remove() { return !_unlink_(real);}
boolean JFile::removeDir() { return !_rmdir_(real);}
boolean JFile::isRoot() { return ::isRoot(path);}

#include <stdio.h>
JArray JFile::list(int attr, const JString& type) {
  JArray result;
  JString name;
  JString left("[");
  JString right("]");
  JString dot(".");
  JString dot2("..");
#if defined(WIN32)
  #if defined(BC5)
  JString temp = path+type;
  struct ffblk data;
  int done = _findfirst_(temp, &data, FA_DIREC);
  if (!done) {
    if ((attr & LA_DIRECTORY) && !isRoot())
      result.append(left+dot2+right);
    do {
      name = JString(data.ff_name, JString::needCopy);
      if ((name == dot) || (name == dot2)) continue;
      if (data.ff_attrib & FA_DIREC) {
	if (attr & LA_DIRECTORY) result.append(left+name+right);
      } else if (attr & LA_FILE) result.append(name);
    } while (!_findnext_(&data));
    if (attr & LA_SORT) result.sort();
  }
  #else
  JString temp = path+type;
  struct _finddata_t data;
  long handle = _findfirst_(temp, &data);
  if (handle != -1) {
    if ((attr & LA_DIRECTORY) && !isRoot())
      result.append(left+dot2+right);
    do {
      name = JString(data.name, JString::needCopy);
      if ((name == dot) || (name == dot2)) continue;
      if (data.attrib & _A_SUBDIR) {
	if (attr & LA_DIRECTORY) result.append(left+name+right);
      } else if (attr & LA_FILE) result.append(name);
    } while (!_findnext_(handle, &data));
    _findclose_(handle);
    if (attr & LA_SORT) result.sort();
  }
  #endif
  if (attr & LA_DRIVE) {
    char tmp[6] = "[-A-]";
    DWORD mask = GetLogicalDrives();
    for (int i=0; i<26; i++) {
      if ((mask >> i) & 1) {
        tmp[2] = (char)('A'+i);
	result.append(JString(tmp, JString::needCopy));
      }
    }
  }
#else
  DIR *dir;
  struct dirent *ent;
  struct _stat_ data;
  if ((dir = opendir(real)) != null) {
    if ((attr & LA_DIRECTORY) && !isRoot())
      result.append(left+dot2+right);
    while ((ent = readdir(dir)) != null) {
      name = JString(ent->d_name, JString::needCopy);
      if ((name == dot) || (name == dot2)) continue;
      if (!match(name, type)) continue;
      if (!_stat_(trimPath(path+name), &data)) {
	if (data.st_mode & _S_IFDIR_) {
	  if (attr & LA_DIRECTORY) result.append(left+name+right);
	} else if (attr & LA_FILE) result.append(name);
      }
    }
    closedir(dir);
    if (attr & LA_SORT) result.sort();
  }
#endif
  return result;
}

boolean JFile::match(JString name, JString type) {
  if (type[0] == '*') {
    if (type[1]) {
      return (name.lastIndexOf((char*)type(1)) > -1);
    } else return true;
  }
  return false;
}
