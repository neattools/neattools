#include <stdio.h>
#include "JObject.h"
#include "JPObject.h"
#include "JCriticalSection.h"
#include "JString.h"
#include "JArray.h"
#include "JList.h"
#include "JDList.h"
#include "JAssociation.h"
#include "JDictionary.h"
#include "JBlock.h"
#include "JThread.h"
#include "JSystem.h"
#include "JMath.h"
#include "JRandom.h"
#include "JBoolean.h"
#include "JCharacter.h"
#include "JInteger.h"
#include "JLong.h"
#include "JFloat.h"
#include "JDouble.h"
#include "JProcess.h"
#include "JPipedStream.h"
#include "JFileInputStream.h"
#include "JFileOutputStream.h"
#include "JEOFException.h"
#include "JSocketException.h"
#include "JInetAddress.h"
#include "JSocket.h"
#include "JServerSocket.h"
#include "JSocketInputStream.h"
#include "JSocketOutputStream.h"
#include "JFile.h"
#include "JFileArray.h"
#include "JDataBase.h"
#include "JDate.h"

class ListenJThread : public JThread {
  virtual void run();
};

void ListenJThread::run() {
  printf("JServerSocket Test\n");
  JSocket accept;
  JServerSocket ssock;
  for (;;) {
    JThread::sleep(500);
    printf("Try Binding\n");
    try {
      ssock = JServerSocket(3490);
      break; 
    } catch (JSocketException *e) {
      printf("Server Binding Error %s\n", (char*)e->getMessage());
      ssock.close();
      delete e;
    }
  }
  for (;;) {
    JThread::sleep(500);
    printf("Try Listen\n");
    try {
      if (ssock.listen(0)) {
        ssock.accept(accept);
        printf("Listen Address : %s\n",
          (char*)accept.getJInetAddress().getAddressJString());
        JSocketOutputStream sos(accept);
        JSocketInputStream sis(accept);
        JBlock data(100, 0);
        printf("Listen Start\n");
        sos << JString("Hello OOP!\n");
        printf("Server Send\n");
        JThread::sleep(500);
        sis >> data;
        printf("Server Receive: %s\n", (char*)JString(data));
        accept.close();
        break;
      }
    } catch (JIOException *e) {
      printf("Server %s\n", (char*)e->getMessage());
      delete e;
    }
  }
  ssock.close();
}

class MyJThread : public JObject {
  public:
    int valid;
    virtual void run();
};

void MyJThread::run() {
  valid = 1;
  while (valid) {
    JThread::sleep(1000);
    printf("Thread1 T%3d\n", valid);
  }
}

class MyJThread2 : public JThread {
  virtual void run();
};

void MyJThread2::run() {
  printf("Thread2 Sleep\n");
  sleep(2000);
  printf("Waitup\n");
}

class MyJThread3 : public JThread {
  public:
    int valid;
    virtual void run();
};

void MyJThread3::run() {
  valid = 1;
  while (valid) {
    sleep(1000);
    printf("Thread3 T%3d\n", valid);
  }
}


void Show(const JObject* p, void**)
{ printf("%s", (char*)*(JString*)p);}

boolean CanShow(const JObject* p, void**)
{ printf("%s", (char*)*(JString*)p); return false;}


