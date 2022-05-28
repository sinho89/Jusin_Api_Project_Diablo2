#ifndef _STRUCT_H
#define	_STRUCT_H
#include "Enum.h"

typedef struct tagInfo
{
	float fX,fY;
	float fCX,fCY;

	float	fSpeed, fAngle;
	int		iLevel, iExp, iMaxExp;
	int		iHp, iMaxHp, iAtt, iDef;
	int		iMp, iMaxMp;
	int		iStamina, iMaxStamina;
	int		iStr, iDex, iWis, iCon;
	int		iStatePoint;
	int		iMoney;
	int		iSortNum;
	int		iKillCnt;

	bool bAlive;
	bool bClick;
	bool m_bTile;
	bool m_bStay;
	bool m_bBoss;
	bool m_bAtt;
	bool m_bHit;
	bool m_bGetHit;
	bool m_bCast1;
	bool m_bCast2;
	
	eUI_TYPE m_UIType;
	eITEM_TYPE eType;
	eITEM_SIZE_TYPE cType;

	tagInfo()
		:fX(0)
		,fY(0)
		,fCX(0)
		,fCY(0)
		,fSpeed(0)
		,fAngle(0)
		,m_bTile(0)
		,m_UIType(UT_END)
	{}

}INFO;

typedef struct RenderInfo
{
	bool m_bInvenRender;
	bool m_bShopRender;
	bool m_bSkillRender;
	bool m_bQuestRender;
	bool m_bItemRender;
	bool m_bStatRender;
	bool m_bCubeRender;

}RENDER;

typedef struct ItemTileInfo
{
	float fX, fY;
	float fCX, fCY;

	eITEM_TYPE eType;
	eITEM_SIZE_TYPE cType;

	bool	m_bCheck;

	ItemTileInfo(float _fX, float _fY, float _fCX, float _fCY,
				eITEM_TYPE _eType, eITEM_SIZE_TYPE _cType, bool _bCheck)
		:fX(_fX)
		,fY(_fY)
		,fCX(_fCY)
		,fCY(_fCY)
		,eType(_eType)
		,cType(_cType)
		,m_bCheck(_bCheck)
	{}
}ITEM_TILE;

typedef struct TileInfo
{
	float fX, fY;
	float fCX, fCY;

	bool	bOption;
	int		iDrawID;
	int		iTileFrameX;
	eTILE_TYPE	eType;

	TileInfo()
		:fX(0)
		,fY(0)
		,bOption(false)
		,iDrawID(0)
	{}
	TileInfo(float _fX, float _fY, float _fCX, float _fCY, 
		bool _bOption, int _iDrawID, eTILE_TYPE _eType, int _iTileFrameX)
		:fX(_fX)
		,fY(_fY)
		,fCX(_fCX)
		,fCY(_fCY)
		,bOption(_bOption)
		,iDrawID(_iDrawID)
		,eType(_eType)
		,iTileFrameX(_iTileFrameX)
	{}

}TILE;

typedef struct NodeInfo
{
	NodeInfo* pParent;
	int iIndex;
	float gCost;
	float hCost;
	float fCost;

	NodeInfo(void)
		:pParent(NULL)
		,iIndex(0)
		,fCost(0)
		,hCost(0)
		,gCost(0)
	{}

	NodeInfo(NodeInfo* _pNode, int _iIndex, float _fCost, float _hCost, float _gCost)
		:pParent(_pNode)
		,iIndex(_iIndex)
		,fCost(_fCost)
		,hCost(_hCost)
		,gCost(_gCost)
	{}

}NODE;

#endif