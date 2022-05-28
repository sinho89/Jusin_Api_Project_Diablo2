#include "StdAfx.h"
#include "RoundFire.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "AmaBoom.h"
#include "FireEnd.h"

CRoundFire::CRoundFire(void)
{
}
CRoundFire::CRoundFire(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}
CRoundFire::~CRoundFire(void)
{
}
void CRoundFire::Initialize(void)
{
	m_tInfo.fCX = 66.f;
	m_tInfo.fCY = 89.f;
	
	m_iFrameX = 0;
	m_iFrameY = 0;
	m_tInfo.bAlive = true;
	CSoundMgr::GetInstance()->EffectSound(L"AmaFire.wav");

	m_dwTime = GetTickCount();
}

void CRoundFire::Progress(void)
{
	FrameMove(36);

	if(m_dwTime + 1500 < GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(L"Fire_end", SORTID_UNITANDOBJ, CFactory<CFireEnd>::CreateObject(m_tInfo.fX, m_tInfo.fY));
		m_dwTime = GetTickCount();
		m_tInfo.bAlive = false;
	}

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();

	if(CScene::m_bBattle == true)
	{
		for(iter; iter != iter_end; ++iter)
		{
			float fX = (*iter)->GetInfo().fX - m_tInfo.fX;								
			float fY = (*iter)->GetInfo().fY - m_tInfo.fY;

			float fDist = sqrt((fX * fX) + (fY * fY));							

			if(fDist < 50)
			{
				(*iter)->GetInfo().m_bHit = true;
				(*iter)->GetInfo().iHp -= 0.0001;
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
			(*Boss_iter)->GetInfo().m_bHit = true;
			(*Boss_iter)->GetInfo().iHp -= 0.0001;
		}
	}

	
}

void CRoundFire::Render(void)
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"GroundFire"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void CRoundFire::Release(void)
{
}