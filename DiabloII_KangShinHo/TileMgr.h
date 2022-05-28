#pragma once

#include "Defines.h"

class CTileMgr
{
CREATE_SINGLETON(CTileMgr);
private:
	DWORD		dwtime; // °Ë»ç¿ë
	vector<TILE*>	m_vecTile;
	vector<ITEM_TILE*>	m_InvenTile;
	vector<ITEM_TILE*>	m_ShopTile;
	vector<ITEM_TILE*>	m_PotionTile;
	vector<ITEM_TILE*>	m_EquiTile;
	vector<ITEM_TILE*>	m_CubeTile;
public:
	vector<TILE*>&	GetTileVector()
	{
		return m_vecTile;
	}
	vector<ITEM_TILE*>& GetShopTile()
	{
		return m_ShopTile;
	}
	vector<ITEM_TILE*>& GetInvenTile()
	{
		return m_InvenTile;
	}
	vector<ITEM_TILE*>& GetPotionTile()
	{
		return m_PotionTile;
	}
	vector<ITEM_TILE*>& GetEquiTile()
	{
		return m_EquiTile;
	}
	vector<ITEM_TILE*>& GetCubeTile()
	{
		return m_CubeTile;
	}
public:
	void SetTile();
	void DeleteTile();
	void SetShopTile();
	void SetInvenTile();
	void SetPotionTile();
	void SetEquiTile();
	void SetCubeTile();
	void DeleteShopTile();
	void DeleteInvenTIle();
	void DeletePotionTile();
	void DeleteEquiTile();
	void DeleteCubeTile();

private:
	CTileMgr(void);
public:
	~CTileMgr(void);
};
