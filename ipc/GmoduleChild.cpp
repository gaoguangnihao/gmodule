#include "GmoduleChild.h"

namespace mozilla {
namespace dom {
namespace gmodule {
	GmoduleChild::GmoduleChild(){
		MOZ_COUNT_CTOR(GmoduleChild);
	}

	GmoduleChild::~GmoduleChild(){
		MOZ_COUNT_DTOR(GmoduleChild);
	}
	
}// namespace gmodule
}// namespace dom
}// namespace mozilla