#pragma once
#include "item.h"

class CArmor :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CArmor(void);
	CArmor(float _fX, float _fY);
	virtual ~CArmor(void);
};
