#include "GmoduleChild.h"

#include <android/log.h>
#define LOG_TAG "GmoduleChild"

namespace mozilla {
namespace dom {
namespace gmodule {
	GmoduleChild::GmoduleChild(){
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "constructor\n");
		MOZ_COUNT_CTOR(GmoduleChild);
	}

	GmoduleChild::~GmoduleChild(){
		MOZ_COUNT_DTOR(GmoduleChild);
	}
	
}// namespace gmodule
}// namespace dom
}// namespace mozilla