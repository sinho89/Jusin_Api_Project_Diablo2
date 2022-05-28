#include "StdAfx.h"
#include "AmaRock.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "RoundFire.h"
#include "AmaHit.h"
#include "FireHit.h"
#include "AmaBoom.h"


CAmaRock::CAmaRock(void)
{
}

CAmaRock::~CAmaRock(void)
{
}
void CAmaRock::Initialize(void)
{
	int iRand = rand() % 6;

	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY - 400;
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + (rand() % 250 ) + 50;

	m_tInfo.fCX = 74;
	m_tInfo.fCY = 137.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.fSpeed = 5.f;

	m_tInfo.bAlive = true;

	m_dwTime = GetTickCount();
}

void CAmaRock::Progress(void)
{
	FrameMove(16);
	m_tInfo.fX -= m_tInfo.fSpeed / 2.f;
	m_tInfo.fY += m_tInfo.fSpeed;

	if(CScene::m_bBattle == true)
	{
		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();

		
		for(iter; iter != iter_end; ++iter)
		{
			float fX = (*iter)->GetInfo().fX - m_tInfo.fX;								
			float fY = (*iter)->GetInfo().fY - m_tInfo.fY;

			float fDist = sqrt((fX * fX) + (fY * fY));							

			if(fDist < 100 && m_tInfo.fY >= 200.f - CObj::m_ptScroll.y)
			{
				//CObjMgr::GetInstance()->AddObject(L"AmaHit", SORTID_UNITANDOBJ, CFactory<CAmaHit>::CreateObject(m_tInfo.fX - m_tInfo.fCX / 2.f, m_tInfo.fY + m_tInfo.fCY / 2.f));
				CObjMgr::GetInstance()->AddObject(L"AmaBoom", SORTID_UNITANDOBJ, CFactory<CAmaBoom>::CreateObject(m_tInfo.fX - m_tInfo.fCX / 2.f, m_tInfo.fY + m_tInfo.fCY / 2.f));
				CObjMgr::GetInstance()->AddObject(L"RoundFire", SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - m_tInfo.fCX / 2.f, m_tInfo.fY + m_tInfo.fCY / 2.f));
				(*iter)->GetInfo().iHp -= 20;
				CObjMgr::GetInstance()->AddObject(L"AmaHit", SORTID_SKILL, CFactory<CAmaHit>::CreateObject((*iter)->GetInfo().fX, (*iter)->GetInfo().fY));
				(*iter)->GetInfo().m_bHit = true;
				m_tInfo.bAlive = false;
			}

			/*POINT	ptRock = { m_tInfo.fX - m_tInfo.fCX / 2.f, m_tInfo.fY + m_tInfo.fCY / 2.f };

			RECT rcMonster = {(*iter)->GetInfo().fX - (*iter)->GetInfo().fCX / 2.f
							, (*iter)->GetInfo().fY - (*iter)->GetInfo().fCY / 2.f
							, (*iter)->GetInfo().fX + (*iter)->GetInfo().fCX / 2.f
							, (*iter)->GetInfo().fY + (*iter)->GetInfo().fCY / 2.f};

			if(PtInRect(&rcMonster, ptRock))
			{
				CObjMgr::GetInstance()->AddObject(L"AmaHit", SORTID_UNITANDOBJ, CFactory<CAmaHit>::CreateObject(m_tInfo.fX - m_tInfo.fCX / 2.f, m_tInfo.fY + m_tInfo.fCY / 2.f));
				(*iter)->GetInfo().iHp -= 50;
				m_tInfo.bAlive = false;
			}*/

		}
		if(CStage::m_bBoss == true)
		{
			list<CObj*>::iterator Boss_iter = CObjMgr::GetInstance()->GetObjList(L"Boss")->begin();

			float fX = (*Boss_iter)->GetInfo().fX - m_tInfo.fX;								
			float fY = (*Boss_iter)->GetInfo().fY - m_tInfo.fY;

			float fDist = sqrt((fX * fX) + (fY * fY));							

			if(fDist < 50)
			{
				(*Boss_iter)->GetInfo().iHp -= 10;
				(*Boss_iter)->GetInfo().m_bHit = true;
				m_tInfo.bAlive = false;
			}
		}
	}

	if(m_dwTime + (rand() % 3000 + 800) < GetTickCount())
	{
		m_dwTime = GetTickCount();
		CObjMgr::GetInstance()->AddObject(L"AmaBoom", SORTID_UNITANDOBJ, CFactory<CAmaBoom>::CreateObject(m_tInfo.fX - m_tInfo.fCX / 2.f, m_tInfo.fY + m_tInfo.fCY / 2.f));
		CObjMgr::GetInstance()->AddObject(L"RoundFire", SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - m_tInfo.fCX / 2.f, m_tInfo.fY + m_tInfo.fCY / 2.f));
		m_tInfo.bAlive = false;
	}
}

