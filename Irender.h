
#ifndef IRENDER_H
#define IRENDER_H value

#include "base/basictypes.h"
#include "nsAString.h"

class Irender
{
public:
	Irender(){};
	~Irender(){};
	
	virtual void render(const nsAString& data) = 0;
};

#endif