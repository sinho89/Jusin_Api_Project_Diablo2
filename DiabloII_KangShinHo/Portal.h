#pragma once
#include "unit.h"

class CPortal :
	public CUnit
{
private:
	ePORTAL_TYPE	m_eType;
	bool			m_bOpen;
	bool			m_bLoading;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CPortal(void);
	CPortal(float _fX, float _fY, ePORTAL_TYPE _eType)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
		m_eType = _eType;
	}
	~CPortal(void);
};
