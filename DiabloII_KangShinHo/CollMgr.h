#pragma once

#include "Defines.h"

class CItem;
class CCollMgr
{
CREATE_SINGLETON(CCollMgr);

private:
	static bool m_bCubePush;
	static bool	m_bInvenPush;
	static bool	m_bShopPush;
	static bool m_bInvenPush2;
	static bool m_bPotionPush;
	static bool m_bEquiPush;
	static bool m_bWeaponPush;
	static bool m_bArmorPush;
	static bool m_bUsePush;
	static bool m_bSell;
	static bool m_bBuy;

	static CItem*		pItem;
public:
	static CItem* GetHandItem()
	{
		return pItem;
	}
	static void RectAndDoteColl(INFO* _pDest, INFO* _pSource);
	static void NormalColl(INFO* _pDest, INFO* _pSource);
	static void ShopItemToTile(list<CItem*>* _pItem);
	static void InvenItemToTile(list<CItem*>* _pItem);
	static void ShopItemColl(list<CItem*>* _pShop);
	static void InvenItemColl(list<CItem*>* _pInven);
	static void PotionItemColl(list<CItem*>* _pPotion);
	static void EquiItemColl(list<CItem*>* _pEqui, list<CItem*>* _pInven);
	static void CubeItemColl(list<CItem*>* _pCube);
	static void TileRender(list<CItem*>* _pInven);
private:
	CCollMgr(void);
public:
	~CCollMgr(void);
};
