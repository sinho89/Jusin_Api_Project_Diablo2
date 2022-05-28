#pragma once
#include "effect.h"

class CColdOver :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CColdOver(void);
	virtual ~CColdOver(void);
};
