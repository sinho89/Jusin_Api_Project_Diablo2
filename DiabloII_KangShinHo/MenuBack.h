#pragma once
#include "field.h"

class CMenuBack :
	public CField
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CMenuBack(void);
	virtual ~CMenuBack(void);
};
