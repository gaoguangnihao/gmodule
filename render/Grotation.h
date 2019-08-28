

#ifndef GROTATION_H
#define GROTATION_H 

#include "Irender.h"

#include <android/log.h>
#undef LOG
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "Grotation", ## args)

class Grotation : public Irender
{
public:
	Grotation(){};
	~Grotation(){};
	
	void render();
private:

	
};
#endif