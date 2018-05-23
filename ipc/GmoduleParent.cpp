#include "nsCOMPtr.h"
#include "GmoduleParent.h"
#include "nsIGmoduleManager.h"
#include "nsIGmoduleXpcom.h"
#include "nsComponentManagerUtils.h"

#include <android/log.h>
#define LOG_TAG "GmoduleParent"

using namespace mozilla::dom;

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

		nsCOMPtr<nsIGmoduleManager> gm = do_CreateInstance("@mozilla.org/gmoduleManager;1");
		if (gm) {
			gm->Init();
		}

		nsCOMPtr<nsIGmoduleXpcom> gx = do_CreateInstance("@mozilla.org/gmodule/gmodulexpcom;1");
		if (gx) {
			int32_t ret = -1;
			gx->Getdata(&ret);
		}
		return true;
	}
	
}// namespace gmodule
}// namespace dom
}// namespace mozilla
