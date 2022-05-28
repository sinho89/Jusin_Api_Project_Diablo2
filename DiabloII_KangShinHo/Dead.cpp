#include "StdAfx.h"
#include "Dead.h"

CDead::CDead(void)
{
}
CDead::CDead(float _fX, float _fY, eDIRTECTION_TYPE _eType)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_DIRTYPE = _eType;
}
CDead::~CDead(void)
{
}
void CDead::Initialize( void )
{
	m_tInfo.fCX = 145.f;
	m_tInfo.fCY = 92.8f;

	m_iFrameX = 0;

	m_tInfo.bAlive = true;


	if(m_DIRTYPE == DIR_DOWN)
		m_iFrameY = 0;
	if(m_DIRTYPE == DIR_DOWN_L)
		m_iFrameY = 1;
	if(m_DIRTYPE == DIR_LEFT)
		m_iFrameY = 2;
	if(m_DIRTYPE == DIR_UP_L)
		m_iFrameY = 3;
	if(m_DIRTYPE == DIR_UP)
		m_iFrameY = 4;
	if(m_DIRTYPE == DIR_UP_R)
		m_iFrameY = 5;
	if(m_DIRTYPE == DIR_RIGHT)
		m_iFrameY = 6;
	if(m_DIRTYPE == DIR_DOWN_R)
		m_iFrameY = 7;
}

void CDead::Progress( void )
{

}

void CDead::Render( void )
{
	if(CScene::m_bBattle == true)
	{
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Cow_Dead2"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(170, 170, 170));
	}
}

void CDead::Release( void )
{

}