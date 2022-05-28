#pragma once
#include "effect.h"

class CRoundFire :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CRoundFire(void);
	CRoundFire(float _fX, float _fY);
	virtual ~CRoundFire(void);
};
