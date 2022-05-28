#pragma once
#include "unit.h"

class CMonster :
	public CUnit
{
private:
	int		iTileCheck;
	bool	bStart;
	bool	m_bDeadSound;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	void SetMonsterPos(void);
public:
	CMonster(void);
	CMonster(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	CMonster(float _fX, float _fY, bool _bA)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
		bStart = _bA;
	}
	CMonster(INFO _pInfo)
	{
		memcpy(&m_tInfo, &_pInfo, sizeof(INFO));
		bStart = true;
	}
	virtual ~CMonster(void);
};
