#include "StdAfx.h"
#include "Unit.h"

CUnit::CUnit(void)
{
	m_Render.m_bInvenRender = false;
	m_Render.m_bShopRender = false;
	m_Render.m_bSkillRender = false;
	m_Render.m_bQuestRender = false;
	m_Render.m_bItemRender = false;
	m_Render.m_bStatRender = false;
	m_Render.m_bCubeRender = false;
}

CUnit::~CUnit(void)
{
}
void CUnit::DirectPos(void)
{
	if(m_BestQueue.empty())
		return;

	int		iIndex = int(m_tInfo.fY / iTILESIZE) * iTILECNTX + int(m_tInfo.fX / iTILESIZE);


	if((iIndex + iTILECNTX) == m_BestQueue.front()) // 아래쪽 -90
	{
		m_DIRTYPE = DIR_DOWN;
		m_iFrameY = 0;
	}
	else if((iIndex + iTILECNTX - 1) == m_BestQueue.front()) // 왼쪽아래 -135
	{
		m_DIRTYPE = DIR_DOWN_L;
		m_iFrameY = 1;
	}
	else if((iIndex - 1) == m_BestQueue.front())//왼쪽 - 180
	{
		m_DIRTYPE = DIR_LEFT;
		m_iFrameY = 2;
	}
	else if((iIndex - iTILECNTX - 1) == m_BestQueue.front())//왼쪽위 - 180
	{
		m_DIRTYPE = DIR_UP_L;
		m_iFrameY = 3;
	}
	else if((iIndex - iTILECNTX) == m_BestQueue.front())
	{
		m_DIRTYPE = DIR_UP;
		m_iFrameY = 4;
	}
	else if((iIndex - iTILECNTX + 1) == m_BestQueue.front())
	{
		m_DIRTYPE = DIR_UP_R;
		m_iFrameY = 5;
	}
	else if((iIndex + 1) == m_BestQueue.front())
	{
		m_DIRTYPE = DIR_RIGHT;
		m_iFrameY = 6;
	}
	else if((iIndex + iTILECNTX + 1) == m_BestQueue.front())
	{
		m_DIRTYPE = DIR_DOWN_R;
		m_iFrameY = 7;
	}

}

