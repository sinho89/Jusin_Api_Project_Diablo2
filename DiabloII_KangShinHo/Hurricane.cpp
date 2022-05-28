#include "StdAfx.h"
#include "Hurricane.h"
#include "Cart.h"
#include "Rock.h"

CHurricane::CHurricane(void)
{
}

CHurricane::~CHurricane(void)
{
}

void CHurricane::Initialize(void)
{
	m_dwTime = GetTickCount();
	m_dwCool = GetTickCount();
	//CSoundMgr::GetInstance()->SkillSound1(L"hurricane.wav");

}

void CHurricane::Progress(void)
{
	if(m_dwTime + 500 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		CObjMgr::GetInstance()->AddObject(L"HurriCart", SORTID_UNITANDOBJ, CFactory<CCart>::CreateObject());
		CObjMgr::GetInstance()->AddObject(L"HurriRock", SORTID_UNITANDOBJ, CFactory<CRock>::CreateObject());
	}
	if(m_dwCool + 8000 < GetTickCount())
	{
		m_dwCool = GetTickCount();
		m_tInfo.bAlive = false;
	}
	if(CScene::m_bBattle == false)
	{
		m_tInfo.bAlive = false;
	}
}

void CHurricane::Render(void)
{
}

void CHurricane::Release(void)
{
}