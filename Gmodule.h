/**
* This module is for study perpose which Edit from guang.gao@kaiostech.com
* Gmodule interface called from gaia
*/

#ifndef mozilla_dom_gmodule_h
#define mozilla_dom_gmodule_h

#include "nsWrapperCache.h"
#include "nsPIDOMWindow.h"

namespace mozilla {
namespace dom {
namespace gmodule {

class Gmodule final : public nsISupports 
                    , public nsWrapperCache
{
public:
  Gmodule(nsPIDOMWindowInner *aWindow){};

  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS(Gmodule)

  nsPIDOMWindowInner* GetParentObject()const{return mWindow;};
 // virtual JSObject* WrapObject(JSContext* aCx) override;
  virtual JSObject* WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto) override;

  /* Impliment the WebIDL interface begin*/
  int32_t SetTestData(const nsAString& data);
  /* Imppliment the WebIDL interface end*/

private:
  virtual~Gmodule(){};

  nsCOMPtr<nsPIDOMWindowInner> mWindow;
};

}// namespace gmodule
}// namespace dom
}// namespace mozilla

#endif //mozilla_dom_gmodule_h