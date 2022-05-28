#include "StdAfx.h"
#include "Stage.h"
#include "StageBack.h"
#include "Player.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "Npc.h"
#include "Inven.h"
#include "Shop.h"
#include "UnderBar.h"
#include "HpBall.h"
#include "MpBall.h"
#include "State.h"
#include "Cube.h"
#include "AlphaTile.h"
#include "Obj.h"
#include "Monster.h"
#include "SkillIcon.h"
#include "Boss.h"
#include "Stamina.h"

bool CStage::m_bBoss = false;

CStage::CStage(void)
:m_bPass(false)

{
}

CStage::~CStage(void)
{
	Release();
}

void CStage::Initialize( void )
{
	CScene::m_bHome = true;
	CScene::m_bBattle = false;

	CImgMgr::GetInstance()->AddTexture(L"../Resource/BackBuffer.bmp", L"BackBuffer", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/StageBack1.bmp", L"StageBack", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/BattleBack.bmp", L"BattleBack", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Loading.bmp", L"Loading", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Player.bmp", L"Player", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Player_W.bmp", L"Player_W", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Player_R.bmp", L"Player_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Edit/Tile.bmp", L"Tile", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Edit/Alpha.bmp", L"Alpha", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Store.bmp", L"Store", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/UnderBar.bmp", L"UnderBar", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/HpBall.bmp", L"HpBall", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/MpBall.bmp", L"MpBall", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Stat.bmp", L"Stat", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Inven.bmp", L"Inven", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Potion.bmp", L"Potion", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Scroll.bmp", L"Scroll", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Armor.bmp", L"Armor", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Weapon.bmp", L"Weapon", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/NPC.bmp", L"NPC", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/Cube.bmp", L"Cube", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/CowPortal1.bmp", L"CowPortal", m_hdc);
	CImgMgr::GetInstance()->AddTexture(L"../Resource/CowPortalDoor1.bmp", L"CowPortalDoor", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Cow_Att.bmp"), L"Cow_Att", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Cow.bmp"), L"Cow", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Cow_Move.bmp"), L"Cow_Move", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Cow_Dead.bmp"), L"Cow_Dead", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Cow_Dead2.bmp"), L"Cow_Dead2", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Cow_GetHit.bmp"), L"Cow_GetHit", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/SkillIcon.bmp"), L"SkillIcon", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Skill_Bear.bmp"), L"Skill_Bear", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Player_Bear.bmp"), L"Player_Bear", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_D.bmp"), L"Bear_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_D_L.bmp"), L"Bear_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_D_R.bmp"), L"Bear_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_L.bmp"), L"Bear_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R.bmp"), L"Bear_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_U.bmp"), L"Bear_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_U_L.bmp"), L"Bear_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_U_R.bmp"), L"Bear_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_W_D.bmp"), L"Bear_W_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_W_D_L.bmp"), L"Bear_W_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_W_D_R.bmp"), L"Bear_W_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_W_L.bmp"), L"Bear_W_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_W_R.bmp"), L"Bear_W_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_W_U.bmp"), L"Bear_W_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_W_U_L.bmp"), L"Bear_W_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_W_U_R.bmp"), L"Bear_W_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R_D.bmp"), L"Bear_R_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R_D_L.bmp"), L"Bear_R_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R_D_R.bmp"), L"Bear_R_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R_L.bmp"), L"Bear_R_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R_R.bmp"), L"Bear_R_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R_U.bmp"), L"Bear_R_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R_U_L.bmp"), L"Bear_R_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_R_U_R.bmp"), L"Bear_R_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_Skill_D.bmp"), L"Bear_Skill_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_Skill_D_L.bmp"), L"Bear_Skill_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_Skill_D_R.bmp"), L"Bear_Skill_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_Skill_L.bmp"), L"Bear_Skill_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_Skill_R.bmp"), L"Bear_Skill_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_Skill_U.bmp"), L"Bear_Skill_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_Skill_U_L.bmp"), L"Bear_Skill_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Bear_Skill_U_R.bmp"), L"Bear_Skill_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/TransEff.bmp"), L"TransEff", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/AmaRock.bmp"), L"AmaRock", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/GroundFire.bmp"), L"GroundFire", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/AmaHit.bmp"), L"AmaHit", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_D.bmp"), L"Boss_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_D_L.bmp"), L"Boss_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_L.bmp"), L"Boss_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_U_L.bmp"), L"Boss_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_U.bmp"), L"Boss_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_U_R.bmp"), L"Boss_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R.bmp"), L"Boss_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_D_R.bmp"), L"Boss_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_W_D.bmp"), L"Boss_W_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_W_D_L.bmp"), L"Boss_W_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_W_L.bmp"), L"Boss_W_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_W_U_L.bmp"), L"Boss_W_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_W_U.bmp"), L"Boss_W_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_W_U_R.bmp"), L"Boss_W_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_W_R.bmp"), L"Boss_W_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_W_D_R.bmp"), L"Boss_W_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Skill1_D.bmp"), L"Boss_Skill1_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Skill1_D_L.bmp"), L"Boss_Skill1_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Skill1_L.bmp"), L"Boss_Skill1_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Skill1_U_L.bmp"), L"Boss_Skill1_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Skill1_U.bmp"), L"Boss_Skill1_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Skill1_U_R.bmp"), L"Boss_Skill1_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Skill1_R.bmp"), L"Boss_Skill1_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Skill1_D_R.bmp"), L"Boss_Skill1_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R_D.bmp"), L"Boss_R_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R_D_L.bmp"), L"Boss_R_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R_L.bmp"), L"Boss_R_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R_U_L.bmp"), L"Boss_R_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R_U.bmp"), L"Boss_R_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R_U_R.bmp"), L"Boss_R_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R_R.bmp"), L"Boss_R_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_R_D_R.bmp"), L"Boss_R_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Fire.bmp"), L"Fire", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Dead.bmp"), L"Boss_Dead", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/HurriCart.bmp"), L"HurriCart", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/HurriRock.bmp"), L"HurriRock", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Tornado.bmp"), L"Tornado", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Shock_D.bmp"), L"Shock_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Shock_D_L.bmp"), L"Shock_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Shock_D_R.bmp"), L"Shock_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Shock_L.bmp"), L"Shock_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Shock_R.bmp"), L"Shock_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Shock_U.bmp"), L"Shock_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Shock_U_L.bmp"), L"Shock_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Shock_U_R.bmp"), L"Shock_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Stamina.bmp"), L"Stamina", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/FireHit.bmp"), L"FireHit", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/AmaOverlay.bmp"), L"AmaOverlay", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/ColdOverlay.bmp"), L"ColdOverlay", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/AmaBoom.bmp"), L"AmaBoom", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Att_D.bmp"), L"Boss_Att_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Att_D_L.bmp"), L"Boss_Att_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Att_L.bmp"), L"Boss_Att_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Att_U_L.bmp"), L"Boss_Att_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Att_U.bmp"), L"Boss_Att_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Att_U_R.bmp"), L"Boss_Att_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Att_R.bmp"), L"Boss_Att_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Att_D_R.bmp"), L"Boss_Att_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Infe_D.bmp"), L"Boss_Infe_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Infe_D_L.bmp"), L"Boss_Infe_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Infe_L.bmp"), L"Boss_Infe_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Infe_U_L.bmp"), L"Boss_Infe_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Infe_U.bmp"), L"Boss_Infe_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Infe_U_R.bmp"), L"Boss_Infe_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Infe_R.bmp"), L"Boss_Infe_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Infe_D_R.bmp"), L"Boss_Infe_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Fire_D.bmp"), L"Boss_Fire_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Fire_D_L.bmp"), L"Boss_Fire_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Fire_L.bmp"), L"Boss_Fire_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Fire_U_L.bmp"), L"Boss_Fire_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Fire_U.bmp"), L"Boss_Fire_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Fire_U_R.bmp"), L"Boss_Fire_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Fire_R.bmp"), L"Boss_Fire_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Boss_Fire_D_R.bmp"), L"Boss_Fire_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Player_GetHit.bmp"), L"Player_GetHit", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Player_Att.bmp"), L"Player_Att", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Player_Cast.bmp"), L"Player_Cast", m_hdc);

	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_S_D.bmp"), L"Ball_S_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_S_D_L.bmp"), L"Ball_S_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_S_L.bmp"), L"Ball_S_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_S_U_L.bmp"), L"Ball_S_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_S_U.bmp"), L"Ball_S_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_S_U_R.bmp"), L"Ball_S_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_S_R.bmp"), L"Ball_S_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_S_D_R.bmp"), L"Ball_S_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_M_D.bmp"), L"Ball_M_D", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_M_D_L.bmp"), L"Ball_M_D_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_M_L.bmp"), L"Ball_M_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_M_U_L.bmp"), L"Ball_M_U_L", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_M_U.bmp"), L"Ball_M_U", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_M_U_R.bmp"), L"Ball_M_U_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_M_R.bmp"), L"Ball_M_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_M_D_R.bmp"), L"Ball_M_D_R", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Ball_Boom.bmp"), L"Ball_Boom", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/Fire_end.bmp"), L"Fire_end", m_hdc);
	CImgMgr::GetInstance()->AddTexture((L"../Resource/BallOver.bmp"), L"BallOver", m_hdc);

	CObjMgr::GetInstance()->AddObject(L"StageBack", SORTID_FIRST, CFactory<CStageBack>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Player", SORTID_UNITANDOBJ, CFactory<CPlayer>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Npc", SORTID_UNITANDOBJ, CFactory<CNpc>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Shop", SORTID_INVENANDSHOP, CFactory<CShop>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Inven", SORTID_INVENANDSHOP, CFactory<CInven>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Cube", SORTID_INVENANDSHOP, CFactory<CCube>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Stat", SORTID_STATE, CFactory<CState>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"UnderBar", SORTID_UI, CFactory<CUnderBar>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Alpha", SORTID_UI, CFactory<CAlphaTile>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Hp", SORTID_UI, CFactory<CHpBall>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Mp", SORTID_UI, CFactory<CMpBall>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Stamina", SORTID_UI, CFactory<CStamina>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"SkillIcon", SORTID_UI, CFactory<CSkillIcon>::CreateObject());

	CTileMgr::GetInstance()->DeleteTile();

	HANDLE			hFile;
	DWORD			dwByte;

	hFile = CreateFile(L"../Data/LogCamp.dat", GENERIC_READ, 0, 0
		, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	for (INT i = 0; i < iTILECNTX * iTILECNTY; ++i)
	{
		TILE*			pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);
		CTileMgr::GetInstance()->GetTileVector().push_back(pTile);
	}
	CloseHandle(hFile);
	
	CObjMgr::GetInstance()->AddObject(L"Cow", SORTID_UNITANDOBJ, CFactory<CMonster>::CreateObject(99999, 99999, false));



	/*CTileMgr::GetInstance()->DeleteTile();



	HANDLE			hFile;
	DWORD			dwByte;

	hFile = CreateFile(L"../Data/Battle.dat", GENERIC_READ, 0, 0
	, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	for (INT i = 0; i < iTILECNTX * iTILECNTY; ++i)
	{
	TILE*			pTile = new TILE;
	ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);
	CTileMgr::GetInstance()->GetTileVector().push_back(pTile);
	}
	CloseHandle(hFile);
	*/
	m_dwTime = GetTickCount();
	m_iShake = 0;


	CSoundMgr::GetInstance()->PlayBGMSound(L"town1.wav");
	CSoundMgr::GetInstance()->PlayVoiceSound(L"Aka_act1_q1_init.wav");

}

