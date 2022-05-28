#include "StdAfx.h"
#include "Shork.h"
#include "Obj.h"
#include "Factory.h"
#include "ShockEff.h"

CShork::CShork(void)
{
}

CShork::CShork( float _fX, float _fY, eDIRTECTION_TYPE _eType )
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;
}

CShork::~CShork(void)
{
}

void CShork::Initialize( void )
{
	m_dwTime = GetTickCount();
	m_dwCool = GetTickCount();

	CSoundMgr::GetInstance()->SkillSound2(L"shockwave.wav");
}

void CShork::Progress( void )
{
	switch(m_eType)
	{
	case DIR_DOWN:
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN_L));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN_R));
		m_tInfo.bAlive = false;
		break;
		
	case DIR_DOWN_L:
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN_L));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN));
		m_tInfo.bAlive = false;
		break;
		
	case DIR_LEFT:
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP_L));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN_L));
		m_tInfo.bAlive = false;
		break;
		
	case DIR_UP_L:
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP_L));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		m_tInfo.bAlive = false;
		break;
		
	case DIR_UP:
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP_L));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP_R));
		m_tInfo.bAlive = false;
		break;
		
	case DIR_UP_R:
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP_R));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
		m_tInfo.bAlive = false;
		break;
		
	case DIR_RIGHT:
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_UP_R));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN_R));
		m_tInfo.bAlive = false;
		break;
		
	case DIR_DOWN_R:
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_DOWN_R));
		CObjMgr::GetInstance()->AddObject(L"ShockEff", SORTID_UNITANDOBJ, CFactory<CShockEff>::CreateObject(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
		m_tInfo.bAlive = false;
		break;
	}

	m_tInfo.bAlive = false;
}

void CShork::Render( void )
{

}

void CShork::Release( void )
{

}