void Test() {
  int i;
/*
  printf("Test Date\n");
  {
    JDate date;
    printf("Seconds Since midnight, January 1, 1970 %d\n",
      (int)date);
    printf("Timezone is %d, TimeDelta is %d\n",
      date.getTimezone(), date.getTimeDelta());
    printf("Daylight Save Time is %d\n",
      date.isDST());
    printf("Today is %s\n", (char*)date.toJString());
    printf("Today is %d/%d/%d %d:%d:%d %d of week %d of year\n",
      date.getMonth()+1, date.getDate(), date.getYear(), 
      date.getHours(), date.getMinutes(), date.getSeconds(),
      date.getWDay(), date.getYDay());
    date = date.UTC();
    printf("UTC is %s\n", (char*)date.toJString());
    printf("UTC is %d/%d/%d %d:%d:%d %d of week %d of year\n",
      date.getMonth()+1, date.getDate(), date.getYear(),
      date.getHours(), date.getMinutes(), date.getSeconds(),
      date.getWDay(), date.getYDay());
    date = JDate("8/27");
    printf("Test 8/27 is %s\n", (char*)date.toJString());
    date = JDate("8/27/1998");
    printf("Test 8/27/1998 is %s\n", (char*)date.toJString());
    date = JDate("8/27/1998 23:10");
    printf("Test 8/27/1998 23:10 is %s\n", (char*)date.toJString());
    date = JDate("8/27/1998 23:10:07");
    printf("Test 8/27/1998 23:10:07 is %s\n", (char*)date.toJString());
    date = JDate("23:10");
    printf("Test 23:10 is %s\n", (char*)date.toJString());
    date = JDate("23:10:07");
    printf("Test 23:10:07 is %s\n", (char*)date.toJString());

    int k, y, m, d, h, min, yd, wd;
    for (i=0; i<1; i++) {
      k = JDate::DtoI(date.getYear(), date.getMonth(), date.getDate(),
        date.getHours(), date.getMinutes());
      printf("DtoI is %d\n", k);
      JDate::ItoD(k, y, m, d, h, min, yd, wd);
      printf("ItoD is %d %d %d %d %d %d %d\n", y, m, d, h, min, yd, wd);
      if ((y != date.getYear()) || (m != date.getMonth()) ||
        (d != date.getDate()) || (yd != date.getYDay()) || (wd != date.getWDay())) {
        printf("Error\n");
      }
      date = JDate(((int)date)+24*60*60);
    }
  }
*/
/*
  printf("Test DataBase\n");
  {
    JDataBase dbf("test.dbf");
    if (dbf.isValid()) {
      printf("NumOfField %d\n", dbf.getNumOfField());
      JDataField df1("First Name", "S", dbf.getNextId());
      JDataField df2("Last Name", "S", dbf.getNextId());
      JDataField df3("ID", "I", dbf.getNextId());
      if (!dbf.hasField(df1)) dbf.appendField(df1);
      if (!dbf.hasField(df2)) dbf.appendField(df2);
      if (!dbf.hasField(df3)) dbf.appendField(df3);
      for (i=0; i<dbf.getNumOfField(); i++) {
        JDataField *df = dbf.getField(i);
        printf("Field %d (%s %s %d %d)\n", i, 
          (char*)df->getName(), (char*)df->getType(), 
          df->getId(), df->current);
      }
      JDataField *df = dbf.getFieldById(2);
      printf("Field id %d (%s %s %d %d)\n", 2, 
        (char*)df->getName(), (char*)df->getType(), 
        df->getId(), df->current);
      if (dbf.size() < 2) {
        JArray data(3);
        data.set(0, JBlock(JString("Yuh-Jye")));
        data.set(1, JBlock(JString("Chang")));
        data.set(2, JBlock(JInteger::toJString(156888331, 128)));
        for (i=0; i<data.size(); i++) {
          printf("Field add %d = %s\n", i, (char*)*(JBlock*)data[i]);
        }
        dbf.append(data);
        data.set(0, JBlock(JString("Shu-Chun")));
        data.set(1, JBlock(JString("Tseng")));
        data.set(2, JBlock(JInteger::toJString(122626622, 128)));
        for (i=0; i<data.size(); i++) {
          printf("Field add %d = %s\n", i, (char*)*(JBlock*)data[i]);
        }
        dbf.append(data);
        data.set(0, JBlock(JString()));
        data.set(1, JBlock(JString()));
        data.set(2, JBlock(JInteger::toJString(122626622, 128)));
        for (i=0; i<data.size(); i++) {
          printf("Field add %d = %s\n", i, (char*)*(JBlock*)data[i]);
        }
        dbf.append(data);
      } else {
        JArray data = dbf.get(0);
        for (i=0; i<data.size(); i++) {
          printf("Field %d = %s\n", i, (char*)*(JBlock*)data[i]);
        }
        data = dbf.get(1);
        for (i=0; i<data.size(); i++) {
          printf("Field %d = %s\n", i, (char*)*(JBlock*)data[i]);
        }
        data = dbf.get(2);
        for (i=0; i<data.size(); i++) {
          printf("Field %d = %s\n", i, (char*)*(JBlock*)data[i]);
        }
      }
      dbf.close();
    }
  }
*/
/*
  printf("Test FileArray\n");
  {
    JFileArray fa("test.dbf");
    int r, index;
    int counter = 400;
    int tmax = 16;
    int tdel = tmax*4/5;
    int tadd = tmax*1/5;
    int cmax = 60;
    JRandom random;
    for (i=0; i<counter; i++) {
      r = random.nextInt(fa.size()+1);
      index = random.nextInt(fa.size()+1);
      if (r < tadd) {
        JBlock data(random.nextInt(cmax), 
          random.nextInt(26)+'A');
        printf("insert(%d): %s\n", index, 
          (char*)JString(data));
        fa.insert(data, index);
      } else if (r < tdel) {
	switch (random.nextInt(3)) {
	  case 0: 
	  {
	    JBlock data(random.nextInt(cmax), 
	      random.nextInt(26)+'A');
            printf("set(%d): %s\n", index, 
	      (char*)JString(data));
            fa.set(index, data);
	    break;
	  }
          case 1:
            printf("get(%d): %s\n", index, 
	      (char*)JString(fa.get(index)));
	    break;
          case 2:
	    printf("free(%d)\n", index);
	    fa.free(index);
	    break;
	}
      } else {
	if (r == tmax-1) {
          printf("delAll()\n");
	  fa.delAll();
	} else {
          printf("del(%d)\n", index);
	  fa.del(index);
	}
      }
    }
    printf("There are %d records\n", fa.size());
    for (i=0; i<fa.size(); i++)
      printf("fa(%d) : %s\n", i, (char*)JString(fa.get(i)));
    fa.close();
    JFileArray fb("test.dbf");
    printf("There are %d records\n", fb.size());
    fb.compact();
    for (i=0; i<fb.size(); i++)
      printf("fb(%d) : %s\n", i, (char*)JString(fb.get(i)));
  }
*/
/*
  printf("Sleep 500ms\n");
  JThread::sleep(500);
  printf("Waitup\n");
  printf("Sleep 500ms\n");
  JThread::sleep(500);
  printf("Waitup\n");
  */
/*
  printf("Test Object I/O\n");
  JObject obj;
  try {
    JFileOutputStream fos("oop.dat");
    obj.write(fos);
    JInteger(7).write(fos);
    JBoolean(true).write(fos);
    JCharacter('A').write(fos);
    JCriticalSection().write(fos);
    JDouble(-1.5).write(fos);
    JFloat(.5f).write(fos);
    JLong(-101).write(fos);
    JPObject(&obj).write(fos);
    JString("String Class").write(fos);
    JBlock(12, "Block Class").write(fos);
    JInetAddress().write(fos);
    JArray ar(4);
    ar.set(0, JString("S1"));
    ar.set(2, JString("S2"));
    ar.write(fos);
    JList list;
    list.add(JString("L1"));
    list.add(JString("L2"));
    list.write(fos);
    JAssociation(JString("Key"), JString("Value")).write(fos);
    JHashTable hash(101);
    hash.add(JString("H1"));
    hash.add(JString("H2"));
    hash.write(fos);
  } catch (JIOException *e) {
    printf("%s\n", (char*)e->getMessage());
    delete e;
  }

  try {
    JFileInputStream fis("oop.dat");
    JObject *o = obj.read(fis);
    printf("%x\n", o->prevAddress);
    o = obj.read(fis);
    printf("%d\n", (int)*(JInteger*)o);
    delete o;
    o = obj.read(fis);
    printf("%d\n", (boolean)*(JBoolean*)o);
    delete o;
    o = obj.read(fis);
    printf("%c\n", (char)*(JCharacter*)o);
    delete o;
    o = obj.read(fis);
    printf("%s\n", o->className());
    delete o;
    o = obj.read(fis);
    printf("%g\n", (double)*(JDouble*)o);
    delete o;
    o = obj.read(fis);
    printf("%g\n", (double)*(JFloat*)o);
    delete o;
    o = obj.read(fis);
    printf("%ld\n", (long)*(JLong*)o);
    delete o;
    o = obj.read(fis);
    printf("%x\n", (JObject*)*(JPObject*)o);
    delete o;
    o = obj.read(fis);
    printf("%s\n", (char*)*(JString*)o);
    delete o;
    o = obj.read(fis);
    printf("%s\n", (char*)*(JBlock*)o);
    delete o;
    o = obj.read(fis);
    printf("%s\n", (char*)((JInetAddress*)o)->className());
    delete o;
    o = obj.read(fis);
    printf("ar[0]=%s\n", (char*)*(JString*)(*(JArray*)o)[0]);
    printf("ar[2]=%s\n", (char*)*(JString*)(*(JArray*)o)[2]);
    delete o;
    o = obj.read(fis);
    printf("list.size()=%d\n", (*(JList*)o).size());
    delete o;
    o = obj.read(fis);
    printf("assoc.key()=%s\n", (*(JAssociation*)o).key()->className());
    delete o;
    o = obj.read(fis);
    printf("hash[H1]=%s\n", (char*)*(JString*)((*(JHashTable*)o)[JString("H1")]));
    delete o;
  } catch (JIOException *e) {
    printf("%s\n", (char*)e->getMessage());
    delete e;
  }

  printf("JString Class Test:\n");
  JString a;            // String()
  JString b("Test\n");        // String(char*)
  JString c("KKK\n");        // String(char*)
  JString d = c;            // String(String&)
  c.Dereference();              // Make Extra Copy
  printf((char*)b);        // operator const char*
  printf("%c\n", c[0]);        // operator []
  printf("%s", (char*)c(2));    // operator (begin)
  printf("%s\n", (char*)c(1, 3));// operator (begin, end)
  printf(a = b);        // operator = String&
  printf(a = "Assign");        // operator = const char*
  printf(a += "\n");         // operator += const char*
  printf("length()=%d\n", a.length()); // int length()
  printf("equalsIgnoreCase()=%d\n", a.equalsIgnoreCase("Assign\n"));
  printf("a == ?? %d\n", a > b);
  printf((char*)(a+c+"\n"));    // operator + const char*
  printf("a==c ? %d\n", a==c);    // operator == String& String&
  printf("c==d ? %d\n", c==d);    // operator == String& String&
  printf("Lowercase=%s", (char*)a.toLowerCase());
  printf("Uppercase=%s", (char*)a.toUpperCase());

  
  printf("JArray Test:\n");
  JArray sa(6), sb;

  sa.set(0, a);
  sa.set(1, b);
  sa.set(2, c);
  sa.set(3, d);
  for (i=0; i<4; i++)
    printf("sa[%d]=%s", i, (char*)*(JString*)sa[i]);

  sb = sa;
  printf("sb.size() = %d\n", sb.size());
  printf("sa == sb ? %d\n", sa == sb);

  sb.Dereference();

  printf("sa == sb ? %d\n", sa == sb);

  sb.set(4, a.toUpperCase());

  printf("sa == sb ? %d\n", sa == sb);
  
  for (i=0; i<5; i++) {
    printf("sb[%d]=%s", i, (char*)*(JString*)sb[i]);
  }

  sb = JArray(10);
  printf("sb.size() = %d\n", sb.size());

  printf("JList Test:\n");
  JList la(a), lb;
  la.add(b);
  la.add(c);
  JArray ar(la);
  lb = la;
  printf("ar.size() = %d\n", ar.size());
  printf("ar[0] = %s", (char*)*(JString*)ar[0]);
  printf("ar[1] = %s", (char*)*(JString*)ar[1]);
  printf("ar[1]->className() = %s\n", (char*)ar[1]->className());
  printf("la == lb ? %d\n", la == lb);
  lb.Dereference();
  printf("la == lb ? %d\n", la == lb);
  printf("la.size() = %d\n", la.size());
  la.forEach(Show);
  la.del(b);
  printf("la.size() = %d\n", la.size());
  la.forEach(Show);
  la.del(c);
  printf("la.size() = %d\n", la.size());
  la.forEach(Show);
  printf("lb.size() = %d\n", lb.size());
  lb.forEach(Show);
  printf("la == lb ? %d\n", la == lb);
  
  printf("JDList Test:\n");
  JDList lda(a), ldb;
  lda.add(b);
  lda.add(c);
  
  ldb = lda;
  printf("lda[0] = %s", (char*)*(JString*)lda[0]);
  printf("lda[1] = %s", (char*)*(JString*)lda[1]);
  printf("lda[1].className() = %s\n", (char*)lda[1]->className());
  printf("lda == ldb ? %d\n", lda == ldb);
  ldb.Dereference();			  
  printf("lda == ldb ? %d\n", lda == ldb);
  printf("lda.size() = %d\n", lda.size());
  lda.forEach(Show);
  lda.reparent(b, ldb);
  printf("lda.size() = %d\n", lda.size());
  printf("ldb.size() = %d\n", ldb.size());
  lda.forEach(Show);
  lda.del(c);
  printf("lda.size() = %d\n", lda.size());
  lda.forEach(Show);
  printf("ldb.size() = %d\n", ldb.size());
  ldb.forEach(Show);
  printf("lda == ldb ? %d\n", lda == ldb);
  ldb.lastThat(CanShow);
  printf("lda == ldb ? %d\n", lda == ldb);

  printf("JAssociation Test:\n");
  JAssociation assoc(a, b);
  printf("Key %s", (char*)*(JString*)assoc.key());
  printf("Value %s", (char*)*(JString*)assoc.value());

  printf("JDicitionary Test:\n");
  JDictionary dict(101);
  printf("Add %d\n", dict.add(a, b));
  printf("Add %d\n", dict.add(c, d));
  printf("dict.count() : %d\n", dict.count());
  printf("%s -> %s", (char*)a, (char*)*(JString*)dict[a]);
  printf("%s -> %s", (char*)c, (char*)*(JString*)dict[c]);

  dict.rehash(10);
  printf("%s -> %s", (char*)a, (char*)*(JString*)dict[a]);
  printf("%s -> %s", (char*)c, (char*)*(JString*)dict[c]);

  printf("JBlock Test:\n");
  JBlock bk1(10, 0), bk2;
  for (i=0; i<10; i++) bk1[i] = (char)(i+'0');
  bk2 = bk1;
  printf("bk1 == bk2 ? %d\n", bk1 == bk2);
  bk2.Dereference();
  bk2[0] = '1';
  printf("bk1 == bk2 ? %d\n", bk1 == bk2);
  bk2 = JBlock(20, 0);

  printf("JPipedStream Test:\n");
  JPipedStream ps;
  for (i=0; i<10; i++) ps << bk1[i];
  for (i=0; i<10; i++) ps >> bk2[i];
  for (i=0; i<10; i++) printf("%c", bk2[i]);
  printf("\n");

  printf("JFileInputStream Test:\n");
  try {
    JFileInputStream fis("oop.cpx");
    JFileOutputStream fos("oop.txt");
    JBlock buf(64, 0);
    for (;;) {
      try {
        fis >> buf;
        fos << buf;
        for (i=0; i<buf.size(); i++)
          printf("%c", buf[i]);
      } catch (JEOFException *e) {
        printf("%s\n", (char*)e->getMessage());
        delete e;
        break;
      }
    }
    printf("\n");
  } catch (JIOException *e) {
    printf("%s\n", (char*)e->getMessage());
    delete e;
  }
*/
/*
  printf("JInetAddress Test:\n");
  JInetAddress local("");
  printf("host = %s\n", (char*)local.getHostName());
  printf("host = %s\n", (char*)JInetAddress::getLocalHostName());
  printf("Address: %s\n", (char*)local.getAddressJString());

  local = JInetAddress(local.getAddress());
  printf("host = %s\n", (char*)local.getHostName());
  printf("Address: %s\n", (char*)local.getAddressJString());
  */
  /*
  JInetAddress top("nova");
  printf("host = %s\n", (char*)top.getHostName());
  printf("Address: %s\n", (char*)top.getAddressJString());
  JInetAddress nova("nova");
  printf("host = %s\n", (char*)nova.getHostName());
  printf("Address: %s\n", (char*)nova.getAddressJString());
  uchar test[] = { 128, 230, 31, 4};
  nova = JInetAddress::getByAddr(JBlock(4, (char*)test));
  printf("host = %s\n", (char*)nova.getHostName());
  printf("Address: %s\n", (char*)nova.getAddressJString());
  */
/*
  {
    ListenJThread test;
    test.start();
    printf("JSocket Test\n");
    for (;;) {
      JThread::sleep(500);
      printf("Try connect\n");
      try {
        JSocket sock(JInetAddress::localHost, 3490);
        if (sock.connect()) {
          JSocketInputStream sis(sock);
          JSocketOutputStream sos(sock);
          JBlock data(100, 0);
          printf("Client Start:\n");
          sis >> data;
          printf("Client Receive: %s\n", (char*)JString(data));
          sos << data;
          printf("Client Send: %s\n", (char*)JString(data));
          test.waitFor();
          sock.close();
          break;
        }
        sock.close();
      } catch (JIOException *e) {
        printf("Socket %s\n", (char*)e->getMessage());
        delete e;
      }
    }
  }
*/
/*
  {
    printf("Delay Test 500ms\n");
    JThread::sleep(500);
  }
*/
/*
  {
    printf("JThread Test\n");
    MyJThread test1;
    MyJThread3 test2;
    JThread r1(&test1);
    r1.start();
    test2.start();
    for (i=0;i<5;i++) {
      JThread::sleep(1000);
      if (i == 3) {
        test1.valid = 0;
        test2.valid = 0;
        r1.waitFor();
        test2.waitFor();
      }
      printf("M%3d,%lu\n", i,
	JSystem::currentTimeMillis());
    }
    MyJThread2 test3;
    test3.start();
    printf("waitFor\n");
    test3.waitFor();
    printf("resume\n");
  }
*/
  /*
  {
    printf("JMath Test\n");
    printf("sin(0.5) = %lf\n", JMath::sin(0.5));
    printf("cos(0.5) = %lf\n", JMath::cos(0.5));
    printf("tan(0.5) = %lf\n", JMath::tan(0.5));
    for (i=0; i<10; i++)
      printf("next() = %lf\n", JMath::random());
  }

  {
    printf("JRandom Test\n");
    JRandom rand;
    for (i=0; i<10; i++)
      printf("next() = %d\n", rand.nextInt(10));
  }
  
  
  {
    printf("JCharacter Test\n");
    printf("isLowerCase('A')=%d\n", JCharacter::isLowerCase('A'));
    printf("isUpperCase('A')=%d\n", JCharacter::isUpperCase('A'));
    printf("toLowerCase('A')=%c\n", JCharacter::toLowerCase('A'));
    printf("toUpperCase('A')=%c\n", JCharacter::toUpperCase('A'));
  }
  {
    printf("JInteger Test\n");
    printf("MAX_VALUE=%d\n", JInteger::MAX_VALUE);
    printf("MIN_VALUE=%d\n", JInteger::MIN_VALUE);
    printf("toJString(1234)=%s\n", (char*)JInteger::toJString(1234));
    printf("toJString(1234, 16)=%s\n", (char*)JInteger::toJString(1234, 16));
    printf("parse(\"1234\")=%d\n", JInteger::parse("1234"));
    printf("parse(\"1234\", 16)=%d\n", JInteger::parse("1234", 16));
  }
  {
    printf("JLong Test\n");
    printf("MAX_VALUE=%ld\n", JLong::MAX_VALUE);
    printf("MIN_VALUE=%ld\n", JLong::MIN_VALUE);
    printf("toJString(1234)=%s\n", (char*)JLong::toJString(1234));
    printf("toJString(1234, 16)=%s\n", (char*)JLong::toJString(1234, 16));
    printf("parse(\"1234\")=%d\n", JLong::parse("1234"));
    printf("parse(\"1234\", 16)=%d\n", JLong::parse("1234", 16));
  }
  {
    printf("JBoolean Test\n");
    printf("MAX_VALUE=%d\n", JBoolean::MAX_VALUE);
    printf("MIN_VALUE=%d\n", JBoolean::MIN_VALUE);
    printf("toJString(1)=%s\n", (char*)JBoolean::toJString(1));
    printf("toJString(0)=%s\n", (char*)JBoolean::toJString(0));
    printf("parse(\"true\")=%d\n", JBoolean::parse("true"));
    printf("parse(\"false\")=%d\n", JBoolean::parse("false"));
  }
  
  
  {
    printf("JFloat Test\n");
    printf("MAX_VALUE=%g\n", JFloat::MAX_VALUE);
    printf("MIN_VALUE=%g\n", JFloat::MIN_VALUE);
    printf("EPSILON=%g\n", JFloat::EPSILON);
    printf("toJString(1.1234F)=%s\n", (char*)JFloat::toJString(1.1234F));
    printf("toJString(-0.11F)=%s\n", (char*)JFloat::toJString(-0.11F));
    printf("parse(\"1.1234\")=%g\n", JFloat::parse("1.1234"));
    printf("parse(\"-0.11\")=%g\n", JFloat::parse("-0.11"));
  }
  
  {
    printf("JDouble Test\n");
    printf("MAX_VALUE=%g\n", JDouble::MAX_VALUE);
    printf("MIN_VALUE=%g\n", JDouble::MIN_VALUE);
    printf("EPSILON=%g\n", JDouble::EPSILON);
    printf("toJString(1.1234)=%s\n", (char*)JDouble::toJString(1.1234));
    printf("toJString(-0.11)=%s\n", (char*)JDouble::toJString(-0.11));
    printf("parse(\"1.1234\")=%g\n", JDouble::parse("1.1234"));
    printf("parse(\"-0.11\")=%g\n", JDouble::parse("-0.11"));
  }

  {
    printf("JProcess Test\n");
    char* argv[] = { "notepad", "Oop.cpp", null};
    JProcess proc(argv);
    printf("Free Memroy = %ld\n", JProcess::freeMemory());
    printf("Total Memroy = %ld\n", JProcess::totalMemory());
    proc.start();
    proc.waitFor();
  }
  */
  {
    printf("JFile Test\n");
    JFile f1("test.dat");
    JFile f2(".", "test.dat");
    JFile f3("..", "test.dat");
    JFile f4("oopw.cfg");
    JFile f5(".", "oopw.cfg");
    JFile f6("..", "oopw.cfg");
    JFile f7(".", "");
    printf("work = %s isdir = %d\n", (char*)JFile::workDir.getPath(), JFile::workDir.isDirectory());
    printf("f1 = %s isdir = %d\n", (char*)f1.getPath(), f1.isDirectory());
    printf("f2 = %s isdir = %d\n", (char*)f2.getPath(), f2.isDirectory());
    printf("f3 = %s isdir = %d\n", (char*)f3.getPath(), f3.isDirectory());
    printf("f4 = %s isdir = %d\n", (char*)f4.getPath(), f4.isDirectory());
    printf("f5 = %s isFile = %d\n", (char*)f5.getPath(), f5.isFile());
    printf("f6 = %s isdir = %d\n", (char*)f6.getPath(), f6.isDirectory());
    printf("f7 = %s isdir = %d\n", (char*)f7.getPath(), f7.isDirectory());
    printf("f7.getParent = %s\n", (char*)f7.getParent());
    JArray fs = f7.list(JFile::LA_DRIVE);
    printf("Drive:\n");
    for (i=0; i<fs.size(); i++) {
      printf("%s\n", (char*)*(JString*)fs[i]);
    }
    fs = f7.list(JFile::LA_DIRECTORY);
    printf("Directory:\n");
    for (i=0; i<fs.size(); i++) {
      printf("%s\n", (char*)*(JString*)fs[i]);
    }
    fs = f7.list(JFile::LA_FILE, "*.exe");
    printf("File:*.exe\n");
    for (i=0; i<fs.size(); i++) {
      printf("%s\n", (char*)*(JString*)fs[i]);
    }
  }
}

