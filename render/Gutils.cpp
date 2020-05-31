#include "Gutils.h"

void
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

void
convertEventType(const nsAString& data, int& eventType) {
    if (data.EqualsASCII("0")){
        eventType = 0;
    } else if(data.EqualsASCII("1")){
        eventType = 1;
    } else if(data.EqualsASCII("2")) {
        eventType = 2;
    } else if(data.EqualsASCII("3")){
        eventType =3;
    } else {
        eventType = 4;
    }
}
