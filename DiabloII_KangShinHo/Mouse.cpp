#include "StdAfx.h"
#include "Mouse.h"
#include "ImgMgr.h"

POINT	CMouse::m_ptMouse;

CMouse::CMouse()
{
	
}
CMouse::~CMouse()
{
}
void CMouse::SetMousePos(void)
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);
	ShowCursor(false);
}
POINT CMouse::GetMousePos(void)
{
	return m_ptMouse;
}
