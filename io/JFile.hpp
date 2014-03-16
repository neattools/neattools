#if defined(UNDER_CE)
#else
  #include <sys/stat.h>
#endif
#if defined(WIN32) || defined(UNDER_CE)
  #if defined(UNDER_CE)
    #define _open_ _open
    #define _dup_ _dup
    #define _lseek_ _lseek
    #define _read_ _read
    #define _write_ _write
    #define _close_ _close
    #define _access_ _access
    #define _unlink_ _unlink
    #define _mkdir_ _mkdir
    #define _rmdir_ _rmdir
    #define _stat_ _stat
    #define _getcwd_ _getcwd
    #define _chdir_ _chdir
    #define _truncate_ _chsize
    #define _findfirst_ _findfirst
    #define _findnext_ _findnext
    #define _findclose_ _findclose
    #define _S_IFREG_ _S_IFREG
    #define _S_IFDIR_ _S_IFDIR
  #else
    #include <io.h>
    #include <direct.h>
    #define _open_ _open
    #define _dup_ _dup
    #define _lseek_ _lseek
    #define _read_ _read
    #define _write_ _write
    #define _close_ _close
    #define _access_ _access
    #define _unlink_ _unlink
    #define _mkdir_ _mkdir
    #define _rmdir_ _rmdir
    #define _stat_ _stat
    #define _getcwd_ _getcwd
    #define _chdir_ _chdir
    #define _truncate_ _chsize
    #define _findfirst_ _findfirst
    #define _findnext_ _findnext
    #define _findclose_ _findclose
    #define _S_IFREG_ _S_IFREG
    #define _S_IFDIR_ _S_IFDIR
  #endif
  #define MAXPATHLEN 128
#else
  #include <sys/param.h>
  #include <unistd.h>
  #include <stdio.h>
  #define _open_ ::open
  #define _dup_ ::dup
  #define _lseek_ ::lseek
  #define _read_ ::read
  #define _write_ ::write
  #define _close_ ::close
  #define _access_ ::access
  #define _unlink_ ::unlink
  #define _mkdir_(p) mkdir(p, 0777)
  #define _rmdir_ ::rmdir
  #define _getcwd_ ::getcwd
  #define _chdir_ ::chdir
  #define _truncate_ ::ftruncate
  #define _stat_ stat
  #define _S_IFREG_ S_IFREG
  #define _S_IFDIR_ S_IFDIR
  #define O_BINARY 0
#endif

