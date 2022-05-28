#include "StdAfx.h"
#include "Boss.h"
#include "ObjMgr.h"
#include "AstarMgr.h"
#include "TileMgr.h"
#include "Factory.h"
#include "Inferno.h"
#include "Fire.h"
#include "Mouse.h"

CBoss::CBoss(void)
{
}

CBoss::~CBoss(void)
{
}

void CBoss::Initialize( void )
{
	iTileCheck = 0;
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"StageBack")->fCX / 2.f;
	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"StageBack")->fCY / 2.f;
	m_tInfo.fCX = 138.f;
	m_tInfo.fCY = 157.f;
	m_iFrameX = 0;
	m_iFrameY = 0;
	m_DIRTYPE = DIR_DOWN_L;

	m_bMoveCheck = false;
	m_bCanMove = false;
	m_bMove = false;
	m_bRun = false;
	m_bSetHit = false;
	m_bGetHit = false;
	m_bHitCheck = false;
	m_bInferno = false;
	m_bDash = false;
	m_bFire = false;
	m_bDead = false;
	m_bDeadSound = false;
	m_bInfeSound = false;
	m_bFireSound = false;
	iInfernoTime = 0;
	iFireTime = 0;

	m_tInfo.m_bAtt = false;
	m_tInfo.m_bCast1 = false;
	m_tInfo.m_bCast2 = false;
	m_tInfo.m_bGetHit = false;

	m_tInfo.iHp = 2000.f;

	m_tInfo.fAngle = 0;
	m_tInfo.fSpeed = 3.f;

	m_tInfo.bAlive = true;
	m_dwTest = GetTickCount();
	m_dwFire = GetTickCount();
}

void CBoss::Progress( void )
{
	if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == true)
	{
		m_tInfo.m_bAtt = false;
		m_tInfo.m_bCast1 = true; 
	}

	if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast2 == true)
	{
		m_tInfo.m_bAtt = false;
		m_tInfo.m_bCast2 = true; 
	}
	float fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - m_tInfo.fX;								
	float fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY - m_tInfo.fY;

	float fDist = sqrt((fX * fX) + (fY * fY));

	if(fDist < 500)
		m_bMoveCheck = true;

	if(m_bInferno == false)
		DirectPos();
	SetBossPos();


	if(m_bMoveCheck == true)
	{
		int		iMonsterIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX)  / iTILESIZE;
		int		iPlayerIndex = (int(CObj::m_ptPlayer.y) / iTILESIZE) * iTILECNTX + int(CObj::m_ptPlayer.x) / iTILESIZE;

		if(m_tInfo.iHp <= 0)
		{
			m_bMove = false;
			m_bDead = true; // 279 329
			CTileMgr::GetInstance()->GetTileVector()[iTileCheck]->bOption = false;
			CTileMgr::GetInstance()->GetTileVector()[iTileCheck]->iDrawID = 0;
			return;
		}
		if(Inferno())
			return;
		if(Fire())
			return;

		Dash();

		if(m_dwTime + 500 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			while(!m_BestQueue.empty())	
			{
				m_BestQueue.pop();		
			}

			CAstarMgr::GetInstance()->StartAStar(iMonsterIndex, iPlayerIndex);

			list<int>::iterator iter = CAstarMgr::GetInstance()->GetBestList()->begin();
			list<int>::iterator iter_end = CAstarMgr::GetInstance()->GetBestList()->end();

			for(iter; iter != iter_end; iter++)
			{
				m_BestQueue.push(*iter);
			}

		}
		m_bCanMove = true;
		m_bMove = true;
		m_bGetHit = false;

		if(m_BestQueue.size() < 2)												
		{	
			m_bDash = false;
			m_bMove = false;
			m_bGetHit = true;
			m_tInfo.m_bAtt = true;
		}
		else
			m_tInfo.m_bAtt = false;
		if(/*!m_BestQueue.empty()*/m_BestQueue.size() > 1)												
		{	
			vector<TILE*>::iterator iter = CTileMgr::GetInstance()->GetTileVector().begin();				
			int iIndex = m_BestQueue.front();

			iter += iIndex;

			if(m_bCanMove)													
			{
				if( ( m_tInfo.fX > (*iter)->fX - (*iter)->fCX / 2.2f  ) 
					&& ( m_tInfo.fX < (*iter)->fX + (*iter)->fCX / 2.2f ) 
					&& ( m_tInfo.fY > (*iter)->fY - (*iter)->fCY / 2.2f )
					&& ( m_tInfo.fY < (*iter)->fY + (*iter)->fCY / 2.2f ))
				{
					CTileMgr::GetInstance()->GetTileVector()[iTileCheck]->bOption = false;
					CTileMgr::GetInstance()->GetTileVector()[iTileCheck]->iDrawID = 0;
					CTileMgr::GetInstance()->GetTileVector()[iIndex]->bOption = true;
					CTileMgr::GetInstance()->GetTileVector()[iIndex]->iDrawID = 1;
					m_BestQueue.pop();	
					iTileCheck = iIndex;
				}

				else																	
				{
					float fX = (*iter)->fX - m_tInfo.fX;								
					float fY = (*iter)->fY - m_tInfo.fY;

					float fDist = sqrt((fX * fX) + (fY * fY));							

					if(fDist < m_tInfo.fSpeed)
					{
						m_tInfo.fAngle = atan2f(-fY, fX) * 180 / PI;
						m_tInfo.fX += long(cosf(m_tInfo.fAngle * PI / 180) * fDist);
						m_tInfo.fY -= long(sinf(m_tInfo.fAngle * PI / 180) * fDist);
					}
					else
					{
						m_tInfo.fAngle = atan2f(-fY, fX) * 180 / PI;
						m_tInfo.fX += long(cosf(m_tInfo.fAngle * PI / 180) * m_tInfo.fSpeed);
						m_tInfo.fY -= long(sinf(m_tInfo.fAngle * PI / 180) * m_tInfo.fSpeed);
					}	
				}
			}
		}
		else
		{
			m_bCanMove = false;
		}

	}
}