/*
#define MAX_CHAR 9
void writeIndex(JFileOutputStream &fos, uchar* from, uchar *to) {
  int count = 0;
  JBlock buf(2, 0);
  for (uchar i=from[0]; i<=to[0]; i++) {
    printf("%3d ", i);
    buf[0] = i;
    for (uchar j=from[1]; j<=to[1]; j++) {
      buf[1] = j;
      fos << buf;
      if ((++count)%MAX_CHAR == 0) {
        buf[0] = 0x0D;
        buf[1] = 0x0A;
        fos << buf;
	buf[0] = i;
      }
    }
  }
}

void makeIndex() {
  try {
    uchar f1[] = { 0x81, 0x40};
    uchar f2[] = { 0xE0, 0x40};
    uchar t1[] = { 0x9F, 0xFC};
    uchar t2[] = { 0xFC, 0xFC};
    JFileOutputStream fos("jap.txt");
    writeIndex(fos, f1, t1);
    writeIndex(fos, f2, t2);
  } catch (JIOException *e) {
    printf("%s\n", (char*)e->getMessage());
    delete e;
  }
}
*/

class JApplication : public JObject {
  public:
    JApplication();
    virtual const char* className() const { return "JApplication";}
    virtual JObject* clone() const { return new JApplication;}
};

