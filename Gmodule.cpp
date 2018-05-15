#include "Gmodule.h"

#include "mozilla/dom/GmoduleBinding.h"
#include "mozilla/dom/ContentChild.h"

#include "nsXULAppAPI.h"

using namespace mozilla;

using namespace mozilla::dom;

using namespace mozilla::dom::gmodule;

// cycle collector与isupports的宏定义

NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(Gmodule)

NS_INTERFACE_MAP_ENTRY(nsISupports)

NS_WRAPPERCACHE_INTERFACE_MAP_ENTRY

NS_INTERFACE_MAP_END

NS_IMPL_CYCLE_COLLECTING_ADDREF(Gmodule)

NS_IMPL_CYCLE_COLLECTING_RELEASE(Gmodule)

NS_IMPL_CYCLE_COLLECTION_WRAPPERCACHE(Gmodule, mWindow)

// 构造函数与西沟函数的实现

Gmodule::Gmodule(nsPIDOMWindowInner* aWindow)

: mWindow(aWindow)

{
	LOG("Gmodule enter MozGmodule\n");
}

Gmodule::~Gmodule()

{

	LOG("Gmodule enter ~Gmodule\n");

}

// WrapObject的实现

JSObject*

Gmodule::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto)
{
  return GmoduleBinding::Wrap(aCx, this, aGivenProto);
}


// webidl中定义的接口的实现

int32_t Gmodule::SetTestData(){

	LOG("Gmodule enter SetTestData:isSuccessed\n");

	 if(GeckoProcessType_Default != XRE_GetProcessType()) {
	 	LOG("content process");
	 	ContentChild::GetSingleton()->SendPGmoduleConstructor()->SendSetTestData();
	} else {
		LOG("main process");
	}
	return 0;
}