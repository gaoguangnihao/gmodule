
#ifndef mozilla_dom_gmodule_Parent_h
#define mozilla_dom_gmodule_Parent_h

#include "mozilla/dom/gmodule/PGmoduleParent.h"

namespace mozilla {
namespace dom {
namespace gmodule {

class GmoduleParent :public PGmoduleParent
                    ,public nsISupports

{
public:
  NS_DECL_ISUPPORTS
  GmoduleParent();
 
  virtual void ActorDestroy(ActorDestroyReason aWhy) override;
protected:
  /*receive child function call*/
	virtual bool RecvSetTestData() override;

private:
	~GmoduleParent();
};

}// namespace gmodule
}// namespace dom
}// namespace mozilla
#endif /*mozilla_dom_gmodule_Parent_h*/