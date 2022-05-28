#pragma once
#include "effect.h"

class CFire :
	public CEffect
{
private:
	DWORD	m_dwCool;
	bool	m_bCheck;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CFire(void);
	CFire(float _fX, float _fY, float _fAngle);
	virtual ~CFire(void);
};
