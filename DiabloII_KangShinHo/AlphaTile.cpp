#include "StdAfx.h"
#include "AlphaTile.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "ObjMgr.h"
#include "CollMgr.h"
#include "Mouse.h"
#include "Item.h"

CAlphaTile::CAlphaTile(void)
{
}

CAlphaTile::~CAlphaTile(void)
{
}

void CAlphaTile::Initialize( void )
{
	m_tInfo.fCX = iITEMTILESIZEX;
	m_tInfo.fCY = iITEMTILESIZEY;

	m_tInfo.bAlive = true;

	m_iFrameX = 0;
	m_iFrameY = 0;
}

void CAlphaTile::Progress( void )
{
	POINT ptMouse = CMouse::GetMousePos();

	RECT	rcInven = {long(CTileMgr::GetInstance()->GetInvenTile()[0]->fX
		- CTileMgr::GetInstance()->GetInvenTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[0]->fY
		- CTileMgr::GetInstance()->GetInvenTile()[0]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fX
		+ CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fY
		+ CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fCY / 2.f)};

	if(PtInRect(&rcInven, ptMouse))
	{

		int		iInvenIndex = int((ptMouse.y - 325) / iITEMTILESIZEY) * iSHOPTILECNTX + int((ptMouse.x - 425) / iITEMTILESIZEX);

		if(iInvenIndex < 0 || 39 < iInvenIndex)
			return;

		m_tInfo.fX = CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX;
		m_tInfo.fY = CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY;
	}



}

void CAlphaTile::Render( void )
{
	POINT ptMouse = CMouse::GetMousePos();

	RECT	rcInven = {long(CTileMgr::GetInstance()->GetInvenTile()[0]->fX
		- CTileMgr::GetInstance()->GetInvenTile()[0]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[0]->fY
		- CTileMgr::GetInstance()->GetInvenTile()[0]->fCY / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fX
		+ CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fCX / 2.f)
		, long(CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fY
		+ CTileMgr::GetInstance()->GetInvenTile()[iINVENMAX - 1]->fCY / 2.f)};

	if(PtInRect(&rcInven, ptMouse))
	{

		int		iInvenIndex = int((ptMouse.y - 325) / iITEMTILESIZEY) * iSHOPTILECNTX + int((ptMouse.x - 425) / iITEMTILESIZEX);

		if(iInvenIndex < 0 || 39 < iInvenIndex)
			return;

		if(CObjMgr::GetInstance()->GetRender(L"Player")->m_bInvenRender == true && CCollMgr::GetInstance()->GetHandItem() != NULL)
		{

			HDC			dcTemp = CreateCompatibleDC(GetDC(g_hWnd));
			HBITMAP		hBitMap = CreateCompatibleBitmap(GetDC(g_hWnd),
				int(m_tInfo.fCX), int(m_tInfo.fCY));

			HBITMAP	hOld = (HBITMAP)SelectObject(dcTemp, hBitMap);

			//����ȭ ó���� �ϱ� ���ؼ� ���ݱ��� ������Ʈ���� �׷��� �ִ�
			//����۸� ���ο� DC�� �����ϰ� �� Dc ���� �÷��̾� �̹����� �ø���
			//�� Dc�� ��ä�� ����ۿ� �����ϰ� �׷��� �ȴ�.

			TransparentBlt(dcTemp,0
				, 0
				, 800
				, 600
				, *CImgMgr::GetInstance()->GetTexture(L"BackBuffer"), 0
				, 0, 800, 600, RGB(0, 0, 0));

			TransparentBlt(dcTemp,0
				, 0
				, int(m_tInfo.fCX)
				, int(m_tInfo.fCY)
				, *CImgMgr::GetInstance()->GetTexture(L"Alpha"), m_iFrameX * m_tInfo.fCX
				, 0, int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(0, 0, 0));

			//�÷��̾� ������ ��� ����


			//�ð��� ���� ������ ���� ������ ���� �� ����.

			

			BLENDFUNCTION	tFunction;
			tFunction.BlendOp = AC_SRC_OVER;
			tFunction.BlendFlags = 0;
			tFunction.SourceConstantAlpha = 50;	//�̰� ������ ������ ��Ÿ���� 0 ~ 255
			tFunction.AlphaFormat = 0;

	
			AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
				int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCX / 2.f),
				int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCY / 2.f),
				int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCX),
				int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex]->fCY),
				dcTemp,
				m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
				0,//�̹��� Y ���� * ������
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				tFunction);	//�÷��̾� ������ ��� ����

			if(CCollMgr::GetInstance()->GetHandItem()->GetInfo().cType == IST_TWO_BY_THREE)
			{
				if(iInvenIndex >= 0 && 9 > iInvenIndex)
				{
					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
					int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCX / 2.f),
					int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCY / 2.f),
					int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCX),
					int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCY),
					dcTemp,
					m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
					0,//�̹��� Y ���� * ������
					int(m_tInfo.fCX),
					int(m_tInfo.fCY),
					tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX * 2 + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����
				}

				else if(iInvenIndex >= 10 && 19 > iInvenIndex)
				{
					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����
				}
				else if(iInvenIndex >= 20 && 29 > iInvenIndex)
				{
					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + iINVENTILECNTX + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����
				}
				else if(iInvenIndex >= 30 && 39 > iInvenIndex)
				{
					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����

					AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 + 1]->fX - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 + 1]->fCX / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 + 1]->fY - CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 + 1]->fCY / 2.f),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 + 1]->fCX),
						int(CTileMgr::GetInstance()->GetInvenTile()[iInvenIndex - iINVENTILECNTX * 2 + 1]->fCY),
						dcTemp,
						m_iFrameX * m_tInfo.fCX, //������ ��ŸƮ * ������
						0,//�̹��� Y ���� * ������
						int(m_tInfo.fCX),
						int(m_tInfo.fCY),
						tFunction);	//�÷��̾� ������ ��� ����
				}
			}

			/*AlphaBlend(*CImgMgr::GetInstance()->GetTexture(L"BackBuffer"),
				int(m_tInfo.fX - m_tInfo.fCX / 2.f),
				int(m_tInfo.fY - m_tInfo.fCY / 2.f),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				dcTemp,
				0, //������ ��ŸƮ * ������
				0,//�̹��� Y ���� * ������
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				tFunction);	//�÷��̾� ������ ��� ����*/

			hBitMap = (HBITMAP)SelectObject(dcTemp, hOld);
			DeleteObject(hBitMap);
			DeleteDC(dcTemp);
		}
	}

}

void CAlphaTile::Release( void )
{

}
