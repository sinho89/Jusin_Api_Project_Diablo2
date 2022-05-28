#pragma once

#include "Defines.h"
class CObj;

template <typename T>
class CFactory abstract
{
public:
	static CObj* CreateObject()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(float _fX, float _fY) 
	{
		CObj* pObj = new T(_fX, _fY);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(float _fX, float _fY, ePORTAL_TYPE _eType)
	{
		CObj* pObj = new T(_fX, _fY, _eType);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(float _fX, float _fY, eDIRTECTION_TYPE _eType) 
	{
		CObj* pObj = new T(_fX, _fY, _eType);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(float _fX, float _fY, bool _bStart) 
	{
		CObj* pObj = new T(_fX, _fY, _bStart);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(float _fX, float _fY, float _fAngle) 
	{
		CObj* pObj = new T(_fX, _fY, _fAngle);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(INFO _pInfo) 
	{
		CObj* pObj = new T(_pInfo);
		pObj->Initialize();
		return pObj;
	}
public:
	CFactory(void);
	~CFactory(void);
};
