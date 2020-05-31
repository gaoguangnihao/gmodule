
#ifndef GUTILS_H
#define GUTILS_H 

#include <stdio.h>
#include <android/log.h>
#include "nsString.h"

#ifndef GTAG
#define GTAG "ggg"
#endif // GTAG

#undef GLOG
#define GLOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, GTAG, ## args)

void dumptofile(const char * fname,const void* buffer, size_t bytes);

void convertEventType(const nsAString& data, int& eventType);

#endif
