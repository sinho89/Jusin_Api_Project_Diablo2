#include "StdAfx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "Unit.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Inven.h"
#include "Cube.h"

INIT_SINGLETON(CObjMgr);

CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

void CObjMgr::SetImgKey(const TCHAR* pObjKey, TCHAR* pImgKey, int iCnt)			   
{
	for (int i = 0; i < SORTID_END; ++i)
	{
		map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].find(pObjKey);

		if(iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	iter1 = iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++iter1;
		}

		(*iter1)->SetImgKey(pImgKey);
	}		
}

list<CObj*>*	CObjMgr::GetObjList(const TCHAR* pObjKey)
{
	map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[SORTID_UNITANDOBJ].find(pObjKey);

	return &(iter->second);
}

list<CItem*>*	CObjMgr::GetInvenList(const TCHAR* pKey, int iCnt)
{
	
	map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[SORTID_INVENANDSHOP].find(pKey);

	list<CObj*>::iterator	iter1 = iter->second.begin();

	for (int i = 0; i < iCnt; ++i)
	{
		++iter1;
	}

	return ((CInven*)((CUi*)(*iter1)))->GetInven();
}

list<CItem*>*	CObjMgr::GetPotionList(const TCHAR* pKey, int iCnt)
{

	map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[SORTID_UI].find(pKey);

	list<CObj*>::iterator	iter1 = iter->second.begin();

	for (int i = 0; i < iCnt; ++i)
	{
		++iter1;
	}

	return ((CInven*)((CUi*)(*iter1)))->GetInven();
}

INFO* CObjMgr::GetInfo(const TCHAR* pKey, int iCnt)
{
	for (int i = 0; i < SORTID_END; ++i)
	{
		map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].find(pKey);

		if(iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	iter1 = iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++iter1;
		}

		return &((*iter1)->GetInfo());
	}

	return NULL;
}

eSKILL_TYPE* CObjMgr::GetSkill(const TCHAR* pKey, int iCnt)
{
	for (int i = 0; i < SORTID_END; ++i)
	{
		map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].find(pKey);

		if(iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	iter1 = iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++iter1;
		}

		return &((*iter1)->GetSkill());
	}

	return NULL;
}
eSKILL_TYPE* CObjMgr::GetSaveSkill(const TCHAR* pKey, int iCnt)
{
	for (int i = 0; i < SORTID_END; ++i)
	{
		map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].find(pKey);

		if(iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	iter1 = iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++iter1;
		}

		return (*iter1)->GetSaveSkill();
	}

	return NULL;
}

RENDER* CObjMgr::GetRender(const TCHAR* pKey, int iCnt)
{
	for (int i = 0; i < SORTID_END; ++i)
	{
		map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].find(pKey);

		if(iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	iter1 = iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++iter1;
		}

		return &((*iter1)->GetRender());
	}

	return NULL;

}

void CObjMgr::AddObject(const TCHAR* pObjKey, SORTID ID, CObj* pObject)
{
	map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[ID].find(pObjKey);

	if(iter == m_ObjMap[ID].end())
	{
		list<CObj*>		ObjList;
		ObjList.push_back(pObject);
		m_ObjMap[ID].insert(make_pair(pObjKey, ObjList));
	}

	else
	{
		iter->second.push_back(pObject);
	}

}

void CObjMgr::EraseObject(void)
{
	for (int i = 0; i < SORTID_END; ++i)
	{
		for (map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].begin();
			iter != m_ObjMap[i].end();)
		{
			for (list<CObj*>::iterator	iter1 = iter->second.begin();
				iter1 != iter->second.end();)
			{
				if((*iter1)->GetInfo().bAlive == false)
				{
					delete (*iter1);
					(*iter1) = NULL;
					iter1 = iter->second.erase(iter1);				
				}
				else
					++iter1;
			}

			if(iter->second.empty())
				iter = m_ObjMap[i].erase(iter);
			else
				++iter;
		}
	}

}


void CObjMgr::Progress(void)
{
	EraseObject();

	for (int i = 0; i < SORTID_END; ++i)
	{
		for (map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].begin();
			iter != m_ObjMap[i].end(); ++iter)
		{
			for (list<CObj*>::iterator	iter1 = iter->second.begin();
				iter1 != iter->second.end(); ++iter1)
			{
				if(i == SORTID_UNITANDOBJ)
					m_mapSort_UnitObj.insert(make_pair((*iter1)->GetInfo().fY, *iter1));

				else if(i == SORTID_INVENANDSHOP)
					m_mapSort_ShopInven.insert(make_pair(float((*iter1)->GetInfo().iSortNum), *iter1));

				(*iter1)->Progress();
			}	
		}	
	}

}

void CObjMgr::Render(void)
{
	for (int i = 0; i < SORTID_END; ++i)
	{
		if(i == SORTID_UNITANDOBJ)
		{
			for (multimap<float, CObj*>::iterator	iter = m_mapSort_UnitObj.begin();
				iter != m_mapSort_UnitObj.end(); ++iter)
			{
				iter->second->Render();
			}
			m_mapSort_UnitObj.clear();
		}
		else if(i == SORTID_INVENANDSHOP)
		{
			for (multimap<float, CObj*>::iterator	iter = m_mapSort_ShopInven.begin();
				iter != m_mapSort_ShopInven.end(); ++iter)
			{
				iter->second->Render();
			}
			m_mapSort_ShopInven.clear();
		}
		else
		{
			for (map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].begin();
				iter != m_ObjMap[i].end(); ++iter)
			{
				for (list<CObj*>::iterator	iter1 = iter->second.begin();
					iter1 != iter->second.end(); ++iter1)
				{
					(*iter1)->Render();
				}	
			}	

		}

	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < SORTID_END; ++i)
	{
		for (map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].begin();
			iter != m_ObjMap[i].end(); ++iter)
		{
			for (list<CObj*>::iterator	iter1 = iter->second.begin();
				iter1 != iter->second.end(); ++iter1)
			{
				delete (*iter1);
				(*iter1) = NULL;
			}	
			iter->second.clear();
		}	
		m_ObjMap[i].clear();
	}
}

list<CItem*>* CObjMgr::GetEquiList( const TCHAR* pKey, int iCnt /*= 0*/ )
{
	map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[SORTID_INVENANDSHOP].find(pKey);

	list<CObj*>::iterator	iter1 = iter->second.begin();

	for (int i = 0; i < iCnt; ++i)
	{
		++iter1;
	}

	return ((CInven*)((CUi*)(*iter1)))->GetEqui();

}

list<CItem*>* CObjMgr::GetCubeList( const TCHAR* pKey, int iCnt /*= 0*/ )
{
	map<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[SORTID_INVENANDSHOP].find(pKey);

	list<CObj*>::iterator	iter1 = iter->second.begin();

	for (int i = 0; i < iCnt; ++i)
	{
		++iter1;
	}

	return ((CCube*)((CUi*)(*iter1)))->GetCube();

}

