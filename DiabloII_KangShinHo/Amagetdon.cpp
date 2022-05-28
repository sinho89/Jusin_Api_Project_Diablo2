#include "StdAfx.h"
#include "Amagetdon.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "AmaRock.h"

CAmagetdon::CAmagetdon(void)
{
}

CAmagetdon::~CAmagetdon(void)
{
}
void CAmagetdon::Initialize(void)
{
	m_dwTime = GetTickCount();
	m_dwCool = GetTickCount();
}

void CAmagetdon::Progress(void)
{
	if(m_dwTime + 500 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		CObjMgr::GetInstance()->AddObject(L"AmaRock", SORTID_SKILL, CFactory<CAmaRock>::CreateObject());
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

void CAmagetdon::Render(void)
{
}

void CAmagetdon::Release(void)
{
}