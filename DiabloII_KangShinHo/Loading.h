#pragma once
#include "obj.h"

class CLoading :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CLoading(void);
	virtual ~CLoading(void);
};
