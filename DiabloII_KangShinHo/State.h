#pragma once
#include "ui.h"

class CState :
	public CUi
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CState(void);
	virtual ~CState(void);
};
