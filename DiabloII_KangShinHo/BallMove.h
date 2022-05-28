#pragma once
#include "effect.h"

class CBallMove :
	public CEffect
{
private:
	eDIRTECTION_TYPE m_eType;
	DWORD	m_dwTime;
	DWORD	m_dwAlive;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CBallMove(void);
	CBallMove(float _fX, float _fY, eDIRTECTION_TYPE _eType);
	virtual ~CBallMove(void);
};
