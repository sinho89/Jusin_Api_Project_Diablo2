#include "StdAfx.h"
#include "AstarMgr.h"
#include "TileMgr.h"

INIT_SINGLETON(CAstarMgr);

CAstarMgr::CAstarMgr(void)
{
}

CAstarMgr::~CAstarMgr(void)
{
	Release();
}

void CAstarMgr::StartAStar(int _iStartIndex, int _iGoalIndex)
{
	m_iStartIndex = 0;
	m_iGoalIndex = 0;
	m_iIndex = 0;

	m_pTileMap = NULL;

	if(_iStartIndex == _iGoalIndex)
		return;

	m_pTileMap = 	&(CTileMgr::GetInstance()->GetTileVector());	

	Release();

	vector<TILE*>::iterator iter = m_pTileMap->begin();
	iter += _iGoalIndex;

	if((*iter)->bOption == true)					
		return;											

	m_iStartIndex = _iStartIndex;
	m_iGoalIndex = _iGoalIndex;
	m_iIndex = m_iStartIndex;							

	PathFinding();										
}

void CAstarMgr::PathFinding(void)
{
	NODE* pParent = new NODE;			
	pParent->iIndex = m_iIndex;			
	pParent->fCost = 0;
	pParent->gCost = 0;
	pParent->hCost = 0;
	pParent->pParent = NULL;

	m_CloseList.push_back(pParent);		

	vector<TILE*>::iterator iter;

	int iCnt = 0;

	while(true)
	{
		bool bIsUP		= false;
		bool bIsDOWN	= false;
		bool bIsLEFT	= false;
		bool bIsRIGHT	= false;

		//UP
		iter = m_pTileMap->begin();
		m_iIndex = pParent->iIndex - iTILECNTX;

		if(m_iIndex >= 0 && m_iIndex < (iTILECNTX * iTILECNTY)) 
		{
			iter += m_iIndex;								
			if(((*iter)->bOption == false)					
				&& CheckList(m_iIndex))								
			{
				AddNode(pParent, CT_LINE);				
				bIsUP = true;
			}
		}

		//DOWN
		iter = m_pTileMap->begin();
		m_iIndex = pParent->iIndex + iTILECNTX;

		if(m_iIndex >= 0 && m_iIndex < (iTILECNTX * iTILECNTY))
		{
			iter += m_iIndex;									
			if(((*iter)->bOption == false)					
				&& CheckList(m_iIndex))								
			{
				AddNode(pParent, CT_LINE);				
				bIsDOWN = true;
			}
		}

		//LEFT
		iter = m_pTileMap->begin();
		m_iIndex = pParent->iIndex - 1;

		if(m_iIndex >= 0 && m_iIndex < (iTILECNTX * iTILECNTY))
		{
			iter += m_iIndex;										
			if(((*iter)->bOption == false)						
				&& (pParent->iIndex / iTILECNTX == m_iIndex / iTILECNTX)								
				&& CheckList(m_iIndex))								
			{
				AddNode(pParent, CT_LINE);				
				bIsLEFT = true;
			}
		}

		//RIGHT
		iter = m_pTileMap->begin();
		m_iIndex = pParent->iIndex + 1;

		if(m_iIndex >= 0 && m_iIndex < (iTILECNTX * iTILECNTY))
		{
			iter += m_iIndex;										
			if(((*iter)->bOption == false
				&& (pParent->iIndex / iTILECNTX == m_iIndex / iTILECNTX))						
				&& CheckList(m_iIndex))								
			{
				AddNode(pParent, CT_LINE);					
				bIsRIGHT = true;
			}
		}

		if(bIsUP)
		{
			if(bIsLEFT)
			{
				//UP-LEFT
				iter = m_pTileMap->begin();
				m_iIndex = pParent->iIndex - iTILECNTX - 1;

				if(m_iIndex >= 0 && m_iIndex < (iTILECNTX * iTILECNTY))
				{
					iter += m_iIndex;									
					if(((*iter)->bOption == false)					
						&& CheckList(m_iIndex))								
					{
						AddNode(pParent, CT_DIAGONAL);				
					}
				}
			}

			if(bIsRIGHT)
			{

				//UP-RIGHT
				iter = m_pTileMap->begin();
				m_iIndex = pParent->iIndex - iTILECNTX + 1;

				if(m_iIndex >= 0 && m_iIndex < (iTILECNTX * iTILECNTY))
				{
					iter += m_iIndex;									
					if(((*iter)->bOption == false)					
						&& CheckList(m_iIndex))								
					{
						AddNode(pParent, CT_DIAGONAL);				
					}
				}
			}
		}


		if(bIsDOWN)
		{
			if(bIsLEFT)
			{
				//DOWN-LEFT
				iter = m_pTileMap->begin();
				m_iIndex = pParent->iIndex + iTILECNTX - 1;

				if(m_iIndex >= 0 && m_iIndex < (iTILECNTX * iTILECNTY))
				{
					iter += m_iIndex;								
					if(((*iter)->bOption == false)				
						&& CheckList(m_iIndex))								
					{
						AddNode(pParent, CT_DIAGONAL);				
					}
				}
			}

			if(bIsRIGHT)
			{

				//DOWN-RIGHT
				iter = m_pTileMap->begin();
				m_iIndex = pParent->iIndex + iTILECNTX + 1;

				if(m_iIndex >= 0 && m_iIndex < (iTILECNTX * iTILECNTY))
				{
					iter += m_iIndex;							
					if(((*iter)->bOption == false)					
						&& CheckList(m_iIndex))								
					{
						AddNode(pParent, CT_DIAGONAL);			
					}
				}
			}
		}

		++iCnt;


		if(m_OpenList.empty() || iCnt > 30)
		{
			break;
		}

		m_OpenList.sort(Compare);
		list<NODE*>::iterator open_iter = m_OpenList.begin();
		m_CloseList.push_back((*open_iter));
		pParent = (*open_iter);
		open_iter = m_OpenList.erase(open_iter);

		if(pParent->iIndex == m_iGoalIndex)
		{
			while(true)
			{
				m_BestList.push_back(pParent->iIndex);
				pParent = pParent->pParent;

				if(pParent->iIndex == m_iStartIndex)
					break;
			}

			m_BestList.reverse();
			break;
		}
	}
}

