#pragma once
#include "field.h"

class CLogoBack :
	public CField
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CLogoBack(void);
	virtual ~CLogoBack(void);
};
