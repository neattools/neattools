#include "JFileIOStream.h"
#include "JString.h"
#include "JBlock.h"
#include "JIOException.h"
#include "JFile.hpp"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

char* theJFileIOStream = JFileIOStream().Register();
const char* JFileIOStream::className() const { return "JFileIOStream";}
JObject* JFileIOStream::clone() const { return new JFileIOStream(*this);}
JFileIOStream::JFileIOStream() {}
JFileIOStream::JFileIOStream(const JString& name) { open(name);}

void JFileIOStream::open(JString name) {
  int fd = _open_(name, O_RDWR | O_CREAT | O_BINARY, 0664);
  if (fd == -1) {
    switch (errno) {
      case EACCES:
        throw new JIOException("File I/O: Permission denied");
      case EMFILE:
        throw new JIOException("File I/O: Too many open files");
      case ENOENT:
        throw new JIOException("File I/O: Path or file not found");
      default:
        throw new JIOException("File I/O: Can't open file");
    }
  }
  Allocate(fd);
}

JOutputStream& JFileIOStream::operator<<(const JBlock &B) {
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

void JFileIOStream::close() { Release();}
boolean JFileIOStream::truncate(long size) 
{ return !_truncate_(hnd, size);}

