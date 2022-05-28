#pragma once
#include "scene.h"

class CLogo :
	public CScene
{
private:
	bool	m_bIntro;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CLogo(void);
	virtual ~CLogo(void);
};
