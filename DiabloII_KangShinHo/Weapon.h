#pragma once
#include "item.h"

class CWeapon :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CWeapon(void);
	CWeapon(float _fX, float _fY);
	virtual ~CWeapon(void);
};
