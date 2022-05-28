#include "StdAfx.h"
#include "Intro.h"
#include "Factory.h"
#include "IntroBack.h"
#include "ObjMgr.h"
#include "ImgMgr.h"
#include "SceneMgr.h"

CIntro::CIntro(void)
{
}

CIntro::~CIntro(void)
{
	Release();
}

void CIntro::Initialize( void )
{
	CImgMgr::GetInstance()->AddTexture(L"../Resource/BackBuffer.bmp", L"BackBuffer", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Intro.bmp", L"IntroBack", m_hdc);

	CObjMgr::GetInstance()->AddObject(L"IntroBack", SORTID_FIRST, CFactory<CIntroBack>::CreateObject());
	CSoundMgr::GetInstance()->PlayBGMSound(L"Intro.wav");

}

void CIntro::Progress( void )
{

	if(CObjMgr::GetInstance()->GetInfo(L"IntroBack")->m_bStay == true)
	{
		CObjMgr::GetInstance()->GetInfo(L"IntroBack")->bAlive = false;
		CSceneMgr::GetInstance()->SetState(ST_LOGO);
		return;
	}

	CObjMgr::GetInstance()->Progress();
}

void CIntro::Render( void )
{
	CObjMgr::GetInstance()->Render();

	BitBlt(m_hdc, 0, 0, iWINCX, iWINCY, *CImgMgr::GetInstance()->GetTexture(L"BackBuffer")
		, 0, 0, SRCCOPY);
}

void CIntro::Release( void )
{
	CObjMgr::GetInstance()->Destroy();
}
