#pragma once
#include "item.h"

class CPotion :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CPotion(void);
	CPotion(float _fX, float _fY);
	virtual ~CPotion(void);
};
