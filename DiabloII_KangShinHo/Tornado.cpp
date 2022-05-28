#include "StdAfx.h"
#include "Tornado.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "TorEff.h"

CTornado::CTornado(void)
{
}

CTornado::CTornado( float _fX, float _fY, eDIRTECTION_TYPE _eType )
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;
}

CTornado::~CTornado(void)
{
}

void CTornado::Initialize( void )
{
	m_dwTime = GetTickCount();
	m_dwCool = GetTickCount();
	CObjMgr::GetInstance()->AddObject(L"TorEff", SORTID_UNITANDOBJ, CFactory<TorEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_eType));

}

void CTornado::Progress( void )
{

	m_tInfo.bAlive = false;
}

void CTornado::Render( void )
{

}

void CTornado::Release( void )
{

}
