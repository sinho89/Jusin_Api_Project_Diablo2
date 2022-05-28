#include "StdAfx.h"
#include "Fire.h"
#include "FireHit.h"

CFire::CFire(void)
{
}
CFire::CFire(float _fX, float _fY, float _fAngle)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_tInfo.fAngle = _fAngle;
}
CFire::~CFire(void)
{
}
void CFire::Initialize( void )
{
	m_tInfo.fCX = 66.f;
	m_tInfo.fCY = 167.f;
	m_tInfo.fSpeed = 7.f;

	m_iFrameX = 0;
	m_iFrameY = 0;
	m_tInfo.bAlive = true;

	m_dwCool = GetTickCount();
	m_bCheck = false;

	CSoundMgr::GetInstance()->MonsterSound1(L"volcano.wav");
}

void CFire::Progress( void )
{

	m_tInfo.fX += m_tInfo.fSpeed * cosf(m_tInfo.fAngle);
	m_tInfo.fY -= m_tInfo.fSpeed * sinf(m_tInfo.fAngle);

	float fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - m_tInfo.fX;								
	float fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY- m_tInfo.fY;

	float fDist = sqrt((fX * fX) + (fY * fY));							

	if(fDist < 50)
	{
		if(m_bCheck == true)
			return;
		m_bCheck = true;
		CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 0.5;
		CObjMgr::GetInstance()->AddObject(L"FireHit", SORTID_SKILL, CFactory<CFireHit>::CreateObject(CObjMgr::GetInstance()->GetInfo(L"Player")->fX, CObjMgr::GetInstance()->GetInfo(L"Player")->fY));
	}


	FrameMove(37);

	if(m_dwCool + 2000 < GetTickCount())
	{
		m_dwCool = GetTickCount();
		m_tInfo.bAlive = false;
	}
}

void CFire::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Fire"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void CFire::Release( void )
{

}