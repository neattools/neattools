#if !defined( _JProcess_h )
#define _JProcess_h

#include "JReference.h"
#include "JThread.h"
#include "JString.h"

class
#include "JBase.hpp"
JProcess : public JReference {
  protected:
    virtual void Delete();
    virtual int Duplicate();
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    JProcess();
    JProcess(int hProcess);
    JProcess(const JString& cmdLine);
    JProcess(char** argv);
    virtual ~JProcess();
    virtual void start();
    boolean isAlive();
    void stop();
    void suspend();
    void resume();
    void setPriority(int newPriority);
    int getPriority();
    long waitFor();
    long exitValue();
    static JProcess currentJProcess();
    static void exit(int status = null);
    static long freeMemory();
    static long totalMemory();
  private:
    JThread mainJThread;
    JString cmdLine;
};

#endif

