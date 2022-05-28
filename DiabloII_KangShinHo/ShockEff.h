#pragma once
#include "effect.h"

class CShockEff :
	public CEffect
{
private:
	eDIRTECTION_TYPE m_eType;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CShockEff(void);
	CShockEff(float _fX, float _fY, eDIRTECTION_TYPE _eType);
	virtual ~CShockEff(void);
};
