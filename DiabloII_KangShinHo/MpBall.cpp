#include "StdAfx.h"
#include "MpBall.h"

CMpBall::CMpBall(void)
{
}

CMpBall::~CMpBall(void)
{
}
void CMpBall::Initialize( void )
{
	m_tInfo.fX = 730.f;
	m_tInfo.fY = 545.f;
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
}

void CMpBall::Progress( void )
{

}

void CMpBall::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + (CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp - CObjMgr::GetInstance()->GetInfo(L"Player")->iMp)
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY) - (CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp - CObjMgr::GetInstance()->GetInfo(L"Player")->iMp)
		, *CImgMgr::GetInstance()->GetTexture(L"MpBall"), int(m_iFrameX  * m_tInfo.fCX)
		, (CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp - CObjMgr::GetInstance()->GetInfo(L"Player")->iMp), int(m_tInfo.fCX), int(m_tInfo.fCY) - (CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp - CObjMgr::GetInstance()->GetInfo(L"Player")->iMp), RGB(255, 255, 255));

}

void CMpBall::Release( void )
{

}