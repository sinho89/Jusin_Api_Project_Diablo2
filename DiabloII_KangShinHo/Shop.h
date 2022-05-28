#pragma once
#include "ui.h"

class CItem;
class CShop :
	public CUi
{
private:
	list<CItem*>		m_ShopList;
public:
	list<CItem*>* GetShop()
	{
		return &m_ShopList;
	}

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CShop(void);
	virtual ~CShop(void);
};
