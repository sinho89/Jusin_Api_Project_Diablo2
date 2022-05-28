#pragma once


#include "ObjMgr.h"
#include "ImgMgr.h"
#include "Factory.h"
#include "Defines.h"
#include "SoundMgr.h"

class CScene
{
protected:
	HDC		m_hdc;
	POINT	m_ptTileScroll1;
	DWORD	m_dwTime;
	int		m_iShake;
public:
	static bool m_bBattle;
	static bool m_bHome;
	static bool m_bTileSet;
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
public:
	CScene(void);
	virtual ~CScene(void);
};
