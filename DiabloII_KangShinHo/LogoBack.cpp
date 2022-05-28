#include "StdAfx.h"
#include "LogoBack.h"

CLogoBack::CLogoBack(void)
{
}

CLogoBack::~CLogoBack(void)
{
}

void CLogoBack::Initialize( void )
{
	m_tInfo.fX = iWINCX / 2.f;
	m_tInfo.fY = iWINCY / 2.f;
	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 600.f;

	m_tInfo.iSortNum = 0;
}

void CLogoBack::Progress( void )
{
	
}

void CLogoBack::Render( void )
{
	BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 0, 0
		, int(m_tInfo.fCX), int(m_tInfo.fCY)
		,*CImgMgr::GetInstance()->GetTexture(L"LogoBack")
		, 0, 0, SRCCOPY);
}

void CLogoBack::Release( void )
{

}

