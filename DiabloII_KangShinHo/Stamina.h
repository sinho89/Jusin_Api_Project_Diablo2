#pragma once
#include "ui.h"

class CStamina :
	public CUi
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CStamina(void);
	virtual ~CStamina(void);
};
