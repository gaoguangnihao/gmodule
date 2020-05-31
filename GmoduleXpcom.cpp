#include "nsString.h"
#include "Gutils.h"
#include "BinderTest.h"
#include "GmoduleXpcom.h"
#include "Irender.h"
#include "Ghwcomposer.h"
#include "Ggralloc.h"
#include "Grotation.h"
//#include "GOpengles.h"

#include <android/log.h>
#undef LOG
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "GmoduleXpcom", ## args)

namespace mozilla {
namespace dom {
namespace gmodule {
	
/* static */ StaticRefPtr<GmoduleXpcom> GmoduleXpcom::sSingleton;

NS_IMPL_ISUPPORTS(GmoduleXpcom, nsIGmoduleXpcom)

GmoduleXpcom:: GmoduleXpcom()
:pRender(nullptr){
    mDataCache = 0;
}

GmoduleXpcom:: ~GmoduleXpcom() {
}

NS_IMETHODIMP
GmoduleXpcom::GetData(int32_t *ret) {
	LOG("Get data %d", mDataCache);
	*ret = mDataCache;
	return NS_OK;
}

NS_IMETHODIMP
GmoduleXpcom::SetData(const nsAString& data, int32_t *ret) {
    LOG("SetData data %s",  NS_ConvertUTF16toUTF8(data).get());
    convertEventType(data, mDataCache);
	switch(mDataCache) {
        case 1:
	        pRender = new Ghwcomposer();
            break;
        case 2:
        	LOG("Initializing BinderTest");
   //     	BinderTest::instantiate()->grallocRender(); 
            break;
        case 3:
   //     	pRender = new Grotation();
        	break;

        case 4:
            LOG("Create GOpengles instantiate");
            //pRender = new GOpengles();
        case 5:
            pRender = new Ggralloc();
        case 0:
        default:
            break;
    }
    if (pRender)
    	pRender->render();
	return NS_OK;
}

/* static */ already_AddRefed<GmoduleXpcom>
GmoduleXpcom::GetInstance() {
	if (!sSingleton) {
		sSingleton = new GmoduleXpcom();
	}
	RefPtr<GmoduleXpcom> service = sSingleton.get();
	return service.forget();
}

} // namespace gmodule
} // namespace dom
} // namespace mozilla
