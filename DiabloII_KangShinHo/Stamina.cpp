#include "StdAfx.h"
#include "Stamina.h"

CStamina::CStamina(void)
{
}

CStamina::~CStamina(void)
{
}

void CStamina::Initialize( void )
{
	m_tInfo.fX = 323.5f;
	m_tInfo.fY = 582.f;
	m_tInfo.fCX = 103.f;
	m_tInfo.fCY = 18.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;

}

void CStamina::Progress( void )
{
	
}

void CStamina::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		, int(m_tInfo.fCX) * CObjMgr::GetInstance()->GetInfo(L"Player")->iStamina / CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxStamina 
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Stamina"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 255, 255));
}

void CStamina::Release( void )
{

}