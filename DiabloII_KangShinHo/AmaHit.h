#pragma once
#include "effect.h"

class CAmaHit :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CAmaHit(void);
	CAmaHit(float _fX, float _fY);
	virtual ~CAmaHit(void);
};
