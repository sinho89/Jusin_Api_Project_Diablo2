#pragma once
#include "scene.h"

class CIntro :
	public CScene
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CIntro(void);
	virtual ~CIntro(void);
};
