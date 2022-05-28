#include "StdAfx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"

CMainGame::CMainGame(void)
{
	//AllocConsole(); 
	//freopen( "CONOUT$",  "wt", stdout);
	//SetConsoleTitleA("Debug");
	CSoundMgr::GetInstance()->LoadSoundFile();
}

CMainGame::~CMainGame(void)
{
	Release();
	//FreeConsole();
}

void CMainGame::Initialize(void)
{
	CSceneMgr::GetInstance()->SetState(ST_INTRO);
	
}
void CMainGame::Progress(void)
{
	CMouse::SetMousePos();
	CKeyMgr::GetInstance()->SetKeyState();
	CSceneMgr::GetInstance()->Progress();
}
void CMainGame::Render(void)
{
	CSceneMgr::GetInstance()->Render();
}
void CMainGame::Release(void)
{
	CSoundMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->Destroy();
}