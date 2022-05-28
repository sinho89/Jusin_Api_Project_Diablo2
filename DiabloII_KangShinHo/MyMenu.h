#pragma once
#include "scene.h"

class CMyMenu :
	public CScene
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CMyMenu(void);
	virtual ~CMyMenu(void);
};
