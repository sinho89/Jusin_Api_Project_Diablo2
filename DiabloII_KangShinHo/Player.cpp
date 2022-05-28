#include "StdAfx.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "AstarMgr.h"
#include "Factory.h"
#include "Inven.h"
#include "Shop.h"
#include "Mouse.h"
#include "UnderBar.h"
#include "ObjMgr.h"
#include "TransForm.h"
#include "Amagetdon.h"
#include "Hurricane.h"
#include "Tornado.h"
#include "Shork.h"
#include "Item.h"
#include "AmaOver.h"
#include "ColdOver.h"
#include "Ball.h"
#include "BallOver.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::Initialize( void )
{

	INFO* pBackGroundInfo = CObjMgr::GetInstance()->GetInfo(L"StageBack");

	m_tInfo.iLevel = 1;
	m_tInfo.iMoney = 10000;
	m_tInfo.iStr = 40;
	m_tInfo.iDex = 30;
	m_tInfo.iCon = 50;
	m_tInfo.iWis = 45;
	m_tInfo.iAtt = 20;
	m_tInfo.iDef = 10;
	m_tInfo.iMaxHp = 80;
	m_tInfo.iHp = 80;
	m_tInfo.iMaxMp = 80;
	m_tInfo.iMp = 80;
	m_tInfo.iStatePoint = 0;
	m_tInfo.iMaxStamina = 10000;
	m_tInfo.iStamina = 10000;

	m_tInfo.iExp = 0;
	m_tInfo.iMaxExp = 1200;

	m_tInfo.fCX = 43.f;
	m_tInfo.fCY = 77.f;

	m_bStat = false;
	m_bCube = false;
	m_bRun = false;
	m_bMove = false;
	m_bSetHit = false;
	m_bGetHit = false;
	m_bRunPush = false;
	m_bTransForm = false;
	m_bHitTick = false;
	m_bSkillTick = false;
	m_bTransFormTick = false;
	m_bShake = false;
	m_bTor = false;
	m_bShock = false;

	m_iFrameX = 0;
	m_iFrameY = 0;
	m_tInfo.fSpeed = 2.f;

	m_tInfo.iSortNum = 1;
	m_tInfo.iKillCnt = 0;

	m_bCanMove = false;
	m_tInfo.fAngle = 270.f;
	m_tInfo.bAlive = true;
	m_tInfo.m_bBoss = false;
	m_tInfo.m_bAtt = false;
	m_tInfo.m_bCast1 = false;
	m_tInfo.m_bCast2 = false;
	m_tInfo.m_bGetHit = false;

	m_Render.m_bInvenRender = false;
	m_Render.m_bShopRender = false;
	m_Render.m_bQuestRender = false;
	m_Render.m_bSkillRender = false;
	m_eType = KT_NORMAL;
	m_DIRTYPE = DIR_DOWN;

	m_dwTime = GetTickCount();
	m_dwShake = GetTickCount();


	CObj::m_ptPlayer.x = long(pBackGroundInfo->fCX / 2.f);
	CObj::m_ptPlayer.y = long(pBackGroundInfo->fCY / 2.f);

	m_eSaveType[0] = KT_END;
	m_eSaveType[1] = KT_END;
	m_eSaveType[2] = KT_END;
	m_eSaveType[3] = KT_END;
	m_eSaveType[4] = KT_END;
}

