
#include "BinderTest.h"

#include "GmoduleXpcom.h"

#include <android/log.h>
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "GmoduleXpcom", ## args)

namespace mozilla {
namespace dom {
namespace gmodule {
	
/* static */ StaticRefPtr<GmoduleXpcom> GmoduleXpcom::sSingleton;

NS_IMPL_ISUPPORTS(GmoduleXpcom, nsIGmoduleXpcom)

GmoduleXpcom:: ~GmoduleXpcom() {

}

NS_IMETHODIMP
GmoduleXpcom::Getdata(int32_t *ret) {
	LOG("Getdata");
	*ret = 2;

	LOG("Initializing BinderTest");
	BinderTest::instantiate(); 
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
