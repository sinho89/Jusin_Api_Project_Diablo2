#include "StdAfx.h"
#include "TransForm.h"
#include "ObjMgr.h"
#include "ImgMgr.h"

CTransForm::CTransForm(void)
{
}

CTransForm::~CTransForm(void)
{
}

void CTransForm::Initialize(void)
{
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX;
	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY;

	m_tInfo.fCX = 161.f;
	m_tInfo.fCY = 217.f;

	m_iFrameX = 3;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;
}

void CTransForm::Progress(void)
{
	m_tInfo.fX = CObjMgr::GetInstance()->GetInfo(L"Player")->fX;
	m_tInfo.fY = CObjMgr::GetInstance()->GetInfo(L"Player")->fY;

	FrameMove(13);
	if(m_iFrameX == 12)
		m_tInfo.bAlive = false;

}

void CTransForm::Render(void)
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"TransEff"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

}

void CTransForm::Release(void)
{

}
