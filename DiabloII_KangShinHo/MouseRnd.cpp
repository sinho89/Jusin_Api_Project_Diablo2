#include "StdAfx.h"
#include "MouseRnd.h"
#include "Mouse.h"

CMouseRnd::CMouseRnd(void)
{
}

CMouseRnd::~CMouseRnd(void)
{
}
void CMouseRnd::Initialize( void )
{
	m_tInfo.fCX = 31.f;
	m_tInfo.fCY = 27.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

}

void CMouseRnd::Progress( void )
{
	m_tInfo.fX = float(CMouse::GetMousePos().x) + 15;
	m_tInfo.fY = float(CMouse::GetMousePos().y) + 15;
}

void CMouseRnd::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Mouse"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 255, 255));

}

void CMouseRnd::Release( void )
{
	
}
