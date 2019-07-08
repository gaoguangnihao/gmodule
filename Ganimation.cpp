#include "nsAString.h"

#include "hardware/gralloc.h"
#include "Ganimation.h"
#include "GonkDisplay.h"

using namespace mozilla;

#include "android/log.h"
#define LOG(args...)  __android_log_print(ANDROID_LOG_INFO, "ganimation" , ## args)
#define LOGW(args...) __android_log_print(ANDROID_LOG_WARN, "ganimation", ## args)
#define LOGE(args...) __android_log_print(ANDROID_LOG_ERROR, "ganimation", ## args)

void
Ganimation::render(const nsAString& data) {
	LOG("render");
	GonkDisplay *display = GetGonkDisplay();

	const GonkDisplay::DisplayNativeData& dispData
        = display->GetDispNativeData(GonkDisplay::DISPLAY_PRIMARY);

	ANativeWindowBuffer *buffer = display->DequeueBuffer(GonkDisplay::DISPLAY_PRIMARY);
	if(!buffer) {
		LOGW("failed to get an ANativeWindowBuffer");
		return;
	}

    LOG("native window buffer height:%d,stride:%d, display format:%d",
        buffer->height, buffer->stride, dispData.mSurfaceformat);
	const hw_module_t *module = nullptr;
    if (hw_get_module(GRALLOC_HARDWARE_MODULE_ID, &module)) {
        LOGW("Could not get gralloc module");
        return;
    }

    long length = buffer->height * buffer->stride * GetFormatBPP(dispData.mSurfaceformat);
    char temp[length] = {'\0'};
    pBuffer = temp;

    switch(GetTypeFromData(data)) {
        case 0:
            memset(pBuffer, 0x77, length);
            break;
        case 1:
            pBuffer = pGrender->getRenderContent(1);
            break;
        case 2:
            break;
        default:
            break;
    }

  //  dump(pBuffer, length);   // dump pBuffer

    const gralloc_module_t *grmodule = reinterpret_cast<gralloc_module_t const*>(module);
    void *mappedAddress = nullptr;

	if(!grmodule->lock(grmodule, buffer->handle, GRALLOC_USAGE_SW_READ_NEVER |
    	GRALLOC_USAGE_SW_WRITE_OFTEN |
    	GRALLOC_USAGE_HW_FB, 0, 0, buffer->width, buffer->height, &mappedAddress)) {
		memcpy(mappedAddress, pBuffer, length);
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

int
Ganimation::GetTypeFromData(const nsAString& data) {
    int type = -1;
    if (data.EqualsASCII("0")){
        type = 0;
    } else if(data.EqualsASCII("1")){
        type = 1;
    } else if(data.EqualsASCII("2")) {
        type = 2;
    } else {
        type =3;
    }

    return type;
}

void 
Ganimation::dump(void * buf, long length) {
    int index = 0;
    int LINE_NUB = 240;
    printf("=====DUMP Buffer, size %ld: \n", length);
    char *c = static_cast<char *> (buf);
    while(index <= length - 1) {
        index += LINE_NUB;
        for (int i = index; i < index + LINE_NUB; i ++) {
            printf("%x \t", c[index]);
        }
        printf("\n");
    }
    printf("DUMP END ======");
}