void CBoss::Render( void )
{
	if(m_bMove == true && m_bDead == false)
	{
		if(m_bRun == true)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R_D"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_DOWN_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R_D_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_LEFT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R_U_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R_U"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R_U_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_RIGHT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_DOWN_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R_D_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}

		}
		if(m_bRun == false)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_W_D"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_DOWN_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_W_D_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_LEFT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_W_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_W_U_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_W_U"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_W_U_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_RIGHT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_W_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_DOWN_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_W_D_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
		}
	}

	if(m_bMove == false && m_bDead == false)
	{
		if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Att_D"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_DOWN_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Att_D_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_LEFT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Att_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Att_U_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Att_U"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Att_U_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_RIGHT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Att_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_DOWN_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Att_D_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}

		}
		if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Fire_D"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_DOWN_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Fire_D_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_LEFT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Fire_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Fire_U_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Fire_U"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Fire_U_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_RIGHT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Fire_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_DOWN_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Fire_D_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}

		}
		if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Infe_D"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_DOWN_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Infe_D_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_LEFT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Infe_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Infe_U_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Infe_U"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_UP_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Infe_U_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_RIGHT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Infe_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}
			if(m_DIRTYPE == DIR_DOWN_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_Infe_D_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
			}

		}
		if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
		{
			if(m_DIRTYPE == DIR_DOWN)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_D"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_DOWN_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_D_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_LEFT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP_L)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_U_L"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_U"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_UP_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_U_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_RIGHT)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
			if(m_DIRTYPE == DIR_DOWN_R)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Boss_D_R"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
			}
		}
	}
	if(m_bDead == true)
	{
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Dead"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
	}
	if(m_bDead == false)
	{
		POINT m_ptMouse = CMouse::GetMousePos();

		RECT	rcMonster = { m_tInfo.fX - m_tInfo.fCX / 2.f
			, m_tInfo.fY - m_tInfo.fCY / 2.f
			, m_tInfo.fX + m_tInfo.fCX / 2.f
			, m_tInfo.fY + m_tInfo.fCY / 2.f};

		m_ptMouse.x -= CObj::m_ptScroll.x;
		m_ptMouse.y -= CObj::m_ptScroll.y;

		if(PtInRect(&rcMonster, m_ptMouse))
		{
			TCHAR				szString[128];
			wsprintf(szString, L" HP: %d ", m_tInfo.iHp);
			TextOut( *CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), m_tInfo.fX + CObj::m_ptScroll.x , (m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y, szString, lstrlen(szString));
		}
	}
}

