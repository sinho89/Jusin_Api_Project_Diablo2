#pragma once
#include "unit.h"

class CPlayer :
	public CUnit
{
private:
	bool m_bStat;
	bool m_bCube;
	bool m_bRunPush;
	bool m_bSkillCheck;
	bool m_bHitTick;
	bool m_bSkillTick;
	bool m_bShake;
	bool m_bTor;
	bool m_bShock;

	DWORD	m_dwShake;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	void KeyCheck(void);
	void Moving(void);
	void Hit(void);
	void SkillCheck(void);
	void SetMotion(void);
public:
	CPlayer(void);
	virtual ~CPlayer(void);
};
