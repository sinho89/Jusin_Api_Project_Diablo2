#include "StdAfx.h"
#include "Monster.h"
#include "ImgMgr.h"
#include "AstarMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Dead.h"
#include "Mouse.h"

CMonster::CMonster(void)
{
}

CMonster::~CMonster(void)
{
}

void CMonster::Initialize( void )
{
	iTileCheck = 0;
	m_tInfo.fCX = 141.f;
	m_tInfo.fCY = 143.8f;
	m_iFrameX = 0;
	m_iFrameY = 0;
	m_tInfo.bAlive = true;
	m_tInfo.fAngle = 0;
	m_tInfo.fSpeed = 3.f;
	m_bHitCheck = false;
	m_bMove = false;
	m_bSetHit = false;
	m_bGetHit = false;
	m_bDead = false;
	m_bDeadCheck = false;
	m_bMoveCheck = false;
	m_bDeadSound = false;
	m_tInfo.iAtt = 1;
	m_tInfo.iHp = 500.f;
	m_tInfo.iMaxHp = 100.f;
	FrameMove(10);
	m_DIRTYPE = DIR_DOWN;
}

void CMonster::Progress( void )
{
	if(m_tInfo.iHp <= 0)
		m_tInfo.iHp = 0;
	if(bStart == false)
	{
		m_tInfo.fSpeed = 0.f;
		return;
	}

	float fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - m_tInfo.fX;								
	float fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY - m_tInfo.fY;

	float fDist = sqrt((fX * fX) + (fY * fY));

	if(fDist < 300)
		m_bMoveCheck = true;

	DirectPos();
	SetMonsterPos();

	if(m_bMoveCheck == true)
	{
		if(m_tInfo.iHp <= 0 )
		{
			int		iMonsterIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX)  / iTILESIZE;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->bOption = false;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex + 1]->bOption = false;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex - 1]->bOption = false;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex + iTILECNTX]->bOption = false;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex - iTILECNTX]->bOption = false;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->iDrawID = 0;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex + 1]->iDrawID = 0;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex - 1]->iDrawID = 0;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex + iTILECNTX]->iDrawID = 0;
			CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex - iTILECNTX]->iDrawID = 0;
			//int		iMonsterIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX)  / iTILESIZE;
			//CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->bOption = false;
			//CTileMgr::GetInstance()->GetTileVector()[iMonsterIndex]->iDrawID = 0;
			m_bDead = true;
			m_bMove = false;
			m_bGetHit = false;
			m_bSetHit = false;

			return;
		}
		if(m_bGetHit == true && m_iFrameX == 10 && m_bHitCheck == false)
		{
			m_bHitCheck = true;
			CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= m_tInfo.iAtt;
			CObjMgr::GetInstance()->GetInfo(L"Player")->m_bGetHit = true;
		}

		if(m_iFrameX == 18)
			m_bHitCheck = false;

		int		iMonsterIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX)  / iTILESIZE;
		int		iPlayerIndex = (int(CObj::m_ptPlayer.y) / iTILESIZE) * iTILECNTX + int(CObj::m_ptPlayer.x) / iTILESIZE;

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
			m_bMove = false;

			if(iMonsterIndex + 1 == iPlayerIndex
				|| iMonsterIndex - 1 == iPlayerIndex
				|| iMonsterIndex - iTILECNTX == iPlayerIndex
				|| iMonsterIndex + iTILECNTX == iPlayerIndex
				|| iMonsterIndex - iTILECNTX + 1== iPlayerIndex
				|| iMonsterIndex - iTILECNTX - 1== iPlayerIndex
				|| iMonsterIndex + iTILECNTX + 1== iPlayerIndex
				|| iMonsterIndex + iTILECNTX - 1== iPlayerIndex)
				m_bGetHit = true;
		}
		if(m_BestQueue.size() > 1)												
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

