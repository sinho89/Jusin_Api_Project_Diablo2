#include "StdAfx.h"
#include "Scene.h"
#include "ImgMgr.h"
#include "AstarMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "MouseRnd.h"
#include "CollMgr.h"

bool CScene::m_bBattle = false;
bool CScene::m_bHome = false;
bool CScene::m_bTileSet = false;


CScene::CScene(void)
{
	m_hdc = GetDC(g_hWnd);


	CImgMgr::GetInstance()->AddTexture(L"../Resource/Mouse.bmp", L"Mouse", m_hdc);
	CObjMgr::GetInstance()->AddObject(L"Mouse", SORTID_LAST, CFactory<CMouseRnd>::CreateObject());
}

CScene::~CScene(void)
{
	ReleaseDC(g_hWnd, m_hdc);

	CImgMgr::GetInstance()->Destroy();
	CAstarMgr::GetInstance()->Destroy();
	CTileMgr::GetInstance()->Destroy();
	CKeyMgr::GetInstance()->Destroy();
	CCollMgr::GetInstance()->Destroy();
}
