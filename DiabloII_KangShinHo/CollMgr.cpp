#include "StdAfx.h"
#include "CollMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Inven.h"
#include "Factory.h"

INIT_SINGLETON(CCollMgr);
bool CCollMgr::m_bShopPush = false;
bool CCollMgr::m_bInvenPush = false;
bool CCollMgr::m_bInvenPush2 = false;
bool CCollMgr::m_bPotionPush = false;
bool CCollMgr::m_bWeaponPush = false;
bool CCollMgr::m_bArmorPush = false;
bool CCollMgr::m_bEquiPush = false;
bool CCollMgr::m_bSell = false;
bool CCollMgr::m_bBuy = false;
bool CCollMgr::m_bUsePush = false;
bool CCollMgr::m_bCubePush = false;
CItem* CCollMgr::pItem = NULL;



CCollMgr::CCollMgr(void)
{
}

CCollMgr::~CCollMgr(void)
{
}

void CCollMgr::RectAndDoteColl(INFO* _pDest, INFO* _pSource)
{


}
void CCollMgr::NormalColl(INFO* _pDest, INFO* _pSource)
{

}

void CCollMgr::ShopItemToTile(list<CItem*>* _pItem)
{
	
}

void CCollMgr::InvenItemToTile(list<CItem*>* _pItem)
{
	for(int i = 0; i < iINVENTILECNTY; ++i)
	{
		for(int j = 0; j < iINVENTILECNTX; ++j)
		{
			int iIndex = j + i * iINVENTILECNTX; 
			CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
		}
	}

	list<CItem*>::iterator iter = _pItem->begin();
	list<CItem*>::iterator iter_end = _pItem->end();
	RECT	rcTemp;

	for(iter; iter != iter_end; ++iter)
	{
		RECT	rcItem = {long((*iter)->GetInfo().fX - (*iter)->GetInfo().fCX / 2.f)
			, long((*iter)->GetInfo().fY - (*iter)->GetInfo().fCY / 2.f)
			, long((*iter)->GetInfo().fX + (*iter)->GetInfo().fCX / 2.f)
			, long((*iter)->GetInfo().fY + (*iter)->GetInfo().fCY / 2.f)};

		for(int i = 0; i < iINVENTILECNTY; ++i)
		{
			for(int j = 0; j < iINVENTILECNTX; ++j)
			{
				int iIndex = j + i * iINVENTILECNTX; 

				RECT	rcInven = {long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)};

				if(IntersectRect(&rcTemp, &rcItem, &rcInven))
				{
					CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
					CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = (*iter)->GetInfo().eType;
					CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = (*iter)->GetInfo().cType;
				}
			}
		}
	}
}
void CCollMgr::ShopItemColl(list<CItem*>* _pShop)
{
	list<CItem*>::iterator Shop_iter = _pShop->begin();
	list<CItem*>::iterator Shop_iter_end = _pShop->end();

	POINT	ptMouse = CMouse::GetMousePos();

	RECT	rcShop = {long(CTileMgr::GetInstance()->GetShopTile()[0]->fX
		- CTileMgr::GetInstance()->GetShopTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetShopTile()[0]->fY
		- CTileMgr::GetInstance()->GetShopTile()[0]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetShopTile()[iSHOPMAX - 1]->fX
		+ CTileMgr::GetInstance()->GetShopTile()[iSHOPMAX - 1]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetShopTile()[iSHOPMAX - 1]->fY
		+ CTileMgr::GetInstance()->GetShopTile()[iSHOPMAX - 1]->fCY / 2.f)};


	if(PtInRect(&rcShop, ptMouse) && CObjMgr::GetInstance()->GetRender(L"Player")->m_bShopRender == true && CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true)
	{

		if((GetAsyncKeyState(VK_LBUTTON) & 0x8000) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000)) 
		{
			if(CCollMgr::m_bShopPush == true)
				return;
			CCollMgr::m_bShopPush = true;

			int		iShopIndex = int((ptMouse.y - 76) / iITEMTILESIZEY) * iSHOPTILECNTX + int((ptMouse.x - 22) / iITEMTILESIZEX);

			if(iShopIndex < 0 || 99 < iShopIndex)
				return;


			for(Shop_iter; Shop_iter != Shop_iter_end; ++Shop_iter)
			{

				RECT	rcTile = {long(CTileMgr::GetInstance()->GetShopTile()[iShopIndex]->fX - CTileMgr::GetInstance()->GetShopTile()[iShopIndex]->fCX / 2.f)
					, long(CTileMgr::GetInstance()->GetShopTile()[iShopIndex]->fY - CTileMgr::GetInstance()->GetShopTile()[iShopIndex]->fCY / 2.f)
					, long(CTileMgr::GetInstance()->GetShopTile()[iShopIndex]->fX + CTileMgr::GetInstance()->GetShopTile()[iShopIndex]->fCX / 2.f)
					, long(CTileMgr::GetInstance()->GetShopTile()[iShopIndex]->fY + CTileMgr::GetInstance()->GetShopTile()[iShopIndex]->fCY / 2.f)};

				RECT	rcItem = {long((*Shop_iter)->GetInfo().fX - (*Shop_iter)->GetInfo().fCX / 2.f)
					, long((*Shop_iter)->GetInfo().fY - (*Shop_iter)->GetInfo().fCY / 2.f)
					, long((*Shop_iter)->GetInfo().fX + (*Shop_iter)->GetInfo().fCX / 2.f)
					, long((*Shop_iter)->GetInfo().fY + (*Shop_iter)->GetInfo().fCY / 2.f)};


				if(PtInRect(&rcTile, ptMouse) && PtInRect(&rcItem, ptMouse) && pItem == NULL) // 우클릭 정렬 구매
				{
					for(int i = 0; i < iINVENTILECNTY; ++i)
					{
						for(int j = 0; j < iINVENTILECNTX; ++j)
						{
							int iIndex = j + i * iINVENTILECNTX; 

							RECT	rcShop = {long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
								, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)
								, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
								, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)};

							if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck != true)
							{
								if((*Shop_iter)->GetInfo().eType == IT_POTION)
								{
									CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney -= (*Shop_iter)->GetInfo().iMoney;
									CSoundMgr::GetInstance()->ItemSound(L"potionui.wav");
									for(int i = 0; i < 4; ++i)
									{
										if(CTileMgr::GetInstance()->GetPotionTile()[i]->m_bCheck != true)
										{
											CItem*	pItem = new CPotion;
											memcpy(pItem, (*Shop_iter), sizeof(CPotion));
											pItem->GetInfo().fX = CTileMgr::GetInstance()->GetPotionTile()[i]->fX;
											pItem->GetInfo().fY = CTileMgr::GetInstance()->GetPotionTile()[i]->fY;
											CTileMgr::GetInstance()->GetPotionTile()[i]->m_bCheck = true;
											CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->push_back(pItem);
											return;
										}
									}
									CItem*	pItem = new CPotion;
									memcpy(pItem, (*Shop_iter), sizeof(CPotion));
									pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
									pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
									CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
									CObjMgr::GetInstance()->GetInvenList(L"Inven")->push_back(pItem);
									return;
								}
								if((*Shop_iter)->GetInfo().eType == IT_SCROLL)
								{
									CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney -= (*Shop_iter)->GetInfo().iMoney;
									CSoundMgr::GetInstance()->ItemSound(L"scroll.wav");
									CItem*	pItem = new CScroll;
									memcpy(pItem, (*Shop_iter), sizeof(CScroll));
									pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
									pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
									CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
									CObjMgr::GetInstance()->GetInvenList(L"Inven")->push_back(pItem);
									return;

								}
								if((*Shop_iter)->GetInfo().eType == IT_WEAPON)
								{
									if((iIndex + 1) % 10 == 0)
									{
										iIndex += 1;
									}
									if(iIndex >= 20)
										return;
									
									if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck != true
										&& CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck != true
										&& CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck != true
										&& CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck != true
										&& CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck != true)
									{

										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney -= (*Shop_iter)->GetInfo().iMoney;
										RECT	rcWeapon = {long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX
											- CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
											, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY
											- CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)
											, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fX
											+ CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fCX / 2.f)
											, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fY
											+ CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fCY / 2.f)};

										CItem*	pItem = new CWeapon;
										memcpy(pItem, (*Shop_iter), sizeof(CWeapon));
										pItem->GetInfo().fX = ((rcWeapon.right - rcWeapon.left) / 2.f) + rcWeapon.left;
										pItem->GetInfo().fY = ((rcWeapon.bottom - rcWeapon.top) / 2.f) + rcWeapon.top;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										CObjMgr::GetInstance()->GetInvenList(L"Inven")->push_back(pItem);
										(*Shop_iter)->GetInfo().bAlive = false;
										return;

									}
								}
								if((*Shop_iter)->GetInfo().eType == IT_ARMOR)
								{
									if((iIndex + 1) % 10 == 0)
									{
										iIndex += 1;
									}
									if(iIndex >= 20)
										return;


									if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck != true
										&& CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck != true
										&& CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck != true
										&& CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck != true
										&& CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck != true)
									{
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");

										CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney -= (*Shop_iter)->GetInfo().iMoney;
										RECT	rcArmor = {long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX
											- CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
											, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY
											- CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)
											, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fX
											+ CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fCX / 2.f)
											, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fY
											+ CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fCY / 2.f)};

										CItem*	pItem = new CArmor;
										memcpy(pItem, (*Shop_iter), sizeof(CArmor));
										pItem->GetInfo().fX = ((rcArmor.right - rcArmor.left) / 2.f) + rcArmor.left;
										pItem->GetInfo().fY = ((rcArmor.bottom - rcArmor.top) / 2.f) + rcArmor.top;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;
										CObjMgr::GetInstance()->GetInvenList(L"Inven")->push_back(pItem);
										(*Shop_iter)->GetInfo().bAlive = false;
										return;
									}
								}
							}
						}
					}
				}
				if(PtInRect(&rcTile, ptMouse) && pItem != NULL) // 판매
				{
					for(int i = 0; i < iSHOPTILECNTY; ++i)
					{
						for(int j = 0; j < iSHOPTILECNTX; ++j)
						{
							int iIndex = j + i * iSHOPTILECNTX; 

							RECT	rcShop = {long(CTileMgr::GetInstance()->GetShopTile()[iIndex]->fX - CTileMgr::GetInstance()->GetShopTile()[iIndex]->fCX / 2.f)
								, long(CTileMgr::GetInstance()->GetShopTile()[iIndex]->fY - CTileMgr::GetInstance()->GetShopTile()[iIndex]->fCY / 2.f)
								, long(CTileMgr::GetInstance()->GetShopTile()[iIndex]->fX + CTileMgr::GetInstance()->GetShopTile()[iIndex]->fCX / 2.f)
								, long(CTileMgr::GetInstance()->GetShopTile()[iIndex]->fY + CTileMgr::GetInstance()->GetShopTile()[iIndex]->fCY / 2.f)};

							if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck != true)
							{
								CSoundMgr::GetInstance()->ItemSound(L"gold.wav");

								if(pItem->GetInfo().eType == IT_POTION)
								{
									CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney += pItem->GetInfo().iMoney;
									pItem->GetInfo().bAlive = false;
									pItem = NULL;
									return;
								}
								if(pItem->GetInfo().eType == IT_SCROLL)
								{
									CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney += pItem->GetInfo().iMoney;
									pItem->GetInfo().bAlive = false;
									pItem = NULL;
									return;
								}
								if(pItem->GetInfo().eType == IT_WEAPON)
								{
									CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney += pItem->GetInfo().iMoney;
									pItem->GetInfo().bAlive = false;
									pItem = NULL;

									_pShop->push_back(((CItem*)CFactory<CWeapon>::CreateObject()));
									return;
								}
								if(pItem->GetInfo().eType == IT_ARMOR)
								{
									CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney += pItem->GetInfo().iMoney;
									pItem->GetInfo().bAlive = false;
									pItem = NULL;

									_pShop->push_back(((CItem*)CFactory<CArmor>::CreateObject()));
									return;
								}
							}
						}
					}
				}
			}
		}
		else
			CCollMgr::m_bShopPush = false;
	}	
}
void CCollMgr::CubeItemColl(list<CItem*>* _pCube)
{
	list<CItem*>::iterator Cube_iter = _pCube->begin();
	list<CItem*>::iterator Cube_iter_end = _pCube->end();

	list<CItem*>::iterator Inven_iter = CObjMgr::GetInstance()->GetInvenList(L"Inven")->begin();
	list<CItem*>::iterator Inven_iter_end = CObjMgr::GetInstance()->GetInvenList(L"Inven")->end();

	POINT	ptMouse = CMouse::GetMousePos();

	RECT	rcCube= {long(CTileMgr::GetInstance()->GetCubeTile()[0]->fX
		- CTileMgr::GetInstance()->GetCubeTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetCubeTile()[0]->fY
		- CTileMgr::GetInstance()->GetCubeTile()[0]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetCubeTile()[iCUBEMAX - 1]->fX
		+ CTileMgr::GetInstance()->GetCubeTile()[iCUBEMAX - 1]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetCubeTile()[iCUBEMAX - 1]->fY
		+ CTileMgr::GetInstance()->GetCubeTile()[iCUBEMAX - 1]->fCY / 2.f)};

	if(PtInRect(&rcCube, ptMouse) && CObjMgr::GetInstance()->GetRender(L"Player")->m_bCubeRender == true)
	{
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if(CCollMgr::m_bCubePush == true)
				return;

			CCollMgr::m_bCubePush = true;

			int		iCubeIndex = int((ptMouse.y - 172) / iITEMTILESIZEY) * iCUBETILECNTX + int((ptMouse.x - 148) / iITEMTILESIZEX);


			if(iCubeIndex < 0 || 11 < iCubeIndex)
				return;

			RECT	rcTile = {long(CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fX - CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fY - CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fCY / 2.f)
				, long(CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fX + CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fY + CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fCY / 2.f)};

			if(PtInRect(&rcTile, ptMouse) && pItem == NULL && CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->m_bCheck == true) // 아이템 집기
			{
				for(Cube_iter; Cube_iter != Cube_iter_end; ++Cube_iter)
				{
					CSoundMgr::GetInstance()->ItemSound(L"pickup.wav");
					RECT	rcTile = {long(CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fX - CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fCX / 2.f)
						, long(CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fY - CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fCY / 2.f)
						, long(CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fX + CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fCX / 2.f)
						, long(CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fY + CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fCY / 2.f)};

					RECT	rcItem = {long((*Cube_iter)->GetInfo().fX - (*Cube_iter)->GetInfo().fCX / 2.f)
						, long((*Cube_iter)->GetInfo().fY - (*Cube_iter)->GetInfo().fCY / 2.f)
						, long((*Cube_iter)->GetInfo().fX + (*Cube_iter)->GetInfo().fCX / 2.f)
						, long((*Cube_iter)->GetInfo().fY + (*Cube_iter)->GetInfo().fCY / 2.f)};

					if(PtInRect(&rcTile, ptMouse) && PtInRect(&rcItem, ptMouse) && pItem == NULL)
					{
						if((*Cube_iter)->GetInfo().eType == IT_SCROLL)
						{
							pItem =  (*Cube_iter);
							pItem->GetInfo().bClick = true;
							CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->m_bCheck = false;
							CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->eType = IT_END;
							CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->cType = IST_END;
							return;
						}
					}
				}
			}
			else if(PtInRect(&rcTile, ptMouse) && pItem != NULL && CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->m_bCheck == false) // 아이템 넣기
			{
				if(pItem->GetInfo().eType == IT_SCROLL) 
				{
					CSoundMgr::GetInstance()->ItemSound(L"scroll.wav");
					pItem->GetInfo().bClick = false;
					pItem->GetInfo().fX = CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fX;
					pItem->GetInfo().fY = CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->fY;
					CTileMgr::GetInstance()->GetCubeTile()[iCubeIndex]->m_bCheck = true;
					CItem*	_pItem = new CScroll;
					memcpy(_pItem, pItem, sizeof(CScroll));
					_pCube->push_back(_pItem);
					pItem->GetInfo().bAlive = false;
					pItem = NULL;
					return;

				}
			}
		}
		else
			CCollMgr::m_bCubePush = false;
	}

	
}

