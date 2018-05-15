
#include "GmoduleParent.h"

#include <android/log.h>
#define LOG_TAG "GmoduleParent"


namespace mozilla {
namespace dom {
namespace gmodule {
	NS_INTERFACE_MAP_BEGIN(GmoduleParent)
	NS_INTERFACE_MAP_ENTRY(nsISupports)
	NS_INTERFACE_MAP_END
	NS_IMPL_ADDREF(GmoduleParent)
	NS_IMPL_RELEASE(GmoduleParent)

	GmoduleParent::GmoduleParent(){
	  //LOG("enter\n");
	  MOZ_COUNT_CTOR(GmoduleParent);

	}

	GmoduleParent::~GmoduleParent(){
	  //LOG("enter\n");
	  MOZ_COUNT_DTOR(GmoduleParent);
	}

	void GmoduleParent::ActorDestroy(ActorDestroyReason aWhy){

	}

	bool GmoduleParent::RecvSetTestData(){
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "enter\n");
		return true;
	}
	
}// namespace gmodule
}// namespace dom
}// namespace mozilla