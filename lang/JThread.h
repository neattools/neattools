#if !defined( _JThread_h )
#define _JThread_h

#include "JReference.h"

class
#include "JBase.hpp"
JThread : public JReference {
  protected:
    virtual void Delete();
    virtual int Duplicate();
  public:
    static int TMIN_PRIORITY;
    static int TMAX_PRIORITY;
    static int TNORM_PRIORITY;
    virtual const char* className() const;
    virtual JObject* clone() const;
#if defined(WIN32)
    virtual int compareTo(const JObject& s) const;
#endif
    JThread();
    JThread(JObject* target);
    operator int();
    virtual ~JThread();
    virtual void start();
    virtual void run();
    boolean isAlive();
    void stop();
    void suspend();
    void resume();
    void setPriority(int newPriority);
    int getPriority();
    long waitFor();
    static JThread currentJThread();
    static void yield();
    static void sleep(ulong ms);
  protected:
    int priority;
    JObject *ptarget;
    int toPlatform(int Priority);
    int fromPlatform(int Priority);
#if defined(WIN32)
    ulong id;
    JThread(int handle, ulong id);
#else
  public:
    JThread(int handle);
#endif
};

#endif

