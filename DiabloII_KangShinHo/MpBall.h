#pragma once
#include "ui.h"

class CMpBall :
	public CUi
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CMpBall(void);
	virtual ~CMpBall(void);
};
