#if !defined( _JTNG3XObj_h )
#define _JTNG3XObj_h

#include "JTNGObj.h"

class JTNG3XObj : public JTNGObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JTNG3XObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void processByte(int v);
  protected:
    int sepCount;
	int byteCount;
	int oddbyte;
	int a;
	int iByte;
	int StoreIt;
	int ClockIt;
	int ClockOff;
	int d;
    uchar separators[2];
};

#endif
