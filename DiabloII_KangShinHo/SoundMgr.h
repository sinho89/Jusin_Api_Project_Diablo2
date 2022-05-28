#pragma once

#include "Defines.h"

class CSoundMgr
{
private:
	static CSoundMgr* m_pInstance;
public:
	static CSoundMgr* GetInstance()
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CSoundMgr;
		}
		return m_pInstance;
	}
	void DestroyInstance()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

	/////////////// fmod �������̽�
private:
	FMOD_SYSTEM*	m_pSystem;		//fmod �ý��� ������
	FMOD_CHANNEL*	m_pEffect[WT_END];
	FMOD_CHANNEL*	m_pMonster[5];
	FMOD_CHANNEL*	m_pSkill[5];
	FMOD_CHANNEL*	m_pMainBGM;		//�����

	FMOD_RESULT		m_Result;		// fmod �����߿� ����üũ

	unsigned int	m_iVersion;

	map<TCHAR*, FMOD_SOUND*>		m_mapSound;
	
	//��� �Լ��� ��������.

public:
	void Initialize(void);
	void LoadSoundFile(void);
	void PlayVoiceSound(TCHAR* pSoundKey);
	void MonsterSound1(TCHAR* pSoundKey);
	void MonsterSound2(TCHAR* pSoundKey);
	void MonsterSound3(TCHAR* pSoundKey);
	void MonsterSound4(TCHAR* pSoundKey);
	void MonsterSound5(TCHAR* pSoundKey);
	void ExploSound(TCHAR* pSoundKey);
	void EffectSound(TCHAR* pSoundKey);
	void SkillSound1(TCHAR* pSoundKey);
	void SkillSound2(TCHAR* pSoundKey);
	void SkillSound3(TCHAR* pSoundKey);
	void SkillSound4(TCHAR* pSoundKey);
	void SkillSound5(TCHAR* pSoundKey);
	void PlayerSound(TCHAR* pSoundKey);
	void ItemSound(TCHAR* pSoundKey);
	void PlayBGMSound(TCHAR* pSoundKey);
	void SoundAllStop(void);
	void SkillSoundStop(int i);

public:
	map<TCHAR*, FMOD_SOUND*>* GetSoundMap(void)
	{
		return &m_mapSound;
	}
private:
	void ErrorCheck(FMOD_RESULT _result);
private:
	CSoundMgr(void);
public:
	~CSoundMgr(void);
};
