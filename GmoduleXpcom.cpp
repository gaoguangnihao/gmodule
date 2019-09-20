
#include "BinderTest.h"
#include "GmoduleXpcom.h"
#include "Irender.h"
#include "Ghwcomposer.h"
#include "Ggralloc.h"
#include "Grotation.h"

#include <android/log.h>
#undef LOG
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "GmoduleXpcom", ## args)

namespace mozilla {
namespace dom {
namespace gmodule {
	
/* static */ StaticRefPtr<GmoduleXpcom> GmoduleXpcom::sSingleton;

NS_IMPL_ISUPPORTS(GmoduleXpcom, nsIGmoduleXpcom)

GmoduleXpcom:: GmoduleXpcom()
:pRender(nullptr){

}

GmoduleXpcom:: ~GmoduleXpcom() {
}

NS_IMETHODIMP
GmoduleXpcom::GetData(int32_t *ret) {
	LOG("Getdata");
	*ret = 2;
	return NS_OK;
}

NS_IMETHODIMP
GmoduleXpcom::SetData(const nsAString& data, int32_t *ret) {
	switch(GetEventTypeFromData(data)) {
        case 0:
            pRender = new Ggralloc();
            break;
        case 1:
	        pRender = new Ghwcomposer();
            break;
        case 2:
        	LOG("Initializing BinderTest");
        	BinderTest::instantiate()->grallocRender(); 
            break;
        case 3:
        	pRender = new Grotation();
        	break;
        default:
            break;
    }
    if (pRender)
    	pRender->render();
	return NS_OK;
}

int 
GmoduleXpcom::GetEventTypeFromData(const nsAString& data) {
    int type = -1;
    if (data.EqualsASCII("0")){
        type = 0;
    } else if(data.EqualsASCII("1")){
        type = 1;
    } else if(data.EqualsASCII("2")) {
        type = 2;
    } else {
        type =3;
    }
    return type;
}

/* static */ already_AddRefed<GmoduleXpcom>
GmoduleXpcom::GetInstance() {
	if (!sSingleton) {
		sSingleton = new GmoduleXpcom();
	}
	RefPtr<GmoduleXpcom> service = sSingleton.get();
	return service.forget();
}

} // namespace gmodule
} // namespace dom
} // namespace mozilla
