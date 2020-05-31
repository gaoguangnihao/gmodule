/**
* This module is for study perpose which Edit from guang.gao@kaiostech.com
* Gmodule interface called from gaia
*/

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