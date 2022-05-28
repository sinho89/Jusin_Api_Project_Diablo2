#pragma once
#include "unit.h"

class CNpc :
	public CUnit
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CNpc(void);
	virtual ~CNpc(void);
};
