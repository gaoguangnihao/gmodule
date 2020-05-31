/**
* This module is for study perpose which Edit from guang.gao@kaiostech.com
* Gmodule interface called from gaia
*/

#include "Gmodule.h"
#include "mozilla/dom/GmoduleBinding.h"
#include "mozilla/dom/gmodule/PGmoduleChild.h"
#include "mozilla/dom/ContentChild.h"
#include "nsXULAppAPI.h"

#include <android/log.h>
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "gmodule", ## args)

using namespace mozilla;
using namespace mozilla::dom;
using namespace mozilla::dom::gmodule;

// Define cycle collector and isupports
NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(Gmodule)
NS_INTERFACE_MAP_ENTRY(nsISupports)
NS_WRAPPERCACHE_INTERFACE_MAP_ENTRY
NS_INTERFACE_MAP_END
NS_IMPL_CYCLE_COLLECTING_ADDREF(Gmodule)
NS_IMPL_CYCLE_COLLECTING_RELEASE(Gmodule)
NS_IMPL_CYCLE_COLLECTION_WRAPPERCACHE(Gmodule, mWindow)

// WrapObject implement

JSObject*
Gmodule::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto)
{
  return GmoduleBinding::Wrap(aCx, this, aGivenProto);
}

// webidl implement
int32_t Gmodule::SetTestData(const nsAString& data){
	LOG("Set Data: %s \n", NS_LossyConvertUTF16toASCII(data).get());
	if(GeckoProcessType_Default != XRE_GetProcessType()) {
	 	PGmoduleChild* proxy = ContentChild::GetSingleton()->SendPGmoduleConstructor();
	 	if (proxy) {
	 		proxy->SendSetTestData(nsString(data));
	 	}
	} else {
		LOG("Main process in maintenane");
	}
	return 0;
}