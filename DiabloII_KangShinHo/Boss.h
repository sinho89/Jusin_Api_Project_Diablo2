#pragma once
#include "unit.h"

class CBoss :
	public CUnit
{
private:
	int		iTileCheck;
	int		iInfernoTime;
	int		iFireTime;
	bool	m_bInferno;
	bool	m_bDash;
	bool	m_bFire;
	bool	m_bDeadSound;
	bool	m_bInfeSound;
	bool	m_bFireSound;
	DWORD	m_dwTest;
	DWORD	m_dwFire;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	void SetBossPos(void);
	void PlayerPosFind(void);
	bool Inferno(void);
	bool Dash(void);
	bool Fire(void);
public:
	CBoss(void);
	virtual ~CBoss(void);
};
