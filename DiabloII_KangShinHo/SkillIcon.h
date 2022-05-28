#pragma once
#include "ui.h"

class CSkillIcon :
	public CUi
{
private:
	eSKILL_TYPE		m_eType;
	bool			m_bView;
	bool			m_bClick;
	bool			m_SelectTick;
	bool			m_bSet;
	bool			m_bSet1;
	bool			m_bSet2;
	bool			m_bSet3;
	bool			m_bSet4;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CSkillIcon(void);
	virtual ~CSkillIcon(void);
};
