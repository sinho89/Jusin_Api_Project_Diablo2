#include "StdAfx.h"
#include "Rock.h"
#include "ObjMgr.h"

CRock::CRock(void)
{
}

CRock::~CRock(void)
{
}

void CRock::Initialize( void )
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 12.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
	m_tInfo.fAngle = rand() % 180;
	m_tInfo.fSpeed = rand() % 50 + 200.f;

	m_dwTime = GetTickCount();

}

void CRock::Progress( void )
{
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX;
	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY;

	m_ptPoint.x = long(m_tInfo.fX + m_tInfo.fSpeed * cosf(m_tInfo.fAngle * 3.14f / 180.f));
	m_ptPoint.y = long(m_tInfo.fY - (m_tInfo.fSpeed - 100) * sinf(m_tInfo.fAngle * 3.14f / 180.f));

	m_tInfo.fAngle += 5.f;

	FrameMove(20);

	if(CScene::m_bBattle == true)
	{
		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();


		for(iter; iter != iter_end; ++iter)
		{
			float fX = (*iter)->GetInfo().fX - m_ptPoint.x;								
			float fY = (*iter)->GetInfo().fY - m_ptPoint.y;

			float fDist = sqrt((fX * fX) + (fY * fY));							

			if(fDist < 50)
			{
				(*iter)->GetInfo().iHp -= 0.025;
				(*iter)->GetInfo().m_bHit = true;
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
				(*Boss_iter)->GetInfo().iHp -= 0.025;
				(*Boss_iter)->GetInfo().m_bHit = true;
				m_tInfo.bAlive = false;
			}
		}

	}

	if(m_dwTime + 5000 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		m_tInfo.bAlive = false;

	}
	if(CScene::m_bBattle == false)
	{
		m_tInfo.bAlive = false;
	}
}

void CRock::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_ptPoint.x - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_ptPoint.y - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"HurriRock"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

}

void CRock::Release( void )
{

}
