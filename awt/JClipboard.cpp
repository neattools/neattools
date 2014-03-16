#include "JClipboard.h"
#include "JWindow.hpp"
#include <string.h>

#define magicHeader 55862971

char* theJClipboard = JClipboard().Register();
const char* JClipboard::className() const { return "JClipboard";}
JObject* JClipboard::clone() const { return new JClipboard(*this);}

#if defined(WIN32)

  void JClipboard::open(int handle) 
  { OpenClipboard((HWND)handle);}

  void JClipboard::close() 
  { CloseClipboard();}

  void JClipboard::empty() 
  { EmptyClipboard();}

  boolean JClipboard::isAvailable(int type) 
  { return IsClipboardFormatAvailable(CF_PRIVATEFIRST+type) != 0;}

  boolean JClipboard::setData(int type, JBlock& data) {
    int sz = data.size();
    int header = magicHeader^type;
    HGLOBAL hptr = GlobalAlloc(GHND, 
      sz+sizeof(int)*2);
    if (!hptr) return false;
    LPSTR ptr = (LPSTR)GlobalLock(hptr);
    if (!ptr) return false;
    memcpy(ptr, &header, sizeof(int));
    memcpy(ptr+sizeof(int), &sz, sizeof(int));
    memcpy(ptr+sizeof(int)*2, data, sz);
    GlobalUnlock(hptr);
    SetClipboardData(CF_PRIVATEFIRST+type, hptr);
    return true;
  }

  JBlock JClipboard::getData(int type) {
    JBlock data;
    HGLOBAL hptr = GetClipboardData(CF_PRIVATEFIRST+type);
    if (!hptr) return data;
    LPSTR ptr = (LPSTR)GlobalLock(hptr);
    if (!ptr) return data;
    int header, size;
    memcpy(&header, ptr, sizeof(int));
    if (header == (magicHeader ^ type)) {
      memcpy(&size, ptr+sizeof(int), sizeof(int));
      if (size > 0) {
        data = JBlock(size, 
	  ptr+sizeof(int)*2, 
	  JBlock::needCopy);
      }
    }
    GlobalUnlock(hptr);
    return data;
  }

  boolean JClipboard::isTextAvailable() 
  { return IsClipboardFormatAvailable(CF_TEXT) != 0;}

  boolean JClipboard::setText(JString data) {
    int sz = data.length()+1;
    HGLOBAL hptr = GlobalAlloc(GHND, sz);
    if (!hptr) return false;
    LPSTR ptr = (LPSTR)GlobalLock(hptr);
    if (!ptr) return false;
    strcpy(ptr, (char*)data);
    GlobalUnlock(hptr);
    SetClipboardData(CF_TEXT, hptr);
    return true;
  }

  JString JClipboard::getText() {
    JString data;
    HGLOBAL hptr = GetClipboardData(CF_TEXT);
    if (!hptr) return data;
    int size = GlobalSize(hptr);
    LPSTR ptr = (LPSTR)GlobalLock(hptr);
    if (!ptr) return data;
    ptr[size-1] = 0;
    data = JString(ptr, JString::needCopy);
    GlobalUnlock(hptr);
    return data;
  }

#else

  void JClipboard::open(int handle) {}

  void JClipboard::close() {}

  void JClipboard::empty() 
  { XStoreBytes(JUNIX::theDisplay, null, 0);}

  boolean JClipboard::isAvailable(int type) {
    int count;
    char *ptr = XFetchBytes(JUNIX::theDisplay, &count);
    XFree(ptr);
    return (ptr != null);
  }

  boolean JClipboard::setData(int type, JBlock& data) {
    int size = data.size();
    int count = size+sizeof(int)*2;
    int header = magicHeader^type;
    JBlock buf(count, 0);
    memcpy(buf, &header, sizeof(int));
    memcpy((char*)buf+sizeof(int), &size, sizeof(int));
    memcpy((char*)buf+sizeof(int)*2, data, size);
    XStoreBytes(JUNIX::theDisplay, buf, count);
    return true;
  }

  JBlock JClipboard::getData(int type) {
    JBlock data;
    int count;
    char *ptr = XFetchBytes(JUNIX::theDisplay, &count);
    if (ptr) {
      int header, size;
      memcpy(&header, ptr, sizeof(int));
      if (header == (magicHeader ^ type)) {
        memcpy(&size, ptr+sizeof(int), sizeof(int));
        if (size > 0) {
          data = JBlock(size, 
	    ptr+sizeof(int)*2, 
	    JBlock::needCopy);
        }
      }
      XFree(ptr);
    }
    return data;
  }

  boolean JClipboard::isTextAvailable() 
  { return isAvailable(0);}

  boolean JClipboard::setText(JString data) {
    XStoreBytes(JUNIX::theDisplay, (char*)data, data.length()+1);
    return true;
  }

  JString JClipboard::getText() {
    JString data;
    int count;
    char *ptr = XFetchBytes(JUNIX::theDisplay, &count);
    if (ptr) {
      ptr[count-1] = 0;
      data = JString(ptr, JString::needCopy);
      XFree(ptr);
    }
    return data;
  }

#endif


