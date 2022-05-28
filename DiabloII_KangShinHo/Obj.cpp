#include "StdAfx.h"
#include "Obj.h"

POINT	CObj::m_ptScroll;
POINT	CObj::m_ptTileScroll;
POINT	CObj::m_ptPlayer;
POINT	CObj::m_ptMonster;
bool	CObj::m_bCamera = false;
bool	CObj::m_bRound = false;


CObj::CObj(void)
:m_bPush(false)
{
	m_hdc = GetDC(g_hWnd);
	m_dwFrameTick = GetTickCount();
	m_dwTime = GetTickCount();
	m_tInfo.bClick = false;
	m_tInfo.m_bHit = false;
	m_tInfo.m_bCast1 = false;
	m_tInfo.m_bCast2 = false;
	m_tInfo.m_bAtt = false;
}

CObj::~CObj(void)
{
	ReleaseDC(g_hWnd, m_hdc);
}
void CObj::FrameMove(int iMaxFrame)
{
	if(m_dwFrameTick + 50 < GetTickCount())
	{
		m_dwFrameTick = GetTickCount();
		++m_iFrameX;

		if(m_iFrameX >= iMaxFrame)
		{
			m_iFrameX = 0;
		}
	}
}
void CObj::FrameSkillMove(int iMaxFrame)
{
	if(m_dwFrameTick + 100 < GetTickCount())
	{
		m_dwFrameTick = GetTickCount();
		++m_iFrameX;

		if(m_iFrameX >= iMaxFrame)
		{
			m_iFrameX = 0;
		}
	}
}
void CObj::FrameIntroMove(int iMaxFrame)
{
	if(m_dwFrameTick + 30 < GetTickCount())
	{
		m_dwFrameTick = GetTickCount();
		++m_iFrameX;

		if(m_iFrameX >= iMaxFrame)
		{
			m_iFrameX = 0;
		}
	}
}

void CObj::FrameDeathMove(int iMaxFrame)
{
	if(m_dwFrameTick + 50 < GetTickCount())
	{
		m_dwFrameTick = GetTickCount();
		++m_iFrameX;

		if(m_iFrameX >= iMaxFrame)
		{
			m_iFrameX = 140;
		}
	}
}

void CObj::FrameMoveReverse()
{
	if(m_dwFrameTick + 50 < GetTickCount())
	{
		m_dwFrameTick = GetTickCount();
		--m_iFrameX;

		if(0 >= m_iFrameX)
		{
			m_iFrameX = 0;
		}
	}
}




void CObj::FramePortalMove(int iMaxFrame)
{
	if(m_dwFrameTick + 50 < GetTickCount())
	{
		m_dwFrameTick = GetTickCount();
		++m_iFrameX;

		if(m_iFrameX >= iMaxFrame)
		{
			m_iFrameX = 0;
		}
	}
}

void CObj::FrameInferno( int iMaxFrame )
{
	if(m_dwFrameTick + 50 < GetTickCount())
	{
		m_dwFrameTick = GetTickCount();
		++m_iFrameX;

		if(m_iFrameX >= iMaxFrame)
		{
			m_iFrameX = 10;
		}
	}

}

