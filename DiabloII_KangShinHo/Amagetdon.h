#pragma once
#include "skill.h"

class CAmagetdon :
	public CSkill
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CAmagetdon(void);
	virtual ~CAmagetdon(void);
};
