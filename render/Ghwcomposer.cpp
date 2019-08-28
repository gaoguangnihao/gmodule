
#include <system/window.h>
#include <hardware/hardware.h>
#include <hardware/fb.h>
#include <hardware/gralloc.h>
#include "hardware/hwcomposer.h"

#include "Ghwcomposer.h"


Ghwcomposer::Ghwcomposer():
mList(nullptr)
,mDisplayNativeData(new DisplayNativeData()) {


/*	int err = hw_get_module(HWC_HARDWARE_MODULE_ID, &mModule);
	if(err) {
		LOG("error: hwcomposer get failed!!");
	};
	err = hwc_open_1(mModule, &mHwc);
	if(err) {
		LOG("error: open hwc failed!!");
	}

	int32_t values[4];
	const int32_t attrs[] = {
		HWC_DISPLAY_WIDTH,
		HWC_DISPLAY_HEIGHT,
		HWC_DISPLAY_DPI_X,
		HWC_DISPLAY_FBFORMAT,
		HWC_DISPLAY_NO_ATTRIBUTE
	};

	mHwc->getDisplayAttributes(mHwc, 0, 0, attrs, values);

	mDisplayNativeData->mWidth = values[0];
	mDisplayNativeData->mHeight = values[1];
	mDisplayNativeData->mXdpi = values[2]/1000.0f;
	mDisplayNativeData->mSurfaceFormate = values[3];
	LOG("Get display attributes width:%d, height:%d, xdpi:%f, surfaceFormate:%d",
		mDisplayNativeData->mWidth,
		mDisplayNativeData->mHeight,
		mDisplayNativeData->mXdpi,
		mDisplayNativeData->mSurfaceFormate); */
}

Ghwcomposer::~Ghwcomposer() {
	free(mDisplayNativeData);
}

void Ghwcomposer::render() {
	
}