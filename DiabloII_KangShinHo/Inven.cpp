#include "StdAfx.h"
#include "Inven.h"
#include "ImgMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "CollMgr.h"
#include "Item.h"
#include "Mouse.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Shop.h"
#include "Factory.h"

CInven::CInven(void)
{
	CTileMgr::GetInstance()->SetInvenTile();
	CTileMgr::GetInstance()->SetEquiTile();
}

CInven::~CInven(void)
{
	Release();
}

void CInven::Initialize( void )
{
	m_tInfo.fX = iWINCX - iWINCX / 4.f;
	m_tInfo.fY = iWINCY / 2.f - 22;
	m_tInfo.fCX = 400;
	m_tInfo.fCY = 540;

	m_tInfo.iSortNum = 3;

	m_tInfo.bAlive = true;
	m_tInfo.m_UIType = UT_INVEN;

	m_iFrameX = 0;
	m_iFrameY = 0;

}

void CInven::Progress( void )
{
	CCollMgr::GetInstance()->InvenItemColl(&m_InvenList);
	CCollMgr::GetInstance()->EquiItemColl(&m_EquiList, &m_InvenList);
	CCollMgr::GetInstance()->TileRender(&m_InvenList);


	list<CItem*>::iterator iter = m_InvenList.begin();
	list<CItem*>::iterator iter_end = m_InvenList.end();
	
	for(iter; iter != iter_end;)
	{
		if((*iter)->GetInfo().bAlive == false)
		{
			safe_delete((*iter));
			iter = m_InvenList.erase(iter);
		}
		else
		{
			(*iter)->Progress();
			++iter;
		}
	}

	list<CItem*>::iterator Equi_iter = m_EquiList.begin();
	list<CItem*>::iterator Equi_iter_end = m_EquiList.end();

	for(Equi_iter; Equi_iter != Equi_iter_end;)
	{
		if((*Equi_iter)->GetInfo().bAlive == false)
		{
			safe_delete((*Equi_iter));
			Equi_iter = m_EquiList.erase(Equi_iter);
		}
		else
		{
			(*Equi_iter)->Progress();
			++Equi_iter;
		}
	}
}

void CInven::Render( void )
{
	if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true)
	{
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Inven"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 255, 0));

		
			list<CItem*>::iterator iter = m_InvenList.begin();
			list<CItem*>::iterator iter_end = m_InvenList.end();

			for(iter; iter != iter_end; ++iter)
				(*iter)->Render();

			list<CItem*>::iterator Equi_iter = m_EquiList.begin();
			list<CItem*>::iterator Equi_iter_end = m_EquiList.end();

			for(Equi_iter; Equi_iter != Equi_iter_end; ++Equi_iter)
				(*Equi_iter)->Render();

			/*for(int i = 0; i < iINVENTILECNTY; ++i)
			{
				for(int j = 0; j < iINVENTILECNTX; ++j)
				{
					int iIndex = j + i * iINVENTILECNTX; 

					if(CTileMgr::GetInstance()->GetInvenTile()[iIndex]->m_bCheck == true)
					{
						Rectangle(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer")
							,CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f
							,CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f
							,CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fX + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCX / 2.f
							,CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fY + CTileMgr::GetInstance()->GetInvenTile()[iIndex]->fCY / 2.f);
					}
				}
				}*/
			TCHAR				szString[128];

			wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iMoney);
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 550, 500, szString, lstrlen(szString));

	}

}

void CInven::Release( void )
{
	CTileMgr::GetInstance()->DeleteInvenTIle();
	CTileMgr::GetInstance()->DeleteEquiTile();

	list<CItem*>::iterator iter = m_InvenList.begin();
	list<CItem*>::iterator iter_end = m_InvenList.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);

	m_InvenList.clear();

	list<CItem*>::iterator Equi_iter = m_EquiList.begin();
	list<CItem*>::iterator Equi_iter_end = m_EquiList.end();

	for(Equi_iter; Equi_iter != Equi_iter_end; ++Equi_iter)
		safe_delete(*Equi_iter);

	m_EquiList.clear();

	
}

