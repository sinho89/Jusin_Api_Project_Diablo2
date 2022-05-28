#pragma once
#include "effect.h"

class CCart :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CCart(void);
	virtual ~CCart(void);
};
