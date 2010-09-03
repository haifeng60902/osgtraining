#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "binEmitter.h"
#include "./ParticlePlayer/Emitter.h"

class Particle
{
public:
	Particle();
	~Particle();

	//инициализация
	void Init();

private:
	typedef std::vector< Emitter* > tVecEmitterClass;

	//добавить очередной эмиттер
	void AddEmitter( binEmitter &mEmitter );

	//набор эммитеров, которые предстоит отобразить
	tVecEmitterClass m_vEmitterClass;
};

#endif	//_PARTICLE_H_