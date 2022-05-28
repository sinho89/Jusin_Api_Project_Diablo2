#include "StdAfx.h"
#include "TorEff.h"
#include "Mouse.h"
#include "TileMgr.h"


TorEff::TorEff(void)
{
}

TorEff::TorEff( float _fX, float _fY, eDIRTECTION_TYPE _eType )
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;
}

TorEff::~TorEff(void)
{
}

void TorEff::Initialize( void )
{
	m_tInfo.fCX = 112.f;
	m_tInfo.fCY = 130.f;

	m_tInfo.fAngle = 0;
	m_tInfo.fSpeed = 2.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;

	POINT ptMouse = CMouse::GetMousePos();

	float		fWidth, fHeight, fDistance;

	fWidth = (ptMouse.x - CObj::m_ptScroll.x) - m_tInfo.fX;
	fHeight = (ptMouse.y - CObj::m_ptScroll.y) - m_tInfo.fY;
	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fCos = fWidth / fDistance;

	m_tInfo.fAngle = acosf(fCos);

	if(m_tInfo.fY < (ptMouse.y - CObj::m_ptScroll.y))
		m_tInfo.fAngle = 2.f * 3.14f - m_tInfo.fAngle;
}

void TorEff::Progress( void )
{
	int		iIndex = int(m_tInfo.fY) / iTILESIZE * iTILECNTX + int(m_tInfo.fX) / iTILESIZE;

	m_tInfo.fX += m_tInfo.fSpeed * cosf(m_tInfo.fAngle);
	m_tInfo.fY -= m_tInfo.fSpeed * sinf(m_tInfo.fAngle);

	/*switch(m_eType)
	{
	case DIR_DOWN:
		break;
	case DIR_DOWN_L:
		break;
	case DIR_DOWN_R:
		break;
	case DIR_LEFT:
		break;
	case DIR_RIGHT:
		break;
	case DIR_UP:
		break;
	case DIR_UP_L:
		break;
	case DIR_UP_R:
		break;
	}*/
	FrameMove(41);

	if(CScene::m_bBattle == true)
	{

		if(m_iFrameX == 39)
		{
			m_tInfo.bAlive = false;
		}
		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();


		for(iter; iter != iter_end; ++iter)
		{
			float fX = (*iter)->GetInfo().fX - m_tInfo.fX;								
			float fY = (*iter)->GetInfo().fY - m_tInfo.fY;

			float fDist = sqrt((fX * fX) + (fY * fY));							

			if(fDist < 50)
			{
				(*iter)->GetInfo().m_bHit = true;
				(*iter)->GetInfo().iHp -= 0.025;
			}

		}
		if(CStage::m_bBoss == true)
		{
			list<CObj*>::iterator Boss_iter = CObjMgr::GetInstance()->GetObjList(L"Boss")->begin();

			float fX = (*Boss_iter)->GetInfo().fX - m_tInfo.fX;								
			float fY = (*Boss_iter)->GetInfo().fY - m_tInfo.fY;

			float fDist = sqrt((fX * fX) + (fY * fY));							

			if(fDist < 50)
			{
				(*Boss_iter)->GetInfo().m_bHit = true;
				(*Boss_iter)->GetInfo().iHp -= 0.025;
				m_tInfo.bAlive = false;
			}
		}

	}
}

void TorEff::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Tornado"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));
}

void TorEff::Release( void )
{

}
