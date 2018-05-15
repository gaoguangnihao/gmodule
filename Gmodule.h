#ifndef mozilla_dom_gmodule_h

#define mozilla_dom_gmodule_h

#include "nsWrapperCache.h"

#include "nsPIDOMWindow.h"

#include <android/log.h>
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "gmodule", ## args)

namespace mozilla {

namespace dom {

namespace gmodule {



class Gmodule final : public nsISupports 
                    , public nsWrapperCache
{
public:
  Gmodule(nsPIDOMWindowInner *aWindow);

  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS(Gmodule)


  nsPIDOMWindowInner* GetParentObject()const{return mWindow;};

 // virtual JSObject* WrapObject(JSContext* aCx) override;
  virtual JSObject* WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto) override;

  /* Impliment the WebIDL interface begin*/

  int32_t SetTestData();

  /* Imppliment the WebIDL interface end*/

  private:
    virtual~Gmodule();

    nsCOMPtr<nsPIDOMWindowInner> mWindow;
  protected:

  };

}// namespace gmodule

}// namespace dom

}// namespace mozilla

#endif