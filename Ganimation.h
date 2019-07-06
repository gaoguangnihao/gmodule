

#ifndef GANIMATION_H
#define GANIMATION_H 

class Ganimation
{
public:
	Ganimation(){};
	~Ganimation(){};

	void render();
private:
	
	uint16_t GetFormatBPP(int format);
};
#endif
