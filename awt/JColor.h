#if !defined( _JColor_h )
#define _JColor_h

#include "JDescriptor.h"

class
#include "JAWT.hpp"
#if defined(WIN32)
JColor : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
#else
JColor : public JDescriptor {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
    virtual void Delete();
    virtual int Duplicate();
#endif
  public:
    static JColor white;
    static JColor lightGray;
    static JColor gray;
    static JColor darkGray;
    static JColor black;
    static JColor red;
    static JColor pink;
    static JColor orange;
    static JColor yellow;
    static JColor green;
    static JColor magenta;
    static JColor cyan;
    static JColor blue;  
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JColor();
    JColor(int rgb, int alpha = 0);
    JColor(int r, int g, int b, int alpha = 0);
    JColor(float r, float g, float b, float alpha = 0.0);
    operator int();
    int getAlpha();
    int getRed();
    int getGreen();
    int getBlue();
    int getRGB();
#if !defined(WIN32)
    ~JColor();
    void setPixel(int pixel);
    int& getPixel();
#endif;
    JColor brighter();
    JColor darker();
    static int HSBtoRGB(float hue, float saturation, float brightness);
    static float* RGBtoHSB(int r, int g, int b, float* hsbvals);
    static JColor getHSBJColor(float h, float s, float b);
  private:
    int value;
    static double FACTOR;
};

#endif