void CCollMgr::EquiItemColl(list<CItem*>* _pEqui, list<CItem*>* _pInven)
{

	list<CItem*>::iterator Equi_iter = _pEqui->begin();
	list<CItem*>::iterator Equi_iter_end = _pEqui->end();

	list<CItem*>::iterator Inven_iter = _pInven->begin();
	list<CItem*>::iterator Inven_iter_end = _pInven->end();

	POINT	ptMouse = CMouse::GetMousePos();

	RECT	rcWeapon= {long(CTileMgr::GetInstance()->GetEquiTile()[0]->fX
		- CTileMgr::GetInstance()->GetEquiTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetEquiTile()[0]->fY
		- CTileMgr::GetInstance()->GetEquiTile()[0]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetEquiTile()[0]->fX
		+ CTileMgr::GetInstance()->GetEquiTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetEquiTile()[0]->fY
		+ CTileMgr::GetInstance()->GetEquiTile()[0]->fCY / 2.f)};

	RECT	rcArmor= {long(CTileMgr::GetInstance()->GetEquiTile()[1]->fX
		- CTileMgr::GetInstance()->GetEquiTile()[1]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetEquiTile()[1]->fY
		- CTileMgr::GetInstance()->GetEquiTile()[1]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetEquiTile()[1]->fX
		+ CTileMgr::GetInstance()->GetEquiTile()[1]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetEquiTile()[1]->fY
		+ CTileMgr::GetInstance()->GetEquiTile()[1]->fCY / 2.f)};

	if(PtInRect(&rcWeapon, ptMouse) && CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true)
	{
		
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000) // 무기칸 클릭
		{
			if(m_bWeaponPush == true)
				return;
			m_bWeaponPush = true;
			
			if(pItem != NULL && pItem->GetInfo().eType == IT_WEAPON) // 장착
			{
				if(CTileMgr::GetInstance()->GetEquiTile()[0]->m_bCheck == true)
					return;
				CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");

				pItem->GetInfo().bClick = false;
				pItem->GetInfo().fX = CTileMgr::GetInstance()->GetEquiTile()[0]->fX;
				pItem->GetInfo().fY = CTileMgr::GetInstance()->GetEquiTile()[0]->fY;
				CTileMgr::GetInstance()->GetEquiTile()[0]->m_bCheck = true;
				CTileMgr::GetInstance()->GetEquiTile()[0]->eType = IT_WEAPON;
				CTileMgr::GetInstance()->GetEquiTile()[0]->cType = IST_TWO_BY_THREE;
				CObjMgr::GetInstance()->GetInfo(L"Player")->iAtt += pItem->GetInfo().iAtt;

				CItem*	_pItem = new CWeapon;
				memcpy(_pItem, pItem, sizeof(CWeapon));
				_pEqui->push_back(_pItem);
				pItem->GetInfo().bAlive = false;
				pItem = NULL;
				return;
			}
			else if(pItem == NULL) // 해제
			{
				for(Equi_iter; Equi_iter != Equi_iter_end; ++Equi_iter)
				{
					if((*Equi_iter)->GetInfo().eType == IT_WEAPON)
					{
						CSoundMgr::GetInstance()->ItemSound(L"pickup.wav");
						pItem = (*Equi_iter);
						CObjMgr::GetInstance()->GetInfo(L"Player")->iAtt -= pItem->GetInfo().iAtt;
						pItem->GetInfo().bClick = true;
						CTileMgr::GetInstance()->GetEquiTile()[0]->m_bCheck = false;
						CTileMgr::GetInstance()->GetEquiTile()[0]->eType = IT_END;
						CTileMgr::GetInstance()->GetEquiTile()[0]->cType = IST_END;
						return;
					}
				}
			}
		}
		else
			m_bWeaponPush = false;
	}
	if(PtInRect(&rcArmor, ptMouse) && CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true)
	{
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000) // 장비칸 클릭
		{
			if(m_bArmorPush == true)
				return;
			m_bArmorPush = true;

			if(pItem != NULL && pItem->GetInfo().eType == IT_ARMOR) // 장착
			{
				if(CTileMgr::GetInstance()->GetEquiTile()[1]->m_bCheck == true)
					return;
				CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");

				pItem->GetInfo().bClick = false;
				pItem->GetInfo().fX = CTileMgr::GetInstance()->GetEquiTile()[1]->fX;
				pItem->GetInfo().fY = CTileMgr::GetInstance()->GetEquiTile()[1]->fY;
				CTileMgr::GetInstance()->GetEquiTile()[1]->m_bCheck = true;
				CTileMgr::GetInstance()->GetEquiTile()[1]->eType = IT_ARMOR;
				CTileMgr::GetInstance()->GetEquiTile()[1]->cType = IST_TWO_BY_THREE;
				CObjMgr::GetInstance()->GetInfo(L"Player")->iDef += pItem->GetInfo().iDef;
				CItem*	_pItem = new CArmor;
				memcpy(_pItem, pItem, sizeof(CArmor));
				_pEqui->push_back(_pItem);
				pItem->GetInfo().bAlive = false;
				pItem = NULL;
				return;

			}
			else if(pItem == NULL) // 해제
			{
				for(Equi_iter; Equi_iter != Equi_iter_end; ++Equi_iter)
				{
					if((*Equi_iter)->GetInfo().eType == IT_ARMOR)
					{
						CSoundMgr::GetInstance()->ItemSound(L"pickup.wav");
						pItem = (*Equi_iter);
						CObjMgr::GetInstance()->GetInfo(L"Player")->iDef -= pItem->GetInfo().iDef;
						pItem->GetInfo().bClick = true;
						CTileMgr::GetInstance()->GetEquiTile()[1]->m_bCheck = false;
						CTileMgr::GetInstance()->GetEquiTile()[1]->eType = IT_END;
						CTileMgr::GetInstance()->GetEquiTile()[1]->cType = IST_END;
						return;

					}
				}

			}
		}
		else
			m_bArmorPush = false;
	}

}

