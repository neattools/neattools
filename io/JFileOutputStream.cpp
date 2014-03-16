#include "JFileOutputStream.h"
#include "JString.h"
#include "JBlock.h"
#include "JIOException.h"
#include "JFile.hpp"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

char* theJFileOutputStream = JFileOutputStream().Register();
void JFileOutputStream::Delete() { _close_(hnd);}
int JFileOutputStream::Duplicate() 
{ return _dup_(hnd);}

const char* JFileOutputStream::className() const { return "JFileOutputStream";}
JObject* JFileOutputStream::clone() const { return new JFileOutputStream(*this);}
JFileOutputStream::JFileOutputStream() {}
JFileOutputStream::JFileOutputStream(const JString& name) { open(name);}
JFileOutputStream::JFileOutputStream(int handle, boolean ref) { open(handle, ref);}
JFileOutputStream::~JFileOutputStream() { Release();}

void JFileOutputStream::open(JString name) {
  int fd = _open_(name, O_WRONLY | O_CREAT | O_BINARY | O_TRUNC, 0664);
  if (fd == -1) {
    switch (errno) {
      case EACCES:
        throw new JIOException("Output: Permission denied");
      case EMFILE:
        throw new JIOException("Output: Too many open files");
      case ENOENT:
        throw new JIOException("Output: Path or file not found");
      default:
        throw new JIOException("Output: Can't open file");
    }
  }
  Allocate(fd);
}

void JFileOutputStream::open(int handle, boolean ref) 
{ Allocate(handle, ref);}

JOutputStream& JFileOutputStream::operator<<(const JBlock &B) {
  int numWrite;
  int numBytes = B.size();
  if (!numBytes) return *this;
  if ((numWrite = _write_(hnd, B, numBytes)) < 0) {
    throw new JIOException("file write error");
  } else if (numWrite != numBytes) {
    B.setSize(numWrite);
    throw new JIOException("file write not complete");
  }
  return *this;
}

void JFileOutputStream::close() 
{ Release();}

long JFileOutputStream::pos() 
{ return _lseek_(hnd, 0, SEEK_CUR);}
long JFileOutputStream::seek(long pos) 
{ return _lseek_(hnd, pos, SEEK_SET);}
long JFileOutputStream::move(long ofs) 
{ return _lseek_(hnd, ofs, SEEK_CUR);}

