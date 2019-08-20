
#ifndef mozilla_dom_gmodulexpcom_h
#define mozilla_dom_gmodulexpcom_h


#include "base/basictypes.h"
#include "mozilla/ClearOnShutdown.h"
#include "mozilla/StaticPtr.h"
#include "mozilla/Services.h"
#include "nsIGmoduleXpcom.h"

#include "Irender.h"
#include "Ganimation.h"

namespace mozilla {
namespace dom {
namespace gmodule {

class GmoduleXpcom : public nsIGmoduleXpcom
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIGMODULEXPCOM

	GmoduleXpcom();

	static already_AddRefed<GmoduleXpcom> GetInstance();

private:
	virtual ~GmoduleXpcom();

	static StaticRefPtr<GmoduleXpcom> sSingleton;
	
	Irender* pRender;
};

} // namespace gmodule
} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_gmodulexpcom_h