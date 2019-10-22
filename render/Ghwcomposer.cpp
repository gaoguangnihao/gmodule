#include <system/window.h>
#include <hardware/hardware.h>
#include <hardware/fb.h>
#include <hardware/gralloc.h>
#include "hardware/hwcomposer.h"

#include "gui/IGraphicBufferProducer.h"
#include "gui/IGraphicBufferConsumer.h"

#include "FramebufferSurface.h"
#include "Ghwcomposer.h"

#include "Gutils.h"

#undef GTAG
#define GTAG "Ghwcomposer"

using namespace android;

Ghwcomposer::Ghwcomposer()
    :mList(nullptr)
    ,mDisplayNativeData(new DisplayNativeData()) 
{

    pGrender = new Grender();

    mList = (hwc_display_contents_1_t *)calloc(1, sizeof(*mList) + (sizeof(hwc_layer_1_t)*2));

    const hw_module_t *module = nullptr;
    int err = hw_get_module(HWC_HARDWARE_MODULE_ID, &module);
    if(err) {
        GLOG("error: hwcomposer get failed!!");
    };
    err = hwc_open_1(module, &mHwc);
    if(err) {
        GLOG("error: open hwc failed!!");
    }

    int32_t values[4];
    const uint32_t attrs[] = {
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
    GLOG("Get display attributes width:%d, height:%d, xdpi:%f, surfaceFormate:%d",
        mDisplayNativeData->mWidth,
        mDisplayNativeData->mHeight,
        mDisplayNativeData->mXdpi,
        mDisplayNativeData->mSurfaceFormate); 

    // create frameBufferSurface
    android::sp<android::IGraphicBufferAlloc> alloc = new GraphicBufferAlloc();
    sp<IGraphicBufferProducer> producer;
    sp<IGraphicBufferConsumer> consumer;
    BufferQueue::createBufferQueue(&producer, &consumer, alloc);

    // consumer
    int dip = 0;
    uint32_t width = 240;
    uint32_t height = 320;
    uint32_t format = 4;
    mDisplaySurface = new FramebufferSurface(dip, width, height, format, consumer);

    // producer
    mNativeWindow = new Surface(producer);
}

Ghwcomposer::~Ghwcomposer() {
    free(mDisplayNativeData);
}

void Ghwcomposer::render() {
    // dequeueBuffer
    ANativeWindowBuffer *buf;
    int fenceFd = -1;
    mNativeWindow->dequeueBuffer(mNativeWindow.get(), &buf, &fenceFd);

    const hw_module_t *module = nullptr;
    if (hw_get_module(GRALLOC_HARDWARE_MODULE_ID, &module)) {
        GLOG("Could not get gralloc module");
        return;
    }

    long length = buf->height * buf->stride * 2;//GetFormatBPP(dispData.mSurfaceformat);
    void *pBuffer = pGrender->getRenderContent(2);
    dumptofile("/data/data/1.txt", pBuffer, length);

    const gralloc_module_t *grmodule = reinterpret_cast<gralloc_module_t const*>(module);
    void *mappedAddress = nullptr;

    if(!grmodule->lock(grmodule, buf->handle, GRALLOC_USAGE_SW_READ_NEVER |
        GRALLOC_USAGE_SW_WRITE_OFTEN |
        GRALLOC_USAGE_HW_FB, 0, 0, buf->width, buf->height, &mappedAddress)) {
        memcpy(mappedAddress, pBuffer, length);
        grmodule->unlock(grmodule, buf->handle);
    };

    mNativeWindow->queueBuffer(mNativeWindow.get(), buf, -1);

    // post
    post(mDisplaySurface->lastHandle, mDisplaySurface->GetPrevDispAcquireFd());
}

bool Ghwcomposer::post(buffer_handle_t buf, int fence) {
    hwc_display_contents_1_t *displays[HWC_NUM_DISPLAY_TYPES] = {NULL};
    const hwc_rect_t r = { 0, 0, 240, 320};
    displays[HWC_DISPLAY_PRIMARY] = mList;
    mList->retireFenceFd = -1;
    mList->numHwLayers = 2;
    mList->flags = HWC_GEOMETRY_CHANGED;
    mList->outbuf = nullptr;
    mList->outbufAcquireFenceFd = -1;
    mList->hwLayers[0].compositionType = HWC_FRAMEBUFFER;
    mList->hwLayers[0].hints = 0;
    /* Skip this layer so the hwc module doesn't complain about null handles */
    mList->hwLayers[0].flags = HWC_SKIP_LAYER;
    mList->hwLayers[0].backgroundColor = {0};
    mList->hwLayers[0].acquireFenceFd = -1;
    mList->hwLayers[0].releaseFenceFd = -1;
    /* hwc module checks displayFrame even though it shouldn't */
    mList->hwLayers[0].displayFrame = r;

    mList->hwLayers[1].compositionType = HWC_FRAMEBUFFER_TARGET;
    mList->hwLayers[1].hints = 0;
    mList->hwLayers[1].flags = 0;
    mList->hwLayers[1].handle = buf;
    mList->hwLayers[1].transform = 0;
    mList->hwLayers[1].blending = HWC_BLENDING_NONE;
    mList->hwLayers[1].sourceCropf.left = 0;
    mList->hwLayers[1].sourceCropf.top = 0;
    mList->hwLayers[1].sourceCropf.right = 240;
    mList->hwLayers[1].sourceCropf.bottom = 320;
    mList->hwLayers[1].displayFrame = r;
    mList->hwLayers[1].visibleRegionScreen.numRects = 1;
    mList->hwLayers[1].visibleRegionScreen.rects = &mList->hwLayers[1].displayFrame;
    mList->hwLayers[1].acquireFenceFd = fence;
    mList->hwLayers[1].releaseFenceFd = -1;
    mList->hwLayers[1].planeAlpha = 0xFF;
    mHwc->prepare(mHwc, HWC_NUM_DISPLAY_TYPES, displays);
    int err = mHwc->set(mHwc, HWC_NUM_DISPLAY_TYPES, displays);

    if (!mDisplaySurface.get()) {
        mDisplaySurface->setReleaseFenceFd(mList->hwLayers[1].releaseFenceFd);
    if (mList->retireFenceFd >= 0)
        close(mList->retireFenceFd);
    return !err;
    }
    return false;
}