void CUnit::SetPos( void )
{
	if(m_DIRTYPE == DIR_DOWN)
	{
		if(m_bMove == true && m_bTransForm == false) // 변신 전 이동
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 71.f;
				m_tInfo.fCY = 83.f;
				FrameMove(7);
			}
			else if(m_bRun == false)
			{

				m_tInfo.fCX = 46.f;
				m_tInfo.fCY = 80.f;
				FrameMove(7);
			}
		}
		if(m_bMove == true && m_bTransForm == true) // 변신 후 이동
		{
			if(m_bRun == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 75.f;
				m_tInfo.fCY = 92.f;
				FrameMove(8);
			}
			else if(m_bRun == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 65.f;
				m_tInfo.fCY = 94.f;
				FrameMove(8);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == false) // 변신전 평소
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 84.8f;
				FrameMove(16);
				if(m_iFrameX == 15)
					m_tInfo.m_bAtt = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 97.8f;
				FrameMove(15);
				if(m_iFrameX == 14)
					m_tInfo.m_bCast1 = false;

			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == true)
			{
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 90.8f;
				FrameMove(7);
				if(m_iFrameX == 6)
					m_tInfo.m_bGetHit = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 43.f;
				m_tInfo.fCY = 78.f;
				FrameMove(5);
			}

		}
		else if(m_bMove == false && m_bTransFormTick == true) // 변신후 평소
		{
			if(m_tInfo.m_bCast2 == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 128.f;
				m_tInfo.fCY = 102.f;
				FrameMove(10);
				if(m_iFrameX == 9)
				{
					m_iFrameX = 0;
					m_tInfo.m_bCast2 = false;
				}
				
			}
			else if(m_tInfo.m_bCast2 == false)
			{
				m_tInfo.fCX = 80.f;
				m_tInfo.fCY = 95.f;
				FrameMove(10);
			}
		}
	}
	if(m_DIRTYPE == DIR_DOWN_L)
	{
		if(m_bMove == true && m_bTransForm == false) // 변신 전 이동
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 71.f;
				m_tInfo.fCY = 84.f;
				FrameMove(7);
			}
			else if(m_bRun == false)
			{

				m_tInfo.fCX = 46.f;
				m_tInfo.fCY = 81.f;
				FrameMove(7);
			}
		}
		if(m_bMove == true && m_bTransForm == true) // 변신 후 이동
		{
			if(m_bRun == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 77.f;
				m_tInfo.fCY = 92.f;
				FrameMove(8);
			}
			else if(m_bRun == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 67.f;
				m_tInfo.fCY = 96.f;
				FrameMove(8);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == false) // 변신전 평소
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 84.8f;
				FrameMove(16);
				if(m_iFrameX == 15)
					m_tInfo.m_bAtt = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 97.8f;
				FrameMove(15);
				if(m_iFrameX == 14)
					m_tInfo.m_bCast1 = false;

			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == true)
			{
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 90.8f;
				FrameMove(7);
				if(m_iFrameX == 6)
					m_tInfo.m_bGetHit = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 43.f;
				m_tInfo.fCY = 78.f;
				FrameMove(5);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == true) // 변신후 평소
		{
			if(m_tInfo.m_bCast2 == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 124.f;
				m_tInfo.fCY = 116.f;
				FrameMove(10);
				if(m_iFrameX == 9)
				{
					m_iFrameX = 0;
					m_tInfo.m_bCast2 = false;
				}
			}
			else if(m_tInfo.m_bCast2 == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 58.f;
				m_tInfo.fCY = 101.f;
				FrameMove(10);
			}
		}

	}
	if(m_DIRTYPE == DIR_LEFT)
	{
		if(m_bMove == true && m_bTransForm == false) // 변신 전 이동
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 71.f;
				m_tInfo.fCY = 84.f;
				FrameMove(7);
			}
			else if(m_bRun == false)
			{
				m_tInfo.fCX = 46.f;
				m_tInfo.fCY = 81.f;
				FrameMove(7);
			}
		}
		if(m_bMove == true && m_bTransForm == true) // 변신 후 이동
		{
			if(m_bRun == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 94.f;
				m_tInfo.fCY = 93.f;
				FrameMove(8);
			}
			else if(m_bRun == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 73.f;
				m_tInfo.fCY = 95.f;
				FrameMove(8);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == false) // 변신전 평소
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 84.8f;
				FrameMove(16);
				if(m_iFrameX == 15)
					m_tInfo.m_bAtt = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 97.8f;
				FrameMove(15);
				if(m_iFrameX == 14)
					m_tInfo.m_bCast1 = false;

			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == true)
			{
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 90.8f;
				FrameMove(7);
				if(m_iFrameX == 6)
					m_tInfo.m_bGetHit = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 43.f;
				m_tInfo.fCY = 78.f;
				FrameMove(5);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == true) // 변신후 평소
		{
			if(m_tInfo.m_bCast2 == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 123.f;
				FrameMove(10);
				if(m_iFrameX == 9)
				{
					m_iFrameX = 0;
					m_tInfo.m_bCast2 = false;
				}
			}
			else if(m_tInfo.m_bCast2 == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 54.f;//54.f;
				m_tInfo.fCY = 102.f;//102.f;
				FrameMove(10);
			}
		}
	}
	if(m_DIRTYPE == DIR_UP_L)
	{
		if(m_bMove == true && m_bTransForm == false) // 변신 전 이동
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 71.f;
				m_tInfo.fCY = 84.f;
				FrameMove(7);
			}
			else if(m_bRun == false)
			{

				m_tInfo.fCX = 46.f;
				m_tInfo.fCY = 81.f;
				FrameMove(7);
			}
		}
		if(m_bMove == true && m_bTransForm == true) // 변신 후 이동
		{
			if(m_bRun == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 75.f;
				m_tInfo.fCY = 110.f;
				FrameMove(8);
			}
			else if(m_bRun == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 66.f;
				m_tInfo.fCY = 102.f;
				FrameMove(8);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == false) // 변신전 평소
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 84.8f;
				FrameMove(16);
				if(m_iFrameX == 15)
					m_tInfo.m_bAtt = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 97.8f;
				FrameMove(15);
				if(m_iFrameX == 14)
					m_tInfo.m_bCast1 = false;

			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == true)
			{
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 90.8f;
				FrameMove(7);
				if(m_iFrameX == 6)
					m_tInfo.m_bGetHit = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 43.f;
				m_tInfo.fCY = 78.f;
				FrameMove(5);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == true) // 변신후 평소
		{
			if(m_tInfo.m_bCast2 == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 124.f;
				m_tInfo.fCY = 119.f;
				FrameMove(10);
				if(m_iFrameX == 9)
				{
					m_iFrameX = 0;
					m_tInfo.m_bCast2 = false;
				}
			}
			else if(m_tInfo.m_bCast2 == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 65.f;
				m_tInfo.fCY = 99.f;
				FrameMove(10);
			}
		}
	}
	if(m_DIRTYPE == DIR_UP)
	{
		if(m_bMove == true && m_bTransForm == false) // 변신 전 이동
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 71.f;
				m_tInfo.fCY = 84.f;
				FrameMove(7);
			}
			else if(m_bRun == false)
			{

				m_tInfo.fCX = 46.f;
				m_tInfo.fCY = 81.f;
				FrameMove(7);
			}
		}
		if(m_bMove == true && m_bTransForm == true) // 변신 후 이동
		{
			if(m_bRun == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 74.f;
				m_tInfo.fCY = 115.f;
				FrameMove(8);
			}
			else if(m_bRun == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 64.f;
				m_tInfo.fCY = 105.f;
				FrameMove(8);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == false) // 변신전 평소
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 84.8f;
				FrameMove(16);
				if(m_iFrameX == 15)
					m_tInfo.m_bAtt = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 97.8f;
				FrameMove(15);
				if(m_iFrameX == 14)
					m_tInfo.m_bCast1 = false;

			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == true)
			{
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 90.8f;
				FrameMove(7);
				if(m_iFrameX == 6)
					m_tInfo.m_bGetHit = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 43.f;
				m_tInfo.fCY = 78.f;
				FrameMove(5);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == true) // 변신후 평소
		{
			if(m_tInfo.m_bCast2 == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 112.f;
				m_tInfo.fCY = 119.f;
				FrameMove(10);
				if(m_iFrameX == 9)
				{
					m_iFrameX = 0;
					m_tInfo.m_bCast2 = false;
				}
			}
			else if(m_tInfo.m_bCast2 == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 102.f;
				FrameMove(10);
			}
		}
	}
	if(m_DIRTYPE == DIR_UP_R)
	{
		if(m_bMove == true && m_bTransForm == false) // 변신 전 이동
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 71.f;
				m_tInfo.fCY = 84.f;
				FrameMove(7);
			}
			else if(m_bRun == false)
			{

				m_tInfo.fCX = 46.f;
				m_tInfo.fCY = 81.f;
				FrameMove(7);
			}
		}
		if(m_bMove == true && m_bTransForm == true) // 변신 후 이동
		{
			if(m_bRun == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 77.f;
				m_tInfo.fCY = 106.f;
				FrameMove(8);
			}
			else if(m_bRun == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 64.f;
				m_tInfo.fCY = 102.f;
				FrameMove(8);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == false) // 변신전 평소
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 84.8f;
				FrameMove(16);
				if(m_iFrameX == 15)
					m_tInfo.m_bAtt = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 97.8f;
				FrameMove(15);
				if(m_iFrameX == 14)
					m_tInfo.m_bCast1 = false;

			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == true)
			{
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 90.8f;
				FrameMove(7);
				if(m_iFrameX == 6)
					m_tInfo.m_bGetHit = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 43.f;
				m_tInfo.fCY = 78.f;
				FrameMove(5);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == true) // 변신후 평소
		{
			if(m_tInfo.m_bCast2 == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 122.f;
				m_tInfo.fCY = 123.f;
				FrameMove(10);
				if(m_iFrameX == 9)
				{
					m_iFrameX = 0;
					m_tInfo.m_bCast2 = false;
				}
			}
			else if(m_tInfo.m_bCast2 == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 58.f;
				m_tInfo.fCY = 104.f;
				FrameMove(10);
			}
		}
	}
	if(m_DIRTYPE == DIR_RIGHT)
	{
		if(m_bMove == true && m_bTransForm == false) // 변신 전 이동
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 71.f;
				m_tInfo.fCY = 84.f;
				FrameMove(7);
			}
			else if(m_bRun == false)
			{
				m_tInfo.fCX = 46.f;
				m_tInfo.fCY = 81.f;
				FrameMove(7);
			}
		}
		if(m_bMove == true && m_bTransForm == true) // 변신 후 이동
		{
			if(m_bRun == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 94.f;
				m_tInfo.fCY = 94.f;
				FrameMove(8);
			}
			else if(m_bRun == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 94.f;
				FrameMove(8);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == false) // 변신전 평소
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 84.8f;
				FrameMove(16);
				if(m_iFrameX == 15)
					m_tInfo.m_bAtt = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 97.8f;
				FrameMove(15);
				if(m_iFrameX == 14)
					m_tInfo.m_bCast1 = false;

			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == true)
			{
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 90.8f;
				FrameMove(7);
				if(m_iFrameX == 6)
					m_tInfo.m_bGetHit = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 43.f;
				m_tInfo.fCY = 78.f;
				FrameMove(5);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == true) // 변신후 평소
		{
			if(m_tInfo.m_bCast2 == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 89.f;
				m_tInfo.fCY = 126.f;
				FrameMove(10);
				if(m_iFrameX == 9)
				{
					m_iFrameX = 0;
					m_tInfo.m_bCast2 = false;
				}
			}
			else if(m_tInfo.m_bCast2 == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 56.f;
				m_tInfo.fCY = 101.f;
				FrameMove(10);
			}
		}
	}
	if(m_DIRTYPE == DIR_DOWN_R)
	{
		if(m_bMove == true && m_bTransForm == false) // 변신 전 이동
		{
			if(m_bRun == true)
			{
				m_tInfo.fCX = 71.f;
				m_tInfo.fCY = 83.5f;
				FrameMove(7);
			}
			else if(m_bRun == false)
			{

				m_tInfo.fCX = 46.f;
				m_tInfo.fCY = 80.5f;
				FrameMove(7);
			}
		}
		if(m_bMove == true && m_bTransForm == true) // 변신 후 이동
		{
			if(m_bRun == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 76.f;
				m_tInfo.fCY = 90.f;
				FrameMove(8);
			}
			else if(m_bRun == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 68.f;
				m_tInfo.fCY = 95.f;
				FrameMove(8);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == false) // 변신전 평소
		{
			if(m_tInfo.m_bAtt == true && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 84.8f;
				FrameMove(16);
				if(m_iFrameX == 15)
					m_tInfo.m_bAtt = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == true && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 79.f;
				m_tInfo.fCY = 97.f;
				FrameMove(15);
				if(m_iFrameX == 14)
					m_tInfo.m_bCast1 = false;

			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == true)
			{
				m_tInfo.fCX = 72.f;
				m_tInfo.fCY = 90.8f;
				FrameMove(7);
				if(m_iFrameX == 6)
					m_tInfo.m_bGetHit = false;
			}
			else if(m_tInfo.m_bAtt == false && m_tInfo.m_bCast1 == false && m_tInfo.m_bGetHit == false)
			{
				m_tInfo.fCX = 43.f;
				m_tInfo.fCY = 77.5f;
				FrameMove(5);
			}
		}
		else if(m_bMove == false && m_bTransFormTick == true) // 변신후 평소
		{
			if(m_tInfo.m_bCast2 == true)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 128.f;
				m_tInfo.fCY = 113.f;
				FrameMove(10);
				if(m_iFrameX == 9)
				{
					m_iFrameX = 0;
					m_tInfo.m_bCast2 = false;
				}
			}
			else if(m_tInfo.m_bCast2 == false)
			{
				m_iFrameY = 0;
				m_tInfo.fCX = 67.f;
				m_tInfo.fCY = 92.f;
				FrameMove(10);
			}
		}
	}
}
