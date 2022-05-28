#pragma once
#include "obj.h"
#include "Stage.h"

class CEffect :
	public CObj
{
protected:
	POINT	m_ptPoint;
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
public:
	CEffect(void);
	virtual ~CEffect(void);
};
