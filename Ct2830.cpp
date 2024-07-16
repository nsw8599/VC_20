// Ct2830.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Ct2830.h"
#include "./packet/t2830.h"


// Ct2830

IMPLEMENT_DYNAMIC(Ct2830, CWnd)

Ct2830::Ct2830()
{

}

Ct2830::~Ct2830()
{
}


BEGIN_MESSAGE_MAP(Ct2830, CWnd)
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceiveData)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeoutData)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// Ct2830 message handlers
void Ct2830::RequestData(BOOL bNext)
{
	//-----------------------------------------------------------
	// Eurex �ü���ȸ
	t2830InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t2830";
	char			szNextKey[] = "";

	//-----------------------------------------------------------
	// ������ ���
	CString str_focode = "201M9317";	//SetDlgItemText(IDC_INBLOCK_SHCODE, str_shcode);

	//-----------------------------------------------------------
	// ������ �ʱ�ȭ
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// ������ �Է�
	SetPacketData(pckInBlock.focode, sizeof(pckInBlock.focode), str_focode, DATA_TYPE_STRING);

	//�� �����
	//((CListCtrl*)GetDlgItem(IDC_OUTBLOCK))->DeleteAllItems();

	//-----------------------------------------------------------
	// ������ ����
	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_DATA ���� �´�.
		szTrNo,						// TR ��ȣ
		&pckInBlock,				// InBlock ������
		sizeof(pckInBlock),		// InBlock ������ ũ��
		bNext,						// ������ȸ ���� : ������ȸ�� ��쿡 �����Ѵ�.
		szNextKey,					// ������ȸ Key : Header Type�� B �� ��쿣 ���� ��ȸ�� ���� Next Key�� �־��ش�.
		30							// Timeout(��) : �ش� �ð�(��)���� �����Ͱ� ���� ������ Timeout�� �߻��Ѵ�. XM_TIMEOUT_DATA �޽����� �߻��Ѵ�.
		);

	//-----------------------------------------------------------
	// Request ID�� 0���� ���� ��쿡�� �����̴�.
	if (nRqID < 0)
	{
		MessageBox("��ȸ����", "����", MB_ICONSTOP);
	}
}

//--------------------------------------------------------------------------------------
// �����͸� ����
//--------------------------------------------------------------------------------------
LRESULT Ct2830::OnXMReceiveData(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data�� ����
	if (wParam == REQUEST_DATA)
	{
		LPRECV_PACKET pRpData = (LPRECV_PACKET)lParam;
		LPt2830OutBlock pOutBlock = (LPt2830OutBlock)pRpData->lpData;

		//m_ctrlOutBlock.SetItemText(0, 1, GetDispData(pOutBlock->hname, sizeof(pOutBlock->hname), DATA_TYPE_STRING));
	}

	//-------------------------------------------------------------------------------------
	// �޽����� ����
	else if (wParam == MESSAGE_DATA)
	{
		LPMSG_PACKET pMsg = (LPMSG_PACKET)lParam;

		CString strMsg((char*)pMsg->lpszMessageData, pMsg->nMsgLength);
		GetParent()->SendMessage(WMU_SET_MESSAGE, (WPARAM)pMsg->szMsgCode, (LPARAM)(LPCTSTR)strMsg);

		g_iXingAPI.ReleaseMessageData(lParam);
	}

	//-------------------------------------------------------------------------------------
	// System Error�� ����
	else if (wParam == SYSTEM_ERROR_DATA)
	{
		LPMSG_PACKET pMsg = (LPMSG_PACKET)lParam;

		CString strMsg((char*)pMsg->lpszMessageData, pMsg->nMsgLength);
		GetParent()->SendMessage(WMU_SET_MESSAGE, (WPARAM)pMsg->szMsgCode, (LPARAM)(LPCTSTR)strMsg);

		g_iXingAPI.ReleaseMessageData(lParam);
	}

	//-------------------------------------------------------------------------------------
	// Release Data�� ����
	else if (wParam == RELEASE_DATA)
	{
		g_iXingAPI.ReleaseRequestData((int)lParam);
	}
	return 0L;
}

//--------------------------------------------------------------------------------------
// Timeout �߻�
//--------------------------------------------------------------------------------------
LRESULT Ct2830::OnXMTimeoutData(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);

	return 0L;
}

