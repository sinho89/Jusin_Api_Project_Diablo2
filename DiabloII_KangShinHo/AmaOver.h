#pragma once
#include "effect.h"

class CAmaOver :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CAmaOver(void);
	virtual ~CAmaOver(void);
};
