#include "StdAfx.h"
#include "Scroll.h"
#include "TileMgr.h"
#include "Mouse.h"

CScroll::CScroll(void)
{
	m_tInfo.fX = CTileMgr::GetInstance()->GetShopTile()[99]->fX;
	m_tInfo.fY = CTileMgr::GetInstance()->GetShopTile()[99]->fY;
}

CScroll::CScroll( float _fX, float _fY )
{

	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;

}

CScroll::~CScroll(void)
{
}
void CScroll::Initialize( void )
{
	m_tInfo.fCX = 28.f;
	m_tInfo.fCY = 28.f;

	m_tInfo.iMoney = 75.f;
	m_tInfo.eType = IT_SCROLL;
	m_tInfo.cType = IST_ONE_BY_ONE;
	m_tInfo.bClick = false;
	m_tInfo.bAlive = true;
}

void CScroll::Progress( void )
{
	POINT	ptMouse = CMouse::GetMousePos();

	if(m_tInfo.bClick == true)
	{
		m_tInfo.fX = float(ptMouse.x);
		m_tInfo.fY = float(ptMouse.y);
	}
}

void CScroll::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Scroll"), 0
		, 0, int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 255, 255));
}

void CScroll::Release( void )
{

}