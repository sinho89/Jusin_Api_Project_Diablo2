#pragma once
#include "effect.h"

class CInferno :
	public CEffect
{
private:
	eDIRTECTION_TYPE m_eType;
	DWORD	m_dwCool;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CInferno(void);
	CInferno(float _fX, float _fY, eDIRTECTION_TYPE _eType);
	virtual ~CInferno(void);
};
