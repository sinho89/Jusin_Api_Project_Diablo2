#pragma once
#include "effect.h"

class CFireHit :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CFireHit(void);
	CFireHit(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	virtual ~CFireHit(void);
};