/*
void FindPrime(int from) {
  while (from <= 0x7FFFFFFF) {
	int check = ((int)DMath::sqrt(from))+1;
    for (i=2; i<check; i++) {
	  if (!(from%i)) break;
    }
	if (i==check) break;
	from++;
  }
  printf("Find Prime %X\n", from);
}
*/

class OBJ {
public:
  OBJ() { printf("%x:OBJ()\n", this);}
  OBJ(const OBJ& obj) { printf("%x:OBJ(OBJ)\n", this);}
  virtual ~OBJ() { printf("~OBJ\n");}
};

class A1 {
public:
  int x;
  A1() { x = 1; printf("%x:A1()\n", this);}
  A1(const A1& s) { x = 2; printf("%x:A1(A1)\n", this);}
  virtual A1& operator<<(int x) { printf("A1<<int\n"); return *this;}
  A1& operator<<(double x) { *this << (int)x; return *this;}
};

class A2 : public OBJ {
public:
  int y;
  A2() { y = 2; printf("%x:A2()\n", this);}
//  A2(const A2& s) { y = 3; printf("%x:A2(A2)\n", this);}
  virtual ~A2() { printf("~A2\n");}
  A2& operator=(const A2& s) {
    printf("before:%d, ", y);
    y = s.y;
    printf("after:%d\n", y);
    printf("%x:A2=\n", this);
    return *this;
  }
};

