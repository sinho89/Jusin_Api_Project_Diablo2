#include "StdAfx.h"
#include "MyEdit.h"
#include "ObjMgr.h"
#include "ImgMgr.h"
#include "Factory.h"
#include "StageBack.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "Mouse.h"
#include "Monster.h"
#include "Obj.h"


CMyEdit::CMyEdit(void)
:m_bPush(false)
{
}

CMyEdit::~CMyEdit(void)
{
	Release();
}
void CMyEdit::Initialize( void )
{

	CTileMgr::GetInstance()->SetTile();

	CImgMgr::GetInstance()->AddTexture(L"../Resource/BackBuffer.bmp", L"BackBuffer", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/StageBack1.bmp", L"StageBack", m_hdc);;
	CImgMgr::GetInstance()->AddTexture(L"../Resource/BattleBack.bmp", L"BattleBack", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Edit/Tile.bmp", L"Tile", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Cow_Att.bmp"), L"Cow_Att", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Cow.bmp"), L"Cow", m_hdc);

}

void CMyEdit::Progress( void )
{
	POINT ptMouse = CMouse::GetMousePos();
	
	if(ptMouse.x > iWINCX)
		CObj::m_ptScroll.x -= 10;
	if(ptMouse.x< 0)
		CObj::m_ptScroll.x += 10;
	if(ptMouse.y > iWINCY)
		CObj::m_ptScroll.y -= 10;
	if(ptMouse.y < 0)
		CObj::m_ptScroll.y += 10;

	if(CObj::m_ptScroll.x > 0)
		CObj::m_ptScroll.x = 0;
	if(CObj::m_ptScroll.y > 0)
		CObj::m_ptScroll.y = 0;

	ptMouse.x -= CObj::m_ptScroll.x;
	ptMouse.y -= CObj::m_ptScroll.y;

	int		iIndex = int(ptMouse.x) / iTILESIZE + int(ptMouse.y) / iTILESIZE * iTILECNTX;

	if(iIndex < 0)
		return;

	if(GetKeyState('P') & 0x8000)
	{
		if(m_bPush == true)
			return;
		m_bPush = true;
		CObjMgr::GetInstance()->AddObject(L"Cow",SORTID_UNITANDOBJ,CFactory<CMonster>::CreateObject(ptMouse.x, ptMouse.y));

	}
	else
		m_bPush = false;

	if(GetKeyState(VK_LBUTTON) & 0x8000)
	{		
		CTileMgr::GetInstance()->GetTileVector()[iIndex]->iDrawID = 1;
		CTileMgr::GetInstance()->GetTileVector()[iIndex]->bOption = true;		
	}

	if(GetKeyState(VK_RBUTTON) & 0x8000)
	{		
		CTileMgr::GetInstance()->GetTileVector()[iIndex]->iDrawID = 0;
		CTileMgr::GetInstance()->GetTileVector()[iIndex]->bOption = false;		
	}


	if(GetAsyncKeyState('1') & 0x8000)
	{
		if(MessageBox(g_hWnd, L"저장ㄱㄱ?", L"SystemMsg", MB_OKCANCEL) == IDCANCEL)
			return;	

		HANDLE			hFile;
		DWORD			dwByte;

		hFile = CreateFile(L"../Data/LogCamp.dat", GENERIC_WRITE, 0, 0
			, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		for (int i = 0; i < (iTILECNTX * iTILECNTY); ++i)
		{
			WriteFile(hFile, CTileMgr::GetInstance()->GetTileVector()[i], sizeof(TILE), &dwByte, NULL);
		}

		CloseHandle(hFile);
	}

	if(GetAsyncKeyState('2') & 0x8000)
	{
		if(MessageBox(g_hWnd, L"저장ㄱㄱ?", L"SystemMsg", MB_OKCANCEL) == IDCANCEL)
			return;	

		HANDLE			hFile;
		DWORD			dwByte;

		hFile = CreateFile(L"../Data/Battle.dat", GENERIC_WRITE, 0, 0
			, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		for (int i = 0; i < (iTILECNTX * iTILECNTY); ++i)
		{
			WriteFile(hFile, CTileMgr::GetInstance()->GetTileVector()[i], sizeof(TILE), &dwByte, NULL);
		}

		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();

		for(iter; iter != iter_end; ++iter)
		{
			WriteFile(hFile, &(*iter)->GetInfo(), sizeof(INFO), &dwByte, NULL);
		}

		CloseHandle(hFile);
	}
	if(GetAsyncKeyState('3') & 0x8000)
	{
		HANDLE			hFile;
		DWORD			dwByte;

		hFile = CreateFile(L"../Data/Monster1.dat", GENERIC_WRITE, 0, 0
			, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();

		for(iter; iter != iter_end; ++iter)
		{
			WriteFile(hFile, &(*iter)->GetInfo(), sizeof(INFO), &dwByte, NULL);
		}

		CloseHandle(hFile);
	}

	if(GetAsyncKeyState('4') & 0x8000)
	{
		HANDLE			hFile;
		DWORD			dwByte;

		hFile = CreateFile(L"../Data/Monster2.dat", GENERIC_WRITE, 0, 0
			, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();

		for(iter; iter != iter_end; ++iter)
		{
			WriteFile(hFile, &(*iter)->GetInfo(), sizeof(INFO), &dwByte, NULL);
		}

		CloseHandle(hFile);
	}

	CObjMgr::GetInstance()->Progress();

}

void CMyEdit::Render( void )
{
	
	BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 0 + CObj::m_ptScroll.x
		, 0 + CObj::m_ptScroll.y
		, 4456
		, 2850
		, *CImgMgr::GetInstance()->GetTexture(L"BattleBack")
		, 0
		, 0
		, SRCCOPY);

	int iCullX = iWINCX / iTILESIZE;		//12.5
	int iCullY = iWINCY / iTILESIZE;		//9.375

	//출력되는 index를 구하자.
	int iCullStartX = -CObj::m_ptScroll.x / iTILESIZE;
	int iCullStartY = -CObj::m_ptScroll.y / iTILESIZE;

	int iCullEndX = iCullStartX + iCullX + 2;
	int iCullEndY = iCullStartY + iCullY + 2;

	for(int i = iCullStartY; i < iCullEndY; ++i)
	{
		for(int j = iCullStartX; j < iCullEndX; ++j)
		{
			int iIndex = j + i * iTILECNTX;

			if(iIndex < 0 || iIndex >= iTILECNTX * iTILECNTY)
				continue;

			TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fX - CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX / 2)  + CObj::m_ptScroll.x
				, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fY - CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY / 2.f)  + CObj::m_ptScroll.y
				, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX)
				, int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"Tile"), int( CTileMgr::GetInstance()->GetTileVector()[iIndex]->iDrawID  * CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX)
				, 0, 
				int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCX), int(CTileMgr::GetInstance()->GetTileVector()[iIndex]->fCY), RGB(255, 255, 255));
		}
	}
	
	CObjMgr::GetInstance()->Render();

	BitBlt(m_hdc, 0, 0, iWINCX, iWINCY, *CImgMgr::GetInstance()->GetTexture(L"BackBuffer")
		, 0, 0, SRCCOPY);
}

void CMyEdit::Release( void )
{
	CObjMgr::GetInstance()->Destroy();
}