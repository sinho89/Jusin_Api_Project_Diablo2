#include "StdAfx.h"
#include "SkillIcon.h"
#include "Mouse.h"
#include "ObjMgr.h"

CSkillIcon::CSkillIcon(void)
{
}

CSkillIcon::~CSkillIcon(void)
{
}

void CSkillIcon::Initialize(void)
{
	m_tInfo.fX = 659;
	m_tInfo.fY = 577;

	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 48.f;

	m_iFrameX = 0;
	m_iFrameY = 0;

	m_bView = false;
	m_bClick = false;
	m_SelectTick = false;
	m_bSet = false;
	m_bSet1 = false;
	m_bSet2 = false;
	m_bSet3 = false;
	m_bSet4 = false;

	m_eType = KT_NORMAL;
}

void CSkillIcon::Progress(void)
{
	POINT	ptMouse = CMouse::GetMousePos();

	RECT	rcSkillUI = { m_tInfo.fX - m_tInfo.fCX / 2.f
						, m_tInfo.fY - m_tInfo.fCY / 2.f
						, m_tInfo.fX + m_tInfo.fCX / 2.f
						, m_tInfo.fY + m_tInfo.fCY / 2.f};

	if(PtInRect(&rcSkillUI, ptMouse))
	{
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if(m_bClick == true)
				return;
			m_bClick = true;

			if(m_bView == true)
				m_bView = false;
			else if(m_bView == false)
				m_bView = true;
		}
		else
			m_bClick = false;
	}
	if(m_bView == false)
	{
		if(GetAsyncKeyState(VK_F1) & 0x8000)
		{
			*CObjMgr::GetInstance()->GetSkill(L"Player") = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0];
			m_eType = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0];
		}
		if(GetAsyncKeyState(VK_F2) & 0x8000)
		{
			*CObjMgr::GetInstance()->GetSkill(L"Player") = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1];
			m_eType = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1];
		}
		if(GetAsyncKeyState(VK_F3) & 0x8000)
		{
			*CObjMgr::GetInstance()->GetSkill(L"Player") = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2];
			m_eType = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2];
		}
		if(GetAsyncKeyState(VK_F4) & 0x8000)
		{
			*CObjMgr::GetInstance()->GetSkill(L"Player") = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3];
			m_eType = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3];
		}
		if(GetAsyncKeyState(VK_F5) & 0x8000)
		{
			*CObjMgr::GetInstance()->GetSkill(L"Player") = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4];
			m_eType = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4];

		}
	}
	

	if(m_bView == true)
	{
		CObjMgr::GetInstance()->GetRender(L"Player")->m_bSkillRender = true;

		if(GetAsyncKeyState(VK_F1) & 0x8000)
		{
			if(m_bSet == true)
				return;
			m_bSet = true;

			for(int i = 0; i < 6; ++i)
			{
				RECT	rcSkill = {((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + i * m_tInfo.fCX
									, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50)
									, ((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + (i + 1) * m_tInfo.fCX
									, (m_tInfo.fY + m_tInfo.fCY / 2.f - 50)};
				if(PtInRect(&rcSkill, ptMouse))
				{
					switch(i)
					{
					case 0:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_NORMAL;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_NORMAL)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_NORMAL
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_NORMAL)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_NORMAL;
						}


						break;
					case 1:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_TRANSFORM;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_TRANSFORM)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_TRANSFORM
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TRANSFORM)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_TRANSFORM;
						}
						break;
					case 2:
					   if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_END)
						   CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_AMA;
					   else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_AMA)
						   CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_END;
					   else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_AMA
						   && CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_END)
					   {
						   eSKILL_TYPE eTemp;
						   eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0];
						   for(int i = 0; i < 5; ++i)
						   {
							   if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_AMA)
							   {
								   CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
								   break;
							   }
						   }
						   CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_AMA;
					   }
					   break;
					case 3:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_HURRI;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_HURRI)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_HURRI
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_HURRI)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_HURRI;
						}
						break;
					case 4:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_TOR;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_TOR)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_TOR
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TOR)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_TOR;
						}
						break;
					case 5:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_SHOCK;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_SHOCK)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_SHOCK
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_SHOCK)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] = KT_SHOCK;
						}
						break;
					}
					break;
				}
			}
		}
		else
			m_bSet = false;
		if(GetAsyncKeyState(VK_F2) & 0x8000)
		{
			if(m_bSet1 == true)
				return;
			m_bSet1 = true;
			for(int i = 0; i < 6; ++i)
			{
				RECT	rcSkill = {((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + i * m_tInfo.fCX
									, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50)
									, ((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + (i + 1) * m_tInfo.fCX
									, (m_tInfo.fY + m_tInfo.fCY / 2.f - 50)};
				if(PtInRect(&rcSkill, ptMouse))
				{
					switch(i)
					{
					case 0:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_NORMAL;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_NORMAL)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_NORMAL
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_NORMAL)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_NORMAL;
						}


						break;
					case 1:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_TRANSFORM;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_TRANSFORM)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_TRANSFORM
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TRANSFORM)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_TRANSFORM;
						}
						break;
					case 2:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_AMA;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_AMA)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_AMA
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_AMA)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_AMA;
						}
						break;
					case 3:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_HURRI;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_HURRI)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_HURRI
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_HURRI)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_HURRI;
						}
						break;
					case 4:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_TOR;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_TOR)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_TOR
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TOR)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_TOR;
						}
						break;
					case 5:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_SHOCK;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_SHOCK)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_SHOCK
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_SHOCK)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] = KT_SHOCK;
						}
						break;
					}
					break;
				}
			}
		}
		else
			m_bSet1 = false;
		if(GetAsyncKeyState(VK_F3) & 0x8000)
		{
			if(m_bSet2 == true)
				return;
			m_bSet2 = true;
			for(int i = 0; i < 6; ++i)
			{
				RECT	rcSkill = {((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + i * m_tInfo.fCX
									, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50)
									, ((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + (i + 1) * m_tInfo.fCX
									, (m_tInfo.fY + m_tInfo.fCY / 2.f - 50)};
				if(PtInRect(&rcSkill, ptMouse))
				{
					switch(i)
					{
					case 0:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_NORMAL;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_NORMAL)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_NORMAL
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_NORMAL)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_NORMAL;
						}


						break;
					case 1:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_TRANSFORM;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_TRANSFORM)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_TRANSFORM
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TRANSFORM)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_TRANSFORM;
						}
						break;
					case 2:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_AMA;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_AMA)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_AMA
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_AMA)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_AMA;
						}
						break;
					case 3:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_HURRI;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_HURRI)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_HURRI
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_HURRI)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_HURRI;
						}
						break;
					case 4:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_TOR;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_TOR)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_TOR
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TOR)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_TOR;
						}
						break;
					case 5:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_SHOCK;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_SHOCK)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_SHOCK
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_SHOCK)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] = KT_SHOCK;
						}
						break;
					}
					break;
				}
			}
		}
		else
			m_bSet2 = false;
		if(GetAsyncKeyState(VK_F4) & 0x8000)
		{
			if(m_bSet3 == true)
				return;
			m_bSet3 = true;
			for(int i = 0; i < 6; ++i)
			{
				RECT	rcSkill = {((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + i * m_tInfo.fCX
									, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50)
									, ((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + (i + 1) * m_tInfo.fCX
									, (m_tInfo.fY + m_tInfo.fCY / 2.f - 50)};
				if(PtInRect(&rcSkill, ptMouse))
				{
					switch(i)
					{
					case 0:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_NORMAL;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_NORMAL)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_NORMAL
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_NORMAL)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_NORMAL;
						}


						break;
					case 1:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_TRANSFORM;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_TRANSFORM)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_TRANSFORM
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TRANSFORM)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_TRANSFORM;
						}
						break;
					case 2:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_AMA;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_AMA)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_AMA
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_AMA)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_AMA;
						}
						break;
					case 3:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_HURRI;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_HURRI)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_HURRI
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_HURRI)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_HURRI;
						}
						break;
					case 4:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_TOR;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_TOR)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_TOR
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TOR)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_TOR;
						}
						break;
					case 5:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_SHOCK;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_SHOCK)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_SHOCK
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_SHOCK)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] = KT_SHOCK;
						}
						break;
					}
					break;
				}
			}
		}
		else
			m_bSet3 = false;
		if(GetAsyncKeyState(VK_F5) & 0x8000)
		{
			if(m_bSet4 == true)
				return;
			m_bSet4 = true;
			for(int i = 0; i < 6; ++i)
			{
				RECT	rcSkill = {((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + i * m_tInfo.fCX
									, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50)
									, ((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + (i + 1) * m_tInfo.fCX
									, (m_tInfo.fY + m_tInfo.fCY / 2.f - 50)};
				if(PtInRect(&rcSkill, ptMouse))
				{
					switch(i)
					{
					case 0:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_NORMAL;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_NORMAL)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_NORMAL
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_NORMAL)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_NORMAL;
						}


						break;
					case 1:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_TRANSFORM;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_TRANSFORM)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_TRANSFORM
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TRANSFORM)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_TRANSFORM;
						}
						break;
					case 2:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_AMA;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_AMA)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_AMA
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_AMA)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_AMA;
						}
						break;
					case 3:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_HURRI;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_HURRI)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_HURRI
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_HURRI)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_HURRI;
						}
						break;
					case 4:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_TOR;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_TOR)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_TOR
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_TOR)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_TOR;
						}
						break;
					case 5:
						if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_END)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_SHOCK;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_SHOCK)
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_END;
						else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_SHOCK
							&& CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] != KT_END)
						{
							eSKILL_TYPE eTemp;
							eTemp = CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4];
							for(int i = 0; i < 5; ++i)
							{
								if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] == KT_SHOCK)
								{
									CObjMgr::GetInstance()->GetSaveSkill(L"Player")[i] = eTemp;
									break;
								}
							}
							CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] = KT_SHOCK;
						}
						break;
					}
					break;
				}
			}
		}
		else
			m_bSet4 = false;

		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if(m_SelectTick == true)
				return;
			m_SelectTick = true;

			for(int i = 0; i < 6; ++i)
			{
				RECT	rcSkill = {((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + i * m_tInfo.fCX
									, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50)
									, ((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + (i + 1) * m_tInfo.fCX
									, (m_tInfo.fY + m_tInfo.fCY / 2.f - 50)};
				if(PtInRect(&rcSkill, ptMouse))
				{
					switch(i)
					{
					case 0:
						*CObjMgr::GetInstance()->GetSkill(L"Player") = KT_NORMAL;
						m_eType = KT_NORMAL;
						break;
					case 1:
						*CObjMgr::GetInstance()->GetSkill(L"Player") = KT_TRANSFORM;
						m_eType = KT_TRANSFORM;
						break;
					case 2:
						*CObjMgr::GetInstance()->GetSkill(L"Player") = KT_AMA;
						m_eType = KT_AMA;
						break;
					case 3:
						*CObjMgr::GetInstance()->GetSkill(L"Player") = KT_HURRI;
						m_eType = KT_HURRI;
						break;
					case 4:
						*CObjMgr::GetInstance()->GetSkill(L"Player") = KT_TOR;
						m_eType = KT_TOR;
						break;
					case 5:
						*CObjMgr::GetInstance()->GetSkill(L"Player") = KT_SHOCK;
						m_eType = KT_SHOCK;
						break;
					}
					break;
				}
			}
		}
		else
			m_SelectTick = false;

	}
	if(m_bView == false)
	{
		CObjMgr::GetInstance()->GetRender(L"Player")->m_bSkillRender = false;
	}

}

