#ifndef _BIN_EFFECT_H_
#define _BIN_EFFECT_H_

#include "binEmitter.h"

#include <vector>

//описание эффекта
struct binEffect
{
	binEffect()
	{};

	tVecEmitter m_vEmitters;
};

#endif	//_BIN_EFFECT_H_