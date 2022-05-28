#pragma once
#include "field.h"

class CStageBack :
	public CField
{
private:
	DWORD	dwTime;
	bool	m_bMoveX;
	bool	m_bMoveY;
	bool	m_bTileView;
	bool	m_bShake;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CStageBack(void);
	virtual ~CStageBack(void);
};
