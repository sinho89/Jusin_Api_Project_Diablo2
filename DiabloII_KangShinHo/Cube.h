#pragma once
#include "ui.h"

class CItem;
class CCube :
	public CUi
{
private:
	list<CItem*>		m_CubeList;
	bool				m_bPortal;
	bool				m_bOne;
	int					m_iCnt;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	list<CItem*>*	GetCube()
	{
		return &m_CubeList;
	}
public:
	CCube(void);
	virtual ~CCube(void);
};
