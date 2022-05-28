#pragma once
#include "effect.h"

class CFireEnd :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CFireEnd(void);
	CFireEnd(float _fX, float _fY);
	virtual ~CFireEnd(void);
};
