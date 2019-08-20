
#include "BinderTest.h"
#include "GmoduleXpcom.h"
#include "Irender.h"
#include "Ghwcomposer.h"

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

}

GmoduleXpcom:: ~GmoduleXpcom() {
}

NS_IMETHODIMP
GmoduleXpcom::GetData(int32_t *ret) {
	LOG("Getdata");
	*ret = 2;

	LOG("Initializing BinderTest");
	BinderTest::instantiate()->grallocRender(); 
	return NS_OK;
}

NS_IMETHODIMP
GmoduleXpcom::SetData(const nsAString& data, int32_t *ret) {
	// LOG("SetData %s", NS_LossyConvertUTF16toASCII(data).get());
	// pGanimation->render(data);

	pRender = new Ghwcomposer();
	pRender->render(data);
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
