#pragma once

#include "Defines.h"

class CScene;
class CSceneMgr
{
CREATE_SINGLETON(CSceneMgr);
private:
	CScene*		m_pScene;
public:
	void SetState(eSCENE_TYPE	_eType);
	void Progress(void);
	void Render(void);
	void Release(void);
private:
	CSceneMgr(void);
public:
	~CSceneMgr(void);
};
