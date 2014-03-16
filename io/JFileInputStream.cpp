#include "JFileInputStream.h"
#include "JString.h"
#include "JBlock.h"
#include "JEOFException.h"
#include "JIOException.h"
#include "JFile.hpp"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

char* theJFileInputStream = JFileInputStream().Register();
void JFileInputStream::Delete() { _close_(hnd);}
int JFileInputStream::Duplicate() 
{ return _dup_(hnd);}

const char* JFileInputStream::className() const { return "JFileInputStream";}
JObject* JFileInputStream::clone() const { return new JFileInputStream(*this);}
JFileInputStream::JFileInputStream() {}
JFileInputStream::JFileInputStream(const JString& name) { open(name);}
JFileInputStream::JFileInputStream(int handle, boolean ref) { open(handle, ref);}
JFileInputStream::~JFileInputStream() { Release();}

void JFileInputStream::open(JString name) {
  int fd = _open_(name, O_RDONLY | O_BINARY, 0444);
  if (fd == -1) {
    switch (errno) {
      case EACCES:
        throw new JIOException("Input: Permission denied");
      case EMFILE:
        throw new JIOException("Input: Too many open files");
      case ENOENT:
        throw new JIOException("Input: Path or file not found");
      default:
        throw new JIOException("Input: Can't open file");
    }
  }
  Allocate(fd);
}

void JFileInputStream::open(int handle, boolean ref) 
{ Allocate(handle, ref);}

JInputStream& JFileInputStream::operator>>(const JBlock &B) {
  int numBytes;
  if ((numBytes = _read_(hnd, B, B.size())) <= 0) {
    if (!numBytes) throw new JEOFException("end of file");
    throw new JIOException("file read error");
  } else B.setSize(numBytes);
  return *this;
}

JInputStream& JFileInputStream::operator>>(JString &v) 
{ return JInputStream::operator>>(v);}

long JFileInputStream::skip(long n) {
  long pos = _lseek_(hnd, 0, SEEK_CUR);
  return (_lseek_(hnd, n, SEEK_CUR) - pos);
}

int JFileInputStream::available() {
  long pos = _lseek_(hnd, 0, SEEK_CUR);
  long avail = _lseek_(hnd, 0, SEEK_END)-pos;
  _lseek_(hnd, pos, SEEK_SET);
  return avail;
}

void JFileInputStream::close() { Release();}
void JFileInputStream::reset() 
{ _lseek_(hnd, 0, SEEK_SET);}
long JFileInputStream::pos() 
{ return _lseek_(hnd, 0, SEEK_CUR);}
long JFileInputStream::seek(long pos) 
{ return _lseek_(hnd, pos, SEEK_SET);}
long JFileInputStream::move(long ofs) 
{ return _lseek_(hnd, ofs, SEEK_CUR);}