void CPlayer::Progress( void )
{
	if(m_tInfo.iHp <= 0)
		m_tInfo.iHp = m_tInfo.iMaxHp;
	if(m_tInfo.iMp <= 0)
		m_tInfo.iMp = m_tInfo.iMaxMp;
	if(m_tInfo.iStamina <= 0)
		m_tInfo.iStamina = m_tInfo.iMaxStamina;

	cout << "피격 :" << m_tInfo.m_bGetHit << endl;
	cout << "공격 :" << m_tInfo.m_bAtt << endl;
	cout << "캐스팅 :" << m_tInfo.m_bCast1 << endl;

	if(m_tInfo.m_bAtt == true && m_tInfo.m_bGetHit == true)
	{
		m_tInfo.m_bAtt = false;
		m_tInfo.m_bGetHit = true; 
	}

	if(m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == true)
	{
		m_tInfo.m_bCast1 = false;
		m_tInfo.m_bGetHit = true; 
	}
	if(m_tInfo.m_bCast1 == true && m_tInfo.m_bAtt == true)
	{
		m_tInfo.m_bAtt = false;
		m_tInfo.m_bCast1 = true; 
	}

	if(CScene::m_bBattle == true)
	{
		if(m_bRun == true && m_bMove == true)
		{
			if(m_tInfo.iStamina > 0)
			{
				m_tInfo.iStamina -= 30;
			}
			else if(m_tInfo.iStamina <= 0)
			{
				m_bRun = false;
			}
		}
		if((m_bRun == false && m_bMove == false)
			|| (m_bRun == false && m_bMove == true)
			|| (m_bRun == true && m_bMove == false))
		{
			if(m_tInfo.iStamina < m_tInfo.iMaxStamina)
			{
				m_tInfo.iStamina += 10;
			}
			else if(m_tInfo.iStamina >= m_tInfo.iMaxStamina)
			{
				m_tInfo.iStamina = m_tInfo.iMaxStamina;
			}
		}
	}
	if(m_bTransForm == true && m_bTransFormTick == false)
	{

		m_iFrameY = 0;
		m_DIRTYPE = DIR_END;
		m_tInfo.fCX = 80.f;
		m_tInfo.fCY = 103.f;
		FrameMove(16);
		if(m_iFrameX == 15)
		{
			CSoundMgr::GetInstance()->PlayerSound(L"BearNeutral.wav");
			m_tInfo.iAtt += 30;
			m_DIRTYPE = DIR_DOWN;
			m_iFrameX = 0;
			m_bTransFormTick = true;
		}
	} // 변신 풀기 밑에


	else if(m_bTransForm == false && m_bTransFormTick == true)
	{
		CSoundMgr::GetInstance()->PlayerSound(L"windcast.wav");
		CObjMgr::GetInstance()->AddObject(L"TransEff", SORTID_UNITANDOBJ, CFactory<CTransForm>::CreateObject());

		m_dwTime = GetTickCount();
		m_tInfo.fCX = 43.f;
		m_tInfo.fCY = 77.f;
		m_tInfo.iAtt -= 30;
		m_bTransFormTick = false;
	}
	KeyCheck();
	Moving();

	if(m_bTor == true || m_bShock == true)
		SetMotion();
	else if(m_bTor == false && m_bShock == false)
		DirectPos();

	SetPos();
	Hit();
	SkillCheck();


	cout << m_tInfo.iHp << endl;

	m_tInfo.fX = float(CObj::m_ptPlayer.x);
	m_tInfo.fY = float(CObj::m_ptPlayer.y);	
}


