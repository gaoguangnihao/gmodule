/**
* This module is for study perpose which Edit from guang.gao@kaiostech.com
* Gmodule interface called from gaia
*/

#include "nsCOMPtr.h"
#include "GmoduleParent.h"
#include "nsIGmoduleManager.h"
#include "nsIGmoduleXpcom.h"
#include "nsComponentManagerUtils.h"

#include "GOpengles.h"

#include <android/log.h>
#undef LOG_TAG
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
	  MOZ_COUNT_CTOR(GmoduleParent);
	}

	GmoduleParent::~GmoduleParent(){
	  MOZ_COUNT_DTOR(GmoduleParent);
	}

	void GmoduleParent::ActorDestroy(ActorDestroyReason aWhy){
	}

	bool GmoduleParent::RecvSetTestData(const nsString& data){
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "data %s\n", NS_ConvertUTF16toUTF8(data).get());

		nsCOMPtr<nsIGmoduleManager> gmoduleManager = do_CreateInstance("@mozilla.org/gmoduleManager;1");
		if (gmoduleManager) {
			gmoduleManager->Init();
		}

		nsCOMPtr<nsIGmoduleXpcom> gmoduleXpcom = do_CreateInstance("@mozilla.org/gmodule/gmodulexpcom;1");
		if (gmoduleXpcom) {
			int32_t ret = -1;
			gmoduleXpcom->SetData(data, &ret);
		}

		// GL set draw type here, will draw in LayerCompositeManager
		GOpengles::SetDrawType(data);
		return true;
	}
	
}// namespace gmodule
}// namespace dom
}// namespace mozilla
