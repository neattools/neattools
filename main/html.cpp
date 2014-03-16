#include <stdio.h>
#include "JString.h"
#include "JBlock.h"
#include "JArray.h"
#include "JFileInputStream.h"
#include "JFileOutputStream.h"
#include "JIOException.h"
#include "JFile.h"

JString HtoTXT(JString name) 
{ return name(0, name.length()-2)+".txt";}

JFile getCurrent(JArray& all, JString current) {
  int j, sz;
  JString name;
  for (j=0, sz=all.size(); j<sz; j++) {
    name = ((JFile*)all[j])->getName();
    if (name(0, name.length()-2) == current)
      return *(JFile*)all[j];
  }
  return JFile();
}

JArray findChildren(JArray& all, JString current) {
  int j, sz, pos, plen;
  JArray children;
  JString pattern = JString(": public ")+current;
  plen = pattern.length();
  for (j=0, sz=all.size(); j<sz; j++) {
	try {
      JFileInputStream fis(((JFile*)all[j])->getPath());
      JBlock data(fis.available(), 0);
      fis >> data;
      pos = JString(data).indexOf(pattern);
      if ((pos > -1) && 
        ((data[pos+plen] == ' ') || 
        (data[pos+plen] == ',')))
        children.append(*all[j]);
    } catch (JIOException *e) {
      printf("%s\n", (char*)e->getMessage());
      delete e;
    }
  }
  children.sort();
  return children;
}

void recursive(JArray& all, int level, JString prefix, JString current, boolean next) {
  int j, sz;
  JFile file = getCurrent(all, current);
  JArray children = findChildren(all, current);
  printf("%s+-<a href=\"%s/%s\">%s</a>\n", 
    (char*)prefix, 
    (char*)JFile(file.getParent()).getName(),
    (char*)HtoTXT(file.getName()),
    (char*)current);
  if (next) prefix+="|   ";
  else prefix+="    ";
  for (j=0, sz=children.size(); j<sz; j++) {
    JString name = ((JFile*)children[j])->getName();
    name = name(0, name.length()-2);
    printf("%s|\n", (char*)prefix);
    recursive(all, level+1, prefix, name, (j<sz-1));
  }
}

void makeHTML() {
  int i, j, sz;
  char* dirTag[] = { "lang", "util", "io", 
    "net", "awt", "neat", "modules", "scsi", null};
  JFile mainDir("\\bc5\\oop");
  JArray fa, all;
  printf("<HTML>\n");
  printf("<BODY background=\"../sands.gif\" width=100 height=100>\n");
  printf("<HEAD>\n");
  printf("<TITLE>Java Like Cross Platform C++ API</TITLE>\n");
  printf("<H1>Java Like Cross Platform C++ API</H1>\n");
  printf("<HR>\n");
  for (i=0; dirTag[i]; i++) {
    JFile subDir(mainDir, dirTag[i]);
    fa = subDir.list(JFile::LA_FILE | JFile::LA_SORT, "*.h");
    for (j=0, sz=fa.size(); j<sz; j++) {
      all.append(JFile(subDir, *(JString*)fa[j]));
    }
  }
  if (all.size()) {
    all.sort();
    printf("<PRE>\n");
    recursive(all, 0, "", "JObject", false);
    printf("</PRE>\n");
  }
  printf("<HR>\n");
  for (i=0; dirTag[i]; i++) {
    JFile subDir(mainDir, dirTag[i]);
    fa = subDir.list(JFile::LA_FILE | JFile::LA_SORT, "*.h");
    printf("<H2>Directory [%s]:</H2>\n", dirTag[i]);
    printf("<UL>\n");
    for (j=0, sz=fa.size(); j<sz; j++) {
      printf("<LI><A href=%s/%s>%s</A>\n", 
	dirTag[i],
	(char*)HtoTXT(*(JString*)fa[j]),
	(char*)*(JString*)fa[j]);
      all.append(JFile(dirTag[i], *(JString*)fa[j]).getPath());
    }
    printf("</UL><P>\n");
  }
  printf("<HR>\n");
  printf("<ADDRESS>\n");
  printf("Yuh-Jye Chang,<BR>\n");
  printf("<A HREF=\"http://www.npac.syr.edu/\">\n");
  printf("Northeast Parallel Architectures Center</A>\n");
  printf("Syracuse University.<BR>\n");
  printf("Send comments or suggestions to yjchang@npac.syr.edu.<BR>\n");
  printf("Last modified 3 Oct 97.\n");
  printf("</ADDRESS>\n");
  printf("</BODY>\n");
  printf("</HTML>\n");
}

void main() {
  makeHTML();
}

