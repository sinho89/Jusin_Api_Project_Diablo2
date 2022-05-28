#pragma once
#include "scene.h"

class CStage :
	public CScene
{
private:
	bool m_bTileSet;
	bool m_bPass;
	bool m_bMon;
public:
	static bool m_bBoss;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CStage(void);
	virtual ~CStage(void);
};