void CPlayer::Render( void )
{
	if(m_Render.m_bInvenRender == false && m_Render.m_bShopRender == true 
		|| m_Render.m_bStatRender == true || m_Render.m_bCubeRender == true)
	{
		if(m_bMove == true && m_bTransForm == false) // 움직일때 걷기 & 뛰기 (변신전)
		{
			if(m_bRun == true)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_R"), int(m_iFrameX) * int(m_tInfo.fCX)
					, int(m_iFrameY) * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_bRun == false)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_W"), int(m_iFrameX)  * int(m_tInfo.fCX)
					, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
		}

		if(m_bMove == true  && m_bTransForm == true && m_bTransFormTick == true) // 움직일때 걷기 & 뛰기 (변신후)
		{
			if(m_bRun == true)
			{
				if(m_DIRTYPE == DIR_DOWN)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_LEFT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_RIGHT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_bRun == false)
			{
				if(m_DIRTYPE == DIR_DOWN)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_LEFT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_RIGHT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
		}

		else if(m_bMove == false && m_bTransForm == false) // 평소 상태 ( 변신 전)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_Att"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == true && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_GetHit"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}

			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == true)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f - 10
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_Cast"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

			}
		}

		else if(m_bMove == false && m_bTransForm == true && m_bTransFormTick == false) // 곰변신 스킬중
		{
			TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
				, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"Skill_Bear"), int(m_iFrameX  * m_tInfo.fCX)
				, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		}

		else if(m_bMove == false && m_bTransForm == true && m_bTransFormTick == true) // 평소 상태 ( 변신 후)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_D"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_DOWN_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_D_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_DOWN_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_D_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_LEFT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_RIGHT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_UP)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_U"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_UP_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_U_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}

			else if(m_DIRTYPE == DIR_UP_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f + 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_U_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}

		}

	}
	if(m_Render.m_bInvenRender == true && m_Render.m_bShopRender == false 
		&& m_Render.m_bStatRender == false && m_Render.m_bCubeRender == false)
	{
		if(m_bMove == true && m_bTransForm == false) // 움직일때 걷기 & 뛰기 (변신전)
		{
			if(m_bRun == true)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_R"), int(m_iFrameX) * int(m_tInfo.fCX)
					, int(m_iFrameY) * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_bRun == false)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_W"), int(m_iFrameX)  * int(m_tInfo.fCX)
					, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
		}

		if(m_bMove == true  && m_bTransForm == true && m_bTransFormTick == true) // 움직일때 걷기 & 뛰기 (변신후)
		{
			if(m_bRun == true)
			{
				if(m_DIRTYPE == DIR_DOWN)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_LEFT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_RIGHT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_bRun == false)
			{
				if(m_DIRTYPE == DIR_DOWN)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_LEFT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_RIGHT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
		}

		else if(m_bMove == false && m_bTransForm == false) // 평소 상태 ( 변신 전)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_Att"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == true && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_GetHit"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}

			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == true)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f - 10
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_Cast"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

			}
		}

		else if(m_bMove == false && m_bTransForm == true && m_bTransFormTick == false) // 곰변신 스킬중
		{
			TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
				, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"Skill_Bear"), int(m_iFrameX  * m_tInfo.fCX)
				, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		}

		else if(m_bMove == false && m_bTransForm == true && m_bTransFormTick == true) // 평소 상태 ( 변신 후)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_D"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_DOWN_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_D_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_DOWN_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_D_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_LEFT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_RIGHT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_UP)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_U"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_DIRTYPE == DIR_UP_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_U_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}

			else if(m_DIRTYPE == DIR_UP_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f - 200
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Bear_U_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}

		}
	}
	if(m_Render.m_bInvenRender == false && m_Render.m_bStatRender == false
		&& m_Render.m_bCubeRender == false && m_Render.m_bShopRender == false)
	{
		if(m_bMove == true && m_bTransForm == false) // 움직일때 걷기 & 뛰기 (변신전)
		{
			if(m_bRun == true)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_R"), int(m_iFrameX) * int(m_tInfo.fCX)
					, int(m_iFrameY) * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			else if(m_bRun == false)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_W"), int(m_iFrameX)  * int(m_tInfo.fCX)
					, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
		}

		if(m_bMove == true  && m_bTransForm == true && m_bTransFormTick == true) // 움직일때 걷기 & 뛰기 (변신후)
		{
			if(m_bRun == true)
			{
				if(m_DIRTYPE == DIR_DOWN)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_D_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_LEFT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_RIGHT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R_U_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_bRun == false)
			{
				if(m_DIRTYPE == DIR_DOWN)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_DOWN_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_D_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_LEFT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_RIGHT)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_L)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U_L"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				if(m_DIRTYPE == DIR_UP_R)
				{

					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_W_U_R"), int(m_iFrameX)  * int(m_tInfo.fCX)
						, int(m_iFrameY)  * int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
		}

		else if(m_bMove == false && m_bTransForm == false) // 평소 상태 ( 변신 전)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_Att"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == true && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_GetHit"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}

			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == true)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f - 10
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player_Cast"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

				return;

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == false)
			{

				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Player"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

			}
		}

		else if(m_bMove == false && m_bTransForm == true && m_bTransFormTick == false) // 곰변신 스킬중
		{
			TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
				, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"Skill_Bear"), int(m_iFrameX  * m_tInfo.fCX)
				, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		}

		else if(m_bMove == false && m_bTransForm == true && m_bTransFormTick == true) // 평소 상태 ( 변신 후)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				if(m_tInfo.m_bCast2 == true)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_Skill_D"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
					
					return;
				}
				else if(m_tInfo.m_bCast2 == false)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_D"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_DIRTYPE == DIR_DOWN_L)
			{
				if(m_tInfo.m_bCast2 == true)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_Skill_D_L"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				else if(m_tInfo.m_bCast2 == false)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_D_L"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_DIRTYPE == DIR_DOWN_R)
			{
				if(m_tInfo.m_bCast2 == true)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_Skill_D_R"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				else if(m_tInfo.m_bCast2 == false)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_D_R"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_DIRTYPE == DIR_LEFT)
			{
				if(m_tInfo.m_bCast2 == true)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_Skill_L"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				else if(m_tInfo.m_bCast2 == false)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_L"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_DIRTYPE == DIR_RIGHT)
			{
				if(m_tInfo.m_bCast2 == true)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_Skill_R"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				else if(m_tInfo.m_bCast2 == false)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_R"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_DIRTYPE == DIR_UP)
			{
				if( m_tInfo.m_bAtt == false && m_tInfo.m_bGetHit == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_Skill_U"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
					return;
				}
				else if(m_tInfo.m_bCast2 == false)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_U"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}
			else if(m_DIRTYPE == DIR_UP_L)
			{
				if(m_tInfo.m_bCast2 == true)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_Skill_U_L"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				else if(m_tInfo.m_bCast2 == false)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_U_L"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}

			else if(m_DIRTYPE == DIR_UP_R)
			{
				if(m_tInfo.m_bCast2 == true)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_Skill_U_R"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
				else if(m_tInfo.m_bCast2 == false)
				{
					TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f - CObj::m_ptPlayer.x) + iWINCX / 2.f
						, int(m_tInfo.fY - m_tInfo.fCY / 2.f - CObj::m_ptPlayer.y) + iWINCY / 2.f
						, int(m_tInfo.fCX)
						, int(m_tInfo.fCY)
						, *CImgMgr::GetInstance()->GetTexture(L"Bear_U_R"), int(m_iFrameX  * m_tInfo.fCX)
						, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
				}
			}

		}
	}
}

void CPlayer::Release( void )
{

}

