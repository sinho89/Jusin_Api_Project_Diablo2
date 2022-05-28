#include "StdAfx.h"
#include "ShockEff.h"

CShockEff::CShockEff(void)
{
}

CShockEff::CShockEff( float _fX, float _fY, eDIRTECTION_TYPE _eType )
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;
}

CShockEff::~CShockEff(void)
{
}

void CShockEff::Initialize( void )
{ // Shock_D
	switch(m_eType)
	{
	case DIR_DOWN:
		m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fCX = 74.f;
		m_tInfo.fCY = 47.f;
		break;
	case DIR_DOWN_L:
		m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 76.f;
		m_tInfo.fCY = 48.f;
		break;
	case DIR_LEFT:
		m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 79.f;
		m_tInfo.fCY = 47.f;
		break;
	case DIR_UP_L:
		m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 80.f;
		m_tInfo.fCY = 49.f;
		break;
	case DIR_UP:
		m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY - CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fCX = 73.f;
		m_tInfo.fCY = 48.f;
		break;
	case DIR_UP_R:
		m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 79.f;
		m_tInfo.fCY = 47.f;
		break;
	case DIR_RIGHT:
		m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 76.f;
		m_tInfo.fCY = 44.f;
		break;
	case DIR_DOWN_R:
		m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 75.f;
		m_tInfo.fCY = 46.f;
		break;
	}

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
	m_tInfo.fSpeed = 6.f;

}

void CShockEff::Progress( void )
{
	FrameMove(7);
	if(m_iFrameX == 6)
		m_tInfo.bAlive = false;

	switch(m_eType)
	{
	case DIR_DOWN:
		m_tInfo.fY += m_tInfo.fSpeed + 3;
		break;
	case DIR_DOWN_L:
		m_tInfo.fX -= m_tInfo.fSpeed;
		m_tInfo.fY += m_tInfo.fSpeed;
		break;
	case DIR_LEFT:
		m_tInfo.fX -= m_tInfo.fSpeed + 3;
		break;
	case DIR_UP_L:
		m_tInfo.fX -= m_tInfo.fSpeed;
		m_tInfo.fY -= m_tInfo.fSpeed;
		break;
	case DIR_UP:
		m_tInfo.fY -= m_tInfo.fSpeed + 3;
		break;
	case DIR_UP_R:
		m_tInfo.fX += m_tInfo.fSpeed;
		m_tInfo.fY -= m_tInfo.fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_tInfo.fSpeed + 3;
		break;
	case DIR_DOWN_R:
		m_tInfo.fX += m_tInfo.fSpeed;
		m_tInfo.fY += m_tInfo.fSpeed;
		break;
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
				(*iter)->GetInfo().m_bHit = true;
				(*iter)->GetInfo().iHp -= 20;
				m_tInfo.bAlive = false;
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
				(*Boss_iter)->GetInfo().m_bHit = true;
				(*Boss_iter)->GetInfo().iHp -= 20;
				m_tInfo.bAlive = false;
			}
		}
		
	}
}

void CShockEff::Render( void )
{
	switch(m_eType)
	{
	case DIR_DOWN:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Shock_D"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_DOWN_L:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Shock_D_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_LEFT:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Shock_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP_L:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Shock_U_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Shock_U"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP_R:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Shock_U_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_RIGHT:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Shock_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_DOWN_R:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Shock_D_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	}
}

void CShockEff::Release( void )
{

}
