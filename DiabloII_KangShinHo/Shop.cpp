#include "StdAfx.h"
#include "Shop.h"
#include "Item.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Scroll.h"
#include "Mouse.h"
#include "Inven.h"
#include "CollMgr.h"



CShop::CShop(void)
{
}

CShop::~CShop(void)
{
	Release();
}

void CShop::Initialize( void )
{
	m_tInfo.fX = iWINCX / 4.f;
	m_tInfo.fY = iWINCY / 2.f - 30;
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 552.f;

	m_tInfo.bAlive = true;
	m_tInfo.m_UIType = UT_SHOP;

	m_tInfo.iSortNum = 3;
	m_iFrameX = 0;
	m_iFrameY = 0;

	CTileMgr::GetInstance()->SetShopTile();

	m_ShopList.push_back(((CItem*)CFactory<CWeapon>::CreateObject()));
	m_ShopList.push_back(((CItem*)CFactory<CArmor>::CreateObject()));
	m_ShopList.push_back(((CItem*)CFactory<CPotion>::CreateObject()));
	m_ShopList.push_back(((CItem*)CFactory<CScroll>::CreateObject()));
	

	m_bPush = true;

}

void CShop::Progress( void )
{
	CCollMgr::GetInstance()->ShopItemColl(&m_ShopList);
	
	list<CItem*>::iterator iter = m_ShopList.begin();
	list<CItem*>::iterator iter_end = m_ShopList.end();

	for(iter; iter != iter_end;)
	{
		if((*iter)->GetInfo().bAlive == false)
		{
			safe_delete((*iter));
			iter = m_ShopList.erase(iter);
		}
		else
		{
			(*iter)->Progress();
			++iter;
		}
	}
}

void CShop::Render( void )
{
	if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bShopRender == true)
	{

		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Store"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 255, 0));
		
		list<CItem*>::iterator iter = m_ShopList.begin();
		list<CItem*>::iterator iter_end = m_ShopList.end();

		for(iter; iter != iter_end; ++iter)
			(*iter)->Render();
		
	}
}

void CShop::Release( void )
{
	CTileMgr::GetInstance()->DeleteShopTile();

	list<CItem*>::iterator iter = m_ShopList.begin();
	list<CItem*>::iterator iter_end = m_ShopList.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);

	m_ShopList.clear();
}
