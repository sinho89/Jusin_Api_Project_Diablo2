#include "StdAfx.h"
#include "MyMenu.h"
#include "MenuBack.h"
#include "Mouse.h"
#include "SceneMgr.h"

CMyMenu::CMyMenu(void)
{
}

CMyMenu::~CMyMenu(void)
{
	Release();
}

void CMyMenu::Initialize( void )
{
	CImgMgr::GetInstance()->AddTexture(L"../Resource/BackBuffer.bmp", L"BackBuffer", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/MenuBack.bmp", L"MenuBack", m_hdc);

	CObjMgr::GetInstance()->AddObject(L"MenuBack", SORTID_FIRST, CFactory<CMenuBack>::CreateObject());



}

void CMyMenu::Progress( void )
{
	POINT ptMouse = CMouse::GetMousePos();

	RECT	rcPlay = {265, 290, 535, 320};
	RECT	rcEdit = {265, 400, 535, 430};
	RECT	rcExit = {265, 535, 535, 565};


	if(PtInRect(&rcPlay, ptMouse))
	{
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			CSceneMgr::GetInstance()->SetState(ST_STAGE);
			return;
		}
	}

	if(PtInRect(&rcEdit, ptMouse))
	{
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			CSceneMgr::GetInstance()->SetState(ST_EDIT);
			return;
		}
	}

	if(PtInRect(&rcExit, ptMouse))
	{
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			DestroyWindow(g_hWnd);
		}
	}
	CObjMgr::GetInstance()->Progress();
}

void CMyMenu::Render( void )
{
	CObjMgr::GetInstance()->Render();

	BitBlt(m_hdc, 0, 0, iWINCX, iWINCY, *CImgMgr::GetInstance()->GetTexture(L"BackBuffer")
		, 0, 0, SRCCOPY);
}

void CMyMenu::Release( void )
{
	CObjMgr::GetInstance()->Destroy();
}
