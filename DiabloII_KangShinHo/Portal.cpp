#include "StdAfx.h"
#include "Portal.h"
#include "Mouse.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Loading.h"

CPortal::CPortal(void)
{
}

CPortal::~CPortal(void)
{
}

void CPortal::Initialize( void )
{
	if(m_eType == PT_COW)
	{
		m_tInfo.fCX = 204;
		m_tInfo.fCY = 204;
		CSoundMgr::GetInstance()->EffectSound(L"portalcast.wav");
	}

	m_tInfo.bAlive = true;
	m_iFrameX = 0;
	m_iFrameY = 0;
	m_bOpen = false;
	m_bLoading = false;

}

void CPortal::Progress( void )
{

	POINT ptMouse = CMouse::GetMousePos();

	ptMouse.x -= CObj::m_ptScroll.x;
	ptMouse.y -= CObj::m_ptScroll.y;

	if(m_eType == PT_COW)
	{
		if(m_bOpen == false)
		{
			FramePortalMove(15);
			if(m_iFrameX == 13)
			{
				m_tInfo.fCX = 115;
				m_tInfo.fCY = 154;
				m_bOpen = true;
				m_iFrameX = 0;
			}
		}
		else
			FramePortalMove(14);
	}

	float fX = m_tInfo.fX - CObj::m_ptPlayer.x;								
	float fY = m_tInfo.fY - CObj::m_ptPlayer.y;

	float fDist = sqrt((fX * fX) + (fY * fY));	

	if(m_bLoading == false)
	{
		if(fDist < 50)
		{
			if(CScene::m_bHome == true && CScene::m_bBattle == false)
			{
				CScene::m_bHome = false;
				CScene::m_bBattle = true;
				CScene::m_bTileSet = true;
			}
			else if(CScene::m_bHome == false && CScene::m_bBattle == true)
			{
				CScene::m_bHome = true;
				CScene::m_bBattle = false;
				CScene::m_bTileSet = true;
			}
			
			CObjMgr::GetInstance()->AddObject(L"Loading", SORTID_LAST, CFactory<CLoading>::CreateObject());
			m_bLoading = true;
			/*CScene::m_bHomeToBattle = true;
			CObj::m_bRound = true;
			memcpy(&CObj::m_tSaveInfo, CObjMgr::GetInstance()->GetInfo(L"Player"), sizeof(INFO));*/
		}
	}
	else if(fDist > 100)
	{
		m_bLoading = false;
	}

}

void CPortal::Render( void )
{
	if(m_eType == PT_COW)
	{
		if(m_bOpen == false)
		{
			TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
				, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"CowPortal"), int(m_iFrameX  * m_tInfo.fCX)
				, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

		}
		if(m_bOpen == true)
		{
			TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
				, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"CowPortalDoor"), int(m_iFrameX  * m_tInfo.fCX)
				, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		}
		
	}
}

void CPortal::Release( void )
{

}
