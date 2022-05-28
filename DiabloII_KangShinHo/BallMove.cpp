#include "StdAfx.h"
#include "BallMove.h"
#include "RoundFire.h"
#include "BallBoom.h"
#include "TileMgr.h"

CBallMove::CBallMove(void)
{
}
CBallMove::CBallMove( float _fX, float _fY, eDIRTECTION_TYPE _eType )
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;

}
CBallMove::~CBallMove(void)
{
}

void CBallMove::Initialize( void )
{
	m_iFrameX = 0;
	m_iFrameY = 0;
	m_dwTime = GetTickCount();
	m_dwAlive = GetTickCount();

	switch(m_eType)
	{
	case DIR_DOWN:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fCX = 48.f;
		m_tInfo.fCY = 51.f;
		break;
	case DIR_DOWN_L:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 52.f;
		m_tInfo.fCY = 51.f;
		break;
	case DIR_LEFT:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 51.f;
		break;
	case DIR_UP_L:
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 51.f;
		m_tInfo.fCY = 51.f;
		break;
	case DIR_UP:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY - CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fCX = 48.f;
		m_tInfo.fCY = 51.f;
		break;
	case DIR_UP_R:
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 52.f;
		m_tInfo.fCY = 50.f;
		break;
	case DIR_RIGHT:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 51.f;
		m_tInfo.fCY = 51.f;
		break;
	case DIR_DOWN_R:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 51.f;
		m_tInfo.fCY = 51.f;
		break;
	}

	m_tInfo.bAlive = true;
	m_tInfo.fSpeed = 2.f;
}

void CBallMove::Progress( void )
{
	if(m_dwTime + 200 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY));
	}

	int		iIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX) / iTILESIZE;

	if(CTileMgr::GetInstance()->GetTileVector()[iIndex]->bOption == true)
	{
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY  - iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY + iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY - iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY + iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE * 2,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE * 2,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE * 2));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE * 2));

		CObjMgr::GetInstance()->AddObject(L"Boom",SORTID_UNITANDOBJ, CFactory<CBallBoom>::CreateObject(m_tInfo.fX,m_tInfo.fY,m_eType));

		m_tInfo.bAlive = false;

	}

	if(CScene::m_bBattle == true)
	{
		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();


		for(iter; iter != iter_end; ++iter)
		{
			float fX = (*iter)->GetInfo().fX - m_tInfo.fX;								
			float fY = (*iter)->GetInfo().fY - m_tInfo.fY;

			float fDist = sqrt((fX * fX) + (fY * fY));							

			if(fDist < 50)
			{
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY  - iTILESIZE));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY + iTILESIZE));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY - iTILESIZE));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY + iTILESIZE));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE * 2,m_tInfo.fY));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE * 2,m_tInfo.fY));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE * 2));
				CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE * 2));

				CObjMgr::GetInstance()->AddObject(L"Boom",SORTID_UNITANDOBJ, CFactory<CBallBoom>::CreateObject(m_tInfo.fX,m_tInfo.fY,m_eType));

				//(*iter)->GetInfo().iHp -= 5;
				(*iter)->GetInfo().m_bHit = true;
				m_tInfo.bAlive = false;

			}
		}
	}
	if(CStage::m_bBoss == true)
	{
		list<CObj*>::iterator Boss_iter = CObjMgr::GetInstance()->GetObjList(L"Boss")->begin();

		float fX = (*Boss_iter)->GetInfo().fX - m_tInfo.fX;								
		float fY = (*Boss_iter)->GetInfo().fY - m_tInfo.fY;

		float fDist = sqrt((fX * fX) + (fY * fY));							

		if(fDist < 50)
		{
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY  - iTILESIZE));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY + iTILESIZE));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY - iTILESIZE));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY + iTILESIZE));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE * 2,m_tInfo.fY));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE * 2,m_tInfo.fY));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE * 2));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE * 2));

			CObjMgr::GetInstance()->AddObject(L"Boom",SORTID_UNITANDOBJ, CFactory<CBallBoom>::CreateObject(m_tInfo.fX,m_tInfo.fY,m_eType));

			//(*Boss_iter)->GetInfo().iHp -= 5;
			(*Boss_iter)->GetInfo().m_bHit = true;
			m_tInfo.bAlive = false;

		}

	}


	if(m_dwAlive + 1500 < GetTickCount())
	{
		m_dwAlive = GetTickCount();
		
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY  - iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY + iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY - iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY + iTILESIZE));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE * 2,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE * 2,m_tInfo.fY));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE * 2));
		CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE * 2));
		
		CObjMgr::GetInstance()->AddObject(L"Boom",SORTID_UNITANDOBJ, CFactory<CBallBoom>::CreateObject(m_tInfo.fX,m_tInfo.fY,m_eType));

		m_tInfo.bAlive = false;
	}
	FrameMove(10);
	switch(m_eType)
	{
	case DIR_DOWN:
		m_tInfo.fY += m_tInfo.fSpeed + 1;
		break;
	case DIR_DOWN_L:
		m_tInfo.fX -= m_tInfo.fSpeed;
		m_tInfo.fY += m_tInfo.fSpeed;
		break;
	case DIR_LEFT:
		m_tInfo.fX -= m_tInfo.fSpeed + 1;
		break;
	case DIR_UP_L:
		m_tInfo.fX -= m_tInfo.fSpeed;
		m_tInfo.fY -= m_tInfo.fSpeed;
		break;
	case DIR_UP:
		m_tInfo.fY -= m_tInfo.fSpeed + 1;
		break;
	case DIR_UP_R:
		m_tInfo.fX += m_tInfo.fSpeed;
		m_tInfo.fY -= m_tInfo.fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_tInfo.fSpeed + 1;
		break;
	case DIR_DOWN_R:
		m_tInfo.fX += m_tInfo.fSpeed;
		m_tInfo.fY += m_tInfo.fSpeed;
		break;
	}
}

void CBallMove::Render( void )
{

	switch(m_eType)
	{
	case DIR_DOWN:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_M_D"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_DOWN_L:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_M_D_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_LEFT:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_M_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP_L:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_M_U_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_M_U"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP_R:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_M_U_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_RIGHT:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_M_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_DOWN_R:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_M_D_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	}
}

void CBallMove::Release( void )
{

}
