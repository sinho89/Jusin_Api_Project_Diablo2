#include "StdAfx.h"
#include "Loading.h"

CLoading::CLoading(void)
{
}

CLoading::~CLoading(void)
{
}
void CLoading::Initialize( void )
{
	m_tInfo.fX = iWINCX / 2.f;
	m_tInfo.fY = iWINCY / 2.f;

	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 600.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_dwTime = GetTickCount();

}

void CLoading::Progress( void )
{
	if(m_dwTime + 150 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		++m_iFrameX;
	}
	if(m_iFrameX == 11)
	{
		CSoundMgr::GetInstance()->EffectSound(L"portalenter.wav");
		m_tInfo.bAlive = false;
	}
}

void CLoading::Render( void )
{
	BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),0
		, 0
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY) 
		, *CImgMgr::GetInstance()->GetTexture(L"Loading"), m_iFrameX * m_tInfo.fCX
		, 0, SRCCOPY);

}

void CLoading::Release( void )
{

}
