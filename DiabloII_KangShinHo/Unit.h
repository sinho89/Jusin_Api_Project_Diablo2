#pragma once
#include "obj.h"

class CUnit abstract:
	public CObj
{
protected:
	queue<int>		m_BestQueue;
	bool		m_bCanMove;
	bool		m_bMove;
	bool		m_bRun;
	bool		m_bSetHit;
	bool		m_bGetHit;
	bool		m_bHitCheck;
	bool		m_bTransForm;
	bool		m_bTransFormTick;
	bool		m_bDead;
	bool		m_bDeadCheck;
	bool		m_bMoveCheck;
	eDIRTECTION_TYPE	m_DIRTYPE;
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;

public:
	void DirectPos(void);
	void SetPos(void);
public:
	CUnit(void);
	virtual ~CUnit(void);
};