void CStage::Progress( void )
{

	CObjMgr::GetInstance()->Progress();
	
	if(CScene::m_bBattle == true && CScene::m_bHome == false && CScene::m_bTileSet == true)
	{
		CScene::m_bTileSet = false;
		m_bMon = false;

		CTileMgr::GetInstance()->DeleteTile();

		HANDLE			hFile;
		DWORD			dwByte;

		hFile = CreateFile(L"../Data/Battle.dat", GENERIC_READ, 0, 0
			, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		for (INT i = 0; i < iTILECNTX * iTILECNTY; ++i)
		{
			TILE*			pTile = new TILE;
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);
			CTileMgr::GetInstance()->GetTileVector().push_back(pTile);
		}

		CloseHandle(hFile);

		HANDLE			hFile1;
		DWORD			dwByte1;

		hFile1 = CreateFile(L"../Data/Monster1.dat", GENERIC_READ, 0, 0
			, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		
		for(int i = 0; i < 30; ++i)
		{
			INFO*	pInfo = new INFO;
			ReadFile(hFile1, pInfo, sizeof(INFO), &dwByte1, NULL);
			CObjMgr::GetInstance()->AddObject(L"Cow", SORTID_UNITANDOBJ, CFactory<CMonster>::CreateObject(*pInfo));
			safe_delete(pInfo);
		}
		CloseHandle(hFile1);
			
		
	}
	
	if(CObjMgr::GetInstance()->GetObjList(L"Cow")->size() <= 1
		&& CScene::m_bBattle == true && CScene::m_bHome == false
		&& m_bMon == false)
	{
		if(CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt == 60)
			return;

		m_bMon = true;

		HANDLE			hFile;
		DWORD			dwByte;

		hFile = CreateFile(L"../Data/Monster2.dat", GENERIC_READ, 0, 0
			, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		for(int i = 0; i < 30; ++i)
		{
			INFO*	pInfo = new INFO;
			ReadFile(hFile, pInfo, sizeof(INFO), &dwByte, NULL);
			CObjMgr::GetInstance()->AddObject(L"Cow", SORTID_UNITANDOBJ, CFactory<CMonster>::CreateObject(*pInfo));
			safe_delete(pInfo);
		}
		CloseHandle(hFile);
	}

	if(CScene::m_bBattle == false && CScene::m_bHome == true && CScene::m_bTileSet == true)
	{
		
		CScene::m_bTileSet = false;

		CTileMgr::GetInstance()->DeleteTile();

		HANDLE			hFile;
		DWORD			dwByte;

		hFile = CreateFile(L"../Data/LogCamp.dat", GENERIC_READ, 0, 0
			, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		for (INT i = 0; i < iTILECNTX * iTILECNTY; ++i)
		{
			TILE*			pTile = new TILE;
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);
			CTileMgr::GetInstance()->GetTileVector().push_back(pTile);
		}
		CloseHandle(hFile);

		list<CObj*>::iterator iter = ++CObjMgr::GetInstance()->GetObjList(L"Cow")->begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Cow")->end();


		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->GetInfo().bAlive = false;
		}

		if(CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt == 60)
		{
			list<CObj*>::iterator Boss_iter = CObjMgr::GetInstance()->GetObjList(L"Boss")->begin();
			(*Boss_iter)->GetInfo().bAlive = false;
		}
		CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt = 0;
		m_bBoss = false;
	}

	if(CScene::m_bBattle == true && m_bBoss == false)
	{
		if(CObjMgr::GetInstance()->GetInfo(L"Player")->iKillCnt == 60)
		{
			CSoundMgr::GetInstance()->PlayVoiceSound(L"diablotaunt.wav");

			if(m_iShake >= 0
				&& m_iShake < 3)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 3
				&& m_iShake < 6)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 6
				&& m_iShake < 9)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 9
				&& m_iShake < 12)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 12
				&& m_iShake < 15)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 15
				&& m_iShake < 18)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 18
				&& m_iShake < 21)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 21
				&& m_iShake < 24)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 24
				&& m_iShake < 27)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 27
				&& m_iShake < 30)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 30
				&& m_iShake < 33)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 33
				&& m_iShake < 36)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 36
				&& m_iShake < 39)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 39
				&& m_iShake < 42)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 42
				&& m_iShake < 45)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 45
				&& m_iShake < 48)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 48
				&& m_iShake < 51)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 51
				&& m_iShake < 54)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 54
				&& m_iShake < 57)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 57
				&& m_iShake < 60)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 60
				&& m_iShake < 63)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 63
				&& m_iShake < 66)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 66
				&& m_iShake < 69)
			{
				CObj::m_ptScroll.x += 10;
				CObj::m_ptScroll.y += 10;
			}
			if(m_iShake >= 69
				&& m_iShake < 72)
			{
				CObj::m_ptScroll.x -= 10;
				CObj::m_ptScroll.y -= 10;
			}
			if(m_iShake >= 72)
			{
				CObjMgr::GetInstance()->AddObject(L"Boss", SORTID_UNITANDOBJ, CFactory<CBoss>::CreateObject());

				m_bBoss = true;
				m_iShake = 0;
			}

			++m_iShake;
		}
	}
}

void CStage::Render( void )
{
	CObjMgr::GetInstance()->Render();

	BitBlt(m_hdc, 0, 0, iWINCX, iWINCY, *CImgMgr::GetInstance()->GetTexture(L"BackBuffer")
		, 0, 0, SRCCOPY);
}

void CStage::Release( void )
{
	CObjMgr::GetInstance()->Destroy();
}
