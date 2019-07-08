

#ifndef GANIMATION_H
#define GANIMATION_H 

#include "Grender.h"

class Ganimation
{
public:
	Ganimation():pGrender(new Grender()),pBuffer(NULL){};
	~Ganimation(){};

	void render(const nsAString& data);
private:
	
	uint16_t GetFormatBPP(int format);
	int GetTypeFromData(const nsAString& data);

	void dump(void *buf, long length);

	Grender* pGrender;

	void * pBuffer;   // buffer for render content.
};
#endif