void CAmaRock::Render(void)
{
	/*HDC			dcTemp = CreateCompatibleDC(GetDC(g_hWnd));
	HBITMAP		hBitMap = CreateCompatibleBitmap(GetDC(g_hWnd),
		int(m_tInfo.fCX), int(m_tInfo.fCY));

	HBITMAP	hOld = (HBITMAP)SelectObject(dcTemp, hBitMap);

	//투명화 처리를 하기 위해서 지금까지 오브젝트들이 그려져 있는
	//백버퍼를 새로운 DC에 복사하고 그 Dc 위에 플레이어 이미지를 올리고
	//그 Dc를 통채로 백버퍼에 투명하게 그려야 된다.
	//원본의 시작 위치는 플레이어 위치를 중점으로 사이즈와 스크롤 값을 더해서 계산한다.
	int iOriStartX = int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x;
	int iOriStartY = int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y;

	//대상의 시작 위치는 일단 0으로 초기화
	int iDestStartX = 0;
	int iDestStartY = 0;

	//대상의 끝위치는 플레이어 사이즈만큼 일단 초기화 해 둔다.
	int iDestEndX = int(m_tInfo.fCX);
	int iDestEndY = int(m_tInfo.fCY);

	//원본의 복사 시작위치가 음수가 되면 복사가
	//되지 않으므로 양수값으로 초기화를 해 주어야 한다.
	if(iOriStartX < 0)
	{
		iDestStartX = -iOriStartX;
		//원본 시작 위치는 0보다 작으면 0으로 고정
		iOriStartX = 0;
	}
	else if(iOriStartX > iWINCX - m_tInfo.fCX)
	{
		iDestEndX = int(m_tInfo.fCX + (iWINCX - m_tInfo.fCX) - iOriStartX);
	}

	if(iOriStartY < 0)
	{
		iDestStartY = -iOriStartY;
		iOriStartY = 0;
	}
	else if(iOriStartY > iWINCY - m_tInfo.fCY)
	{
		iDestEndY = int(m_tInfo.fCY + ((iWINCY - m_tInfo.fCY) - iOriStartY));
	}

	TransparentBlt(dcTemp,
		iDestStartX,
		iDestStartY,
		iDestEndX,
		iDestEndY,
		*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
		iOriStartX,
		iOriStartY,
		iDestEndX,
		iDestEndY,
		RGB(255, 255, 255));*/
	
	/*TransparentBlt(dcTemp,0
		, 0
		, 800
		, 600
		, *CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 0
		, 0, 800, 600, RGB(0, 0, 0));*/

	/*TransparentBlt(dcTemp,0 
		, 0
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"AmaRock"), m_iFrameX * m_tInfo.fCX
		, 0, int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

	//플레이어 검은색 배경 날려
	//시간이 지날 때마다 점점 투명해 지게 해 놨다.

	BLENDFUNCTION	tFunction;
	tFunction.BlendOp = AC_SRC_OVER;
	tFunction.BlendFlags = 0;
	tFunction.SourceConstantAlpha = 200;	//이게 투명한 정도를 나타낸다 0 ~ 255
	tFunction.AlphaFormat = 0;


	AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
		int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x,
		int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		dcTemp,
		0, //프레임 스타트 * 사이즈
		0,//이미지 Y 종료 * 사이즈
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		tFunction);	//플레이어 검은색 배경 날려*/

	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"AmaRock"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

	

}

void CAmaRock::Release(void)
{

}