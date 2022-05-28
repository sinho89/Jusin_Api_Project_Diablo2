#include "StdAfx.h"
#include "SoundMgr.h"
#include "Func.h"

CSoundMgr*	CSoundMgr::m_pInstance = NULL;

CSoundMgr::CSoundMgr(void)
{
	m_pSystem = NULL;
	for(int i = 0; i < WT_END; ++i)
		m_pEffect[i] = NULL;
	m_pMainBGM = NULL;


	m_iVersion = 0;

	Initialize();
}

CSoundMgr::~CSoundMgr(void)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter = m_mapSound.begin();
	map<TCHAR*, FMOD_SOUND*>::iterator iter_end = m_mapSound.end();

	for( ; iter != iter_end;)
	{
		m_Result = FMOD_Sound_Release(iter->second);
		ErrorCheck(m_Result);

		delete [] (iter->first);

		iter = m_mapSound.erase(iter);
		iter_end = m_mapSound.end();

		if(iter == iter_end)
			break;
	}

	m_Result = FMOD_System_Close(m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Release(m_pSystem);
	ErrorCheck(m_Result);
}

void CSoundMgr::Initialize(void)
{
	m_Result = FMOD_System_Create(&m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_GetVersion(m_pSystem, &m_iVersion);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(m_Result);

	
}
void CSoundMgr::ErrorCheck(FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
	{
		cout << "에러!!" << endl;
		system("pause");
		return;
	}
}
void CSoundMgr::LoadSoundFile(void)
{
	_finddata_t fd; // 순차적으로 찾기 위한

	long handle;

	int iResult = 1;

	handle = _findfirst("..\\SoundFile\\*.*", &fd);

	if(handle == -1)
		return;

	while(iResult != -1)
	{
		TCHAR szName[256];

		ZeroMemory(szName, sizeof(szName)); // 매크로함수 : 내부적으로 memset

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,
							fd.name, strlen(fd.name), szName, 256); 
			// 멀티바이트를 유니코드로 변경해주는 함수.
		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		lstrcpy(pName, szName);		// 유니코드 문자열 복사.

		char szFullName[256];

		strcpy_s(szFullName, "..\\SoundFile\\");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName,
											FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
		{
			// 사운드파일 정상적인 완성!
			m_mapSound.insert( make_pair(pName, pSound) );
		}
		else
		{
			delete [] pName;
		}

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);

	m_Result = FMOD_System_Update(m_pSystem);
	ErrorCheck(m_Result);
}
void CSoundMgr::MonsterSound1(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pMonster[0]);
	ErrorCheck(m_Result);
}
void CSoundMgr::MonsterSound2(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pMonster[1]);
	ErrorCheck(m_Result);
}
void CSoundMgr::MonsterSound3(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pMonster[2]);
	ErrorCheck(m_Result);
}
void CSoundMgr::MonsterSound4(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pMonster[3]);
	ErrorCheck(m_Result);
}
void CSoundMgr::MonsterSound5(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pMonster[4]);
	ErrorCheck(m_Result);
}
void CSoundMgr::ExploSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pEffect[WT_EXPLO]);
	ErrorCheck(m_Result);
}
void CSoundMgr::EffectSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pEffect[WT_EFFECT]);
	ErrorCheck(m_Result);
}
void CSoundMgr::SkillSound1(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pSkill[0]);
	ErrorCheck(m_Result);
}
void CSoundMgr::SkillSound2(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pSkill[1]);
	ErrorCheck(m_Result);
}
void CSoundMgr::SkillSound3(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pSkill[2]);
	ErrorCheck(m_Result);
}
void CSoundMgr::SkillSound4(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pSkill[3]);
	ErrorCheck(m_Result);
}
void CSoundMgr::SkillSound5(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pSkill[4]);
	ErrorCheck(m_Result);
}
void CSoundMgr::PlayerSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pEffect[WT_PLAYER]);
	ErrorCheck(m_Result);
}
void CSoundMgr::ItemSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pEffect[WT_ITEM]);
	ErrorCheck(m_Result);
}
void CSoundMgr::PlayVoiceSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pEffect[WT_STAGE_VOICE]);
	ErrorCheck(m_Result);
}
void CSoundMgr::PlayBGMSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pMainBGM);
	ErrorCheck(m_Result);

}
void CSoundMgr::SoundAllStop(void)
{
	if(m_pMainBGM)
	{
		m_Result = FMOD_Channel_Stop(m_pMainBGM);
		ErrorCheck(m_Result);
	
	}

	for(int i = 0; i < WT_END; ++i)
	{
		if(m_pEffect[i])
		{
			m_Result = FMOD_Channel_Stop(m_pEffect[i]);
			ErrorCheck(m_Result);
		}
	}
	for(int i = 0; i < 5; ++i)
	{
		m_Result = FMOD_Channel_Stop(m_pSkill[i]);
		ErrorCheck(m_Result);
	}
	
}
void CSoundMgr::SkillSoundStop(int i)
{
	m_Result = FMOD_Channel_Stop(m_pSkill[i]);
	ErrorCheck(m_Result);
}