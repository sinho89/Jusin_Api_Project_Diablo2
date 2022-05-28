#include "StdAfx.h"
#include "AmaBoom.h"

CAmaBoom::CAmaBoom(void)
{
}

CAmaBoom::~CAmaBoom(void)
{
}

void CAmaBoom::Initialize( void )
{
	m_tInfo.fCX = 178.f;
	m_tInfo.fCY = 160.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;

	int iRand = rand () % 3;

	switch(iRand)
	{
	case 0:
		CSoundMgr::GetInstance()->ExploSound(L"explode1.wav");
		break;
	case 1:
		CSoundMgr::GetInstance()->ExploSound(L"explode2.wav");
		break;
	case 2:
		CSoundMgr::GetInstance()->ExploSound(L"explode3.wav");
		break;
	}

}

void CAmaBoom::Progress( void )
{
	FrameMove(20);
	if(m_iFrameX == 19)
		m_tInfo.bAlive = false;
}

void CAmaBoom::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"AmaBoom"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void CAmaBoom::Release( void )
{

}
