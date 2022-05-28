#include "StdAfx.h"
#include "Npc.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "Factory.h"
#include "Shop.h"
#include "Inven.h"

CNpc::CNpc(void)
{
}

CNpc::~CNpc(void)
{
}
void CNpc::Initialize( void )
{

	INFO* pBackGroundInfo = CObjMgr::GetInstance()->GetInfo(L"StageBack");

	m_tInfo.fX = (pBackGroundInfo->fCX / 2.f) - 400;
	m_tInfo.fY = (pBackGroundInfo->fCY / 2.f) - 400;

	m_tInfo.fCX = 27.f;
	m_tInfo.fCY = 68.f;

	m_tInfo.iSortNum = 1;
	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
	m_bPush = false;
}

void CNpc::Progress( void )
{
	if(CScene::m_bHome == true && CScene::m_bBattle == false)
	{
		FrameMove(13);
		POINT ptMouse = CMouse::GetMousePos();

		RECT	rcShop = {long(m_tInfo.fX - m_tInfo.fCX / 2.f) 
						, long(m_tInfo.fY - m_tInfo.fCY / 2.f) 
						, long(m_tInfo.fX + m_tInfo.fCX / 2.f) 
						, long(m_tInfo.fY + m_tInfo.fCY / 2.f) };

		ptMouse.x -= CObj::m_ptScroll.x;
		ptMouse.y -= CObj::m_ptScroll.y;


		if(PtInRect(&rcShop, ptMouse))
		{
			if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{

				float fX = m_tInfo.fX - CObj::m_ptPlayer.x;								
				float fY = m_tInfo.fY - CObj::m_ptPlayer.y;

				float fDist = sqrt((fX * fX) + (fY * fY));	

				if(fDist > 50)
					return;

				if(m_bPush == true)
					return;
				m_bPush = true;
				
				if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bShopRender == false)
				{
					if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bStatRender == true)
					{
						CObj::m_ptScroll.x -= 200;
						CObjMgr::GetInstance()->GetRender(L"Player")->m_bStatRender = false;
					}
					if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bCubeRender == true)
					{
						CObj::m_ptScroll.x -= 200;
						CObjMgr::GetInstance()->GetRender(L"Player")->m_bCubeRender = false;
					}

					CObjMgr::GetInstance()->GetRender(L"Player")->m_bShopRender = true;
					CObj::m_ptScroll.x += 200;
					//CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender = true;
				}
			}
		}
		else
			m_bPush = false;

		if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bShopRender == true)
		{
			float fX = m_tInfo.fX - CObj::m_ptPlayer.x;								
			float fY = m_tInfo.fY - CObj::m_ptPlayer.y;

			float fDist = sqrt((fX * fX) + (fY * fY));	

			if(fDist >= 100)
			{
				CObjMgr::GetInstance()->GetRender(L"Player")->m_bShopRender = false;
				CObj::m_ptScroll.x -= 200;
			}
		}
	}


	
}

void CNpc::Render( void )
{
	if(CScene::m_bHome == true && CScene::m_bBattle == false)
	{
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"NPC"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
	}

}

void CNpc::Release( void )
{

}