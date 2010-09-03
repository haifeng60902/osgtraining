#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "binEmitter.h"
#include "./ParticlePlayer/Emitter.h"

class Particle
{
public:
	Particle();
	~Particle();

	//�������������
	void Init();

private:
	typedef std::vector< Emitter* > tVecEmitterClass;

	//�������� ��������� �������
	void AddEmitter( binEmitter &mEmitter );

	//����� ���������, ������� ��������� ����������
	tVecEmitterClass m_vEmitterClass;
};

#endif	//_PARTICLE_H_