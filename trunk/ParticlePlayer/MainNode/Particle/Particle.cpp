#include "Particle.h"

#include "./ParticlePlayer/ParticlePlayer.h"

Particle::Particle()
{

}

Particle::~Particle()
{

}

void Particle::Init()
{
	//�������������
	binEffect &mEffects = ParticlePlayer::Instance().GetEffects();

	for ( int i = 0 ; i < mEffects.m_vEmitters.size() ; ++i )
		//�������� ��������� �������
		AddEmitter( mEffects.m_vEmitters[ i ] );
}

void Particle::AddEmitter( binEmitter &mEmitter )
{
	//�������� ��������� �������

}