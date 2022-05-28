#pragma once
#include "Scene.h"

class CMyEdit :
	public CScene
{
private:
	bool	m_bPush;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CMyEdit(void);
	virtual ~CMyEdit(void);
};
