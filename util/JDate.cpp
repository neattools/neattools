#include "JDate.h"
#include "JMath.h"
#include "JSystem.h"
#include "JString.h"
#include <stdio.h>

char* theJDate = JDate().Register();
void JDate::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putDouble(os, "rvalue", value);
}

void JDate::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value = getDouble(dict, "rvalue");
}

char* JDate::weekTag[] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", 
  "Thursday", "Friday", "Saturday", null
};

char* JDate::monthTag[] = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", 
  "December", null
};

double JDate::constant = 62167305600.0;

JString JDate::toJString(double value) {
  JDate date(value);
  char buf[25];
  sprintf(buf, "%2d/%02d/%04d %02d:%02d:%02d.%03d",
    date.getMonth()+1,
    date.getDate(), date.getYear(),
    date.getHours(), date.getMinutes(), 
    date.getSeconds(), date.getMillis());
  return JString(buf, JString::needCopy);
}

JDate JDate::parse(JString str) {
  int month, date, year;
  int hours = 12, minutes = 0, seconds = 0, mseconds = 0;
  int nf;
  nf = sscanf((char*)str, "%d/%d/%d %d:%d:%d.%d",
    &month, &date, &year, &hours, &minutes, &seconds, &mseconds);
  if (nf >= 2) {
    if (nf == 2) {
      JDate today;
      year = today.getYear();
    }
    --month;
  } else {
    JDate today;
    year = today.getYear();
    month = today.getMonth();
    date = today.getDate();
    nf = sscanf((char*)str, "%d:%d:%d.%d",
      &hours, &minutes, &seconds, &mseconds);
    if (nf < 2) {
      hours = today.getHours();
      minutes = today.getMinutes();
      seconds = today.getSeconds();
      mseconds = today.getMillis();
    }
  }
  return JDate(year, month, date, hours, minutes, seconds, mseconds);
}

const char* JDate::className() const { return "JDate";}
int JDate::hashCode() const { return (int)(value*1000) & hashMask;}
JObject* JDate::clone() const { return new JDate(*this);}
int JDate::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return cmp(((JDate*)this)->getTime(), ((JDate*)&s)->getTime());
}

