#pragma once
#include "effect.h"

class CTransForm :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CTransForm(void);
	virtual ~CTransForm(void);
};
