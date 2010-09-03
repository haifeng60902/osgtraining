#ifndef _EMITTER_H_ 
#define	_EMITTER_H_

#include "binParticle.h"

class Emitter
{
public:
	Emitter();
	~Emitter();

private:
	//сюда будем генерить партиклы
	tVecParticle m_vParticles;
};

#endif	//_EMITTER_H_