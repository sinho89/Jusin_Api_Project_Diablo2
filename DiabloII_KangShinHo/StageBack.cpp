#include "StdAfx.h"
#include "StageBack.h"
#include "ObjMgr.h"
#include "TileMgr.h"

CStageBack::CStageBack(void)
:m_bMoveX(false)
,m_bMoveY(false)
{
}

CStageBack::~CStageBack(void)
{
}

void CStageBack::Initialize( void )
{
	m_tInfo.fX = 0;
	m_tInfo.fY = 0;
	m_tInfo.fCX = 4456;
	m_tInfo.fCY = 2850;
	//3456
	//1850

	m_tInfo.bAlive = true;

	m_tInfo.fSpeed = 7.f;
	m_tInfo.fAngle = 0.f;

	m_iFrameX = 0;
	m_iFrameY = 0;
	//-1328
	//-625;
	CObj::m_ptScroll.x = -1828;
	CObj::m_ptScroll.y = -1125;
	CObj::m_ptTileScroll.x = 0;
	CObj::m_ptTileScroll.y = 0;

	m_tInfo.m_bTile = false;
	m_bTileView = false;
	m_bShake = false;

	m_tInfo.iSortNum = 0;

	dwTime = GetTickCount();
}

void CStageBack::Progress( void )
{
	// 수정필요

	if(CObj::m_ptScroll.x > 0)
		CObj::m_ptScroll.x = 0;
	
	if(CObj::m_ptScroll.y > 0)
		CObj::m_ptScroll.y = 0;
	
	if(CObj::m_ptScroll.x < -(m_tInfo.fCX - iWINCX))
	{
		CObj::m_ptScroll.x = -long(m_tInfo.fCX - iWINCX);
	}
	if(CObj::m_ptScroll.y < -(m_tInfo.fCY - iWINCY))
	{
		CObj::m_ptScroll.y = -long(m_tInfo.fCY - iWINCY);
	}

	if(GetAsyncKeyState('U') & 0x8000)
	{
		if(m_bTileView == true)
			return;
		m_bTileView = true;
		if(m_tInfo.m_bTile == false)
			m_tInfo.m_bTile = true;

		else if(m_tInfo.m_bTile == true)
			m_tInfo.m_bTile = false;
	}
	else
		m_bTileView = false;
}

void CStageBack::Render( void )
{
	if(CScene::m_bHome == true && CScene::m_bBattle == false)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),0 + CObj::m_ptScroll.x
			, 0 +  CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY) 
			, *CImgMgr::GetInstance()->GetTexture(L"StageBack"), 0
			, 0, SRCCOPY);


		if(m_tInfo.m_bTile == true)
		{
			int iCullX = iWINCX / iTILESIZE;		
			int iCullY = iWINCY / iTILESIZE;	

			int iCullStartX = -CObj::m_ptScroll.x / iTILESIZE;
			int iCullStartY = -CObj::m_ptScroll.y / iTILESIZE;

			int iCullEndX = iCullStartX + iCullX + 2;
			int iCullEndY = iCullStartY + iCullY + 2;

			for(int i = iCullStartY; i < iCullEndY; ++i)
			{
				for(int j = iCullStartX; j < iCullEndX; ++j)
				{
					int iIndex = j + i * iTILECNTX;

					if(iIndex < 0 || iIndex >= iTILECNTX * iTILECNTY)
						continue;

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX - CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX / 2) + CObj::m_ptScroll.x
						, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY - CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY / 2)  + CObj::m_ptScroll.y
						, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX )
						, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY )
						, *CImgMgr::GetInstance()->GetTexture(L"Tile"), int( CTileMgr::GetInstance()->GetTileVector()[iIndex]->iDrawID  * CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX)
						, 0, 
						int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX), int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY), RGB(255, 255, 255));
				}
			}
		}
	}

	else if (CScene::m_bHome == false && CScene::m_bBattle == true)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),0 + CObj::m_ptScroll.x
			, 0 +  CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY) 
			, *CImgMgr::GetInstance()->GetTexture(L"BattleBack"), 0
			, 0, SRCCOPY);
		

		if(m_tInfo.m_bTile == true)
		{
			int iCullX = iWINCX / iTILESIZE;		
			int iCullY = iWINCY / iTILESIZE;	

			int iCullStartX = -CObj::m_ptScroll.x / iTILESIZE;
			int iCullStartY = -CObj::m_ptScroll.y / iTILESIZE;

			int iCullEndX = iCullStartX + iCullX + 2;
			int iCullEndY = iCullStartY + iCullY + 2;

			for(int i = iCullStartY; i < iCullEndY; ++i)
			{
				for(int j = iCullStartX; j < iCullEndX; ++j)
				{
					int iIndex = j + i * iTILECNTX;

					if(iIndex < 0 || iIndex >= iTILECNTX * iTILECNTY)
						continue;

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX - CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX / 2) + CObj::m_ptScroll.x
						, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY - CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY / 2)  + CObj::m_ptScroll.y
						, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX )
						, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY )
						, *CImgMgr::GetInstance()->GetTexture(L"Tile"), int( CTileMgr::GetInstance()->GetTileVector()[iIndex]->iDrawID  * CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX)
						, 0, 
						int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX), int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY), RGB(255, 255, 255));
				}
			}
		}
	}
}

void CStageBack::Release( void )
{
	CTileMgr::GetInstance()->DeleteTile();
}
