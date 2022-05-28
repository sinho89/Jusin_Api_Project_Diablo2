#pragma once
#include "effect.h"

class CAmaRock :
	public CEffect
{
private:
	bool	m_bExpl;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CAmaRock(void);
	virtual ~CAmaRock(void);
};
