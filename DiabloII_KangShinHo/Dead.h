#pragma once
#include "unit.h"

class CDead :
	public CUnit
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CDead(void);
	CDead(float _fX, float _fY, eDIRTECTION_TYPE _eType);
	virtual ~CDead(void);
};
