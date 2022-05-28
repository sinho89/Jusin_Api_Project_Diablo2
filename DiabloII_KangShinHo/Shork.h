#pragma once
#include "skill.h"

class CShork :
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
	CShork(void);
	CShork(float _fX, float _fY, eDIRTECTION_TYPE _eType);
	virtual ~CShork(void);
};
