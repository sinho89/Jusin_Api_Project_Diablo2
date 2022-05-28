#include "StdAfx.h"
#include "AmaOver.h"

CAmaOver::CAmaOver(void)
{
}

CAmaOver::~CAmaOver(void)
{
}

void CAmaOver::Initialize( void )
{
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX;
	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY;
	
	CSoundMgr::GetInstance()->SkillSound2(L"firecasta.wav");
	m_tInfo.fCX = 131.f;
	m_tInfo.fCY = 160.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
}

void CAmaOver::Progress( void )
{
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX;
	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY;
	FrameMove(21);
	if(m_iFrameX == 20)
		m_tInfo.bAlive = false;
}

void CAmaOver::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"AmaOverlay"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void CAmaOver::Release( void )
{

}
