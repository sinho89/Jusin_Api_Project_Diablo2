#include "StdAfx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"
#include "MyEdit.h"
#include "Intro.h"

INIT_SINGLETON(CSceneMgr);

CSceneMgr::CSceneMgr(void)
:m_pScene(NULL)
{
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::SetState(eSCENE_TYPE _eType)
{
	safe_delete(m_pScene);

	switch(_eType)
	{
	case ST_INTRO:
		m_pScene = new CIntro;
		break;
	case ST_LOGO:
		m_pScene = new CLogo;
		break;
	case ST_MENU:
		m_pScene = new CMyMenu;
		break;
	case ST_EDIT:
		m_pScene = new CMyEdit;
		break;
	case ST_STAGE:
		m_pScene = new CStage;
		break;
	
	}

	m_pScene->Initialize();
}
void CSceneMgr::Progress(void)
{
	m_pScene->Progress();
}
void CSceneMgr::Render(void)
{
	m_pScene->Render();
}
void CSceneMgr::Release(void)
{
	safe_delete(m_pScene);
}