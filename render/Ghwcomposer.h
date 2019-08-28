
#include "hardware/hwcomposer.h"

#include "Irender.h"

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
	hwc_display_contents_1_t* mList;

	hw_module_t *mModule;

	hwc_composer_device_1_t*  mHwc;

    DisplayNativeData* mDisplayNativeData;
};