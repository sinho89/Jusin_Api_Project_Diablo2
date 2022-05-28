#pragma once
#include "unit.h"

class CAlphaTile :
	public CUnit
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CAlphaTile(void);
	virtual ~CAlphaTile(void);
};
