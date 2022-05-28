#include "StdAfx.h"
#include "Potion.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"

CPotion::CPotion(void)
{

	m_tInfo.fX = CTileMgr::GetInstance()->GetShopTile()[98]->fX;
	m_tInfo.fY = CTileMgr::GetInstance()->GetShopTile()[98]->fY;
}

CPotion::CPotion( float _fX, float _fY )
{

	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	
}

CPotion::~CPotion(void)
{
}
void CPotion::Initialize( void )
{
	m_tInfo.fCX = 28.f;
	m_tInfo.fCY = 28.f;

	m_tInfo.iMoney = 50.f;
	m_tInfo.eType = IT_POTION;
	m_tInfo.cType = IST_ONE_BY_ONE;
	m_tInfo.bClick = false;
	m_tInfo.bAlive = true;

}

void CPotion::Progress( void )
{
	POINT	ptMouse = CMouse::GetMousePos();

	if(m_tInfo.bClick == true)
	{
		m_tInfo.fX = float(ptMouse.x);
		m_tInfo.fY = float(ptMouse.y);
	}
		
}

void CPotion::Render( void )
{

	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Potion"), 0
		, 0, int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 255, 255));

}

void CPotion::Release( void )
{

}
