#pragma once
#include "ui.h"

class CHpBall :
	public CUi
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CHpBall(void);
	virtual ~CHpBall(void);
};
