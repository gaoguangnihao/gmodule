
#ifndef GRENDER_H
#define GRENDER_H 

class Grender
{
public:
	Grender();
	~Grender();
	
	void *getRenderContent(int type);

private:
	void *getBitmap();
	
};
#endif