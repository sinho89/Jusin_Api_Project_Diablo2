#pragma once
#include "Ui.h"

class CItem;
class CMouseRnd :
	public CUi
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMouseRnd(void);
	virtual ~CMouseRnd(void);
};
