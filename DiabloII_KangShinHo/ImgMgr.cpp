#include "StdAfx.h"
#include "ImgMgr.h"

INIT_SINGLETON(CImgMgr);
CImgMgr::CImgMgr(void)
{

}

CImgMgr::~CImgMgr(void)
{
	DeleteTexture();
}

HDC* CImgMgr::GetTexture(const TCHAR* pKey)
{
	// pKey�� �ش��ϴ� pair type�� ������ġ�� �����Ѵ�.
	map<const TCHAR*, HDC*>::iterator	iter = m_MapBmp.find(pKey);

	if(iter == m_MapBmp.end())
	{
		MessageBox(g_hWnd, pKey, L"ErrMsg", MB_OK);
		return NULL;
	}

	return iter->second;
}

bool CImgMgr::AddTexture(TCHAR* pFileName
						 , const TCHAR* pKey
						 , HDC hdc)
{
	// HDC			MemDC;
	// �̹����� �����ϱ����� ����.
	HDC* pMemDC = new HDC;
	*pMemDC = CreateCompatibleDC(hdc);

	// �̹��� �ڵ��̴�.
	HBITMAP		bitmap;

	bitmap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP
		, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if(bitmap == NULL)
	{
		delete pMemDC;
		pMemDC = NULL;
		MessageBox(g_hWnd, L"�̹����ε����", L"ErrMsg", MB_OK);
		return false;
	}

	SelectObject(*pMemDC, bitmap);

	//m_vecBmp.push_back(pMemDC);
	m_MapBmp.insert(make_pair(pKey, pMemDC));

	DeleteObject(bitmap);

	return true;
}

void CImgMgr::DeleteTexture()
{
	map<const TCHAR*, HDC*>::iterator	iter =  m_MapBmp.begin();
	map<const TCHAR*, HDC*>::iterator	iter_end =  m_MapBmp.end();

	for(iter; iter != iter_end; ++iter)
	{
		safe_delete(iter->second);
	}

	m_MapBmp.clear();
}