void CPlayer::Hit(void)
{
	POINT ptMouse = CMouse::GetMousePos();

	if(CScene::m_bBattle == true && CScene::m_bHome == false)
	{

		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();

		for(iter; iter != iter_end; ++iter)
		{
			int		iPlayerIndex = int(CObj::m_ptPlayer.y) / iTILESIZE * iTILECNTX + int(CObj::m_ptPlayer.x)  / iTILESIZE;
			int		iMonsterIndex = int((*iter)->GetInfo().fY)/ iTILESIZE * iTILECNTX + int((*iter)->GetInfo().fX) / iTILESIZE;
			int		iIndex = (((int)ptMouse.y - (int)CObj::m_ptScroll.y) / iTILESIZE) * iTILECNTX + int(((int)ptMouse.x - (int)CObj::m_ptScroll.x) / iTILESIZE);

			if(iPlayerIndex - 1 == iMonsterIndex
				|| iPlayerIndex + 1 == iMonsterIndex
				|| iPlayerIndex + iTILECNTX == iMonsterIndex
				|| iPlayerIndex - iTILECNTX == iMonsterIndex
				|| iPlayerIndex + iTILECNTX - 1 == iMonsterIndex
				|| iPlayerIndex + iTILECNTX + 1 == iMonsterIndex
				|| iPlayerIndex - iTILECNTX - 1 == iMonsterIndex
				|| iPlayerIndex - iTILECNTX + 1 == iMonsterIndex)
			{
				RECT	rcMonster = {(*iter)->GetInfo().fX - (*iter)->GetInfo().fCX / 2.f
					,(*iter)->GetInfo().fY - (*iter)->GetInfo().fCY / 2.f
					,(*iter)->GetInfo().fX + (*iter)->GetInfo().fCX / 2.f
					,(*iter)->GetInfo().fY + (*iter)->GetInfo().fCY / 2.f};

				if(iMonsterIndex == iIndex) // 마우스와 몬스터의 ptinrect로 수정
				{
					if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						if(m_bHitTick == true)
							return;
						m_bHitTick = true;
						m_tInfo.m_bAtt = true;
						(*iter)->GetInfo().iHp -= m_tInfo.iAtt;
						break;
					}
					else
						m_bHitTick = false;
				}		
			}
		}
	}
}

