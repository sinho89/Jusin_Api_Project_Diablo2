#include "StdAfx.h"
#include "TileMgr.h"

INIT_SINGLETON(CTileMgr);

CTileMgr::CTileMgr(void)
{
	dwtime = GetTickCount();
}

CTileMgr::~CTileMgr(void)
{
	DeleteTile();

}

void CTileMgr::SetTile()
{
	for(int i = 0; i < iTILECNTY; ++i)
	{
		for(int j = 0; j < iTILECNTX; ++j)
		{
			TILE* pTile = new TILE(float(j * iTILESIZE + (iTILESIZE / 2.f)), float(i * iTILESIZE + (iTILESIZE / 2.f)), float(iTILESIZE), float(iTILESIZE), false, 0, TT_NORMAL, 0);
			m_vecTile.push_back(pTile);
		}
	}
}
void CTileMgr::DeleteTile()
{
	vector<TILE*>::iterator iter = m_vecTile.begin();
	vector<TILE*>::iterator iter_end = m_vecTile.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);
	m_vecTile.clear();
}

void CTileMgr::SetShopTile()
{
	for(int i = 0; i < iSHOPTILECNTY; ++i)
	{
		for(int j = 0; j < iSHOPTILECNTX; ++j)
		{
			ITEM_TILE* pTile = new ITEM_TILE(float(j * iITEMTILESIZEX + (iITEMTILESIZEX / 2.f)) + 22, float(i * iITEMTILESIZEY + (iITEMTILESIZEY / 2.f)) + 76
				, float(iITEMTILESIZEX), float(iITEMTILESIZEY), IT_END, IST_END, false);
			m_ShopTile.push_back(pTile);
		}
	}

}



void CTileMgr::DeleteShopTile()
{
	vector<ITEM_TILE*>::iterator iter = m_ShopTile.begin();
	vector<ITEM_TILE*>::iterator iter_end = m_ShopTile.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);
	m_ShopTile.clear();
}

void CTileMgr::SetInvenTile()
{
	for(int i = 0; i < iINVENTILECNTY; ++i)
	{
		for(int j = 0; j < iINVENTILECNTX; ++j)
		{
			ITEM_TILE* pTile = new ITEM_TILE(float(j * iITEMTILESIZEX + (iITEMTILESIZEX / 2.f)) + 425, float(i * iITEMTILESIZEY + (iITEMTILESIZEY / 2.f)) + 325
				, float(iITEMTILESIZEX), float(iITEMTILESIZEY), IT_END, IST_END, false);
			m_InvenTile.push_back(pTile);
		}
	}
}

void CTileMgr::DeleteInvenTIle()
{
	vector<ITEM_TILE*>::iterator iter = m_InvenTile.begin();
	vector<ITEM_TILE*>::iterator iter_end = m_InvenTile.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);
	m_InvenTile.clear();
}

void CTileMgr::SetPotionTile()
{
	//420, 560, 455, 595
	for(int i = 0; i < iPOTIONMAX; ++i)
	{
		ITEM_TILE* pTile = new ITEM_TILE(float(i * 30 + (30 / 2.f)) + 424, 577
			, float(35), float(35), IT_END, IST_END, false);
		m_PotionTile.push_back(pTile);
	}

}

void CTileMgr::DeletePotionTile()
{
	vector<ITEM_TILE*>::iterator iter = m_PotionTile.begin();
	vector<ITEM_TILE*>::iterator iter_end = m_PotionTile.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);
	m_PotionTile.clear();

}

void CTileMgr::SetEquiTile()
{
	//Rectangle(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 420, 65, 500, 210);
	//Rectangle(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 560, 100, 640, 210);
	ITEM_TILE* pWeaponTile = new ITEM_TILE(460.f, 137.5f, 80, 145, IT_END, IST_END, false);
	ITEM_TILE* pArmorTile = new ITEM_TILE(600.f, 155.f, 80, 110, IT_END, IST_END, false);

	m_EquiTile.push_back(pWeaponTile);
	m_EquiTile.push_back(pArmorTile);
	

}

void CTileMgr::DeleteEquiTile()
{
	vector<ITEM_TILE*>::iterator iter = m_EquiTile.begin();
	vector<ITEM_TILE*>::iterator iter_end = m_EquiTile.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);
	m_EquiTile.clear();

}

void CTileMgr::SetCubeTile()
{
	for(int i = 0; i < iCUBETILECNTY; ++i)
	{
		for(int j = 0; j < iCUBETILECNTX; ++j)
		{
			//Rectangle(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 148, 172, 185, 210);
			ITEM_TILE* pTile = new ITEM_TILE(float(j * iITEMTILESIZEX + (iITEMTILESIZEX / 2.f)) + 148, float(i * iITEMTILESIZEX + (iITEMTILESIZEX / 2.f)) + 172
				, float(iITEMTILESIZEX), float(iITEMTILESIZEX), IT_END, IST_END, false);
			m_CubeTile.push_back(pTile);
		}
	}
}

void CTileMgr::DeleteCubeTile()
{
	vector<ITEM_TILE*>::iterator iter = m_CubeTile.begin();
	vector<ITEM_TILE*>::iterator iter_end = m_CubeTile.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);
	m_CubeTile.clear();

}
