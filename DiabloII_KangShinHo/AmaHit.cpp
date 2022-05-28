#include "StdAfx.h"
#include "AmaHit.h"

CAmaHit::CAmaHit(void)
{
}
CAmaHit::CAmaHit(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}
CAmaHit::~CAmaHit(void)
{
}
void CAmaHit::Initialize(void)
{
	m_tInfo.fCX = 208.f;
	m_tInfo.fCY = 174.f;
	
	m_iFrameX = 0;
	m_iFrameY = 0;
	m_tInfo.bAlive = true;

	m_dwTime = GetTickCount();
}

void CAmaHit::Progress(void)
{
	FrameMove(15);

	if(m_dwTime + 750 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		m_tInfo.bAlive = false;
	}
}

void CAmaHit::Render(void)
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"AmaHit"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void CAmaHit::Release(void)
{
}