#include "StdAfx.h"
#include "HpBall.h"

CHpBall::CHpBall(void)
{
}

CHpBall::~CHpBall(void)
{
}
void CHpBall::Initialize( void )
{
	m_tInfo.fX = 70.f;
	m_tInfo.fY = 545.f;
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
	m_tInfo.m_UIType = UT_HPBALL;
}

void CHpBall::Progress( void )
{

}

void CHpBall::Render( void ) // º¸·ù
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + (CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp - CObjMgr::GetInstance()->GetInfo(L"Player")->iHp)
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY) - (CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp - CObjMgr::GetInstance()->GetInfo(L"Player")->iHp)
		, *CImgMgr::GetInstance()->GetTexture(L"HpBall"), int(m_iFrameX  * m_tInfo.fCX)
		, (CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp - CObjMgr::GetInstance()->GetInfo(L"Player")->iHp) , int(m_tInfo.fCX), int(m_tInfo.fCY) - (CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp - CObjMgr::GetInstance()->GetInfo(L"Player")->iHp) , RGB(255, 255, 255));
}

void CHpBall::Release( void )
{

}