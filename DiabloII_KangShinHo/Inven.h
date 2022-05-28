#pragma once
#include "ui.h"

class CItem;
class CInven :
	public CUi
{
private:
	list<CItem*>		m_InvenList;
	list<CItem*>		m_EquiList;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	list<CItem*>* GetInven()
	{
		return &m_InvenList;
	}
	list<CItem*>* GetEqui()
	{
		return &m_EquiList;
	}

public:
	CInven(void);
	virtual ~CInven(void);
};