void CMonster::Render( void )
{

	if(m_bMove == true)
	{
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Cow_Move"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(170, 170, 170));
	}
	else if(m_bMove == false)
	{
		if(m_bGetHit == true)
		{
			TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
				, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"Cow_Att"), int(m_iFrameX  * m_tInfo.fCX)
				, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(170, 170, 170));

		}
		else if(m_bDead == true)
		{
			if(m_bDeadCheck == false)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Cow_Dead"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(170, 170, 170));
			}
			else if(m_bDeadCheck == true)
			{
				TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
					, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
					, int(m_tInfo.fCX)
					, int(m_tInfo.fCY)
					, *CImgMgr::GetInstance()->GetTexture(L"Cow_Dead2"), int(m_iFrameX  * m_tInfo.fCX)
					, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(170, 170, 170));
			}
		}
		else
		{
			TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
				, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"Cow"), int(m_iFrameX  * m_tInfo.fCX)
				, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(170, 170, 170));
		}
	}
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

void CMonster::Release( void )
{

}

void CMonster::SetMonsterPos( void )
{

	int		iMonsterIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX)  / iTILESIZE;

	if(m_DIRTYPE == DIR_DOWN)
	{
		if(m_bMove == true)
		{
			m_tInfo.fCX = 145.f;
			m_tInfo.fCY = 140.8f;
			FrameMove(8);
		}
		else if(m_bMove == false)
		{
			if(m_bGetHit == true)
			{
				m_tInfo.fCX = 233.f;
				m_tInfo.fCY = 191.8f;
				FrameMove(19);
			}
			else if(m_bDead == true && m_bDeadCheck == false)
			{ 
				m_tInfo.fCX = 151.f;
				m_tInfo.fCY = 166.8f;
				if(m_bDeadCheck == false)
				{
					if(m_bDeadSound = false)
					{
						int iRand = rand() % 5;
						switch(iRand)
						{
						case 0:
							CSoundMgr::GetInstance()->MonsterSound1(L"death1.wav");
							break;
						case 1:
							CSoundMgr::GetInstance()->MonsterSound2(L"death2.wav");
							break;
						case 2:
							CSoundMgr::GetInstance()->MonsterSound3(L"death3.wav");
							break;
						case 3:
							CSoundMgr::GetInstance()->MonsterSound4(L"death4.wav");
							break;
						case 4:
							CSoundMgr::GetInstance()->MonsterSound5(L"death5.wav");
							break;
						}
						m_bDeadSound = true;
					}
					FrameMove(14);
					if(m_iFrameX == 12)
					{
						CObjMgr::GetInstance()->AddObject(L"Dead", SORTID_DEAD, CFactory<CDead>::CreateObject(m_tInfo.fX, m_tInfo.fY - 50.f, m_DIRTYPE));
						++CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt;
						m_tInfo.bAlive = false;
						return;
					}
				}

			}
			else
			{
				if( m_bDead == false)
				{
					m_tInfo.fCX = 141.f;
					m_tInfo.fCY = 143.8f;
					FrameMove(10);
				}
			}
		}
	}
	if(m_DIRTYPE == DIR_DOWN_L)
	{
		if(m_bMove == true)
		{
			m_tInfo.fCX = 145.f;
			m_tInfo.fCY = 140.8f;
			FrameMove(8);
		}
		else if(m_bMove == false)
		{
			if(m_bGetHit == true)
			{
				m_tInfo.fCX = 233.f;
				m_tInfo.fCY = 191.8f;
				FrameMove(19);
			}
			else if(m_bDead == true && m_bDeadCheck == false)
			{ 
				m_tInfo.fCX = 151.f;
				m_tInfo.fCY = 166.8f;
				if(m_bDeadCheck == false)
				{
					if(m_bDeadSound == false)
					{
						int iRand = rand() % 5;
						switch(iRand)
						{
						case 0:
							CSoundMgr::GetInstance()->MonsterSound1(L"death1.wav");
							break;
						case 1:
							CSoundMgr::GetInstance()->MonsterSound2(L"death2.wav");
							break;
						case 2:
							CSoundMgr::GetInstance()->MonsterSound3(L"death3.wav");
							break;
						case 3:
							CSoundMgr::GetInstance()->MonsterSound4(L"death4.wav");
							break;
						case 4:
							CSoundMgr::GetInstance()->MonsterSound5(L"death5.wav");
							break;
						}
						m_bDeadSound = true;
					}
					FrameMove(14);
					if(m_iFrameX == 12)
					{
						CObjMgr::GetInstance()->AddObject(L"Dead", SORTID_DEAD, CFactory<CDead>::CreateObject(m_tInfo.fX, m_tInfo.fY + 50.f, m_DIRTYPE));
						++CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt;
						m_tInfo.bAlive = false;
						return;
					}
				}

			}
			else
			{
				if( m_bDead == false)
				{
					m_tInfo.fCX = 141.f;
					m_tInfo.fCY = 143.8f;
					FrameMove(10);
				}
			}
		}
	}
	if(m_DIRTYPE == DIR_LEFT)
	{
		if(m_bMove == true)
		{
			m_tInfo.fCX = 145.f;
			m_tInfo.fCY = 140.8f;
			FrameMove(8);
		}
		else if(m_bMove == false)
		{
			if(m_bGetHit == true)
			{
				m_tInfo.fCX = 233.f;
				m_tInfo.fCY = 191.8f;
				FrameMove(19);
			}
			else if(m_bDead == true && m_bDeadCheck == false)
			{ 
				m_tInfo.fCX = 151.f;
				m_tInfo.fCY = 166.8f;
				if(m_bDeadCheck == false)
				{
					if(m_bDeadSound == false)
					{
						int iRand = rand() % 5;
						switch(iRand)
						{
						case 0:
							CSoundMgr::GetInstance()->MonsterSound1(L"death1.wav");
							break;
						case 1:
							CSoundMgr::GetInstance()->MonsterSound2(L"death2.wav");
							break;
						case 2:
							CSoundMgr::GetInstance()->MonsterSound3(L"death3.wav");
							break;
						case 3:
							CSoundMgr::GetInstance()->MonsterSound4(L"death4.wav");
							break;
						case 4:
							CSoundMgr::GetInstance()->MonsterSound5(L"death5.wav");
							break;
						}
						m_bDeadSound = true;
					}
					FrameMove(14);
					if(m_iFrameX == 12)
					{
						CObjMgr::GetInstance()->AddObject(L"Dead", SORTID_DEAD, CFactory<CDead>::CreateObject(m_tInfo.fX, m_tInfo.fY + 50.f, m_DIRTYPE));
						++CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt;
						m_tInfo.bAlive = false;
						return;
					}
				}

			}
			else
			{
				if( m_bDead == false)
				{
					m_tInfo.fCX = 141.f;
					m_tInfo.fCY = 143.8f;
					FrameMove(10);
				}
			}
		}
	}
	if(m_DIRTYPE == DIR_UP_L)
	{
		if(m_bMove == true)
		{
			m_tInfo.fCX = 145.f;
			m_tInfo.fCY = 140.8f;
			FrameMove(8);
		}
		else if(m_bMove == false)
		{
			if(m_bGetHit == true)
			{
				m_tInfo.fCX = 233.f;
				m_tInfo.fCY = 191.8f;
				FrameMove(19);
			}
			else if(m_bDead == true && m_bDeadCheck == false)
			{ 
				m_tInfo.fCX = 151.f;
				m_tInfo.fCY = 166.8f;
				if(m_bDeadCheck == false)
				{
					if(m_bDeadSound == false)
					{
						int iRand = rand() % 5;
						switch(iRand)
						{
						case 0:
							CSoundMgr::GetInstance()->MonsterSound1(L"death1.wav");
							break;
						case 1:
							CSoundMgr::GetInstance()->MonsterSound2(L"death2.wav");
							break;
						case 2:
							CSoundMgr::GetInstance()->MonsterSound3(L"death3.wav");
							break;
						case 3:
							CSoundMgr::GetInstance()->MonsterSound4(L"death4.wav");
							break;
						case 4:
							CSoundMgr::GetInstance()->MonsterSound5(L"death5.wav");
							break;
						}
						m_bDeadSound = true;
					}
					FrameMove(14);
					if(m_iFrameX == 12)
					{
						CObjMgr::GetInstance()->AddObject(L"Dead", SORTID_DEAD, CFactory<CDead>::CreateObject(m_tInfo.fX, m_tInfo.fY + 50.f, m_DIRTYPE));
						++CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt;
						m_tInfo.bAlive = false;
						return;
					}
				}

			}
			else
			{
				if( m_bDead == false)
				{
					m_tInfo.fCX = 141.f;
					m_tInfo.fCY = 143.8f;
					FrameMove(10);
				}
			}
		}
	}
	if(m_DIRTYPE == DIR_UP)
	{
		if(m_bMove == true)
		{
			m_tInfo.fCX = 145.f;
			m_tInfo.fCY = 140.8f;
			FrameMove(8);
		}
		else if(m_bMove == false)
		{
			if(m_bGetHit == true)
			{
				m_tInfo.fCX = 233.f;
				m_tInfo.fCY = 191.8f;
				FrameMove(19);
			}
			else if(m_bDead == true && m_bDeadCheck == false)
			{ 
				m_tInfo.fCX = 151.f;
				m_tInfo.fCY = 166.8f;
				if(m_bDeadCheck == false)
				{
					if(m_bDeadSound == false)
					{
						int iRand = rand() % 5;
						switch(iRand)
						{
						case 0:
							CSoundMgr::GetInstance()->MonsterSound1(L"death1.wav");
							break;
						case 1:
							CSoundMgr::GetInstance()->MonsterSound2(L"death2.wav");
							break;
						case 2:
							CSoundMgr::GetInstance()->MonsterSound3(L"death3.wav");
							break;
						case 3:
							CSoundMgr::GetInstance()->MonsterSound4(L"death4.wav");
							break;
						case 4:
							CSoundMgr::GetInstance()->MonsterSound5(L"death5.wav");
							break;
						}
						m_bDeadSound = true;
					}
					FrameMove(14);
					if(m_iFrameX == 12)
					{
						CObjMgr::GetInstance()->AddObject(L"Dead", SORTID_DEAD, CFactory<CDead>::CreateObject(m_tInfo.fX, m_tInfo.fY + 50.f, m_DIRTYPE));
						++CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt;
						m_tInfo.bAlive = false;
						return;
					}
				}

			}
			else
			{
				if( m_bDead == false)
				{
					m_tInfo.fCX = 141.f;
					m_tInfo.fCY = 143.8f;
					FrameMove(10);
				}
			}
		}
	}
	if(m_DIRTYPE == DIR_UP_R)
	{
		if(m_bMove == true)
		{
			m_tInfo.fCX = 145.f;
			m_tInfo.fCY = 140.8f;
			FrameMove(8);
		}
		else if(m_bMove == false)
		{
			if(m_bGetHit == true)
			{
				m_tInfo.fCX = 233.f;
				m_tInfo.fCY = 191.8f;
				FrameMove(19);
			}
			else if(m_bDead == true && m_bDeadCheck == false)
			{ 
				m_tInfo.fCX = 151.f;
				m_tInfo.fCY = 166.8f;
				if(m_bDeadCheck == false)
				{
					if(m_bDeadSound == false)
					{
						int iRand = rand() % 5;
						switch(iRand)
						{
						case 0:
							CSoundMgr::GetInstance()->MonsterSound1(L"death1.wav");
							break;
						case 1:
							CSoundMgr::GetInstance()->MonsterSound2(L"death2.wav");
							break;
						case 2:
							CSoundMgr::GetInstance()->MonsterSound3(L"death3.wav");
							break;
						case 3:
							CSoundMgr::GetInstance()->MonsterSound4(L"death4.wav");
							break;
						case 4:
							CSoundMgr::GetInstance()->MonsterSound5(L"death5.wav");
							break;
						}
						m_bDeadSound = true;
					}
					FrameMove(14);
					if(m_iFrameX == 12)
					{
						CObjMgr::GetInstance()->AddObject(L"Dead", SORTID_DEAD, CFactory<CDead>::CreateObject(m_tInfo.fX, m_tInfo.fY + 50.f, m_DIRTYPE));
						++CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt;
						m_tInfo.bAlive = false;
						return;
					}
				}
			}
			else
			{
				if( m_bDead == false)
				{
					m_tInfo.fCX = 141.f;
					m_tInfo.fCY = 143.8f;
					FrameMove(10);
				}
			}
		}
	}
	if(m_DIRTYPE == DIR_RIGHT)
	{
		if(m_bMove == true)
		{
			m_tInfo.fCX = 145.f;
			m_tInfo.fCY = 140.8f;
			FrameMove(8);
		}
		else if(m_bMove == false)
		{
			if(m_bGetHit == true)
			{
				m_tInfo.fCX = 233.f;
				m_tInfo.fCY = 191.8f;
				FrameMove(19);
			}
			else if(m_bDead == true && m_bDeadCheck == false)
			{ 
				m_tInfo.fCX = 151.f;
				m_tInfo.fCY = 166.8f;
				if(m_bDeadCheck == false)
				{
					if(m_bDeadSound == false)
					{
						int iRand = rand() % 5;
						switch(iRand)
						{
						case 0:
							CSoundMgr::GetInstance()->MonsterSound1(L"death1.wav");
							break;
						case 1:
							CSoundMgr::GetInstance()->MonsterSound2(L"death2.wav");
							break;
						case 2:
							CSoundMgr::GetInstance()->MonsterSound3(L"death3.wav");
							break;
						case 3:
							CSoundMgr::GetInstance()->MonsterSound4(L"death4.wav");
							break;
						case 4:
							CSoundMgr::GetInstance()->MonsterSound5(L"death5.wav");
							break;
						}
						m_bDeadSound = true;
					}
					FrameMove(14);
					if(m_iFrameX == 12)
					{
						CObjMgr::GetInstance()->AddObject(L"Dead", SORTID_DEAD, CFactory<CDead>::CreateObject(m_tInfo.fX, m_tInfo.fY + 50.f, m_DIRTYPE));
						++CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt;
						m_tInfo.bAlive = false;
						return;
					}
				}

			}
			else
			{
				if( m_bDead == false)
				{
					m_tInfo.fCX = 141.f;
					m_tInfo.fCY = 143.8f;
					FrameMove(10);
				}
			}
		}
	}
	if(m_DIRTYPE == DIR_DOWN_R)
	{
		if(m_bMove == true)
		{
			m_tInfo.fCX = 145.f;
			m_tInfo.fCY = 140.8f;
			FrameMove(8);
		}
		else if(m_bMove == false)
		{
			if(m_bGetHit == true)
			{
				m_tInfo.fCX = 233.f;
				m_tInfo.fCY = 191.8f;
				FrameMove(19);
			}
			else if(m_bDead == true && m_bDeadCheck == false)
			{ 
				m_tInfo.fCX = 151.f;
				m_tInfo.fCY = 166.8f;
				if(m_bDeadCheck == false)
				{
					if(m_bDeadSound == false)
					{
						int iRand = rand() % 5;
						switch(iRand)
						{
						case 0:
							CSoundMgr::GetInstance()->MonsterSound1(L"death1.wav");
							break;
						case 1:
							CSoundMgr::GetInstance()->MonsterSound2(L"death2.wav");
							break;
						case 2:
							CSoundMgr::GetInstance()->MonsterSound3(L"death3.wav");
							break;
						case 3:
							CSoundMgr::GetInstance()->MonsterSound4(L"death4.wav");
							break;
						case 4:
							CSoundMgr::GetInstance()->MonsterSound5(L"death5.wav");
							break;
						}
						m_bDeadSound = true;
					}
					FrameMove(14);
					if(m_iFrameX == 12)
					{
						CObjMgr::GetInstance()->AddObject(L"Dead", SORTID_DEAD, CFactory<CDead>::CreateObject(m_tInfo.fX, m_tInfo.fY + 50.f, m_DIRTYPE));
						++CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt;
						m_tInfo.bAlive = false;
						return;
					}
				}

			}
			else
			{
				if( m_bDead == false)
				{
					m_tInfo.fCX = 141.f;
					m_tInfo.fCY = 143.8f;
					FrameMove(10);
				}
			}
		}
	}

}
