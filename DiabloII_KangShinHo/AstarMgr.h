#pragma once

#include "Defines.h"

class CAstarMgr
{
CREATE_SINGLETON(CAstarMgr);

private:
	list<NODE*> m_OpenList;
	list<NODE*> m_CloseList;
	list<int> m_BestList;

	vector<TILE*>* m_pTileMap;								

	int m_iStartIndex;
	int m_iGoalIndex;
	int m_iIndex;


public:
	void StartAStar(int _iStartIndex, int _iGoalIndex);		
	void PathFinding(void);									
	void AddNode(NODE* _pParent, int _iType);
	void Release(void);
	bool CheckList(int _iIndex);
	float ManhattanDistance(int _iIndex);


	
public:
	list<int>* GetBestList(void)
	{
		return &m_BestList;
	}
	static bool Compare(NODE* pDestNode,NODE* pSourNode)
	{
		return pDestNode->fCost < pSourNode->fCost;
	}

private:
	CAstarMgr(void);
public:
	~CAstarMgr(void);
};
