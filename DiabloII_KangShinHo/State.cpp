#include "StdAfx.h"
#include "State.h"
#include "ObjMgr.h"
#include "ImgMgr.h"

CState::CState(void)
{
}

CState::~CState(void)
{
}

void CState::Initialize( void )
{
	m_tInfo.fX = iWINCX / 4.f;
	m_tInfo.fY = iWINCY / 2.f - 30;
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 540.f;

	m_tInfo.bAlive = true;
	//m_tInfo.m_UIType = UT_STATE;

	m_tInfo.iSortNum = 0;
	m_iFrameX = 0;
	m_iFrameY = 0;
}

void CState::Progress( void )
{
	
}

void CState::Render( void )
{
	if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bStatRender == true)
	{

		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Stat"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 255, 0));

		TCHAR				szString[128];

		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iLevel);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 32, 60, szString, lstrlen(szString));
		wsprintf(szString, L" %d / %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iExp, CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxExp);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 120, 60, szString, lstrlen(szString));

		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iStr);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 110, 105, szString, lstrlen(szString));
		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iDex);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 110, 185, szString, lstrlen(szString));
		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iCon);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 110, 290, szString, lstrlen(szString));
		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iWis);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 110, 370, szString, lstrlen(szString));
		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iStatePoint);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 130, 435, szString, lstrlen(szString));


		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iAtt);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 350, 105, szString, lstrlen(szString));
		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iDef);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 350, 245, szString, lstrlen(szString));

		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iStamina);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 290, 290, szString, lstrlen(szString));
		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxStamina);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 340, 290, szString, lstrlen(szString));

		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iHp);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 290, 320, szString, lstrlen(szString));
		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxHp);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 340, 320, szString, lstrlen(szString));

		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iMp);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 290, 370, szString, lstrlen(szString));
		wsprintf(szString, L" %d", CObjMgr::GetInstance()->GetInfo(L"Player")->iMaxMp);
		TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 340, 370, szString, lstrlen(szString));
	}
}

void CState::Release( void )
{
	
}