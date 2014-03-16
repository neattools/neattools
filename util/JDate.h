#if !defined( _JDate_h )
#define _JDate_h

#include "JObject.h"
#include "JDate.hpp"

class
#include "JBase.hpp"
JDate : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static double constant;
    static char* weekTag[];
    static char* monthTag[];
    static JString toJString(double value);
    static JDate parse(JString str);
    static double DtoR(int year, int month, int date, int hour, int min, int sec, int msec);
    static void RtoD(double value, int& year, int& month, int& date, 
      int& hour, int& min, int& sec, int& msec, int& yday, int& wday);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JDate();
    JDate(int year, int month, int date, 
      int hour = 0, int min = 0, int sec = 0, int msec = 0);
    JDate(double rval, int msec = 0);
    JDate(JString str);
    operator double&();
    JString toJString();
    int getYear();
    void setYear(int year);
    int getMonth(); /* 0-11 */
    void setMonth(int month);
    int getDate(); /* 1-31 */
    void setDate(int date); 
    int getYDay(); /* 0-365 */
    int getWDay(); /* 0-6 */
    int getHours();
    void setHours(int hours);
    int getMinutes();
    void setMinutes(int minutes);
    int getSeconds();
    void setSeconds(int seconds);
    int getMillis();
    void setMillis(int millis);
    double getTime();
    void setTime(double time);
    int getITime();
    void setITime(int time);
    int getTimezone();
    int getTimeDelta();
    int isDST();
    JDate UTC();
  private:
    double value;
    int tm_msec;    /* mili-seconds */
    int tm_sec;     /* seconds after the minute - [0,59] */
    int tm_min;     /* minutes after the hour - [0,59] */
    int tm_hour;    /* hours since midnight - [0,23] */
    int tm_mday;    /* day of the month - [1,31] */
    int tm_mon;     /* months since January - [0,11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday - [0,6] */
    int tm_yday;    /* days since January 1 - [0,365] */
    int tm_isdst;   /* daylight savings time flag */
    int tm_tDelta;
    boolean valueValid, expanded;
    void expand();
    void compute();
    int compareTime(SYSTEMTIME t);
};

#endif
