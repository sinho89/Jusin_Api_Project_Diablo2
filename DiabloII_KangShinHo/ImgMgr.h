#pragma once

#include "Defines.h"

class CImgMgr
{
CREATE_SINGLETON(CImgMgr);
private: 
	map<const TCHAR*, HDC*>		m_MapBmp;
public:
	HDC* GetTexture(const TCHAR* pKey);
public:
	bool AddTexture(TCHAR* pFileName, const TCHAR* pKey, HDC hdc);
	void DeleteTexture();

private:
	CImgMgr(void);
public:
	~CImgMgr(void);
};