void CCollMgr::InvenItemColl(list<CItem*>* _pInven)
{
	if(pItem == NULL)
		InvenItemToTile(_pInven);
	list<CItem*>::iterator Inven_iter = _pInven->begin();
	list<CItem*>::iterator Inven_iter_end = _pInven->end();

	POINT	ptMouse = CMouse::GetMousePos();

	RECT	rcInven = {long(CTileMgr::GetInstance()->GetInvenTile()[0]->fX
		- CTileMgr::GetInstance()->GetInvenTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[0]->fY
		- CTileMgr::GetInstance()->GetInvenTile()[0]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fX
		+ CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fY
		+ CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fCY / 2.f)};
	
	if(PtInRect(&rcInven, ptMouse) && CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true)
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000) // 포탈 & 포션 사용
		{
			if(CCollMgr::m_bUsePush == true)
				return;
			CCollMgr::m_bUsePush = true;

			int		iInvenIndex = int((ptMouse.y - 325) / iITEMTILESIZEY) * iSHOPTILECNTX + int((ptMouse.x - 425) / iITEMTILESIZEX);

			if(iInvenIndex < 0 || 39 < iInvenIndex)
				return;

			if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true )
			{
				for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
				{

					RECT	rcTile = {long(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCX / 2.f)
						, long(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCY / 2.f)
						, long(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCX / 2.f)
						, long(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCY / 2.f)};

					RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
						, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
						, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
						, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

					if(PtInRect(&rcTile, ptMouse) && PtInRect(&rcItem, ptMouse) && pItem == NULL) // 우클릭 정렬 구매
					{
						if((*Inven_iter)->GetInfo().eType == IT_POTION)
						{
							CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
							(*Inven_iter)->GetInfo().bAlive = false;
							
							CSoundMgr::GetInstance()->ItemSound(L"potiondrink.wav");

							if((CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp - CObjMgr::GetInstance()->GetInfo(L"Player")->iHp) > 30)
								CObjMgr::GetInstance()->GetInfo(L"Player")->iHp += 30;
							else
								CObjMgr::GetInstance()->GetInfo(L"Player")->iHp = CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp;

							if((CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp - CObjMgr::GetInstance()->GetInfo(L"Player")->iMp) > 30)
								CObjMgr::GetInstance()->GetInfo(L"Player")->iMp += 30;
							else
								CObjMgr::GetInstance()->GetInfo(L"Player")->iMp =CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp;
							break;
						}
					}
				}
			}
		}
		else
			CCollMgr::m_bUsePush = false;

		
		if(GetAsyncKeyState(VK_SHIFT) & 0x8000) // 쉬프트 물약 장착
		{
			if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if(CCollMgr::m_bInvenPush2 == true)
					return;
				CCollMgr::m_bInvenPush2 = true;

				int		iInvenIndex = int((ptMouse.y - 325) / iITEMTILESIZEY) * iSHOPTILECNTX + int((ptMouse.x - 425) / iITEMTILESIZEX);

				if(iInvenIndex < 0 || 39 < iInvenIndex)
					return;

				if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true )
				{
					for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
					{

						RECT	rcTile = {long(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCY / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCY / 2.f)};

						RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
							, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
							, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
							, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

						if(PtInRect(&rcTile, ptMouse) && PtInRect(&rcItem, ptMouse) && pItem == NULL) // 우클릭 정렬 구매
						{
							if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
							{
								if(CTileMgr::GetInstance()->GetEquiTile()[0]->m_bCheck != true)
								{
									CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
									CObjMgr::GetInstance()->GetInfo(L"Player")->iAtt += (*Inven_iter)->GetInfo().iAtt;
									if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX < (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 왼쪽
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY < (*Inven_iter)->GetInfo().fY) // Index
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
											

										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->m_bCheck = false;
											
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
											
										}
									}

									else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX > (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 오른
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY < (*Inven_iter)->GetInfo().fY) // Index + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;
											
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX - 1]->m_bCheck = false;
											
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2 + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
											
										}
									}

									CItem*	pItem = new CWeapon;
									memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
									pItem->GetInfo().fX = CTileMgr::GetInstance()->GetEquiTile()[0]->fX;
									pItem->GetInfo().fY = CTileMgr::GetInstance()->GetEquiTile()[0]->fY;
									CTileMgr::GetInstance()->GetEquiTile()[0]->m_bCheck = true;
									CObjMgr::GetInstance()->GetEquiList(L"Inven")->push_back(pItem);
									(*Inven_iter)->GetInfo().bAlive = false;
									return;
								}
							}
							if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
							{
								if(CTileMgr::GetInstance()->GetEquiTile()[1]->m_bCheck != true)
								{
									
									CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
									CObjMgr::GetInstance()->GetInfo(L"Player")->iDef += (*Inven_iter)->GetInfo().iDef;
									if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX < (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 왼쪽
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY < (*Inven_iter)->GetInfo().fY) // Index
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;


										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->m_bCheck = false;

										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;

										}
									}

									else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX > (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 오른
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY < (*Inven_iter)->GetInfo().fY) // Index + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;

										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX - 1]->m_bCheck = false;

										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2 + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;

										}
									}

									CItem*	pItem = new CArmor;
									memcpy(pItem, (*Inven_iter), sizeof(CArmor));
									pItem->GetInfo().fX = CTileMgr::GetInstance()->GetEquiTile()[1]->fX;
									pItem->GetInfo().fY = CTileMgr::GetInstance()->GetEquiTile()[1]->fY;
									CTileMgr::GetInstance()->GetEquiTile()[1]->m_bCheck = true;
									CObjMgr::GetInstance()->GetEquiList(L"Inven")->push_back(pItem);
									(*Inven_iter)->GetInfo().bAlive = false;
									return;
								}
							}
							if((*Inven_iter)->GetInfo().eType == IT_POTION)
							{
								for(int i = 0; i < 4; ++i)
								{
									int iIndex = i; 

									RECT	rcInven = {long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
										, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)
										, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
										, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)};

									if(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->m_bCheck != true)
									{
										for(int i = 0; i < 4; ++i)
										{
											if(CTileMgr::GetInstance()->GetPotionTile()[i]->m_bCheck != true)
											{
												CSoundMgr::GetInstance()->ItemSound(L"pickup.wav");
												CItem*	pItem = new CPotion;
												memcpy(pItem, (*Inven_iter), sizeof(CPotion));
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetPotionTile()[i]->fX;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetPotionTile()[i]->fY;
												CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->eType = IT_END;
												CTileMgr::GetInstance()->GetPotionTile()[i]->m_bCheck = true;
												CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->push_back(pItem);
												(*Inven_iter)->GetInfo().bAlive = false;
												return;
											}
										}
									}
								}
							}
						}
					}			
				}	
			}
			else
				CCollMgr::m_bInvenPush2 = false;
		}
		
		else if(GetAsyncKeyState(VK_LBUTTON) & 0x8000) // 정렬 판매 및 인벤 스왑
		{
			if(CCollMgr::m_bInvenPush == true)
				return;
			CCollMgr::m_bInvenPush = true;

			int		iIndex = int((ptMouse.y - 325) / iITEMTILESIZEY) * iSHOPTILECNTX + int((ptMouse.x - 425) / iITEMTILESIZEX);

			if(iIndex < 0 || 39 < iIndex)
				return;


			if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bShopRender == true || CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true )
			{
				RECT	rcTile = {long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)};

				if(PtInRect(&rcTile, ptMouse) && pItem != NULL && CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck == false) // 없는곳에 놓기
				{
					CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;

					if(pItem->GetInfo().cType == IST_ONE_BY_ONE)
					{
						if(pItem->GetInfo().eType == IT_POTION) 
						{
							CSoundMgr::GetInstance()->ItemSound(L"potionui.wav");
							pItem->GetInfo().bClick = false;
							pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
							pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
							CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
							CItem*	_pItem = new CPotion;
							memcpy(_pItem, pItem, sizeof(CPotion));
							_pInven->push_back(_pItem);
							pItem->GetInfo().bAlive = false;
							pItem = NULL;
							return;
							
						}
						else if(pItem->GetInfo().eType == IT_SCROLL)
						{
							CSoundMgr::GetInstance()->ItemSound(L"scroll.wav");
							pItem->GetInfo().bClick = false;
							pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
							pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
							CItem*	_pItem = new CScroll;
							memcpy(_pItem, pItem, sizeof(CScroll));
							_pInven->push_back(_pItem);
							pItem->GetInfo().bAlive = false;
							pItem = NULL;
							CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
							return;
						}
					}
					else if(pItem->GetInfo().cType == IST_TWO_BY_THREE)
					{
						if(pItem->GetInfo().eType == IT_ARMOR)
						{
							if(iIndex < 0 || iIndex >= 40)
								return;

							if( iIndex >= 0 && 10 > iIndex )
							{								
								if(iIndex == 9) // 홀수
								{
									return;
								}
								else
								{									
									if( CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true 
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck == true)    // 2가지 아이템이상 중복충돌 체크
									{
										bool bPotion = false;
										bool bScroll = false;
										bool bWeapon = false;

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													if(bPotion == false)
														bPotion = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													if(bScroll == false)
														bScroll = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
													bWeapon = true;
											}
											
										}

										if((bPotion == true && bScroll == true)
											|| (bPotion == true && bWeapon == true)
											|| (bWeapon == true && bScroll == true))
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
											return;
										}
										
										Inven_iter = _pInven->begin();

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													CItem* pTemp = new CPotion;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CPotion));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													CItem* pTemp = new CScroll;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CScroll));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile1)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 2]->m_bCheck = false;
													}
													else if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile3)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3 + 2]->m_bCheck = false;
													}

													else if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile2)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3 - 1]->m_bCheck = false;
													}
													else if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile2) && PtInRect(&rcItem, ptTile3)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3]->m_bCheck = false;
													}
													CItem* pTemp = new CWeapon;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;
													return;
												}
											}
										}
									}
									else
									{
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;
									}
								}
							}
							else if( iIndex >= 10 && 20 > iIndex )
							{
								if(iIndex == 19) // 홀수
								{
									return;
								}
								else
								{
									if( CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true 
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)    // 2가지 아이템이상 중복충돌 체크
									{
										bool bPotion = false;
										bool bScroll = false;
										bool bWeapon = false;

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													if(bPotion == false)
														bPotion = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													if(bScroll == false)
														bScroll = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
													bWeapon = true;
											}

										}

										if((bPotion == true && bScroll == true)
											|| (bPotion == true && bWeapon == true)
											|| (bWeapon == true && bScroll == true))
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
											return;
										}

										Inven_iter = _pInven->begin();
										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX ]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													CItem* pTemp = new CPotion;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CPotion));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													CItem* pTemp = new CScroll;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CScroll));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
													}
													else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY < (*Inven_iter)->GetInfo().fY) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 2]->m_bCheck = false;
													}
													CItem* pTemp = new CWeapon;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;
													return;
												}
											}
										}
									}
									else
									{
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
									}
								}

							}
							else if( iIndex >= 20 && 30 > iIndex )
							{
								if(iIndex == 29) // 홀수
								{
									return;
								}
								else
								{
									if( CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true 
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)    // 2가지 아이템이상 중복충돌 체크
									{
										bool bPotion = false;
										bool bScroll = false;
										bool bWeapon = false;

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													if(bPotion == false)
														bPotion = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													if(bScroll == false)
														bScroll = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
													bWeapon = true;
											}

										}

										if((bPotion == true && bScroll == true)
											|| (bPotion == true && bWeapon == true)
											|| (bWeapon == true && bScroll == true))
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
											return;
										}

										Inven_iter = _pInven->begin();
										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX ]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													CItem* pTemp = new CPotion;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CPotion));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													CItem* pTemp = new CScroll;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CScroll));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY > (*Inven_iter)->GetInfo().fY) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 2]->m_bCheck = false;
													}

													else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
													}
												
													CItem* pTemp = new CWeapon;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;
													return;
												}
											}
										}
									}
									else
									{
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
									}
								}

							}
							else if( iIndex >= 30 && 40 > iIndex )
							{
								if(iIndex == 39) // 홀수
								{
									return;
								}
								else
								{
									if( CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true 
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck == true)    // 2가지 아이템이상 중복충돌 체크
									{
										bool bPotion = false;
										bool bScroll = false;
										bool bWeapon = false;

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													if(bPotion == false)
														bPotion = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													if(bScroll == false)
														bScroll = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
													bWeapon = true;
											}

										}

										if((bPotion == true && bScroll == true)
											|| (bPotion == true && bWeapon == true)
											|| (bWeapon == true && bScroll == true))
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
											return;
										}

										Inven_iter = _pInven->begin();
										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													CItem* pTemp = new CPotion;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CPotion));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													CItem* pTemp = new CScroll;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CScroll));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
												{
													
													CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
													if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile1)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 2]->m_bCheck = false;
													}
													else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile3)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3 + 2]->m_bCheck = false;
													}

													else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile2)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3 - 1]->m_bCheck = false;
													}
													else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile2) && PtInRect(&rcItem, ptTile3)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3]->m_bCheck = false;
													}
													CItem* pTemp = new CWeapon;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CArmor));
													memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
													memcpy((*Inven_iter), pTemp, sizeof(CArmor));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;
													return;
												}
											}
										}
									}
									else
									{
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;
									}
								}

							}
							pItem->GetInfo().bClick = false;
							CItem*	_pItem = new CArmor;
							memcpy(_pItem, pItem, sizeof(CArmor));
							_pInven->push_back(_pItem);
							pItem->GetInfo().bAlive = false;
							pItem = NULL;
							return;
						}

						if(pItem->GetInfo().eType == IT_WEAPON)
						{
							if(iIndex < 0 || iIndex >= 40)
								return;

							if( iIndex >= 0 && 10 > iIndex )
							{								
								if(iIndex == 9) // 홀수
								{
									return;
								}
								else
								{
									if( CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true 
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck == true)    // 2가지 아이템이상 중복충돌 체크
									{
										bool bPotion = false;
										bool bScroll = false;
										bool bWeapon = false;

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													if(bPotion == false)
														bPotion = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													if(bScroll == false)
														bScroll = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
													bWeapon = true;
											}

										}

										if((bPotion == true && bScroll == true)
											|| (bPotion == true && bWeapon == true)
											|| (bWeapon == true && bScroll == true))
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
											return;
										}

										Inven_iter = _pInven->begin();
										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													CItem* pTemp = new CPotion;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CPotion));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													CItem* pTemp = new CScroll;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CScroll));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile1)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 2]->m_bCheck = false;
													}
													else if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile3)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3 + 2]->m_bCheck = false;
													}

													else if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile2)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3 - 1]->m_bCheck = false;
													}
													else if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile2) && PtInRect(&rcItem, ptTile3)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 3]->m_bCheck = false;
													}
													CItem* pTemp = new CArmor;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CArmor));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;
													return;
												}
											}
										}
									}
									else
									{
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;
									}
								}
							}
							else if( iIndex >= 10 && 20 > iIndex )
							{
								if(iIndex == 19) // 홀수
								{
									return;
								}
								else
								{
									if( CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true 
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)    // 2가지 아이템이상 중복충돌 체크
									{
										bool bPotion = false;
										bool bScroll = false;
										bool bWeapon = false;

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													if(bPotion == false)
														bPotion = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													if(bScroll == false)
														bScroll = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
													bWeapon = true;
											}

										}

										if((bPotion == true && bScroll == true)
											|| (bPotion == true && bWeapon == true)
											|| (bWeapon == true && bScroll == true))
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
											return;
										}

										Inven_iter = _pInven->begin();
										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX ]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													CItem* pTemp = new CPotion;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CPotion));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													CItem* pTemp = new CScroll;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CScroll));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
													}
													else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY < (*Inven_iter)->GetInfo().fY) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 2]->m_bCheck = false;
													}
													CItem* pTemp = new CArmor;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CArmor));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;
													return;
												}
											}
										}
									}
									else
									{
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
									}
								}

							}
							else if( iIndex >= 20 && 30 > iIndex )
							{
								if(iIndex == 29) // 홀수
								{
									return;
								}
								else
								{
									if( CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true 
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)    // 2가지 아이템이상 중복충돌 체크
									{
										bool bPotion = false;
										bool bScroll = false;
										bool bWeapon = false;

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													if(bPotion == false)
														bPotion = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													if(bScroll == false)
														bScroll = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
													bWeapon = true;
											}

										}

										if((bPotion == true && bScroll == true)
											|| (bPotion == true && bWeapon == true)
											|| (bWeapon == true && bScroll == true))
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
											return;
										}

										Inven_iter = _pInven->begin();
										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX ]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													CItem* pTemp = new CPotion;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CPotion));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													CItem* pTemp = new CScroll;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CScroll));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY > (*Inven_iter)->GetInfo().fY) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 2]->m_bCheck = false;
													}

													else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
													}

													CItem* pTemp = new CArmor;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CArmor));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;
													return;
												}
											}
										}
									}
									else
									{
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
									}
								}

							}
							else if( iIndex >= 30 && 40 > iIndex )
							{
								if(iIndex == 39) // 홀수
								{
									return;
								}
								else
								{
									if( CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true 
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck == true
										|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck == true)    // 2가지 아이템이상 중복충돌 체크
									{
										bool bPotion = false;
										bool bScroll = false;
										bool bWeapon = false;

										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													if(bPotion == false)
														bPotion = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													if(bScroll == false)
														bScroll = true;
													else
													{
														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
														return;
													}
												}
												else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
													bWeapon = true;
											}

										}

										if((bPotion == true && bScroll == true)
											|| (bPotion == true && bWeapon == true)
											|| (bWeapon == true && bScroll == true))
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
											return;
										}

										Inven_iter = _pInven->begin();
										for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
										{
											RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
												, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
												, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

											POINT	ptTile1 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->fY)};
											POINT	ptTile2 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY)};
											POINT	ptTile3 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->fY)};
											POINT	ptTile4 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->fY)};
											POINT	ptTile5 = { long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->fX), long(CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->fY)};

											if(PtInRect(&rcItem, ptTile1)
												|| PtInRect(&rcItem, ptTile2)
												|| PtInRect(&rcItem, ptTile3)
												|| PtInRect(&rcItem, ptTile4)
												|| PtInRect(&rcItem, ptTile5))
											{
												if((*Inven_iter)->GetInfo().eType == IT_POTION)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													CItem* pTemp = new CPotion;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CPotion));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													CItem* pTemp = new CScroll;
													pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
													pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CScroll));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;

													CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
													CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;
													return;

												}
												else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
												{
													CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
													if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile1)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 2]->m_bCheck = false;
													}
													else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile3)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 2]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3 + 2]->m_bCheck = false;
													}

													else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile2)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3 - 1]->m_bCheck = false;
													}
													else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY && PtInRect(&rcItem, ptTile2) && PtInRect(&rcItem, ptTile3)) // Index
													{
														pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
														pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3 + 1]->m_bCheck = false;
														CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 3]->m_bCheck = false;
													}

													CItem* pTemp = new CArmor;
													pItem->GetInfo().bClick = false;
													memcpy(pTemp, pItem, sizeof(CWeapon));
													memcpy(pItem, (*Inven_iter), sizeof(CArmor));
													memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
													safe_delete(pTemp);
													pItem->GetInfo().bClick = true;
													return;
												}
											}
										}
									}
									else
									{
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;
									}
								}

							}
							pItem->GetInfo().bClick = false;
							CItem*	_pItem = new CWeapon;
							memcpy(_pItem, pItem, sizeof(CWeapon));
							_pInven->push_back(_pItem);
							pItem->GetInfo().bAlive = false;
							pItem = NULL;
							return;
						}
					}
				}
				if(PtInRect(&rcTile, ptMouse) && pItem != NULL && CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck == true) // 인벤 스왑구매
				{
					for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
					{
						RECT	rcTile = {long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)};

						RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
							, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
							, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
							, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

						if(PtInRect(&rcTile, ptMouse) && PtInRect(&rcItem, ptMouse) && pItem != NULL)
						{
							if(pItem->GetInfo().eType == IT_SCROLL)
							{
								if((*Inven_iter)->GetInfo().eType == IT_POTION)
								{
									CSoundMgr::GetInstance()->ItemSound(L"scroll.wav");
									CItem* pTemp = new CPotion;
									pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
									pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
									CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
									CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
									pItem->GetInfo().bClick = false;
									memcpy(pTemp, pItem, sizeof(CPotion));
									memcpy(pItem, (*Inven_iter), sizeof(CScroll));
									memcpy((*Inven_iter), pTemp, sizeof(CPotion));
									safe_delete(pTemp);
									pItem->GetInfo().bClick = true;
								}
								else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
								{
									if((iIndex + 1) % 10 == 0)
									{
										iIndex += 1;
									}
									if(iIndex >= 20)
										return;
									
									CSoundMgr::GetInstance()->ItemSound(L"scroll.wav");

									if(pItem->GetInfo().fX < (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 왼쪽
									{
										if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY) // Index
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
										}
										else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										}

										CItem* pTemp = new CWeapon;
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										pItem->GetInfo().bClick = false;
										memcpy(pTemp, pItem, sizeof(CWeapon));
										memcpy(pItem, (*Inven_iter), sizeof(CScroll));
										memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
										safe_delete(pTemp);
										pItem->GetInfo().bClick = true;
									}

									else if(pItem->GetInfo().fX > (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 오른
									{
										if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY) // Index + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
										}
										else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2 + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										}

										CItem* pTemp = new CWeapon;
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										pItem->GetInfo().bClick = false;
										memcpy(pTemp, pItem, sizeof(CWeapon));
										memcpy(pItem, (*Inven_iter), sizeof(CScroll));
										memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
										safe_delete(pTemp);
										pItem->GetInfo().bClick = true;
									}

								}
								else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
								{

									if((iIndex + 1) % 10 == 0)
									{
										iIndex += 1;
									}
									if(iIndex >= 20)
										return;
									
									CSoundMgr::GetInstance()->ItemSound(L"scroll.wav");

									if(pItem->GetInfo().fX < (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 왼쪽
									{
										if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY) // Index
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
										}
										else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										}

										CItem* pTemp = new CArmor;
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										pItem->GetInfo().bClick = false;
										memcpy(pTemp, pItem, sizeof(CArmor));
										memcpy(pItem, (*Inven_iter), sizeof(CScroll));
										memcpy((*Inven_iter), pTemp, sizeof(CArmor));
										safe_delete(pTemp);
										pItem->GetInfo().bClick = true;
									}

									else if(pItem->GetInfo().fX > (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 오른
									{
										if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY) // Index + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
										}
										else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2 + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										}

										CItem* pTemp = new CWeapon;
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										pItem->GetInfo().bClick = false;
										memcpy(pTemp, pItem, sizeof(CWeapon));
										memcpy(pItem, (*Inven_iter), sizeof(CScroll));
										memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
										safe_delete(pTemp);
										pItem->GetInfo().bClick = true;
									}
								}
							}
							else if(pItem->GetInfo().eType == IT_POTION)
							{
								if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
								{
									CSoundMgr::GetInstance()->ItemSound(L"potionui.wav");
									CItem* pTemp = new CScroll;
									pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
									pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
									CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
									CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
									pItem->GetInfo().bClick = false;
									memcpy(pTemp, pItem, sizeof(CPotion));
									memcpy(pItem, (*Inven_iter), sizeof(CScroll));
									memcpy((*Inven_iter), pTemp, sizeof(CPotion));
									safe_delete(pTemp);
									pItem->GetInfo().bClick = true;
								}

								else if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
								{
									if((iIndex + 1) % 10 == 0)
									{
										iIndex += 1;
									}
									if(iIndex >= 20)
										return;
									CSoundMgr::GetInstance()->ItemSound(L"potionui.wav");

									if(pItem->GetInfo().fX < (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 왼쪽
									{
										if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY) // Index
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
										}
										else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										}

										CItem* pTemp = new CWeapon;
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										pItem->GetInfo().bClick = false;
										memcpy(pTemp, pItem, sizeof(CWeapon));
										memcpy(pItem, (*Inven_iter), sizeof(CScroll));
										memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
										safe_delete(pTemp);
										pItem->GetInfo().bClick = true;
									}

									else if(pItem->GetInfo().fX > (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 오른
									{
										if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY) // Index + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
										}
										else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2 + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										}

										CItem* pTemp = new CWeapon;
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										pItem->GetInfo().bClick = false;
										memcpy(pTemp, pItem, sizeof(CWeapon));
										memcpy(pItem, (*Inven_iter), sizeof(CScroll));
										memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
										safe_delete(pTemp);
										pItem->GetInfo().bClick = true;
									}

								}
								else if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
								{

									if((iIndex + 1) % 10 == 0)
									{
										iIndex += 1;
									}
									if(iIndex >= 20)
										return;
									CSoundMgr::GetInstance()->ItemSound(L"potionui.wav");

									if(pItem->GetInfo().fX < (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 왼쪽
									{
										if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY) // Index
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
										}
										else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										}

										CItem* pTemp = new CArmor;
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										pItem->GetInfo().bClick = false;
										memcpy(pTemp, pItem, sizeof(CArmor));
										memcpy(pItem, (*Inven_iter), sizeof(CPotion));
										memcpy((*Inven_iter), pTemp, sizeof(CArmor));
										safe_delete(pTemp);
										pItem->GetInfo().bClick = true;
									}

									else if(pItem->GetInfo().fX > (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 오른
									{
										if(pItem->GetInfo().fY < (*Inven_iter)->GetInfo().fY) // Index + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
										}
										else if(pItem->GetInfo().fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2 + 1
										{
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
											CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										}

										CItem* pTemp = new CWeapon;
										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										pItem->GetInfo().bClick = false;
										memcpy(pTemp, pItem, sizeof(CWeapon));
										memcpy(pItem, (*Inven_iter), sizeof(CPotion));
										memcpy((*Inven_iter), pTemp, sizeof(CWeapon));
										safe_delete(pTemp);
										pItem->GetInfo().bClick = true;
									}
								}
							}
							else if(pItem->GetInfo().eType == IT_WEAPON) // 2x3 스왑
							{
								if((*Inven_iter)->GetInfo().eType == IT_ARMOR)
								{
									if(pItem->GetInfo().fX > (*Inven_iter)->GetInfo().fX)
									{
										if(iIndex == 9 || iIndex == 19 || iIndex == 29 || iIndex == 39)
											return;

										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY < (*Inven_iter)->GetInfo().fY) // 첫번쨰칸부터 있을때
										{
											if(iIndex >= 0 && iIndex < 9)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
											else if(iIndex >= 10 && iIndex < 19)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;

											}
												
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 10 && iIndex < 19)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;

											}
												
											else if(iIndex >= 20 && iIndex < 29)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
												
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY > (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 20 && iIndex < 29)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->eType = IT_END;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;

											}
												
											else if(iIndex >= 30 && iIndex < 39)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->eType = IT_END;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
										}
									}
									else if(pItem->GetInfo().fX < (*Inven_iter)->GetInfo().fX)
									{
										if(iIndex == 9 || iIndex == 19 || iIndex == 29 || iIndex == 39)
											return;

										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY < (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 0 && iIndex < 9)
											{
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
											else if(iIndex >= 10 && iIndex < 19)
											{
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = IT_END;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 10 && iIndex < 19)
											{
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
											else if(iIndex >= 20 && iIndex < 29)
											{
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY > (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 20 && iIndex < 29)
											{
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = IT_END;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;


											}
											else if(iIndex >= 30 && iIndex < 39)
											{
												CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
										}
									}
								}
								else if((*Inven_iter)->GetInfo().eType == IT_POTION)
								{
									if(iIndex == 9 || iIndex == 19 || iIndex == 29 || iIndex == 39)
										return;


									if(iIndex >= 0 && iIndex < 9)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 10 && iIndex < 19)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 20 && iIndex < 29)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = IST_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = IST_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = IT_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = IT_END;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 30 && iIndex < 39)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2+ 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;
									}

									CItem* pTemp = new CArmor;

									pItem->GetInfo().bClick = false;
									memcpy(pTemp, pItem, sizeof(CArmor));
									memcpy(pItem, (*Inven_iter), sizeof(CPotion));
									memcpy((*Inven_iter), pTemp, sizeof(CArmor));
									safe_delete(pTemp);
									pItem->GetInfo().bClick = true;

								}
								else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
								{
									if(iIndex == 9 || iIndex == 19 || iIndex == 29 || iIndex == 39)
										return;

									if(iIndex >= 0 && iIndex < 9)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 10 && iIndex < 19)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 20 && iIndex < 29)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = IST_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = IST_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = IT_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = IT_END;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 30 && iIndex < 39)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"woodweaponlarge.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;
									}

									CItem* pTemp = new CArmor;

									pItem->GetInfo().bClick = false;
									memcpy(pTemp, pItem, sizeof(CArmor));
									memcpy(pItem, (*Inven_iter), sizeof(CScroll));
									memcpy((*Inven_iter), pTemp, sizeof(CArmor));
									safe_delete(pTemp);
									pItem->GetInfo().bClick = true;

								}
							}
							else if(pItem->GetInfo().eType == IT_ARMOR)
							{
								if((*Inven_iter)->GetInfo().eType == IT_WEAPON)
								{
									if(pItem->GetInfo().fX > (*Inven_iter)->GetInfo().fX)
									{
										if(iIndex == 9 || iIndex == 19 || iIndex == 29 || iIndex == 39)
											return;

										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY < (*Inven_iter)->GetInfo().fY) // 첫번쨰칸부터 있을때
										{
											if(iIndex >= 0 && iIndex < 9)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
											else if(iIndex >= 10 && iIndex < 19)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;

											}

										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 10 && iIndex < 19)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;

											}

											else if(iIndex >= 20 && iIndex < 29)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}

										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY > (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 20 && iIndex < 29)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->eType = IT_END;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;

											}

											else if(iIndex >= 30 && iIndex < 39)
											{
												if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true
													|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck == true)
												{
													return;
												}
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->eType = IT_END;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
										}
									}
									else if(pItem->GetInfo().fX < (*Inven_iter)->GetInfo().fX)
									{
										if(iIndex == 9 || iIndex == 19 || iIndex == 29 || iIndex == 39)
											return;

										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY < (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 0 && iIndex < 9)
											{
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
											else if(iIndex >= 10 && iIndex < 19)
											{
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = IT_END;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 10 && iIndex < 19)
											{
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
											else if(iIndex >= 20 && iIndex < 29)
											{
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
										}
										else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY > (*Inven_iter)->GetInfo().fY)
										{
											if(iIndex >= 20 && iIndex < 29)
											{
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = IST_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = IT_END;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = IT_END;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;


											}
											else if(iIndex >= 30 && iIndex < 39)
											{
												CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

												CItem* pTemp = new CArmor;
												pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
												pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

												CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
												CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;

												pItem->GetInfo().bClick = false;
												memcpy(pTemp, pItem, sizeof(CArmor));
												memcpy(pItem, (*Inven_iter), sizeof(CWeapon));
												memcpy((*Inven_iter), pTemp, sizeof(CArmor));
												safe_delete(pTemp);
												pItem->GetInfo().bClick = true;
											}
										}
									}
								}
								else if((*Inven_iter)->GetInfo().eType == IT_POTION)
								{
									if(iIndex == 9 || iIndex == 19 || iIndex == 29 || iIndex == 39)
										return;

									if(iIndex >= 0 && iIndex < 9)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 10 && iIndex < 19)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 20 && iIndex < 29)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
										{
											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = IST_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = IST_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = IT_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = IT_END;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 30 && iIndex < 39)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck == true)
										{

											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;
									}

									CItem* pTemp = new CArmor;

									pItem->GetInfo().bClick = false;
									memcpy(pTemp, pItem, sizeof(CArmor));
									memcpy(pItem, (*Inven_iter), sizeof(CPotion));
									memcpy((*Inven_iter), pTemp, sizeof(CArmor));
									safe_delete(pTemp);
									pItem->GetInfo().bClick = true;

								}
								else if((*Inven_iter)->GetInfo().eType == IT_SCROLL)
								{
									if(iIndex == 9 || iIndex == 19 || iIndex == 29 || iIndex == 39)
										return;

									if(iIndex >= 0 && iIndex < 9)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck == true)
										{

											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 10 && iIndex < 19)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
										{

											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 20 && iIndex < 29)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true)
										{

											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = IST_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = IST_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = IT_END;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = IT_END;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
									}
									else if(iIndex >= 30 && iIndex < 39)
									{
										if(CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck == true
											|| CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck == true)
										{

											return;
										}
										CSoundMgr::GetInstance()->ItemSound(L"metalshield.wav");
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = true;

										pItem->GetInfo().fX = CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f;
										pItem->GetInfo().fY = CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->fY;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->eType = pItem->GetInfo().eType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->eType = pItem->GetInfo().eType;

										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->cType = pItem->GetInfo().cType;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->cType = pItem->GetInfo().cType;
									}

									CItem* pTemp = new CArmor;

									pItem->GetInfo().bClick = false;
									memcpy(pTemp, pItem, sizeof(CArmor));
									memcpy(pItem, (*Inven_iter), sizeof(CScroll));
									memcpy((*Inven_iter), pTemp, sizeof(CArmor));
									safe_delete(pTemp);
									pItem->GetInfo().bClick = true;
								}
							}
						}
					}
				}
			}
			
			if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true )
			{
				int		iIndex = int((ptMouse.y - 325) / iITEMTILESIZEY) * iSHOPTILECNTX + int((ptMouse.x - 425) / iITEMTILESIZEX);

				if(iIndex < 0 || 39 < iIndex)
					return;

				RECT	rcTile = {long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
					, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)};

				if(PtInRect(&rcTile, ptMouse) && pItem == NULL && CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck == true) // 안들고 있을때 인벤 클릭 ( 상점창에서 아이템 스왑)
				{
					for(Inven_iter; Inven_iter != Inven_iter_end; ++Inven_iter)
					{
						RECT	rcTile = {long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f)};

						RECT	rcItem = {long((*Inven_iter)->GetInfo().fX - (*Inven_iter)->GetInfo().fCX / 2.f)
							, long((*Inven_iter)->GetInfo().fY - (*Inven_iter)->GetInfo().fCY / 2.f)
							, long((*Inven_iter)->GetInfo().fX + (*Inven_iter)->GetInfo().fCX / 2.f)
							, long((*Inven_iter)->GetInfo().fY + (*Inven_iter)->GetInfo().fCY / 2.f)};

						if(PtInRect(&rcTile, ptMouse) && PtInRect(&rcItem, ptMouse) && pItem == NULL)
						{
							CSoundMgr::GetInstance()->ItemSound(L"pickup.wav");
							if((*Inven_iter)->GetInfo().eType == IT_SCROLL || (*Inven_iter)->GetInfo().eType == IT_POTION)
							{
								pItem =  (*Inven_iter);
								pItem->GetInfo().bClick = true;
								CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
								CTileMgr::GetInstance()->GetInvenTile()[iIndex]->eType = IT_END;
								CTileMgr::GetInstance()->GetInvenTile()[iIndex]->cType = IST_END;
								return;
							}

							else if((*Inven_iter)->GetInfo().eType == IT_WEAPON || (*Inven_iter)->GetInfo().eType == IT_ARMOR)
							{
								if((iIndex + 1) % 10 == 0)
								{
									iIndex += 1;
								}
								
								if(iIndex >= 20)
									return;

								if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX < (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 왼쪽
								{
									if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY < (*Inven_iter)->GetInfo().fY) // Index
									{
										pItem =  (*Inven_iter);
										pItem->GetInfo().bClick = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										return;

									}
									else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX
									{
										pItem =  (*Inven_iter);
										pItem->GetInfo().bClick = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX + 1]->m_bCheck = false;
										return;
									}
									else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2
									{
										pItem =  (*Inven_iter);
										pItem->GetInfo().bClick = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX + 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 + 1]->m_bCheck = false;
										return;
									}
								}

								else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX > (*Inven_iter)->GetInfo().fX) // 클릭한곳이 무기중점의 오른
								{
									if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY < (*Inven_iter)->GetInfo().fY) // Index + 1
									{
										pItem =  (*Inven_iter);
										pItem->GetInfo().bClick = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										return;
									}
									else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY == (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX + 1
									{
										pItem =  (*Inven_iter);
										pItem->GetInfo().bClick = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex + iINVENTILECNTX - 1]->m_bCheck = false;
										return;
									}
									else if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY > (*Inven_iter)->GetInfo().fY) // Index + iINVENCNTX*2 + 1
									{
										pItem =  (*Inven_iter);
										pItem->GetInfo().bClick = true;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX - 1]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2]->m_bCheck = false;
										CTileMgr::GetInstance()->GetInvenTile()[iIndex - iINVENTILECNTX * 2 - 1]->m_bCheck = false;
										return;
									}
								}
							}
						}
					}
				}
			}
		}
		else
			CCollMgr::m_bInvenPush = false;
	}
	if(pItem)
		pItem->Render();
}

