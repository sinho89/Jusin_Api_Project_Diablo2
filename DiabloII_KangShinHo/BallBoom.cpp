#include "StdAfx.h"
#include "BallBoom.h"
#include "RoundFire.h"

CBallBoom::CBallBoom(void)
{
}
CBallBoom::CBallBoom( float _fX, float _fY, eDIRTECTION_TYPE _eType)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eType = _eType;
}
CBallBoom::~CBallBoom(void)
{
}

void CBallBoom::Initialize( void )
{

	CSoundMgr::GetInstance()->SkillSound3(L"explode1.wav");
	m_tInfo.fCX = 235.f;
	m_tInfo.fCY = 202.f;

	m_tInfo.bAlive = true;

	m_iFrameX = 0;
	m_iFrameY = 0;

}

void CBallBoom::Progress( void )
{
	FrameMove(13);
	if(m_iFrameX == 12)
	{
		/*switch(m_eType)
		{
		case DIR_DOWN:
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX - iTILESIZE,m_tInfo.fY));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX + iTILESIZE,m_tInfo.fY));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY - iTILESIZE));
			CObjMgr::GetInstance()->AddObject(L"Fire",SORTID_UNITANDOBJ, CFactory<CRoundFire>::CreateObject(m_tInfo.fX,m_tInfo.fY + iTILESIZE));
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
		m_tInfo.bAlive = false;
	}
}

void CBallBoom::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), int(m_tInfo.fX - m_tInfo.fCX / 2.f) + CObj::m_ptScroll.x
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f) + CObj::m_ptScroll.y
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"Ball_Boom"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

}

void CBallBoom::Release( void )
{

}
