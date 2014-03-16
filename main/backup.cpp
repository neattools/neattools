#include <stdio.h>
#include "JString.h"
#include "JBlock.h"
#include "JArray.h"
#include "JFileInputStream.h"
#include "JFileOutputStream.h"
#include "JIOException.h"
#include "JFile.h"

void copy(JFile from, JFile to) {
  try {
    JFileInputStream fis(from.getPath());
    JFileOutputStream fos(to.getPath());
    JBlock buf(32768, 0);
    for (;;) {
      fis >> buf;
      fos << buf;
    }
  } catch (JException* e) {
    delete e;
  }
}

JString dotdot("[..]");

void removeDir(JFile dir) {
  int attr = JFile::LA_DIRECTORY | JFile::LA_SORT;
  JArray fa = dir.list(attr, "*.*");
  if (*(JString*)fa[0] == dotdot) fa.del(0);
  int i, sz = fa.size();
  for (i=0; i<sz; i++) {
    JString fn = *(JString*)fa[i];
    JFile tf = JFile(dir, fn(1, fn.length()-1));
    removeDir(tf);
  }
  attr = JFile::LA_FILE | JFile::LA_SORT;
  fa = dir.list(attr, "*.*");
  sz = fa.size();
  for (i=0; i<sz; i++) {
    JFile tf = JFile(dir, *(JString*)fa[i]);
    printf("Delete File %s\n", (char*)tf.getPath());
    tf.remove();
  }
  printf("Remove Directory %s\n", (char*)dir.getPath());
  dir.removeDir();
}

void recursive(JFile from, JFile to) {
  JFile ff, tf;
  JString fn, tn;
  int attr = JFile::LA_DIRECTORY | JFile::LA_SORT;
  JArray fa = from.list(attr, "*.*");
  JArray ta = to.list(attr, "*.*");
  if (*(JString*)fa[0] == dotdot) fa.del(0);
  if (*(JString*)ta[0] == dotdot) ta.del(0);
  int i, sz = fa.size();
  int tsz = ta.size();
  for (i=0; i<sz; i++) {
    fn = *(JString*)fa[i];
    ff = JFile(from, fn(1, fn.length()-1));
    if (i < tsz) {
      tn = *(JString*)ta[i];
      tf = JFile(to, tn(1, tn.length()-1));
    } else tf = JFile(to, "*");
    if ((i >= tsz) || (ff.getName() != tf.getName())) {
      if ((i < tsz) && (ff.getName() > tf.getName())) {
        printf("Remove Extra Directory %s\n", (char*)tf.getPath());
	removeDir(tf);
	ta.del(i);
	tsz--;
	i--;
	continue;
      }
      tf = JFile(to, ff.getName());
      printf("Create Directory %s\n", (char*)tf.getPath());
      tf.makeDir();
      ta.insert(JString("[")+ff.getName()+"]", i);
      tsz++;
    }
    if ((ff.getName() == tf.getName()) && tf.exists()) {
      printf("Check Directory %s\n", (char*)tf.getPath());
      recursive(ff, tf);
    }
  }
  for (; i<tsz; i++) {
    tn = *(JString*)ta[i];
    tf = JFile(to, tn(1, tn.length()-1));
    printf("Remove Extra Directory %s\n", (char*)tf.getPath());
    removeDir(tf);
  }
  attr = JFile::LA_FILE | JFile::LA_SORT;
  fa = from.list(attr, "*.*");
  ta = to.list(attr, "*.*");
  sz = fa.size();
  tsz = ta.size();
  for (i=0; i<sz; i++) {
    ff = JFile(from, *(JString*)fa[i]);
    if (i < tsz) tf = JFile(to, *(JString*)ta[i]);
    else tf = JFile(to, "*");
    if ((i >= tsz) || (ff.getName() != tf.getName())) {
      if ((i < tsz) && (ff.getName() > tf.getName())) {
	printf("Delete Extra File %s\n", (char*)tf.getPath());
	tf.remove();
	ta.del(i);
	tsz--;
	i--;
	continue;
      }
      tf = JFile(to, ff.getName());
      printf("Create File %s\n", (char*)tf.getPath());
      copy(ff, tf);
      ta.insert(ff.getName(), i);
      tsz++;
    }
    if ((ff.getName() == tf.getName()) && tf.exists()) {
      if (ff.lastModified() > tf.lastModified()) {
        printf("Update File %s\n", (char*)tf.getPath());
        copy(ff, tf);
      }
    }
  }
  for (; i<tsz; i++) {
    tf = JFile(to, *(JString*)ta[i]);
    printf("Delete Extra File %s\n", (char*)tf.getPath());
    tf.remove();
  }
}

void backup(char* from, char* to) {
  JFile fromDir(from);
  JFile toDir(to);
  if (fromDir == toDir) {
    printf("Destination and Source are the same!\n");
    return;
  }
  if (!fromDir.exists()) {
    printf("Source Directory Not Exist!\n");
    return;
  }
  if (!toDir.exists()) {
    if (!toDir.makeDir()) {
      printf("Can not create Distination Directory!\n");
      return;
    }
  }
  printf("Backup from %s to %s\n", 
    (char*)fromDir.getPath(), (char*)toDir.getPath());
  recursive(fromDir, toDir);
}

void main(int argc, char* argv[]) {
  if (argc == 3) {
    printf("Backup from %s to %s\n",
      argv[1], argv[2]);
    backup(argv[1], argv[2]);
  } else {
    printf("Usage: backup fromDir toDir\n");
    backup("k:\\bc5\\oop\\", "h:\\oop\\");
  }
}

