#pragma once
#include "item.h"

class CScroll :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CScroll(void);
	CScroll(float _fX, float _fY);
	virtual ~CScroll(void);
};
