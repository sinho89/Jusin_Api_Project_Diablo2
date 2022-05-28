#pragma once
#include "obj.h"

class CSkill :
	public CObj
{
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
public:
	CSkill(void);
	virtual ~CSkill(void);
};
