

#ifndef GANIMATION_H
#define GANIMATION_H 

#include "Irender.h"
#include "Grender.h"

class Ganimation : public Irender
{
public:
	Ganimation():pGrender(new Grender()),pBuffer(NULL){};
	~Ganimation(){};

	void render();
private:
	
	uint16_t GetFormatBPP(int format);

	void dump(void *buf, long length);
	
	Grender* pGrender;

	void * pBuffer;   // buffer for render content.
};
#endif