void CPlayer::KeyCheck(void)
{
	POINT ptMouse = CMouse::GetMousePos();

	if(m_BestQueue.empty())												
	{
		m_bMove = false;
	}

	if(GetAsyncKeyState('0') & 0x8000)
	{
		m_tInfo.iHp -= 10;
		m_tInfo.iMp -= 10;
	}


	if(GetAsyncKeyState('1') & 0x8000)
	{
		if(CTileMgr::GetInstance()->GetPotionTile()[0]->m_bCheck == true)
		{
			CTileMgr::GetInstance()->GetPotionTile()[0]->m_bCheck = false;
			list<CItem*>::iterator iter = CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->begin();
			list<CItem*>::iterator iter_end = CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->end();

			RECT	rcTile = { long(CTileMgr::GetInstance()->GetPotionTile()[0]->fX - CTileMgr::GetInstance()->GetPotionTile()[0]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetPotionTile()[0]->fY - CTileMgr::GetInstance()->GetPotionTile()[0]->fCY / 2.f)
							, long(CTileMgr::GetInstance()->GetPotionTile()[0]->fX + CTileMgr::GetInstance()->GetPotionTile()[0]->fCX / 2.f)
							, long(CTileMgr::GetInstance()->GetPotionTile()[0]->fY + CTileMgr::GetInstance()->GetPotionTile()[0]->fCY / 2.f)};

			for(iter; iter != iter_end; ++iter)
			{
				POINT	m_ptPoint = { long((*iter)->GetInfo().fX), long((*iter)->GetInfo().fY) };
				if(PtInRect(&rcTile,m_ptPoint))
				{
					CSoundMgr::GetInstance()->ItemSound(L"potiondrink.wav");
					(*iter)->GetInfo().bAlive = false;

					if((m_tInfo.iMaxHp - m_tInfo.iHp) > 30)
						m_tInfo.iHp += 30;
					else
						m_tInfo.iHp = m_tInfo.iMaxHp;

					if((m_tInfo.iMaxMp - m_tInfo.iMp) > 30)
						m_tInfo.iMp += 30;
					else
						m_tInfo.iMp = m_tInfo.iMaxMp;
					break;
				}
			}
		}
	}
	if(GetAsyncKeyState('2') & 0x8000)
	{
		if(CTileMgr::GetInstance()->GetPotionTile()[1]->m_bCheck == true)
		{
			CTileMgr::GetInstance()->GetPotionTile()[1]->m_bCheck = false;
			list<CItem*>::iterator iter = CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->begin();
			list<CItem*>::iterator iter_end = CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->end();

			RECT	rcTile = { long(CTileMgr::GetInstance()->GetPotionTile()[1]->fX - CTileMgr::GetInstance()->GetPotionTile()[1]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[1]->fY - CTileMgr::GetInstance()->GetPotionTile()[1]->fCY / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[1]->fX + CTileMgr::GetInstance()->GetPotionTile()[1]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[1]->fY + CTileMgr::GetInstance()->GetPotionTile()[1]->fCY / 2.f)};

			for(iter; iter != iter_end; ++iter)
			{
				POINT	m_ptPoint = { long((*iter)->GetInfo().fX), long((*iter)->GetInfo().fY) };
				if(PtInRect(&rcTile,m_ptPoint))
				{
					CSoundMgr::GetInstance()->ItemSound(L"potiondrink.wav");
					(*iter)->GetInfo().bAlive = false;

					if((m_tInfo.iMaxHp - m_tInfo.iHp) > 30)
						m_tInfo.iHp += 30;
					else
						m_tInfo.iHp = m_tInfo.iMaxHp;

					if((m_tInfo.iMaxMp - m_tInfo.iMp) > 30)
						m_tInfo.iMp += 30;
					else
						m_tInfo.iMp = m_tInfo.iMaxMp;
					break;
				}
			}
		}
	}
	if(GetAsyncKeyState('3') & 0x8000)
	{
		if(CTileMgr::GetInstance()->GetPotionTile()[2]->m_bCheck == true)
		{
			CTileMgr::GetInstance()->GetPotionTile()[2]->m_bCheck = false;
			list<CItem*>::iterator iter = CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->begin();
			list<CItem*>::iterator iter_end = CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->end();

			RECT	rcTile = { long(CTileMgr::GetInstance()->GetPotionTile()[2]->fX - CTileMgr::GetInstance()->GetPotionTile()[2]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[2]->fY - CTileMgr::GetInstance()->GetPotionTile()[2]->fCY / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[2]->fX + CTileMgr::GetInstance()->GetPotionTile()[2]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[2]->fY + CTileMgr::GetInstance()->GetPotionTile()[2]->fCY / 2.f)};

			for(iter; iter != iter_end; ++iter)
			{
				POINT	m_ptPoint = { long((*iter)->GetInfo().fX), long((*iter)->GetInfo().fY) };
				if(PtInRect(&rcTile,m_ptPoint))
				{
					CSoundMgr::GetInstance()->ItemSound(L"potiondrink.wav");
					(*iter)->GetInfo().bAlive = false;

					if((m_tInfo.iMaxHp - m_tInfo.iHp) > 30)
						m_tInfo.iHp += 30;
					else
						m_tInfo.iHp = m_tInfo.iMaxHp;

					if((m_tInfo.iMaxMp - m_tInfo.iMp) > 30)
						m_tInfo.iMp += 30;
					else
						m_tInfo.iMp = m_tInfo.iMaxMp;
					break;
				}
			}
		}

	}
	if(GetAsyncKeyState('4') & 0x8000)
	{
		if(CTileMgr::GetInstance()->GetPotionTile()[3]->m_bCheck == true)
		{
			CTileMgr::GetInstance()->GetPotionTile()[3]->m_bCheck = false;
			list<CItem*>::iterator iter = CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->begin();
			list<CItem*>::iterator iter_end = CObjMgr::GetInstance()->GetPotionList(L"UnderBar")->end();

			RECT	rcTile = { long(CTileMgr::GetInstance()->GetPotionTile()[3]->fX - CTileMgr::GetInstance()->GetPotionTile()[3]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[3]->fY - CTileMgr::GetInstance()->GetPotionTile()[3]->fCY / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[3]->fX + CTileMgr::GetInstance()->GetPotionTile()[3]->fCX / 2.f)
				, long(CTileMgr::GetInstance()->GetPotionTile()[3]->fY + CTileMgr::GetInstance()->GetPotionTile()[3]->fCY / 2.f)};

			for(iter; iter != iter_end; ++iter)
			{
				POINT	m_ptPoint = { long((*iter)->GetInfo().fX), long((*iter)->GetInfo().fY) };
				if(PtInRect(&rcTile,m_ptPoint))
				{
					CSoundMgr::GetInstance()->ItemSound(L"potiondrink.wav");
					(*iter)->GetInfo().bAlive = false;

					if((m_tInfo.iMaxHp - m_tInfo.iHp) > 30)
						m_tInfo.iHp += 30;
					else
						m_tInfo.iHp = m_tInfo.iMaxHp;

					if((m_tInfo.iMaxMp - m_tInfo.iMp) > 30)
						m_tInfo.iMp += 30;
					else
						m_tInfo.iMp = m_tInfo.iMaxMp;
					break;
				}
			}
		}

	}

	if(GetAsyncKeyState('R') & 0x8000)
	{
		if(m_bRunPush == true)
			return;
		m_bRunPush = true;

		if(m_bRun == false)
			m_bRun = true;
		else if(m_bRun == true)
			m_bRun = false;
	}
	else
		m_bRunPush = false;
	if(GetAsyncKeyState('I') & 0x8000)
	{
		if(m_bPush == true)
			return;

		m_bPush= true;

		if(m_Render.m_bInvenRender  == false)
		{
			m_Render.m_bInvenRender = true;
			CObj::m_ptScroll.x -= 200;
		}
		else if(m_Render.m_bInvenRender  == true)
		{
			m_Render.m_bInvenRender = false;
			CObj::m_ptScroll.x += 200;
		}
	}
	else
		m_bPush = false;

	if(GetAsyncKeyState('C') & 0x8000)
	{
		if(m_bStat == true)
			return;

		m_bStat= true;

		if(m_Render.m_bCubeRender == true
			|| m_Render.m_bShopRender == true)
			return;

		if(m_Render.m_bStatRender  == false)
		{
			m_Render.m_bStatRender = true;
			CObj::m_ptScroll.x += 200;
		}
		else if(m_Render.m_bStatRender  == true)
		{
			m_Render.m_bStatRender = false;
			CObj::m_ptScroll.x -= 200;
		}
	}
	else
		m_bStat = false;

	if(GetAsyncKeyState('P') & 0x8000)
	{
		if(m_bCube == true)
			return;

		m_bCube= true;

		if(m_Render.m_bStatRender == true
			|| m_Render.m_bShopRender == true)
			return;


		if(m_Render.m_bCubeRender  == false)
		{
			m_Render.m_bCubeRender = true;
			CObj::m_ptScroll.x += 200;
		}
		else if(m_Render.m_bCubeRender  == true)
		{
			m_Render.m_bCubeRender = false;
			CObj::m_ptScroll.x -= 200;
		}
	}
	else
		m_bCube = false;

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	int		iPlayerIndex = int(CObj::m_ptPlayer.y) / iTILESIZE * iTILECNTX + int(CObj::m_ptPlayer.x)  / iTILESIZE;

	int		iIndex = (((int)ptMouse.y - (int)CObj::m_ptScroll.y) / iTILESIZE) * iTILECNTX + int(((int)ptMouse.x - (int)CObj::m_ptScroll.x) / iTILESIZE);

	if(ptMouse.x > CObjMgr::GetInstance()->GetInfo(L"Inven")->fX - CObjMgr::GetInstance()->GetInfo(L"Inven")->fCX / 2.f)
	{	
		CObjMgr::GetInstance()->GetInfo(L"Shop")->iSortNum = 1;
		CObjMgr::GetInstance()->GetInfo(L"Inven")->iSortNum = 0;
	}

	if(ptMouse.x < CObjMgr::GetInstance()->GetInfo(L"Shop")->fX + CObjMgr::GetInstance()->GetInfo(L"Shop")->fCX / 2.f)
	{	
		CObjMgr::GetInstance()->GetInfo(L"Shop")->iSortNum = 0;
		CObjMgr::GetInstance()->GetInfo(L"Inven")->iSortNum = 1;
	}

	if(ptMouse.x > 540)
	{
		CObjMgr::GetInstance()->GetInfo(L"UnderBar")->iSortNum = 0;
		CObjMgr::GetInstance()->GetInfo(L"Shop")->iSortNum = 2;
		CObjMgr::GetInstance()->GetInfo(L"Inven")->iSortNum = 1;
	}

	if( GetAsyncKeyState(VK_LBUTTON) & 0x8000 )
	{
		if(m_Render.m_bInvenRender == true)
		{
			if(ptMouse.x > CObjMgr::GetInstance()->GetInfo(L"Inven")->fX - CObjMgr::GetInstance()->GetInfo(L"Inven")->fCX / 2.f)
				return;
		}
		if(m_Render.m_bShopRender == true)
		{
			if(ptMouse.x < CObjMgr::GetInstance()->GetInfo(L"Shop")->fX + CObjMgr::GetInstance()->GetInfo(L"Shop")->fCX / 2.f)
				return;
		}
		if(m_Render.m_bStatRender == true)
		{
			if(ptMouse.x < CObjMgr::GetInstance()->GetInfo(L"Stat")->fX + CObjMgr::GetInstance()->GetInfo(L"Stat")->fCX / 2.f)
				return;
		}
		if(m_Render.m_bCubeRender == true)
		{
			if(ptMouse.x < CObjMgr::GetInstance()->GetInfo(L"Cube")->fX + CObjMgr::GetInstance()->GetInfo(L"Cube")->fCX / 2.f)
				return;
		}
		if(m_Render.m_bSkillRender == true)
		{
			if(ptMouse.x > CObjMgr::GetInstance()->GetInfo(L"SkillIcon")->fX - CObjMgr::GetInstance()->GetInfo(L"SkillIcon")->fCX / 2.f - 240
				&& ptMouse.y > CObjMgr::GetInstance()->GetInfo(L"SkillIcon")->fY - CObjMgr::GetInstance()->GetInfo(L"SkillIcon")->fCY / 2.f - 50)
				return;
		}

		if(ptMouse.y > 540.f)
			return;

		if(m_dwTime + 350 < GetTickCount())
		{

			m_dwTime = GetTickCount();
			while(!m_BestQueue.empty())	
			{
				m_BestQueue.pop();		
			}

			CAstarMgr::GetInstance()->StartAStar(iPlayerIndex, iIndex);

			list<int>::iterator iter = CAstarMgr::GetInstance()->GetBestList()->begin();
			list<int>::iterator iter_end = CAstarMgr::GetInstance()->GetBestList()->end();

			for(iter; iter != iter_end; iter++)
			{
				m_BestQueue.push(*iter);
			}

		}
		m_bCanMove = true;
		m_bMove = true;
	}		

}
void CPlayer::Moving(void)
{
	if(m_bRun == false)
		m_tInfo.fSpeed = 2.f;
	else if(m_bRun == true)
		m_tInfo.fSpeed = 5.f;

	INFO* pBackGroundInfo = CObjMgr::GetInstance()->GetInfo(L"StageBack");
	int		iPlayerIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX) / iTILESIZE;

	if(!m_BestQueue.empty())												
	{	
		vector<TILE*>::iterator iter = CTileMgr::GetInstance()->GetTileVector().begin();				
		int iIndex = m_BestQueue.front();

		iter += iIndex;

		if(m_bCanMove)													
		{
			if( ( CObj::m_ptPlayer.x > (*iter)->fX - (*iter)->fCX / 4.f ) 
				&& ( CObj::m_ptPlayer.x < (*iter)->fX + (*iter)->fCX / 4.f ) 
				&& ( CObj::m_ptPlayer.y > (*iter)->fY - (*iter)->fCY / 4.f)
				&& ( CObj::m_ptPlayer.y < (*iter)->fY + (*iter)->fCY / 4.f))	
			{																		
				m_BestQueue.pop();														
			}

			else																	
			{
				float fX = (*iter)->fX - CObj::m_ptPlayer.x;								
				float fY = (*iter)->fY - CObj::m_ptPlayer.y;

				float fDist = sqrt((fX * fX) + (fY * fY));							

				if(fDist < m_tInfo.fSpeed)
				{
					m_tInfo.fAngle = atan2f(-fY, fX) * 180 / PI;

					CObj::m_ptScroll.x -= long(cosf(m_tInfo.fAngle * PI / 180) * fDist);
					CObj::m_ptPlayer.x += long(cosf(m_tInfo.fAngle * PI / 180) * fDist);
					CObj::m_ptScroll.y += long(sinf(m_tInfo.fAngle * PI / 180) * fDist);
					CObj::m_ptPlayer.y -= long(sinf(m_tInfo.fAngle * PI / 180) * fDist);
				}
				else
				{
					m_tInfo.fAngle = atan2f(-fY, fX) * 180 / PI;

					CObj::m_ptScroll.x -= long(cosf(m_tInfo.fAngle * PI / 180) * m_tInfo.fSpeed);
					CObj::m_ptPlayer.x += long(cosf(m_tInfo.fAngle * PI / 180) * m_tInfo.fSpeed);
					CObj::m_ptScroll.y += long(sinf(m_tInfo.fAngle * PI / 180) * m_tInfo.fSpeed);
					CObj::m_ptPlayer.y -= long(sinf(m_tInfo.fAngle * PI / 180) * m_tInfo.fSpeed);
				}	
			}
		}
	}
	else
	{
		m_bCanMove = false;
	}
}

