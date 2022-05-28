#include "StdAfx.h"
#include "Ball.h"
#include "BallStart.h"

CBall::CBall(void)
{
}
CBall::CBall( float _fX, float _fY, eDIRTECTION_TYPE _eType )
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;
}
CBall::~CBall(void)
{
}

void CBall::Initialize( void )
{
	m_dwTime = GetTickCount();
	m_dwCool = GetTickCount();
}

void CBall::Progress( void )
{
	switch(m_eType)
	{
	case DIR_DOWN:
		CObjMgr::GetInstance()->AddObject(L"BallStart", SORTID_UNITANDOBJ, CFactory<CBallStart>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
		break;

	case DIR_DOWN_L:
		CObjMgr::GetInstance()->AddObject(L"BallStart", SORTID_UNITANDOBJ, CFactory<CBallStart>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
		break;

	case DIR_LEFT:
		CObjMgr::GetInstance()->AddObject(L"BallStart", SORTID_UNITANDOBJ, CFactory<CBallStart>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
		break;

	case DIR_UP_L:
		CObjMgr::GetInstance()->AddObject(L"BallStart", SORTID_UNITANDOBJ, CFactory<CBallStart>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
		break;

	case DIR_UP:
		CObjMgr::GetInstance()->AddObject(L"BallStart", SORTID_UNITANDOBJ, CFactory<CBallStart>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
		break;

	case DIR_UP_R:
		CObjMgr::GetInstance()->AddObject(L"BallStart", SORTID_UNITANDOBJ, CFactory<CBallStart>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
		break;

	case DIR_RIGHT:
		CObjMgr::GetInstance()->AddObject(L"BallStart", SORTID_UNITANDOBJ, CFactory<CBallStart>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
		break;

	case DIR_DOWN_R:
		CObjMgr::GetInstance()->AddObject(L"BallStart", SORTID_UNITANDOBJ, CFactory<CBallStart>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));
		m_tInfo.bAlive = false;
		break;
	}

	m_tInfo.bAlive = false;
}

void CBall::Render( void )
{

}

void CBall::Release( void )
{

}
