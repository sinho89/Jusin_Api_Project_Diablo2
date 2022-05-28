#pragma once

#include "Defines.h"

class CKeyMgr
{
CREATE_SINGLETON(CKeyMgr);
private:
	DWORD	m_dwKey;



public:
	void SetKeyState(void);
	DWORD GetKeyState(void);

private:
	CKeyMgr(void);
public:
	~CKeyMgr(void);
};
