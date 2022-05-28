#include "StdAfx.h"
#include "TileMgr.h"
#include "Armor.h"
#include "Mouse.h"

CArmor::CArmor(void)
{
	m_tInfo.fX = CTileMgr::GetInstance()->GetShopTile()[1 + iSHOPTILECNTX]->fX - iITEMTILESIZEX / 2;
	m_tInfo.fY = CTileMgr::GetInstance()->GetShopTile()[1 + iSHOPTILECNTY]->fY;
}

CArmor::CArmor( float _fX, float _fY )
{

	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;

}
CArmor::~CArmor(void)
{
}
void CArmor::Initialize( void )
{
	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 84.f;

	m_tInfo.iDef = 30.f;
	m_tInfo.iMoney = 500.f;
	m_tInfo.eType = IT_ARMOR;
	m_tInfo.cType = IST_TWO_BY_THREE;
	m_tInfo.bAlive = true;
}

void CArmor::Progress( void )
{
	POINT	ptMouse = CMouse::GetMousePos();

	if(m_tInfo.bClick == true)
	{
		m_tInfo.fX = float(ptMouse.x);
		m_tInfo.fY = float(ptMouse.y);
	}
}

void CArmor::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Armor"), 0
		, 0, int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 255, 255));
}

void CArmor::Release( void )
{

}
