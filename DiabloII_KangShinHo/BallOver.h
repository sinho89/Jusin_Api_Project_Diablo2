#pragma once
#include "effect.h"

class CBallOver :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CBallOver(void);
	virtual ~CBallOver(void);
};