JDate::JDate() {
#if defined(WIN32_TIME)
  SYSTEMTIME st;
  GetSystemTime(&st);
  value = DtoR(st.wYear, st.wMonth-1, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
  struct _timeb_ tstruct;
  _ftime_(&tstruct);
  value = constant+tstruct.time+0.001*tstruct.millitm;
#endif
  valueValid = true;
  expanded = false;
}

JDate::JDate(double _value, int msec) {
  value = _value;
  tm_msec = msec;
  valueValid = true;
  expanded = false;
}

JDate::JDate(int year, int month, int date, 
  int hour, int min, int sec, int msec) {
  tm_year = year;
  tm_mon = month;
  tm_mday = date;
  tm_hour = hour;
  tm_min = min;
  tm_sec = sec;
  tm_msec = msec;
  compute();
}

JDate::JDate(JString str) 
{ *this = parse(str);}

JDate::operator double&() {
  if (!valueValid) compute();
  else expanded = false;
  return value;
}

JString JDate::toJString() {
  if (!valueValid) compute();
  return toJString(value);
}

int JDate::getYear() {
  if (!expanded) expand();
  return tm_year;
}

void JDate::setYear(int year) {
  if (!expanded) expand();
  tm_year = year;
  valueValid = false;
}

int JDate::getMonth() {
  if (!expanded) expand();
  return tm_mon;
}

void JDate::setMonth(int month) {
  if (!expanded) expand();
  tm_mon = month;
  valueValid = false;
}

int JDate::getDate() {
  if (!expanded) expand();
  return tm_mday;
}

void JDate::setDate(int date) {
  if (!expanded) expand();
  tm_mday = date;
  valueValid = false;
}

int JDate::getYDay() {
  if (!expanded) expand();
  return tm_yday;
}

int JDate::getWDay() {
  if (!expanded) expand();
  return tm_wday;
}

int JDate::getHours() {
  if (!expanded) expand();
  return tm_hour;
}

void JDate::setHours(int hours) {
  if (!expanded) expand();
  tm_hour = hours;
  valueValid = false;
}

int JDate::getMinutes() {
  if (!expanded) expand();
  return tm_min;
}

void JDate::setMinutes(int minutes) {
  if (!expanded) expand();
  tm_min = minutes;
  valueValid = false;
}

int JDate::getSeconds() { 
  if (!expanded) expand();
  return tm_sec;
}

void JDate::setSeconds(int seconds) { 
  if (!expanded) expand();
  tm_sec = seconds;
  valueValid = false;
}

void JDate::setMillis(int mseconds) { 
  if (!expanded) expand();
  tm_msec = mseconds;
  valueValid = false;
}

int JDate::getMillis() { 
  if (!expanded) expand();
  return tm_msec;
}

double JDate::getTime() {
  if (!valueValid) compute();
  return value;
}

void JDate::setTime(double time) {
  value = time;
  valueValid = true;
  expanded = false;
}

int JDate::getITime() {
  if (!valueValid) compute();
  return (int)JMath::floor(value-constant);
}

void JDate::setITime(int time) {
  value = constant+time;
  valueValid = true;
  expanded = false;
}

int JDate::getTimezone() {
#if defined(WIN32_TIME)
  TIME_ZONE_INFORMATION tzi;
  GetTimeZoneInformation(&tzi);
  return -tzi.Bias;
#else
  struct _timeb_ tstruct;
  _ftime_(&tstruct);
  return -tstruct.timezone;
#endif
}

int JDate::getTimeDelta() {
  if (!expanded) expand();
  return tm_tDelta;
}

int JDate::isDST() {
  if (!expanded) expand();
  return tm_isdst;
}

JDate JDate::UTC() {
  if (!valueValid) compute();
  return JDate(value-getTimeDelta()*60, tm_msec);
}

int monthOffset[] = {
  0,	// 31	January
  31,	// 28	February
  59,	// 31	March
  90,	// 30	April
  120,	// 31	May
  151,	// 30	June
  181,	// 31	July
  212,	// 31	August
  243,	// 30	September
  273,	// 31	October
  304,	// 30	November
  334,	// 31	December
  365
};

boolean isLeapYear(int year) 
{ return !(year&3)&&((year%100)||!(year%400));}

int getOffsetLeap(int year, int month) 
{ return (!isLeapYear(year)||(month<2))?0:1;}

int getOffsetDate(int year) {
  return (year*365)+ // days per year
    (year+3)/4-      // plus leap days
    (year-1)/100+    // no leap on century years
    (year+399)/400;  // except %400 years
}

double JDate::DtoR(int year, int month, int date, 
  int hour, int min, int sec, int msec) {
  date+=monthOffset[month]+
    getOffsetLeap(year, month)+
    getOffsetDate(year);
  return 60.0*((((date-1)*24)+hour)*60+min)+sec+0.001*msec;
}

void JDate::RtoD(double value, int& year, int& month, int& date, 
  int& hour, int& min, int& sec, int& msec, int& yday, int& wday) {
  boolean isLeap;
  int oYear, ivalue;
  double remain = value;
  msec = JMath::round(JMath::mod(remain, 1.0)*1000);
  remain = JMath::floor(remain)/60;
  sec = JMath::round(JMath::mod(remain, 1.0)*60);
  ivalue = JMath::round(JMath::floor(remain));
  min = ivalue%60;
  ivalue /= 60;
  hour = ivalue%24;
  ivalue /= 24;
  wday = (ivalue+5)%7;
  year = ivalue/365;
  do {
    oYear = year;
    isLeap = isLeapYear(year);
    date = ivalue-getOffsetDate(year);
    if (date < 0) year--;
    if (date >= 365+isLeap) year++;
  } while (year != oYear);
  yday = date;
  for (month=12; --month>0;) {
    int ofs = isLeap && (month>1);
    if (date >= monthOffset[month]+ofs) {
      date -= monthOffset[month]+ofs;
      break;
    }
  }
  date++;
}

int JDate::compareTime(SYSTEMTIME t) {
  if (tm_mon > t.wMonth-1) return 1;
  if (tm_mon < t.wMonth-1) return -1;
  if (t.wYear != 0) {
    if (tm_mday > t.wDay) return 1;
    if (tm_mday < t.wDay) return -1;
  } else {
    int nearestDay = (tm_mday-tm_wday+t.wDayOfWeek);
    if (nearestDay < 1) return -1;
    int firstWeekDay = ((nearestDay-1)%7)+1;
    int dayOfMonth = firstWeekDay+(t.wDay-1)*7;
    int maxDayOfMonth = monthOffset[tm_mon+1]-monthOffset[tm_mon];
    if (dayOfMonth >= maxDayOfMonth) dayOfMonth-=7;
    if (tm_mday > dayOfMonth) return 1;
    if (tm_mday < dayOfMonth) return -1;
  }
  return 0;
}

void JDate::expand() {
  int timeZone = getTimezone();
  RtoD(value+timeZone*60, tm_year, tm_mon, tm_mday, 
    tm_hour, tm_min, tm_sec, tm_msec, tm_yday, tm_wday);
  SYSTEMTIME daylightDate = { 0, 4, 0, 1, 0, 0, 0, 0};
  SYSTEMTIME standardDate = { 0, 10, 0, 5, 0, 0, 0, 0};
  int daylightBias = -60;
  int standardBias = 0;
#if defined(WIN32_TIME)
  TIME_ZONE_INFORMATION tzi;
  if (GetTimeZoneInformation(&tzi) == TIME_ZONE_ID_STANDARD) {
    daylightDate = tzi.DaylightDate;
    standardDate = tzi.StandardDate;
    daylightBias = tzi.DaylightBias;
    standardBias = tzi.StandardBias;
  }
#endif
  if ((compareTime(daylightDate) >= 0) && (compareTime(standardDate) < 0)) {
    tm_tDelta = getTimezone()-daylightBias;
    tm_isdst = 1;
  } else {
    tm_tDelta = getTimezone()-standardBias;
    tm_isdst = 0;
  }
  if (tm_isdst) {
    RtoD(value+tm_tDelta*60, tm_year, tm_mon, tm_mday, 
      tm_hour, tm_min, tm_sec, tm_msec, tm_yday, tm_wday);
  }
  expanded = true;
}

void JDate::compute() {
  int timeZone = getTimezone();
  value = DtoR(tm_year, tm_mon, tm_mday, tm_hour, 
    tm_min, tm_sec, tm_msec)-timeZone*60;
  expand();
  if (tm_isdst) value+=(timeZone-tm_tDelta)*60;
  valueValid = true;
}

