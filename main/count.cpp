#include <stdio.h>
#include "JString.h"
#include "JBlock.h"
#include "JArray.h"
#include "JFileInputStream.h"
#include "JFileOutputStream.h"
#include "JIOException.h"
#include "JFile.h"

void countLines() {
  int i, j, sz;
  char* dirTag[] = { "lang", "util", "io", 
    "net", "awt", "neat", "modules", "scsi", "mainw", null};
  JFile mainDir("\\bc5\\oop");
  JArray fa, all;
  for (i=0; dirTag[i]; i++) {
    JFile subDir(mainDir, dirTag[i]);
    fa = subDir.list(JFile::LA_FILE, "*.h");
    for (j=0, sz=fa.size(); j<sz; j++)
      all.append(JFile(subDir, *(JString*)fa[j]).getPath());
    fa = subDir.list(JFile::LA_FILE, "*.hpp");
    for (j=0, sz=fa.size(); j<sz; j++)
      all.append(JFile(subDir, *(JString*)fa[j]).getPath());
    fa = subDir.list(JFile::LA_FILE, "*.cpp");
    for (j=0, sz=fa.size(); j<sz; j++)
      all.append(JFile(subDir, *(JString*)fa[j]).getPath());
  }
  int lcount, ltotal = 0;
  int bcount, btotal = 0;
  all.sort();
  printf("Count Lines\n");
  for (i=0, sz=all.size(); i<sz; i++) {
    JString name = *(JString*)all[i];
    try {
      JFileInputStream fis(name);
      JBlock data(fis.available(), 0);
      fis >> data;
      lcount = 0;
      bcount = data.size();
      for (j=0; j<bcount; j++) 
	if (data[j] == '\n') lcount++;
      printf("%s size=%d line=%d, btotal=%d ltotal=%d\n", 
	(char*)name, bcount, lcount, 
	btotal+=bcount, ltotal+=lcount);
    } catch (JIOException* e) {
      delete e;
    }
  }
}

void main() {
  countLines();
}

