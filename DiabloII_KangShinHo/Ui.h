#pragma once
#include "obj.h"

class CUi abstract :
	public CObj 
{
protected:
	bool	m_bBuyItem;
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
public:
	CUi(void);
	virtual ~CUi(void);
};
