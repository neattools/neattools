#include "JBMPFile.h"
#include "JBlock.h"
#include "JMath.h"
#include "JString.h"
#include "JFileInputStream.h"
#include "JIOException.h"
#include "JEOFException.h"

#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L

#define FILEHEADERSIZE 14
#define COREINFOSIZE 12
#define RGBQUADSIZE 4

class JBITMAPFILEHEADER {
  public:
    ushort bfType; 
    uint   bfSize; 
    uint   bfReserved; 
    uint   bfOffBits; 
};

class JBITMAPCOREINFO {
  public:
    uint   bcSize;
    ushort bcWidth;
    ushort bcHeight;
    ushort bcPlanes; 
    ushort bcBitCount;
}; 
 
class JRGBQUAD {
  public:
    uchar rgbBlue; 
    uchar rgbGreen; 
    uchar rgbRed; 
    uchar rgbReserved; 
}; 
 
const char* JBMPFile::className() const { return "JBMPFile";}
JObject* JBMPFile::clone() const { return new JBMPFile(*this);}

int JBMPFile::load(char* fileName) {
  JFileInputStream fis;
  try {
    JBITMAPFILEHEADER fileHeader;
    JBITMAPINFOHEADER infoHeader;
    JBITMAPCOREINFO coreInfo;
    JBlock pdata;
    JRGBQUAD *palette = null;
    uchar    *image = null;
    int paletteCount, bitCount;
    int scanWidth, imageSize;
    fis.open(fileName);
    fis >> JBlock(FILEHEADERSIZE, (char*)&fileHeader);
    if (fileHeader.bfType != *(ushort*)"BM") return TYPE_ERR;
    fis >> JBlock(infoHeader.biSize);
    if (infoHeader.biSize == INFOHEADERSIZE) {
      fis >> JBlock(INFOHEADERSIZE-4, (char*)&infoHeader.biWidth);
    } else if (infoHeader.biSize == COREINFOSIZE) {
      fis >> JBlock(COREINFOSIZE-4, (char*)&coreInfo.bcWidth);
      infoHeader.biSize = INFOHEADERSIZE;
      infoHeader.biWidth = (int)coreInfo.bcWidth;
      infoHeader.biHeight = (int)coreInfo.bcHeight;
      infoHeader.biPlanes = coreInfo.bcPlanes;
      infoHeader.biBitCount = coreInfo.bcBitCount;
      infoHeader.biCompression = BI_RGB;
      infoHeader.biSizeImage = null;
      infoHeader.biXPelsPerMeter = null;
      infoHeader.biYPelsPerMeter = null;
      infoHeader.biClrUsed = null;
      infoHeader.biClrImportant = null;
    } else return TYPE_ERR;
    bitCount = infoHeader.biBitCount;
    if (bitCount <= 16) {
      paletteCount = JMath::ipow(2, infoHeader.biBitCount);
      if (infoHeader.biClrUsed > 0) 
        paletteCount = infoHeader.biClrUsed;
      pdata = JBlock(paletteCount*RGBQUADSIZE, 0);
      palette = (JRGBQUAD*)(char*)pdata;
      if (palette == null) return MEM_ERR;
      fis >> pdata;
    } else paletteCount = 0;
    if (infoHeader.biCompression != BI_RGB) 
      return COMP_ERR+infoHeader.biCompression;
    width = infoHeader.biWidth;
    height = JMath::iabs(infoHeader.biHeight);
    scanWidth = ((width*bitCount/8)+3)&(~3);
    imageSize = scanWidth*height;
    data = JBlock(imageSize, 0);
    image = (uchar*)(char*)data;
    if (image == null) return MEM_ERR;
    fis >> data;
    bmpInfo.biSize = INFOHEADERSIZE;
    bmpInfo.biWidth = width;
    bmpInfo.biHeight = height;
    bmpInfo.biPlanes = 1;
    bmpInfo.biBitCount = 24;
    bmpInfo.biCompression = BI_RGB;
    bmpInfo.biSizeImage = null;
    bmpInfo.biXPelsPerMeter = null;
    bmpInfo.biYPelsPerMeter = null;
    bmpInfo.biClrUsed = null;
    bmpInfo.biClrImportant = null;
    if (paletteCount > 0) {
      uchar* nImage = null;
      int nScanWidth = ((width*3)+3)&(~3);
      int nImageSize = nScanWidth*height;
      JBlock ndata = JBlock(nImageSize, 0);
      nImage = (uchar*)(char*)ndata;
      if (nImage == null) return MEM_ERR;
      JRGBQUAD rgb;
      int y, x, nx, xBase, nxBase;
      nxBase = xBase = 0;
      switch (bitCount) {
        case 8: {
          for (y=0; y<height; y++) {
            for (x=0, nx=nxBase; x<width; x++) {
              rgb = palette[image[xBase+x]];
              nImage[nx++] = rgb.rgbBlue;
              nImage[nx++] = rgb.rgbGreen;
              nImage[nx++] = rgb.rgbRed;
            }
            xBase += scanWidth;
            nxBase += nScanWidth;
          }
          break;
        }
        case 4: {
          for (y=0; y<height; y++) {
            for (x=0, nx=nxBase; x<width; x++) {
              rgb = palette[(image[xBase+x/2]>>((1-x%2)*4))&15];
              nImage[nx++] = rgb.rgbBlue;
              nImage[nx++] = rgb.rgbGreen;
              nImage[nx++] = rgb.rgbRed;
            }
            xBase += scanWidth;
            nxBase += nScanWidth;
          }
          break;
        }
        case 1: {
          for (y=0; y<height; y++) {
            for (x=0, nx=nxBase; x<width; x++) {
              rgb = palette[(image[xBase+x/8]>>(7-x%8))&1];
              nImage[nx++] = rgb.rgbBlue;
              nImage[nx++] = rgb.rgbGreen;
              nImage[nx++] = rgb.rgbRed;
            }
            xBase += scanWidth;
            nxBase += nScanWidth;
          }
          break;
        }
        default:
          return TYPE_ERR; 
      }
      data = ndata;
    }
  } catch (JEOFException* e) {
    delete e;
    return READ_ERR;
  } catch (JIOException* e) {
    delete e;
    return OPEN_ERR;
  }
  return SUCCESS;
}

