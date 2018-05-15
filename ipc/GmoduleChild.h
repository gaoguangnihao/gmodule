
#ifndef mozilla_dom_gmodule_child_h
#define mozilla_dom_gmodule_child_h

#include "mozilla/dom/gmodule/PGmoduleChild.h"
namespace mozilla {
namespace dom {
namespace gmodule {
	class GmoduleChild :public PGmoduleChild
	{
	public:
		GmoduleChild();

	private:
		~GmoduleChild();
};

}// namespace gmodule
}// namespace dom
}// namespace mozilla
#endif