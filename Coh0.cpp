// Coh0.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Coh0.h"

#include "./packet/OH0.h"


// Coh0

IMPLEMENT_DYNAMIC(Coh0, CWnd)

Coh0::Coh0()
{

}

Coh0::~Coh0()
{
}


BEGIN_MESSAGE_MAP(Coh0, CWnd)
	ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealOH0)
END_MESSAGE_MAP()



// Coh0 message handlers
void Coh0::AdviseOH0()
{
	TCHAR	szTrCode[] = "OH0";

	//-----------------------------------------------------------
	// ������ ���
	CString strCode = "201M9317";
	//GetDlgItemText(IDC_EDIT_CODE, strCode);

	//-----------------------------------------------------------
	// ������ ����
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_REAL_DATA ���� �´�.
		szTrCode,					// TR ��ȣ
		strCode,					// �����ڵ�
		strCode.GetLength()
		//sizeof(OH0_InBlock)		// �����ڵ� ����
		);

	//-----------------------------------------------------------
	// ����üũ
	if (bSuccess == FALSE)
	{
		MessageBox("��ȸ����", "����", MB_ICONSTOP);
	}
	else
	{
		m_strCode = strCode;
	}
}

//--------------------------------------------------------------------------------------
// ������ Unadvise
//--------------------------------------------------------------------------------------
void Coh0::UnadviseOH0()
{
	//-----------------------------------------------------------
	// ������ ����� ������ ���ٸ� Return�Ѵ�.
	if (m_strCode.IsEmpty())
	{
		return;
	}

	TCHAR	szTrCode[] = "OH0";

	//-----------------------------------------------------------
	// ������ ����
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_REAL_DATA ���� �´�.
		szTrCode,					// TR ��ȣ
		m_strCode,					// �����ڵ�
		m_strCode.GetLength()
		//sizeof(OH0_InBlock)		// �����ڵ� ����
		);

	//-----------------------------------------------------------
	// ����üũ
	if (bSuccess == FALSE)
	{
		MessageBox("��ȸ����", "����", MB_ICONSTOP);
	}
	else
	{
		m_strCode.Empty();
	}

}

//--------------------------------------------------------------------------------------
// �����͸� ����
//--------------------------------------------------------------------------------------
LRESULT Coh0::OnXMReceiveRealOH0(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;

	if (strcmp(pRealPacket->szTrCode, "OH0") == 0)
	{

		LPOH0_OutBlock pOutBlock = (LPOH0_OutBlock)pRealPacket->pszData;
		//int nRow = 0;
		//m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->hotime, sizeof(pOutBlock->hotime), DATA_TYPE_STRING));    // ȣ���ð�
	}
	return 0L;
}
