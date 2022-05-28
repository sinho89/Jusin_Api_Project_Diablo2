#include "StdAfx.h"
#include "Weapon.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "Mouse.h"

CWeapon::CWeapon(void)
{
	m_tInfo.fX = CTileMgr::GetInstance()->GetShopTile()[3 + iSHOPTILECNTX]->fX - iITEMTILESIZEX / 2;
	m_tInfo.fY = CTileMgr::GetInstance()->GetShopTile()[3 + iSHOPTILECNTY]->fY;
}

CWeapon::CWeapon( float _fX, float _fY )
{

}

CWeapon::~CWeapon(void)
{
}
void CWeapon::Initialize( void )
{
	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 84.f;

	m_tInfo.iAtt = 30.f;
	m_tInfo.iMoney = 500.f;

	m_tInfo.eType = IT_WEAPON;
	m_tInfo.cType = IST_TWO_BY_THREE;
	m_tInfo.bAlive = true;
}

void CWeapon::Progress( void )
{
	POINT	ptMouse = CMouse::GetMousePos();

	if(m_tInfo.bClick == true)
	{
		m_tInfo.fX = float(ptMouse.x);
		m_tInfo.fY = float(ptMouse.y);
	}
}

void CWeapon::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Weapon"), 0
		, 0, int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 255, 255));
}

void CWeapon::Release( void )
{

}
