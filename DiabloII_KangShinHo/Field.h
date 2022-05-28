#pragma once
#include "obj.h"

class CField abstract:
	public CObj
{
protected:
	POINT	m_ptScroll;
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;

public:
	CField(void);
	virtual ~CField(void);
};