void CAstarMgr::AddNode(NODE* _pParent, int _iType)
{
	float fGCost = 0;

	switch(_iType)
	{
	case CT_LINE:									
		fGCost = float(_pParent->gCost + 1);					
		break;

	case CT_DIAGONAL:								
		fGCost = float(_pParent->gCost + 1.41414f);				
		break;
	}

	list<NODE*>::iterator iter = m_OpenList.begin();
	list<NODE*>::iterator iter_end = m_OpenList.end();

	for(iter; iter != iter_end; iter++)
	{
		if((*iter)->iIndex == m_iIndex)						
		{
			if((*iter)->gCost < fGCost)
			{
				return;									
			}
			else
			{
				(*iter)->gCost = fGCost;					
				(*iter)->fCost = (*iter)->gCost + (*iter)->hCost;
				(*iter)->pParent = _pParent;			
				return;
			}
		}
	}

	NODE* pNode = new NODE;									
	pNode->pParent = _pParent;
	pNode->gCost = fGCost;
	pNode->hCost = ManhattanDistance(m_iIndex);
	pNode->fCost = pNode->gCost + pNode->hCost;
	pNode->iIndex = m_iIndex;

	m_OpenList.push_back(pNode);
}

void CAstarMgr::Release(void)
{
	list<NODE*>::iterator open_iter = m_OpenList.begin();
	list<NODE*>::iterator open_iter_end = m_OpenList.end();

	for(open_iter; open_iter != open_iter_end; open_iter++)
	{
		safe_delete((*open_iter));
	}

	m_OpenList.clear();

	list<NODE*>::iterator close_iter = m_CloseList.begin();
	list<NODE*>::iterator close_iter_end = m_CloseList.end();

	for(close_iter; close_iter != close_iter_end; close_iter++)
	{
		safe_delete((*close_iter));
	}

	m_CloseList.clear();

	m_BestList.clear();
}

bool CAstarMgr::CheckList(int _iIndex)
{
	list<NODE*>::iterator iter = m_CloseList.begin();
	list<NODE*>::iterator iter_end = m_CloseList.end();

	for(iter; iter != iter_end; iter++)
	{
		if((*iter)->iIndex == _iIndex)
			return false;
	}

	return true;
}

float CAstarMgr::ManhattanDistance(int _iIndex)
{
	int iX = 0;
	int iY = 0;
	int iGoalX = 0;
	int iGoalY = 0;

	vector<TILE*>::iterator iter = m_pTileMap->begin();

	iter += _iIndex;

	iX = (int)((*iter)->fX / iTILESIZE);
	iY = (int)((*iter)->fY / iTILESIZE);

	iter = m_pTileMap->begin();
	iter += m_iGoalIndex;

	iGoalX = (int)((*iter)->fX / iTILESIZE);
	iGoalY = (int)((*iter)->fY / iTILESIZE);

	return float(abs(iGoalX - iX) + abs(iGoalY - iY));
}
