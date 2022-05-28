#include "StdAfx.h"
#include "BallStart.h"
#include "BallMove.h"

CBallStart::CBallStart(void)
{
}
CBallStart::CBallStart( float _fX, float _fY, eDIRTECTION_TYPE _eType )
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;
}
CBallStart::~CBallStart(void)
{
}

void CBallStart::Initialize( void )
{
	switch(m_eType)
	{
	case DIR_DOWN:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fCX = 48.f;
		m_tInfo.fCY = 68.f;
		break;
	case DIR_DOWN_L:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 54.f;
		m_tInfo.fCY = 69.f;
		break;
	case DIR_LEFT:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 58.f;
		m_tInfo.fCY = 73.f;
		break;
	case DIR_UP_L:
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 55.f;
		m_tInfo.fCY = 76.f;
		break;
	case DIR_UP:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY - CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		m_tInfo.fCX = 48.f;
		m_tInfo.fCY = 77.f;
		break;
	case DIR_UP_R:
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 55.f;
		m_tInfo.fCY = 76.f;
		break;
	case DIR_RIGHT:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 58.f;
		m_tInfo.fCY = 73.f;
		break;
	case DIR_DOWN_R:
		//m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY + CObjMgr::GetInstance()->GetInfo(L"Player")->fCY / 2.f;
		//m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX + CObjMgr::GetInstance()->GetInfo(L"Player")->fCX / 2.f;
		m_tInfo.fCX = 54.f;
		m_tInfo.fCY = 70.f;
		break;
	}

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
	m_tInfo.fSpeed = 2.f;

}

void CBallStart::Progress( void )
{
	FrameMove(6);
	if(m_iFrameX == 5)
	{
		CObjMgr::GetInstance()->AddObject(L"BallMove",SORTID_UNITANDOBJ, CFactory<CBallMove>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
	}

	switch(m_eType)
	{
	case DIR_DOWN:
		m_tInfo.fY += m_tInfo.fSpeed;
		break;
	case DIR_DOWN_L:
		m_tInfo.fX -= m_tInfo.fSpeed;
		m_tInfo.fY += m_tInfo.fSpeed;
		break;
	case DIR_LEFT:
		m_tInfo.fX -= m_tInfo.fSpeed;
		break;
	case DIR_UP_L:
		m_tInfo.fX -= m_tInfo.fSpeed;
		m_tInfo.fY -= m_tInfo.fSpeed;
		break;
	case DIR_UP:
		m_tInfo.fY -= m_tInfo.fSpeed;
		break;
	case DIR_UP_R:
		m_tInfo.fX += m_tInfo.fSpeed;
		m_tInfo.fY -= m_tInfo.fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_tInfo.fSpeed;
		break;
	case DIR_DOWN_R:
		m_tInfo.fX += m_tInfo.fSpeed;
		m_tInfo.fY += m_tInfo.fSpeed;
		break;
	}

}

void CBallStart::Render( void )
{
	switch(m_eType)
	{
	case DIR_DOWN:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_S_D"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_DOWN_L:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_S_D_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_LEFT:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_S_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP_L:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_S_U_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_S_U"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP_R:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_S_U_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_RIGHT:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_S_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_DOWN_R:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Ball_S_D_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	}

}

void CBallStart::Release( void )
{

}
