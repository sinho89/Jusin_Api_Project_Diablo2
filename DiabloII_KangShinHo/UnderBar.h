#pragma once
#include "ui.h"

class CItem;
class CUnderBar :
	public CUi
{
private:
	list<CItem*>		m_PotionList;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	list<CItem*>* GetInven()
	{
		return &m_PotionList;
	}
public:
	CUnderBar(void);
	virtual ~CUnderBar(void);
};
