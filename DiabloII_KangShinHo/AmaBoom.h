#pragma once
#include "effect.h"

class CAmaBoom :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CAmaBoom(void);
	CAmaBoom(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	virtual ~CAmaBoom(void);
};
