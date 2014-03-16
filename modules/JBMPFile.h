#if !defined( _JBMPFile_h )
#define _JBMPFile_h

#include "JBlock.h"

#define INFOHEADERSIZE 40

class JBITMAPINFOHEADER {
  public:
    uint   biSize;
    int    biWidth; 
    int    biHeight; 
    ushort biPlanes; 
    ushort biBitCount;
    uint   biCompression; 
    uint   biSizeImage; 
    int    biXPelsPerMeter; 
    int    biYPelsPerMeter; 
    uint   biClrUsed; 
    uint   biClrImportant; 
}; 
 
class JBMPFile : public JObject {
  protected:
  public:
    enum { OPEN_ERR, SUCCESS, MEM_ERR, READ_ERR, TYPE_ERR, COMP_ERR};
    JBITMAPINFOHEADER bmpInfo;
    JBlock data;
    int width, height;
    virtual const char* className() const;
    virtual JObject* clone() const;
    int load(char* fileName);
};

#endif
