#include <JString.h>
#include <JBlock.h>
#include <JFileInputStream.h>
#include <JFileOutputStream.h>
#include <JIOException.h>

#include <stdio.h>
#include <string.h>

char* mainFile = "Oop.cpp";
char* mainDir = "/root/oop";
char* makefile = "makefile2";
char* subDir[] = {
  "./lang",
  "./util",
  "./io",
  "./net",
  "./awt",
  "./neat",
  "./modules",
  "."
};

#define SUBDIR_MAX (sizeof(subDir)/sizeof(char*))

JString toName(JString data) {
  JString result = data;
  result.Dereference();
  char *ptr = strstr(result, ".cpp");
  if (ptr) *ptr = 0;
  return result;
}

JString toObj(JString data) {
  JString result = data;
  result.Dereference();
  char *ptr = strstr(result, ".cpp");
  if (ptr) strcpy(ptr, ".o");
  return result;
}

JString toC(JString data) {
  JString result = data;
  result.Dereference();
  char *ptr = strstr(result, ".cpp");
  if (ptr) strcpy(ptr, ".C");
  return result;
}

boolean search(char* file, JString& path) {
  long hFile;
  for (int i=0; i<SUBDIR_MAX; i++) {
    JString name = JString(subDir[i])+"/"+file;
    try {
      JFileInputStream test(name);
      path = name;
      return true;
    } catch (JIOException *e) { 
      delete e;
    }
  }
  return false;
}

void analyze(char* file, JString& data) {
  try {
    JBlock buf(16384, 0);
    JFileInputStream fis(file);
    fis >> buf;
    JString content(buf), name, path;
    char *ptr = content, *base;
    do {
      ptr = strstr(ptr, "#include ");
      if (ptr) {
        ptr += 9;
        while (strchr(" <\"", *ptr)) ptr++;
        base = ptr;
        while (!strchr(">\"", *ptr)) ptr++;
        name = JString(JBlock(ptr-base, base));
        if (search(name, path)) {
	  if (!strstr(data, path)) {
            data += JString(" \\\n  ")+path;
	    analyze(path, data);
  	  }
        }
      }
    } while (ptr);
  } catch (JIOException *e) {
    delete &e;
  }
}

#include <fcntl.h>
#include <dirent.h>

void generate() {
  JString objs(""), include("");
  JString data, inc, fname, obj;
  int i;
  DIR *dir;
  struct dirent *ent;

  for (i=0; i<SUBDIR_MAX; i++)
    include += JString(" -I ")+subDir[i];
  printf("CFLAGS = -fhandle-exceptions\n");
  printf("INCLUDES =%s\n", (char*)include);
  printf("CP = cp\nRM = rm\nCC = cc\n\nall :: %s\n\n", 
    (char*)toName(mainFile));
  for (i=0; i<SUBDIR_MAX; i++) {
    if ((dir = opendir(subDir[i])) == NULL) {
      perror("Unable to open directory");
      exit(1);
    }
    while ((ent = readdir(dir)) != NULL) {
      if (JString(ent->d_name).indexOf(".cpp") > -1) {
	data = "";
	fname = JString(subDir[i])+"/"+ent->d_name;
	obj = toObj(fname);
	objs += JString(" \\\n  ")+obj;
	data = obj +" : "+fname+" ";
        analyze(fname, data);
	data += JString("\n\t$(CC) -c $(CFLAGS) ");
	data += JString("$(INCLUDES) -o $@ ")+fname;
 	printf("%s\n\n", (char*)data);
      }
    }
  }
 
  closedir(dir);
  printf("OBJS = %s\n\n", (char*)objs);
  data = toName(mainFile) +" : $(OBJS)";
  data += JString("\n\t$(CC) -lm $(CFLAGS) -o $@ $(OBJS)\n");
  printf("%s\n", (char*)data);
  data = JString("clean : \n\t$(RM) ")+toName(mainFile)+" $(OBJS)";
  printf("%s\n", (char*)data);
}

int main(int argc , char **argv) {
  generate();
  return 0;
}


