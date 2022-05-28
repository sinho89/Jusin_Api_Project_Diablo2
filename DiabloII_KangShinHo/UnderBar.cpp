#include "StdAfx.h"
#include "UnderBar.h"
#include "TileMgr.h"
#include "CollMgr.h"
#include "Item.h"

CUnderBar::CUnderBar(void)
{
}

CUnderBar::~CUnderBar(void)
{
	Release();
}
void CUnderBar::Initialize( void )
{
	m_tInfo.fX = iWINCX / 2.f;
	m_tInfo.fY = iWINCY - (103 / 2.f); 
	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 103.f;

	m_tInfo.iSortNum = 5;
	m_iFrameX = 0;
	m_iFrameY = 0;

	m_tInfo.bAlive = true;

	CTileMgr::GetInstance()->SetPotionTile();
}

void CUnderBar::Progress( void )
{
	CCollMgr::GetInstance()->PotionItemColl(&m_PotionList);

	list<CItem*>::iterator iter = m_PotionList.begin();
	list<CItem*>::iterator iter_end = m_PotionList.end();

	for(iter; iter != iter_end;)
	{
		if((*iter)->GetInfo().bAlive == false)
		{
			safe_delete((*iter));
			iter = m_PotionList.erase(iter);
		}
		else
		{
			(*iter)->Progress();
			++iter;
		}
	}
}

void CUnderBar::Render( void )
{
	TransparentBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		, int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		, int(m_tInfo.fCX)
		, int(m_tInfo.fCY)
		, *CImgMgr::GetInstance()->GetTexture(L"UnderBar"), int(m_iFrameX  * m_tInfo.fCX)
		, int(m_iFrameY  * m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 255, 255));

	list<CItem*>::iterator iter = m_PotionList.begin();
	list<CItem*>::iterator iter_end = m_PotionList.end();

	for(iter; iter != iter_end; ++iter)
		(*iter)->Render();
}

void CUnderBar::Release( void )
{
	CTileMgr::GetInstance()->DeletePotionTile();

	list<CItem*>::iterator iter = m_PotionList.begin();
	list<CItem*>::iterator iter_end = m_PotionList.end();

	for(iter; iter != iter_end; ++iter)
		safe_delete(*iter);

	m_PotionList.clear();

}