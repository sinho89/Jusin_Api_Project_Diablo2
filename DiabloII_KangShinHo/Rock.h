#pragma once
#include "effect.h"

class CRock :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CRock(void);
	virtual ~CRock(void);
};
