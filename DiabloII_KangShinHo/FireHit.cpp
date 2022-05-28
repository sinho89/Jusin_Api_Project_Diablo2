#include "StdAfx.h"
#include "FireHit.h"

CFireHit::CFireHit(void)
{
}

CFireHit::~CFireHit(void)
{
}

void CFireHit::Initialize( void )
{
	m_tInfo.fCX = 59.f;
	m_tInfo.fCY = 55.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
}

void CFireHit::Progress( void )
{
	FrameMove(12);

	if(m_iFrameX == 11)
		m_tInfo.bAlive = false;
}

void CFireHit::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"FireHit"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void CFireHit::Release( void )
{

}