void CPlayer::SkillCheck(void)
{
	if(m_eType == KT_NORMAL)
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if(m_bSkillTick == true)
				return;
			m_bSkillTick = true;

			if(m_bTransForm == true || CScene::m_bHome == true)
				return;

			while(!m_BestQueue.empty())	
			{
				m_BestQueue.pop();		
			}
			if(m_tInfo.m_bCast1 == true)
				return;
			m_tInfo.m_bCast1 = true;
			SetMotion();
			CObjMgr::GetInstance()->AddObject(L"Ball", SORTID_UNITANDOBJ, CFactory<CBall>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_DIRTYPE));
			CObjMgr::GetInstance()->AddObject(L"BallOver", SORTID_UNITANDOBJ, CFactory<CBallOver>::CreateObject());
			m_tInfo.iMp -= 2.f;
		}
		else 
			m_bSkillTick = false;
	}
	if(m_eType == KT_TRANSFORM)
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if(m_bSkillTick == true)
				return;
			m_bSkillTick = true;
			while(!m_BestQueue.empty())	
			{
				m_BestQueue.pop();		
			}
			m_bMove = false;
			if(m_bTransForm == false)
			{
				m_bTransForm = true;
			}
			else if(m_bTransForm == true)
			{
				m_bTransForm = false;
			}
			// 80 103
		}
		else
			m_bSkillTick = false;
	}
	if(m_eType == KT_AMA)
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if(m_bSkillTick == true)
				return;
			m_bSkillTick = true;
			
			if(m_bTransForm == true || CScene::m_bHome == true)
				return;

			while(!m_BestQueue.empty())	
			{
				m_BestQueue.pop();		
			}
			if(m_tInfo.m_bCast1 == true)
				return;
			m_tInfo.m_bCast1 = true;
			CObjMgr::GetInstance()->AddObject(L"Amagetdon", SORTID_SKILL, CFactory<CAmagetdon>::CreateObject());
			CObjMgr::GetInstance()->AddObject(L"AmaOverlay", SORTID_UNITANDOBJ, CFactory<CAmaOver>::CreateObject());
			m_tInfo.iMp -= 2.f;
		}
		else
			m_bSkillTick = false;
	}
	if(m_eType == KT_HURRI)
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if(m_bSkillTick == true)
				return;
			m_bSkillTick = true;

			if(m_bTransForm == true || CScene::m_bHome == true)
				return;

			while(!m_BestQueue.empty())	
			{
				m_BestQueue.pop();		
			}
			if(m_tInfo.m_bCast1 == true)
				return;
			m_tInfo.m_bCast1 = true;
			CObjMgr::GetInstance()->AddObject(L"Hurricane", SORTID_SKILL, CFactory<CHurricane>::CreateObject());
			CObjMgr::GetInstance()->AddObject(L"ColdOverlay", SORTID_UNITANDOBJ, CFactory<CColdOver>::CreateObject());
			m_tInfo.iMp -= 2.f;

		}
		else
			m_bSkillTick = false;
	}

	if(m_eType == KT_TOR)
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if(m_bSkillTick == true)
				return;
			m_bSkillTick = true;
			m_bTor = true;

			if(m_bTransForm == true || CScene::m_bHome == true || m_bMove == true)
				return;

			while(!m_BestQueue.empty())	
			{
				m_BestQueue.pop();		
			}
			if(m_tInfo.m_bCast1 == true)
				return;
			m_tInfo.m_bCast1 = true;
			SetMotion();
			CObjMgr::GetInstance()->AddObject(L"Tornado", SORTID_UNITANDOBJ, CFactory<CTornado>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_DIRTYPE));
			m_tInfo.iMp -= 2.f;

		}
		else
		{
			m_bTor = false;
			m_bSkillTick = false;
		}
	}

	if(m_eType == KT_SHOCK)
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if(m_bSkillTick == true)
				return;
			m_bSkillTick = true;
			m_bShock = true;

			if(m_bTransForm == false || CScene::m_bHome == true || m_bMove == true)
				return;

			while(!m_BestQueue.empty())	
			{
				m_BestQueue.pop();		
			}
			if(m_tInfo.m_bCast2 == true)
				return;
			m_tInfo.m_bCast2 = true;
			SetMotion();
			CObjMgr::GetInstance()->AddObject(L"Shock", SORTID_UNITANDOBJ, CFactory<CShork>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_DIRTYPE));
			m_tInfo.iMp -= 2.f;

		}
		else
		{
			m_bShock = false;
			m_bSkillTick = false;
		}
	}
}

