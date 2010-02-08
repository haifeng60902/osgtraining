#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "Singleton.h"
#include "binLight.h"

class Lighting : public Singleton< Lighting >
{
public:
	Lighting();
	~Lighting();

	//получить доступ к данным источника света
	binLight &GetLight(){ return m_binLight; };

private:
	//данные источника света
	binLight m_binLight;
};

#endif	//_LIGHTING_H_