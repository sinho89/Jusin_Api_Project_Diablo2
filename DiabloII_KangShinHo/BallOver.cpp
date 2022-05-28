#include "StdAfx.h"
#include "BallOver.h"

CBallOver::CBallOver(void)
{
}

CBallOver::~CBallOver(void)
{
}
void CBallOver::Initialize( void )
{
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX;
	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f - 20.f;

	CSoundMgr::GetInstance()->SkillSound3(L"firecastb.wav");
	m_tInfo.fCX = 144.f;
	m_tInfo.fCY = 98.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
}

void CBallOver::Progress( void )
{
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX;
	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f - 20.f;
	FrameMove(21);
	if(m_iFrameX == 20)
		m_tInfo.bAlive = false;
}

void CBallOver::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"BallOver"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void CBallOver::Release( void )
{

}