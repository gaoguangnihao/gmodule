
#include "hardware/gralloc.h"

#include "Ganimation.h"
#include "GonkDisplay.h"

using namespace mozilla;

#include "android/log.h"
#define LOG(args...)  __android_log_print(ANDROID_LOG_INFO, "ganimation" , ## args)
#define LOGW(args...) __android_log_print(ANDROID_LOG_WARN, "ganimation", ## args)
#define LOGE(args...) __android_log_print(ANDROID_LOG_ERROR, "ganimation", ## args)

void
Ganimation::render() {
	LOG("render");
	GonkDisplay *display = GetGonkDisplay();

	const GonkDisplay::DisplayNativeData& dispData
        = display->GetDispNativeData(GonkDisplay::DISPLAY_PRIMARY);

	ANativeWindowBuffer *buffer = display->DequeueBuffer(GonkDisplay::DISPLAY_PRIMARY);
	if(!buffer) {
		LOGW("failed to get an ANativeWindowBuffer");
		return;
	}

	const hw_module_t *module = nullptr;
    if (hw_get_module(GRALLOC_HARDWARE_MODULE_ID, &module)) {
        LOGW("Could not get gralloc module");
        return;
    }

    const gralloc_module_t *grmodule = reinterpret_cast<gralloc_module_t const*>(module);
    void *mappedAddress = nullptr;

	if(!grmodule->lock(grmodule, buffer->handle, GRALLOC_USAGE_SW_READ_NEVER |
    	GRALLOC_USAGE_SW_WRITE_OFTEN |
    	GRALLOC_USAGE_HW_FB, 0, 0, buffer->width, buffer->height, &mappedAddress)) {
		memset(mappedAddress, 0x77, 
			buffer->height * buffer->stride * GetFormatBPP(dispData.mSurfaceformat));	
		grmodule->unlock(grmodule, buffer->handle);
	};
	display->QueueBuffer(buffer, GonkDisplay::DISPLAY_PRIMARY);
}	

uint16_t
Ganimation::GetFormatBPP(int aFormat)
{
    uint16_t bpp = 0;

    switch (aFormat) {
    case HAL_PIXEL_FORMAT_BGRA_8888:
    case HAL_PIXEL_FORMAT_RGBA_8888:
    case HAL_PIXEL_FORMAT_RGBX_8888:
        bpp = 4;
        break;
    case HAL_PIXEL_FORMAT_RGB_888:
        bpp = 3;
        break;
    default:
        LOGW("Unknown pixel format %d. Assuming RGB 565.", aFormat);
        // FALL THROUGH
    case HAL_PIXEL_FORMAT_RGB_565:
        bpp = 2;
        break;
    }

    return bpp;
}