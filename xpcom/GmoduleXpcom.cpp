#include "nsString.h"
#include "Gutils.h"
#include "BinderTest.h"
#include "GmoduleXpcom.h"
#include "Irender.h"
#include "Ghwcomposer.h"
#include "Ggralloc.h"
#include "Grotation.h"

#include "mozilla/RefPtr.h"
#include "Irender.h"

#include <android/log.h>
#undef LOG
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "GmoduleXpcom", ## args)

namespace mozilla {
namespace dom {
namespace gmodule {
	
/* static */ StaticRefPtr<GmoduleXpcom> GmoduleXpcom::sSingleton;

NS_IMPL_ISUPPORTS(GmoduleXpcom, nsIGmoduleXpcom)

GmoduleXpcom:: GmoduleXpcom(){
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
    LOG("SetData data 111 %s",  NS_ConvertUTF16toUTF8(data).get());
    RefPtr<Grotation> pRender(new Grotation());
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
