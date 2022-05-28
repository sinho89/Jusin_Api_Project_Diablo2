#include "StdAfx.h"
#include "FireEnd.h"

CFireEnd::CFireEnd(void)
{
}

CFireEnd::CFireEnd(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}
CFireEnd::~CFireEnd(void)
{
}

void CFireEnd::Initialize( void )
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 81.f;

	m_iFrameY = 0;
	m_iFrameX = 0;

	m_tInfo.bAlive = true;
}

void CFireEnd::Progress( void )
{
	FrameMove(16);
	if(m_iFrameX == 15)
		m_tInfo.bAlive = false;
}

void CFireEnd::Render( void )
{

	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Fire_end"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void CFireEnd::Release( void )
{

}