class B : public A1, public A2 {
public:
  B() { printf("%x:B()\n", this);}
  B(int k) { y = k; printf("%x:B(int)\n", this);}
//  B(const B& s):A1(s), A2(s) { printf("%x:B(B)\n", this);}
  A1& operator<<(int x) { printf("B<<int\n"); return *this;}
};


JObject ret() {
  return JString("TEST");
}

JApplication::JApplication() {
//  A2 a;
  /*
  B b, c;
  B d = b;
  B b, c;
  B d = b;
  B e(7);
  e = B(10);
  printf("e.y:%d\n", e.y);*/
/*
  B b;
  OBJ *o = &b;
  b << 12;
  b << 12.5;
  (*(B*)o) << 13;
  (*(A1*)&b) << 14.5;
  (*(B*)o) << 15.5;
*/
//  FindPrime(0x7F123456);
//  makeIndex();

  Test();


//  makeHTML();
//  countLines();
}

DllImport extern JDictionary *pClassDict;
DllImport extern JArray *pClassArray;

char* sdata = "1938238172";

JString scramble(JString src) {
  int len = src.length();
  if (len == 0) return src;
  int i, N = ((len+1)/10+1)*10;
  char *buf = new char[N+1];
  unsigned char ch = 0;
  for (i=0; i<N; i++) {
    if (i <= len) 
      buf[i] = (ch = (((src[i]^sdata[i%10])+ch)&127))+128;
    else buf[i] = (ch = (((0^sdata[i%10])+ch)&127))+128;
  }
  buf[0] = ((buf[0]-128+ch)&127)+128;
  buf[i] = 0;
  return JString(buf, JString::needCopy);
}

