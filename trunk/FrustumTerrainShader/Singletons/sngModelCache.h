#ifndef _SNG_MODEL_CACHE_H_
#define _SNG_MODEL_CACHE_H_

#include "Singleton.h"

class sngModelCache : public Singleton< sngModelCache >
{
public:
	sngModelCache();
	~sngModelCache();

};

#endif	//_SNG_MODEL_CACHE_H_