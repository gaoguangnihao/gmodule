
#ifndef IRENDER_H
#define IRENDER_H value

#include "base/basictypes.h"
#include "nsAString.h"

#include "mozilla/GenericRefCounted.h"

using namespace mozilla;

class Irender : public GenericAtomicRefCounted
{
public:
	MOZ_DECLARE_REFCOUNTED_VIRTUAL_TYPENAME(Irender)
	Irender(){};
	~Irender(){};
	
	virtual void render() = 0;
};

#endif