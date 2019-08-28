
#include "Grender.h"

#include "core/SkBitmap.h"

Grender::Grender(){
}

Grender::~Grender(){}


void *
Grender::getRenderContent(int type){
    SkBitmap bitmap;
    bitmap.setInfo(SkImageInfo::Make(240, 320, kN32_SkColorType, kPremul_SkAlphaType));
    bitmap.allocPixels();
//    bitmap.eraseColor(0x0000ff00);
    char buf[320*256*4] = {0xdd};
    memset(buf+320*256*3, 0xff, 320*256);
 //   bitmap.setPixels((void *) buf);

  //  return bitmap.getPixels();
    void *pret = (void *)buf;
    return pret;
}