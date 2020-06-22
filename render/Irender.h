
#ifndef IRENDER_H
#define IRENDER_H 

#include "base/basictypes.h"
#include "nsAString.h"

using namespace mozilla;

class Irender
{
public:
	Irender(){};
	~Irender(){};
	
	virtual void render() = 0;
};

#endif