void CCollMgr::PotionItemColl(list<CItem*>* _pPotion)
{
	list<CItem*>::iterator Potion_iter = _pPotion->begin();
	list<CItem*>::iterator Potion_iter_end = _pPotion->end();

	POINT	ptMouse = CMouse::GetMousePos();

	RECT	rcInven = {long(CTileMgr::GetInstance()->GetPotionTile()[0]->fX
		- CTileMgr::GetInstance()->GetPotionTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetPotionTile()[0]->fY
		- CTileMgr::GetInstance()->GetPotionTile()[0]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetPotionTile()[3]->fX
		+ CTileMgr::GetInstance()->GetPotionTile()[3]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetPotionTile()[3]->fY
		+ CTileMgr::GetInstance()->GetPotionTile()[3]->fCY / 2.f)};

	if(PtInRect(&rcInven, ptMouse))
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000) // 사용
		{
			int		iIndex = int((ptMouse.y - 577) / 35) + int((ptMouse.x - 424) / 35);

			if(iIndex < 0 || 3 < iIndex)
				return;

			RECT	rcTile = {long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)};

			if(PtInRect(&rcTile, ptMouse) && pItem == NULL && CTileMgr::GetInstance()->GetPotionTile()[iIndex]->m_bCheck == true) // 아이템 집기
			{
				for(Potion_iter; Potion_iter != Potion_iter_end; ++Potion_iter)
				{
					RECT	rcTile = {long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
						, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)
						, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
						, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)};

					RECT	rcItem = {long((*Potion_iter)->GetInfo().fX - (*Potion_iter)->GetInfo().fCX / 2.f)
						, long((*Potion_iter)->GetInfo().fY - (*Potion_iter)->GetInfo().fCY / 2.f)
						, long((*Potion_iter)->GetInfo().fX + (*Potion_iter)->GetInfo().fCX / 2.f)
						, long((*Potion_iter)->GetInfo().fY + (*Potion_iter)->GetInfo().fCY / 2.f)};

					if(PtInRect(&rcTile, ptMouse) && PtInRect(&rcItem, ptMouse) && pItem == NULL)
					{
						CSoundMgr::GetInstance()->ItemSound(L"potiondrink.wav");
						CTileMgr::GetInstance()->GetPotionTile()[iIndex]->m_bCheck = false;
						(*Potion_iter)->GetInfo().bAlive = false;

						if((CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp - CObjMgr::GetInstance()->GetInfo(L"Player")->iHp) > 30)
							CObjMgr::GetInstance()->GetInfo(L"Player")->iHp += 30;
						else
							CObjMgr::GetInstance()->GetInfo(L"Player")->iHp = CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp;

						if((CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp - CObjMgr::GetInstance()->GetInfo(L"Player")->iMp) > 30)
							CObjMgr::GetInstance()->GetInfo(L"Player")->iMp += 30;
						else
							CObjMgr::GetInstance()->GetInfo(L"Player")->iMp =CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp;
						break;
					}
				}
			}
		}

		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000) // 정렬 판매 및 인벤 스왑
		{
			if(m_bPotionPush == true)
				return;
			m_bPotionPush = true;

			int		iIndex = int((ptMouse.y - 577) / 35) + int((ptMouse.x - 424) / 35);

			if(iIndex < 0 || 3 < iIndex)
				return;

			RECT	rcTile = {long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)};

				if(PtInRect(&rcTile, ptMouse) && pItem == NULL && CTileMgr::GetInstance()->GetPotionTile()[iIndex]->m_bCheck == true) // 아이템 집기
				{
					for(Potion_iter; Potion_iter != Potion_iter_end; ++Potion_iter)
					{
						RECT	rcTile = {long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY - CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)
							, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY + CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fCY / 2.f)};

						RECT	rcItem = {long((*Potion_iter)->GetInfo().fX - (*Potion_iter)->GetInfo().fCX / 2.f)
							, long((*Potion_iter)->GetInfo().fY - (*Potion_iter)->GetInfo().fCY / 2.f)
							, long((*Potion_iter)->GetInfo().fX + (*Potion_iter)->GetInfo().fCX / 2.f)
							, long((*Potion_iter)->GetInfo().fY + (*Potion_iter)->GetInfo().fCY / 2.f)};

						if(PtInRect(&rcTile, ptMouse) && PtInRect(&rcItem, ptMouse) && pItem == NULL)
						{
							if((*Potion_iter)->GetInfo().eType == IT_POTION)
							{
								pItem =  (*Potion_iter);
								pItem->GetInfo().bClick = true;
								CTileMgr::GetInstance()->GetPotionTile()[iIndex]->m_bCheck = false;
								CTileMgr::GetInstance()->GetPotionTile()[iIndex]->eType = IT_END;
								CTileMgr::GetInstance()->GetPotionTile()[iIndex]->cType = IST_END;
								return;
							}
						}
					}
				}
				else if(PtInRect(&rcTile, ptMouse) && pItem != NULL && CTileMgr::GetInstance()->GetPotionTile()[iIndex]->m_bCheck == false) // 아이템 넣기
				{
					if(pItem->GetInfo().eType == IT_POTION) 
					{
						pItem->GetInfo().bClick = false;
						pItem->GetInfo().fX = CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fX;
						pItem->GetInfo().fY = CTileMgr::GetInstance()->GetPotionTile()[iIndex]->fY;
						CTileMgr::GetInstance()->GetPotionTile()[iIndex]->m_bCheck = true;
						CItem*	_pItem = new CPotion;
						memcpy(_pItem, pItem, sizeof(CPotion));
						_pPotion->push_back(_pItem);
						pItem->GetInfo().bAlive = false;
						pItem = NULL;
						return;
						
					}
				}
			}
		
		else
			m_bPotionPush = false;
	}

}

void CCollMgr::TileRender(list<CItem*>* _pInven)
{

	list<CItem*>::iterator Inven_iter = _pInven->begin();
	list<CItem*>::iterator Inven_iter_end = _pInven->end();

	POINT	ptMouse = CMouse::GetMousePos();

	RECT	rcInven = {long(CTileMgr::GetInstance()->GetInvenTile()[0]->fX
		- CTileMgr::GetInstance()->GetInvenTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[0]->fY
		- CTileMgr::GetInstance()->GetInvenTile()[0]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fX
		+ CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fY
		+ CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fCY / 2.f)};

	if(PtInRect(&rcInven, ptMouse) && CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true)
	{
		if(pItem->GetInfo().cType == IST_ONE_BY_ONE)
		{

		}
		if(pItem->GetInfo().cType == IST_TWO_BY_THREE)
		{

		}
	}

}
