#pragma once
#include "skill.h"

class CHurricane :
	public CSkill
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CHurricane(void);
	virtual ~CHurricane(void);
};
