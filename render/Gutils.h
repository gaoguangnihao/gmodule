
#ifndef GUTILS_H
#define GUTILS_H 

#include <stdio.h>
#include <android/log.h>
#ifndef GTAG
#define GTAG "ggg"
#endif // GTAG

#undef GLOG
#define GLOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, GTAG, ## args)


static void
dumptofile(const char * fname,const void* buffer, size_t bytes) {
    static FILE *fp=NULL;
    if(fp==NULL || access( fname, F_OK )==-1){
    	fp = fopen(fname, "ab+" );
        if(fp==NULL){
            GLOG("can't open file!");
            fp=NULL;
            return;
        }
    }
    if(fp!=NULL){
        fwrite(buffer , 1 , bytes , fp );
    }
}

#endif