JString unscramble(JString src) {
  int N = src.length();
  if (N == 0) return src;
  char *buf = new char[N+1];
  int i = N-1;
  unsigned char ch = (src[i]-128);
  src[0] = ((src[0]-128-ch)&127)+128;
  buf[i] = 0;
  ch = 0;
  for (i=0; i<N; i++) {
     buf[i] = ((src[i]-128-ch)^sdata[i%10])&127;
     ch = src[i]-128;
  }
  return JString(buf, JString::needCopy);
}

static JRandom random;
JString randomText() {
  int i, N = random.nextInt(33);
  char *buf = new char[N+1];
  for (i=0; i<N; i++)
    buf[i] = random.nextInt(94)+33;
  buf[i] = 0;
  return JString(buf, JString::needCopy);
}

void scrambleTest() {
  JString text, dest;
  int errorCount = 0;
  for (int i=0; i<500; i++) {
    text = randomText();
    printf("text(%d) = %s ", text.length(), (char*)text);
    dest = scramble(text);
    printf("scramble = %s ", (char*)dest);
    if (text != unscramble(dest)) {
      printf("Error!!!\n");
      errorCount++;
    } else printf("pass\n");
  }
  printf("ErrorCount = %d\n", errorCount);
}

void main() {
  scrambleTest();
  //JApplication app;
//  if (pClassDict) delete pClassDict;
//  if (pClassArray) delete pClassArray;
}

