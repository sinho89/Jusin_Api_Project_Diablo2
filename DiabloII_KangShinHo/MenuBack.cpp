#include "StdAfx.h"
#include "MenuBack.h"

CMenuBack::CMenuBack(void)
{
}

CMenuBack::~CMenuBack(void)
{
}
void CMenuBack::Initialize( void )
{
	m_tInfo.fX = iWINCX / 2.f;
	m_tInfo.fY = iWINCY / 2.f;
	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 600.f;


	m_tInfo.iSortNum = 0;

}

void CMenuBack::Progress( void )
{

}

void CMenuBack::Render( void )
{
	BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 0, 0
		, int(m_tInfo.fCX), int(m_tInfo.fCY)
		,*CImgMgr::GetInstance()->GetTexture(L"MenuBack")
		, 0, 0, SRCCOPY);
}

void CMenuBack::Release( void )
{

}
