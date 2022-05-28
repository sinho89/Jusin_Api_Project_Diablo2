#pragma once
#include "obj.h"
#include "ObjMgr.h"

class CItem :
	public CObj
{
protected:
	POINT	ptSave;
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
public:
	CItem(void);
	virtual ~CItem(void);
};