//#define DEBUG

#ifdef DEBUG

#include <stdio.h>
#include <stdlib.h>
#include "JSystem.h"
#include "JNullPointerException.h"
#define MAXDEBUG 4096
static int allocCount = 0;
static int debugCount = 0;
static int debugMax = 0;
static void* debug[MAXDEBUG];

void* operator new(size_t size) {
  void* ptr = malloc(size);
  if (!ptr) {
    static int nCounter = 0;
    if (!nCounter++)
      throw new JNullPointerException("Free Store Exhaust.");
  }
  allocCount++;
  if (debugCount++ == 0) {
    for (int i=0; i<MAXDEBUG; i++) 
    debug[i] = null;
  }
  if (debugCount > debugMax) debugMax = debugCount;
  int id = ((int)ptr)%MAXDEBUG;
  int base = id;
  while (debug[id]) {
    id=(id+1)%MAXDEBUG;
    if (id == base) {
      printf("Table Full for ptr %d.\n", ptr);
      return ptr;
    }
  }
  debug[id] = ptr;
  return ptr;
}

void operator delete(void* ptr) { 
  free(ptr);
  if (!ptr) {
    printf("delete null.\n");
    return;
  }
  int id = ((int)ptr)%MAXDEBUG;
  int base = id;
  while (debug[id]!=ptr) {
    id=(id+1)%MAXDEBUG;
    if (id == base) {
      printf("ptr %d not found.\n", ptr);
      return;
    }
  }
  debug[id] = 0;
  if (--debugCount == 0) {
#if defined(WIN32)
    JSystem::messageBeep();
#endif
    printf("Just Make. Max JObject=%d, Totle alloc=%d\n",
      debugMax, allocCount);
#if defined(BC5)
    scanf("%c", &debugCount);
#endif
  }
  /*printf("%d\n", debugCount);*/
}
#endif