void CBoss::Release( void )
{

}
bool CBoss::Fire(void)
{
	if(m_bInferno == false && m_bDash == false && m_bFire == false)
	{
		if(rand() % 1000 < 5)
		{
			m_bFire = true;
		}
	}
	if(m_bFire == true)
	{
		if(m_dwFire + 800 < GetTickCount())
		{			
			m_dwFire = GetTickCount();
			m_bMove = false;
			m_tInfo.m_bCast1 = true;

			for(int i = 0; i < 360; i += 7)
				CObjMgr::GetInstance()->AddObject(L"Fire", SORTID_UNITANDOBJ, CFactory<CFire>::CreateObject(m_tInfo.fX, m_tInfo.fY, (float)i));

			++iFireTime;
		}
		if(iFireTime >= 5)
		{
			m_tInfo.m_bCast1 = false;
			m_bFire = false;
			m_bFireSound = false;
			iFireTime = 0;
		}
		return true;
	}

	return false;

}
bool CBoss::Dash(void)
{
	if(m_bInferno == false && m_bDash == false && m_bFire == false)
	{
		if(rand() % 1000 < 5)
		{
			m_bDash = true;
		}
	}
	if(m_bDash == true)
	{
		m_tInfo.fSpeed = 7.f;
		m_bRun = true;
	}
	if(m_bDash == false)
	{
		m_tInfo.fSpeed = 3.f;
		m_bRun = false;
	}

	return false;
}
bool CBoss::Inferno(void)
{
	if(m_bInferno == false && m_bDash == false && m_bFire == false)
	{
		if(rand() % 1000 < 5)
		{
			m_bInferno = true;
		}
	}
	if(m_bInferno == true)
	{
		if(m_dwTest + 100 < GetTickCount())
		{
			if(m_bInfeSound == false)
			{
				m_bInfeSound = true;
				CSoundMgr::GetInstance()->MonsterSound1(L"lazer.wav");
			}
			m_dwTest = GetTickCount();
			PlayerPosFind();
			m_bMove = false;
			m_tInfo.m_bCast2 = true;
			CObjMgr::GetInstance()->AddObject(L"Inferno", SORTID_UNITANDOBJ, CFactory<CInferno>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_DIRTYPE));
			++iInfernoTime;
		}
		if(iInfernoTime >= 20)
		{
			m_tInfo.m_bCast2 = false;
			m_bInferno = false;
			m_bInfeSound = false;
			iInfernoTime = 0;
		}
		return true;
	}

	return false;
}
void CBoss::PlayerPosFind(void)
{
	int		iMonsterIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX)  / iTILESIZE;
	int		iPlayerIndex = int(CObjMgr::GetInstance()->GetInfo(L"Player")->fY) / iTILESIZE * iTILECNTX + int(CObjMgr::GetInstance()->GetInfo(L"Player")->fX)  / iTILESIZE;

	if(CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fX == CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fY < CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY) // Down
	{
		m_DIRTYPE = DIR_DOWN;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fX == CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fY > CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY) // UP
	{
		m_DIRTYPE = DIR_UP;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fX < CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fY == CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY) // RIGHT
	{
		m_DIRTYPE = DIR_RIGHT;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fX > CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fY == CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY) // LEFT
	{
		m_DIRTYPE = DIR_LEFT;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fX > CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fY > CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY) // UP_LEFT
	{
		m_DIRTYPE = DIR_UP_L;
	}

	if(CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fX > CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fY < CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY) // DOWN_LEFT
	{
		m_DIRTYPE = DIR_DOWN_L;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fX < CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fY > CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY) // UP_RIGHT
	{
		m_DIRTYPE = DIR_UP_R;
	}
	if(CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fX < CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fX
		&& CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->fY < CTileMgr::GetInstance()->GetTileVector()[iPlayerIndex]->fY) // DOWN_RIGHT
	{
		m_DIRTYPE = DIR_DOWN_R;
	}
}
void CBoss::SetBossPos(void)
{
	int		iMonsterIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX)  / iTILESIZE;
	m_iFrameY = 0;

	if(m_bDead == true)
	{
		m_tInfo.fCX = 279.f;
		m_tInfo.fCY = 329.f;
		if(m_bDeadSound == false)
		{
			CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
			CSoundMgr::GetInstance()->MonsterSound1(L"death.wav");
			m_bDeadSound = true;
		}
		FrameDeathMove(142);
	}

	if(m_DIRTYPE == DIR_DOWN)
	{
		if(m_bMove == true && m_bDead == false)
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 205.f;
				m_tInfo.fCY = 210.f;
				FrameMove(22);

				if(m_iFrameX == 20)
				{
					m_bRun = false;
					m_bDash = false;
				}
			}
			if(m_bRun == false)
			{
				m_tInfo.fCX = 125.f;
				m_tInfo.fCY = 166.f;
				FrameMove(12);
			}
		}
		if(m_bMove == false && m_bDead == false)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 187.f;
				m_tInfo.fCY = 168.f;
				FrameMove(16);
				if(m_iFrameX == 15)
				{
					CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
					CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 20;
					m_tInfo.m_bAtt = false;
				}
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 190.f;
				m_tInfo.fCY = 252.f;
				FrameMove(16);
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
			{
				m_tInfo.fCX = 201.f;
				m_tInfo.fCY = 201.f;
				FrameInferno(11);
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 135.f;
				m_tInfo.fCY = 158.f;
				FrameMove(12);
			}
		}
	}
	if(m_DIRTYPE == DIR_DOWN_L)
	{
		if(m_bMove == true && m_bDead == false)
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 230.f;
				m_tInfo.fCY = 203.f;
				FrameMove(22);

				if(m_iFrameX == 20)
				{
					m_bRun = false;
					m_bDash = false;
				}
			}
			if(m_bRun == false)
			{
				m_tInfo.fCX = 167.f;
				m_tInfo.fCY = 171.f;
				FrameMove(12);
			}
		}
		if(m_bMove == false && m_bDead == false)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 229.f;
				m_tInfo.fCY = 177.f;
				FrameMove(16);
				if(m_iFrameX == 15)
				{
					CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
					CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 20;
					m_tInfo.m_bAtt = false;
				}
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 196.f;
				m_tInfo.fCY = 259.f;
				FrameMove(16);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
			{
				m_tInfo.fCX = 210.f;
				m_tInfo.fCY = 203.f;
				FrameInferno(11);
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 135.f;
				m_tInfo.fCY = 158.f;
				FrameMove(12);
			}
		}

	}
	if(m_DIRTYPE == DIR_LEFT)
	{
		if(m_bMove == true && m_bDead == false)
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 300.f;
				m_tInfo.fCY = 187.f;
				FrameMove(22);

				if(m_iFrameX == 20)
				{
					m_bRun = false;
					m_bDash = false;
				}
			}
			if(m_bRun == false)
			{
				m_tInfo.fCX = 213.f;
				m_tInfo.fCY = 160.f;
				FrameMove(12);
			}
		}
		if(m_bMove == false && m_bDead == false)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 235.f;
				m_tInfo.fCY = 176.f;
				FrameMove(16);
				if(m_iFrameX == 15)
				{
					CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
					CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 20;
					m_tInfo.m_bAtt = false;
				}
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 231.f;
				m_tInfo.fCY = 257.f;
				FrameMove(16);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
			{
				m_tInfo.fCX = 236.f;
				m_tInfo.fCY = 213.f;
				FrameInferno(11);
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 135.f;
				m_tInfo.fCY = 158.f;
				FrameMove(12);
			}
		}

	}
	if(m_DIRTYPE == DIR_UP_L)
	{
		if(m_bMove == true && m_bDead == false)
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 258.f;
				m_tInfo.fCY = 208.f;
				FrameMove(22);

				if(m_iFrameX == 20)
				{
					m_bRun = false;
					m_bDash = false;
				}
			}
			if(m_bRun == false)
			{
				m_tInfo.fCX = 195.f;
				m_tInfo.fCY = 161.f;
				FrameMove(12);
			}
		}
		if(m_bMove == false && m_bDead == false)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 251.f;
				m_tInfo.fCY = 205.f;
				FrameMove(16);
				if(m_iFrameX == 15)
				{
					CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
					CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 20;
					m_tInfo.m_bAtt = false;
				}
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 259.f;
				m_tInfo.fCY = 261.f;
				FrameMove(16);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
			{
				m_tInfo.fCX = 226.f;
				m_tInfo.fCY = 232.f;
				FrameInferno(11);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 135.f;
				m_tInfo.fCY = 158.f;
				FrameMove(12);
			}
		}

	}
	if(m_DIRTYPE == DIR_UP)
	{
		if(m_bMove == true && m_bDead == false)
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 161.f;
				m_tInfo.fCY = 245.f;
				FrameMove(22);

				if(m_iFrameX == 20)
				{
					m_bRun = false;
					m_bDash = false;
				}
			}
			if(m_bRun == false)
			{
				m_tInfo.fCX = 123.f;
				m_tInfo.fCY = 182.f;
				FrameMove(12);
			}
		}
		if(m_bMove == false && m_bDead == false)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 217.f;
				m_tInfo.fCY = 218.f;
				FrameMove(16);
				if(m_iFrameX == 15)
				{
					CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
					CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 20;
					m_tInfo.m_bAtt = false;
				}
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 198.f;
				m_tInfo.fCY = 295.f;
				FrameMove(16);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
			{
				m_tInfo.fCX = 205.f;
				m_tInfo.fCY = 237.f;
				FrameInferno(11);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 135.f;
				m_tInfo.fCY = 158.f;
				FrameMove(12);
			}
		}

	}
	if(m_DIRTYPE == DIR_UP_R)
	{
		if(m_bMove == true && m_bDead == false)
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 271.f;
				m_tInfo.fCY = 255.f;
				FrameMove(22);

				if(m_iFrameX == 20)
				{
					m_bRun = false;
					m_bDash = false;
				}
			}
			if(m_bRun == false)
			{
				m_tInfo.fCX = 203.f;
				m_tInfo.fCY = 161.f;
				FrameMove(12);
			}
		}
		if(m_bMove == false && m_bDead == false)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 254.f;
				m_tInfo.fCY = 183.f;
				FrameMove(16);
				if(m_iFrameX == 15)
				{
					CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
					CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 20;
					m_tInfo.m_bAtt = false;
				}
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 223.f;
				m_tInfo.fCY = 292.f;
				FrameMove(16);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
			{
				m_tInfo.fCX = 212.f;
				m_tInfo.fCY = 208.f;
				FrameInferno(11);
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 135.f;
				m_tInfo.fCY = 158.f;
				FrameMove(12);
			}
		}

	}
	if(m_DIRTYPE == DIR_RIGHT)
	{
		if(m_bMove == true && m_bDead == false)
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 309.f;
				m_tInfo.fCY = 179.f;
				FrameMove(22);

				if(m_iFrameX == 20)
				{
					m_bRun = false;
					m_bDash = false;
				}
			}
			if(m_bRun == false)
			{
				m_tInfo.fCX = 210.f;
				m_tInfo.fCY = 160.f;
				FrameMove(12);
			}
		}
		if(m_bMove == false && m_bDead == false)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 232.f;
				m_tInfo.fCY = 170.f;
				FrameMove(16);
				if(m_iFrameX == 15)
				{
					CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
					CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 20;
					m_tInfo.m_bAtt = false;
				}
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 237.f;
				m_tInfo.fCY = 258.f;
				FrameMove(16);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
			{
				m_tInfo.fCX = 238.f;
				m_tInfo.fCY = 198.f;
				FrameInferno(11);
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 135.f;
				m_tInfo.fCY = 158.f;
				FrameMove(12);
			}
		}

	}
	if(m_DIRTYPE == DIR_DOWN_R)
	{
		if(m_bMove == true && m_bDead == false)
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 227.f;
				m_tInfo.fCY = 200.f;
				FrameMove(22);

				if(m_iFrameX == 20)
				{
					m_bRun = false;
					m_bDash = false;
				}
			}
			if(m_bRun == false)
			{
				m_tInfo.fCX = 164.f;
				m_tInfo.fCY = 171.f;
				FrameMove(12);
			}
		}
		if(m_bMove == false && m_bDead == false)
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 243.f;
				m_tInfo.fCY = 173.f;
				FrameMove(16);
				if(m_iFrameX == 15)
				{
					CSoundMgr::GetInstance()->MonsterSound1(L"attack2.wav");
					CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 20;
					m_tInfo.m_bAtt = false;
				}
			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 226.f;
				m_tInfo.fCY = 262.f;
				FrameMove(16);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == true)
			{
				m_tInfo.fCX = 215.f;
				m_tInfo.fCY = 198.f;
				FrameInferno(11);

			}
			if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 135.f;
				m_tInfo.fCY = 158.f;
				FrameMove(12);
			}
		}

	}

}