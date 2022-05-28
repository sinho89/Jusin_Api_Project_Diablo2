#ifndef _MECRO_H
#define _MECRO_H

#define PURE	=0
#define PI	3.141592f

#define CREATE_SINGLETON(ClassName)			\
private:									\
	static ClassName*		m_pInstance;	\
public:										\
	static ClassName*		GetInstance(void)\
	{										\
		if(m_pInstance == NULL)				\
			m_pInstance = new ClassName;	\
		return m_pInstance;					\
	}										\
	void Destroy(void)						\
	{										\
		if(m_pInstance)						\
		{									\
			delete m_pInstance;				\
			m_pInstance = NULL;				\
		}									\
	}										\
										

#define INIT_SINGLETON(ClassName)				\
	ClassName*	ClassName::m_pInstance = NULL;	\

const DWORD KEY_LBUTTON	= 0x00000001;
const DWORD KEY_RBUTTON	= 0x00000002;
const DWORD KEY_SHIFT	= 0x00000004;
const DWORD KEY_I		= 0x00000008;
const DWORD KEY_C		= 0x00000010;
const DWORD KEY_K		= 0x00000020;

const int iWINCX = 800;
const int iWINCY = 600;
const int iTILESIZE = 48;
const int iTILECNTX = 4456 / 48;
const int iTILECNTY = 2850 / 48;

const int iITEMTILESIZEX = 36;
const int iITEMTILESIZEY = 37;
const int iSHOPTILECNTX = 10;
const int iSHOPTILECNTY = 10;
const int iSHOPMAX	= 100;
const int iINVENTILECNTX = 10;
const int iINVENTILECNTY = 4;
const int iCUBETILECNTX = 3;
const int iCUBETILECNTY = 4;
const int iCUBEMAX = 12;
const int iINVENMAX = 40;
const int iPOTIONMAX = 4;


template <typename T>
const inline void safe_delete(T& t)
{
	if(t)
	{
		delete t;
		t = NULL;
	}
}

#endif 