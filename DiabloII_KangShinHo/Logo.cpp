#include "StdAfx.h"
#include "Logo.h"
#include "LogoBack.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "MouseRnd.h"

CLogo::CLogo(void)
:m_bIntro(false)
{
}

CLogo::~CLogo(void)
{
	Release();
}

void CLogo::Initialize( void )
{
	CImgMgr::GetInstance()->AddTexture(L"../Resource/BackBuffer.bmp", L"BackBuffer", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/LogoBack.bmp", L"LogoBack", m_hdc);
	
	CObjMgr::GetInstance()->AddObject(L"LogoBack", SORTID_FIRST, CFactory<CLogoBack>::CreateObject());
}

void CLogo::Progress( void )
{
	
	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		CSceneMgr::GetInstance()->SetState(ST_MENU);
		return;
	}
	
	CObjMgr::GetInstance()->Progress();
}

void CLogo::Render( void )
{
	
	CObjMgr::GetInstance()->Render();
	BitBlt(m_hdc, 0, 0, iWINCX, iWINCY, *CImgMgr::GetInstance()->GetTexture(L"BackBuffer")
		, 0, 0, SRCCOPY);
}

void CLogo::Release( void )
{
	CObjMgr::GetInstance()->Destroy();
}
