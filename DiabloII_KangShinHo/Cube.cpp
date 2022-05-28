#include "StdAfx.h"
#include "Cube.h"
#include "ObjMgr.h"
#include "ImgMgr.h"
#include "TileMgr.h"
#include "CollMgr.h"
#include "Item.h"
#include "Mouse.h"
#include "Portal.h"
#include "Factory.h"

CCube::CCube(void)
{

	CTileMgr::GetInstance()->SetCubeTile();
}

CCube::~CCube(void)
{
	Release();
}

void CCube::Initialize( void )
{
	m_tInfo.fX = iWINCX / 4.f;
	m_tInfo.fY = iWINCY / 2.f - 30;
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 540.f;

	m_tInfo.bAlive = true;
	m_bPortal = false;
	m_bOne = false;
	//m_tInfo.m_UIType = UT_STATE;

	m_tInfo.iSortNum = 0;
	m_iFrameX = 0;
	m_iFrameY = 0;
	m_iCnt = 0;
}

void CCube::Progress( void )
{
	m_iCnt = 0;
	POINT	ptMouse = CMouse::GetMousePos();
	CCollMgr::GetInstance()->CubeItemColl(&m_CubeList);

	list<CItem*>::iterator Cube_iter = m_CubeList.begin();
	list<CItem*>::iterator Cube_iter_end = m_CubeList.end();

	for(Cube_iter; Cube_iter != Cube_iter_end;)
	{
		if((*Cube_iter)->GetInfo().bAlive == false)
		{
			safe_delete((*Cube_iter));
			Cube_iter = m_CubeList.erase(Cube_iter);
		}
		else
		{
			(*Cube_iter)->Progress();
			++Cube_iter;
		}
	}

	RECT	rcButton = {180, 320, 230, 370};

	if(PtInRect(&rcButton, ptMouse))
	{
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if(m_bPortal == true)
				return;
			m_bPortal = true;
			if(m_CubeList.size() >= 2)
			{
				Cube_iter = m_CubeList.begin();

				for(Cube_iter; Cube_iter != Cube_iter_end; ++Cube_iter)
				{

					POINT	m_ptPoint = {(*Cube_iter)->GetInfo().fX, (*Cube_iter)->GetInfo().fY};

					for(int i = 0; i < 12; ++i)
					{

						RECT	rcTile = {long(CTileMgr::GetInstance()->GetCubeTile()[i]->fX - CTileMgr::GetInstance()->GetCubeTile()[i]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetCubeTile()[i]->fY - CTileMgr::GetInstance()->GetCubeTile()[i]->fCY / 2.f)
							, long(CTileMgr::GetInstance()->GetCubeTile()[i]->fX + CTileMgr::GetInstance()->GetCubeTile()[i]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetCubeTile()[i]->fY + CTileMgr::GetInstance()->GetCubeTile()[i]->fCY / 2.f)};

						if(PtInRect(&rcTile,m_ptPoint))
						{
							if(m_iCnt < 2)
							{
								CTileMgr::GetInstance()->GetCubeTile()[i]->m_bCheck = false;
								(*Cube_iter)->GetInfo().bAlive = false;
								++m_iCnt;
							}
						}
					}
				}

				/*for(int j = 0; j < 2; ++j)
				{
					(*Cube_iter)->GetInfo().bAlive = false;
					safe_delete((*Cube_iter));
					Cube_iter = m_CubeList.erase(Cube_iter);
				}*/
			
				CObjMgr::GetInstance()->AddObject(L"CowPortal", SORTID_UNITANDOBJ
					, CFactory<CPortal>::CreateObject(CObj::m_ptPlayer.x + 100, CObj::m_ptPlayer.y, PT_COW));
				if(m_bOne == true)
				{
					list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"CowPortal")->begin();
					(*iter)->GetInfo().bAlive = false;
				}
				m_bOne = true;

			}																									   
		}
		else
			m_bPortal = false;
	}


	//Rectangle(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 180, 320, 230, 370);

}

void CCube::Render( void )
{
	if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bCubeRender == true)
	{

		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Cube"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 255, 0));

		list<CItem*>::iterator Cube_iter = m_CubeList.begin();
		list<CItem*>::iterator Cube_iter_end = m_CubeList.end();

		for(Cube_iter; Cube_iter != Cube_iter_end; ++Cube_iter)
			(*Cube_iter)->Render();
	}
}

void CCube::Release( void )
{
	CTileMgr::GetInstance()->DeleteCubeTile();

	list<CItem*>::iterator Cube_iter = m_CubeList.begin();
	list<CItem*>::iterator Cube_iter_end = m_CubeList.end();

	for(Cube_iter; Cube_iter != Cube_iter_end; ++Cube_iter)
		safe_delete(*Cube_iter);

	m_CubeList.clear();
}