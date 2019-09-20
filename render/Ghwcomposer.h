

#ifndef GHWCOMPOSER_H
#define GHWCOMPOSER_H 
#include "hardware/hwcomposer.h"
#include <gui/Surface.h>
#include <gui/GraphicBufferAlloc.h>
#include "DisplaySurface.h"

#include "Irender.h"
#include "Grender.h"

#include <android/log.h>
#undef LOG
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "Ghwcomposer", ## args)

  struct DisplayNativeData
  {
  	DisplayNativeData()
  	:mXdpi(0)
  	,mSurfaceFormate(0)
  	,mWidth(0)
  	,mHeight(0)
  	{};

  	float mXdpi;
  	int32_t mSurfaceFormate;
  	uint32_t mWidth;
  	uint32_t mHeight;
  };


class Ghwcomposer : public Irender
{
public:
	Ghwcomposer();
	~Ghwcomposer();
	
	void render();
private:
  Grender* pGrender;

	hwc_display_contents_1_t* mList;

	hwc_composer_device_1_t*  mHwc;

  DisplayNativeData* mDisplayNativeData;

  // producer
  android::sp<ANativeWindow> mNativeWindow;
  // consumer
  android::sp<android::DisplaySurface> mDisplaySurface;

  bool post(buffer_handle_t buf, int fence);

};

#endif //GHWCOMPOSER_H