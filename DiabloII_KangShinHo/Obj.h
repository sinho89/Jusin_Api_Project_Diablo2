#pragma once

#include "Defines.h"
#include "ImgMgr.h"
#include "Scene.h"
#include "SoundMgr.h"

class CObj abstract
{
protected:
	HDC		m_hdc;
	INFO	m_tInfo;
	RENDER		m_Render;
	eSKILL_TYPE	m_eType;
	eSKILL_TYPE m_eSaveType[6];
	int		m_iFrameX;
	int		m_iFrameY;
	bool	m_bPush;
	static bool		m_bCamera;

	DWORD	m_dwFrameTick;
	DWORD	m_dwTime;
	DWORD	m_dwCool;
public:
	static POINT	m_ptScroll;
	static POINT	m_ptPlayer;
	static POINT	m_ptMonster;
	static bool		m_bRound;

protected:
	TCHAR*		m_pImgKey;
public:
	void SetImgKey(TCHAR* pImgKey)
	{
		m_pImgKey = pImgKey;
	}
public:
	static POINT	m_ptTileScroll;
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
public:
	void FrameMove(int iMaxFrame);
	void FrameSkillMove(int iMaxFrame);
	void FrameInferno(int iMaxFrame);
	void FrameDeathMove(int iMaxFrame);
	void FrameIntroMove(int iMaxFrame);
	void FrameMoveReverse();
	void FramePortalMove(int iMaxFrame);
	void FramePortalDoor(int iMaxFrame);
public:
	INFO&	GetInfo()
	{
		return m_tInfo;
	}
	RENDER& GetRender()
	{
		return m_Render;
	}
	eSKILL_TYPE& GetSkill()
	{
		return m_eType;
	}
	eSKILL_TYPE* GetSaveSkill()
	{
		return m_eSaveType;
	}
public:
	CObj(void);
	virtual ~CObj(void);
};
