#pragma once
#include "effect.h"

class CBallStart :
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
	CBallStart(void);
	CBallStart(float _fX, float _fY, eDIRTECTION_TYPE _eType);
	virtual ~CBallStart(void);
};
