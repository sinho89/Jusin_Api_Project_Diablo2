#pragma once
#include "ui.h"

class CLogoButton :
	public CUi
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CLogoButton(void);
	virtual ~CLogoButton(void);
};
