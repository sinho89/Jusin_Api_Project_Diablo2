#include "StdAfx.h"
#include "IntroBack.h"

CIntroBack::CIntroBack(void)
{
}

CIntroBack::~CIntroBack(void)
{
}

void CIntroBack::Initialize( void )
{
	m_tInfo.fX = iWINCX / 2.f;
	m_tInfo.fY = iWINCY / 2.f;
	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 600.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.m_bStay = false;
}

void CIntroBack::Progress( void )
{
	FrameIntroMove(166);

	if(m_iFrameX == 165 || GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		m_tInfo.m_bStay = true;
		m_tInfo.bAlive = false;
	}


}

void CIntroBack::Render( void )
{
	if(m_tInfo.m_bStay == false)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 0, 0
			, int(m_tInfo.fCX), int(m_tInfo.fCY)
			,*CImgMgr::GetInstance()->GetTexture(L"IntroBack")
			, m_iFrameX * m_tInfo.fCX, 0, SRCCOPY);

	}
}

void CIntroBack::Release( void )
{

}
