#include "StdAfx.h"
#include "Inferno.h"

CInferno::CInferno(void)
{
}

CInferno::CInferno(float _fX, float _fY, eDIRTECTION_TYPE _eType)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;
}
CInferno::~CInferno(void)
{
}

void CInferno::Initialize(void)
{
	m_dwCool = GetTickCount();

	m_tInfo.fAngle = 0;
	m_tInfo.fSpeed = 7.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	switch(m_eType)
	{
	case DIR_DOWN:
		m_tInfo.fCX = 120.f;
		m_tInfo.fCY = 157.f;
		break;
	case DIR_DOWN_L:
		m_tInfo.fCX = 188.f;
		m_tInfo.fCY = 146.f;
		break;
	case DIR_LEFT:
		m_tInfo.fCX = 221.f;
		m_tInfo.fCY = 145.f;
		break;
	case DIR_UP_L:
		m_tInfo.fCX = 155.f;
		m_tInfo.fCY = 148.f;
		break;
	case DIR_UP:
		m_tInfo.fCX = 103.f;
		m_tInfo.fCY = 152.f;
		break;
	case DIR_UP_R:
		m_tInfo.fCX = 162.f;
		m_tInfo.fCY = 142.f;
		break;
	case DIR_RIGHT:
		m_tInfo.fCX = 203.f;
		m_tInfo.fCY = 133.f;
		break;
	case DIR_DOWN_R:
		m_tInfo.fCX = 169.f;
		m_tInfo.fCY = 144.f;
		break;
	}

	INFO*		pPlayerInfo = CObjMgr::GetInstance()->GetInfo(L"Player");

	float		fWidth, fHeight, fDistance;

	fWidth = pPlayerInfo->fX - m_tInfo.fX;
	fHeight = pPlayerInfo->fY - m_tInfo.fY;
	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fCos = fWidth / fDistance;

	m_tInfo.fAngle = acosf(fCos);

	if(m_tInfo.fY < pPlayerInfo->fY)
		m_tInfo.fAngle = 2.f * 3.14f - m_tInfo.fAngle;
}

void CInferno::Progress(void)
{
	float fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX - m_tInfo.fX;								
	float fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY- m_tInfo.fY;

	float fDist = sqrt((fX * fX) + (fY * fY));							

	if(fDist < 50)
	{
		CObjMgr::GetInstance()->GetInfo(L"Player")->iHp -= 0.5;
		
	}

	if(m_dwCool + 1000 < GetTickCount())
	{
		m_dwCool = GetTickCount();
		m_tInfo.bAlive = false;
	}
	m_tInfo.fX += m_tInfo.fSpeed * cosf(m_tInfo.fAngle);
	m_tInfo.fY -= m_tInfo.fSpeed * sinf(m_tInfo.fAngle);


	FrameMove(15);
}

void CInferno::Render(void)
{
	switch(m_eType)
	{
	case DIR_DOWN:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Skill1_D"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_DOWN_L:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Skill1_D_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_LEFT:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Skill1_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP_L:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Skill1_U_L"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Skill1_U"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_UP_R:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Skill1_U_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_RIGHT:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Skill1_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	case DIR_DOWN_R:
		TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
			, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY)
			, *CImgMgr::GetInstance()->GetTexture(L"Boss_Skill1_D_R"), int(m_iFrameX  * m_tInfo.fCX)
			, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
		break;
	}
}

void CInferno::Release(void)
{
}