void CSkillIcon::Render(void)
{
	if(m_eType == KT_NORMAL)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),m_tInfo.fX - m_tInfo.fCX / 2.f
			, m_tInfo.fY - m_tInfo.fCY / 2.f
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY) 
			, *CImgMgr::GetInstance()->GetTexture(L"SkillIcon"), 0 * m_tInfo.fCX
			, 0, SRCCOPY);
	}

	if(m_eType == KT_TRANSFORM)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),m_tInfo.fX - m_tInfo.fCX / 2.f
			, m_tInfo.fY - m_tInfo.fCY / 2.f
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY) 
			, *CImgMgr::GetInstance()->GetTexture(L"SkillIcon"), 1 * m_tInfo.fCX
			, 0, SRCCOPY);
	}

	if(m_eType == KT_AMA)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),m_tInfo.fX - m_tInfo.fCX / 2.f
			, m_tInfo.fY - m_tInfo.fCY / 2.f
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY) 
			, *CImgMgr::GetInstance()->GetTexture(L"SkillIcon"), 2 * m_tInfo.fCX
			, 0, SRCCOPY);
	}

	if(m_eType == KT_HURRI)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),m_tInfo.fX - m_tInfo.fCX / 2.f
			, m_tInfo.fY - m_tInfo.fCY / 2.f
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY) 
			, *CImgMgr::GetInstance()->GetTexture(L"SkillIcon"), 3 * m_tInfo.fCX
			, 0, SRCCOPY);
	}

	if(m_eType == KT_TOR)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),m_tInfo.fX - m_tInfo.fCX / 2.f
			, m_tInfo.fY - m_tInfo.fCY / 2.f
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY) 
			, *CImgMgr::GetInstance()->GetTexture(L"SkillIcon"), 4 * m_tInfo.fCX
			, 0, SRCCOPY);
	}

	if(m_eType == KT_SHOCK)
	{
		BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),m_tInfo.fX - m_tInfo.fCX / 2.f
			, m_tInfo.fY - m_tInfo.fCY / 2.f
			, int(m_tInfo.fCX)
			, int(m_tInfo.fCY) 
			, *CImgMgr::GetInstance()->GetTexture(L"SkillIcon"), 5 * m_tInfo.fCX
			, 0, SRCCOPY);
	}
	
	
	if(m_bView == true)
	{
		for(int i = 0; i < 6; ++i)
		{
			BitBlt(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + i * m_tInfo.fCX
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50)
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY) 
				, *CImgMgr::GetInstance()->GetTexture(L"SkillIcon"), i * m_tInfo.fCX
				, 0, SRCCOPY);

		}		
	}

	if(m_bView == true)
	{
		if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_NORMAL)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F1");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 0 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_TRANSFORM)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F1");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 1 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_AMA)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F1");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 2 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_HURRI)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F1");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 3 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_TOR)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F1");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 4 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[0] == KT_SHOCK)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F1");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 5 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_NORMAL)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F2");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 0 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_TRANSFORM)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F2");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 1 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_AMA)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F2");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 2 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_HURRI)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F2");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 3 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_TOR)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F2");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 4 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[1] == KT_SHOCK)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F2");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 5 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_NORMAL)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F3");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 0 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_TRANSFORM)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F3");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 1 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_AMA)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F3");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 2 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_HURRI)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F3");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 3 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_TOR)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F3");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 4 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[2] == KT_SHOCK)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F3");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 5 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_NORMAL)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F4");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 0 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_TRANSFORM)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F4");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 1 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_AMA)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F4");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 2 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_HURRI)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F4");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 3 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_TOR)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F4");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 4 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[3] == KT_SHOCK)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F4");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 5 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_NORMAL)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F5");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 0 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_TRANSFORM)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F5");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 1 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_AMA)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F5");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 2 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_HURRI)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F5");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 3 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_TOR)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F5");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 4 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));

		}
		else if(CObjMgr::GetInstance()->GetSaveSkill(L"Player")[4] == KT_SHOCK)
		{
			TCHAR				szString[128];

			wsprintf(szString, L"F5");
			TextOut(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), (((m_tInfo.fX - m_tInfo.fCX / 2.f) - 240) + 5 * m_tInfo.fCX)
				, (m_tInfo.fY - m_tInfo.fCY / 2.f - 50), szString, lstrlen(szString));
		}
	}
}

void CSkillIcon::Release(void)
{

}