void CPlayer::SetMotion(void)
{
	POINT ptMouse = CMouse::GetMousePos();

	int		iIndex = (((int)ptMouse.y - (int)CObj::m_ptScroll.y) / iTILESIZE) * iTILECNTX + int(((int)ptMouse.x - (int)CObj::m_ptScroll.x) / iTILESIZE);
	int		iPlayerIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX) / iTILESIZE;

	if(CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX == CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY < CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY) // Down
	{
		m_DIRTYPE = DIR_DOWN;
		m_iFrameY = 0;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX == CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY > CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY) // UP
	{
		m_DIRTYPE = DIR_UP;
		m_iFrameY = 4;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX < CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY == CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY) // RIGHT
	{
		m_DIRTYPE = DIR_RIGHT;
		m_iFrameY = 6;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX > CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY == CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY) // LEFT
	{
		m_DIRTYPE = DIR_LEFT;
		m_iFrameY = 2;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX > CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY > CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY) // UP_LEFT
	{
		m_DIRTYPE = DIR_UP_L;
		m_iFrameY = 3;
	}

	if(CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX > CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY < CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY) // DOWN_LEFT
	{
		m_DIRTYPE = DIR_DOWN_L;
		m_iFrameY = 1;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX < CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY > CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY) // UP_RIGHT
	{
		m_DIRTYPE = DIR_UP_R;
		m_iFrameY = 5;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX < CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY < CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY) // DOWN_RIGHT
	{
		m_DIRTYPE = DIR_DOWN_R;
		m_iFrameY = 7;
	}
}
