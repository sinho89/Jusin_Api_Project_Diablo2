#pragma once

#include "Defines.h"

class CItem;
class CObj;
class CObjMgr
{
CREATE_SINGLETON(CObjMgr);

private:
	map<const TCHAR*, list<CObj*>>		m_ObjMap[SORTID_END];
	multimap<float, CObj*>				m_mapSort_UnitObj;
	multimap<float, CObj*>				m_mapSort_ShopInven;

	TCHAR		m_szString[128];
public:
	void SetImgKey(const TCHAR* pObjKey, TCHAR* pImgKey, int iCnt = 0);
	list<CObj*>*	GetObjList(const TCHAR* pObjKey);
	list<CItem*>*	GetInvenList(const TCHAR* pKey, int iCnt = 0);
	list<CItem*>*	GetPotionList(const TCHAR* pKey, int iCnt = 0);
	list<CItem*>*	GetEquiList(const TCHAR* pKey, int iCnt = 0);
	list<CItem*>*	GetCubeList(const TCHAR* pKey, int iCnt = 0);
	void AddObject(const TCHAR* pObjKey, SORTID ID, CObj* pObject);
	INFO* GetInfo(const TCHAR* pKey, int iCnt = 0);
	RENDER* GetRender(const TCHAR* pKey, int iCnt = 0);
	eSKILL_TYPE* GetSkill(const TCHAR* pKey, int iCnt = 0);
	eSKILL_TYPE* GetSaveSkill(const TCHAR* pKey, int iCnt = 0);
	void EraseObject();
	void Progress();
	void Render();
	void Release();


private:
	CObjMgr(void);
public:
	~CObjMgr(void);
};
