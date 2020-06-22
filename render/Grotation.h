

#ifndef GROTATION_H
#define GROTATION_H 

#include "Irender.h"

#include "mozilla/RefPtr.h"

#include "mozilla/GenericRefCounted.h"

using namespace mozilla;

#include <android/log.h>
#undef LOG
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "Grotation", ## args)

class Grotation : //public Irender,          // Crash when inherit Irender and GenericAtomicRefCounted  ??????
					public GenericAtomicRefCounted
{
public:
	MOZ_DECLARE_REFCOUNTED_TYPENAME(Grotation)

	Grotation(){
		LOG("Grotation constructor");
	};
	~Grotation(){
		LOG("Grotation destructor");
	};
	
	void render();

    // void AddRef() {
    // }

    // void Release() {
    // }
	
};
#endif