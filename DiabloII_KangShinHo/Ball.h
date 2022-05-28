#pragma once
#include "skill.h"

class CBall :
	public CSkill
{
private:
	eDIRTECTION_TYPE m_eType;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CBall(void);
	CBall(float _fX, float _fY, eDIRTECTION_TYPE _eType);
	virtual ~CBall(void);
};
