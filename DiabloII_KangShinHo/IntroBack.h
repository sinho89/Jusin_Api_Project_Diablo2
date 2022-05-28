#pragma once
#include "field.h"

class CIntroBack :
	public CField
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CIntroBack(void);
	virtual ~CIntroBack(void);
};
