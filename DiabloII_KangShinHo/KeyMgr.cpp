#include "StdAfx.h"
#include "KeyMgr.h"

INIT_SINGLETON(CKeyMgr);

CKeyMgr::CKeyMgr(void)
:m_dwKey(0)
{
}

CKeyMgr::~CKeyMgr(void)
{
}

void CKeyMgr::SetKeyState(void)
{

	m_dwKey = 0;


	if( GetAsyncKeyState(VK_RBUTTON) )
	{
		m_dwKey |= KEY_RBUTTON;
	}

	if( GetAsyncKeyState(VK_SHIFT) )
	{
		m_dwKey |= KEY_SHIFT;
	}

	if( GetAsyncKeyState('I') )
	{
		m_dwKey |= KEY_I;
	}

	if( GetAsyncKeyState('C') )
	{
		m_dwKey |= KEY_C;
	}

	if( GetAsyncKeyState('K') )
	{
		m_dwKey |= KEY_K;
	}
}

DWORD CKeyMgr::GetKeyState(void)
{
	return m_dwKey;
}
