// Dlg_CEXAQ21200.cpp : implementation file
//

#include "stdafx.h"
#include "xingapi_sample.h"
#include "Dlg_CEXAQ21200.h"

#include "./Packet/CEXAQ21200.h"
//#include "./packet/t0167.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CEXAQ21200 dialog


IMPLEMENT_DYNCREATE(CDlg_CEXAQ21200, CDialog)

CDlg_CEXAQ21200::CDlg_CEXAQ21200(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CEXAQ21200::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_CEXAQ21200)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_CEXAQ21200::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CEXAQ21200)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_INBLOCK_CODE, m_code);
	DDX_Control(pDX, IDC_INBLOCK_PRICE, m_price);
}


BEGIN_MESSAGE_MAP(CDlg_CEXAQ21200, CDialog)
	//{{AFX_MSG_MAP(CDlg_CEXAQ21200)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST_NEXT, OnButtonRequestNext)
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceiveData)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeoutData)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_CEXAQ21200 message handlers

BOOL CDlg_CEXAQ21200::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCtrls();
	m_RecCnt = "1";
	m_AcntNo = "00151751313";
	m_Pwd = "0716";
	m_QryTp = "1"; //1:�ܰ����
	m_OrdAmt = "0";
	m_RatVal = "0";
	m_BnsTpCode = "2"; // �ż�
	m_ErxPrcCndiTpCode="2"; //

	m_code.SetWindowTextA("201M9317");
	m_price.SetWindowTextA("0.25");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_CEXAQ21200::OnButtonRequest()
{
	RequestData();
	//Request0167();

	SetTimer(1, 10000, NULL);
	//SetTimer(2, 1000, NULL);



}

void CDlg_CEXAQ21200::OnButtonRequestNext()
{
	KillTimer(1);
	//KillTimer(2);
}

//--------------------------------------------------------------------------------------
// ��Ʈ�� �ʱ�ȭ
//--------------------------------------------------------------------------------------
void CDlg_CEXAQ21200::InitCtrls()
{
	//-----------------------------------------------------------
	// OutBlock1
	InsertColumn4List(this, IDC_OUTBLOCK1, 0, "��ȸ����				", FALSE, 7);    // [long  ,    4] CNT   
	InsertColumn4List(this, IDC_OUTBLOCK1, 1, "�ֹ��ݾ�				", FALSE, 16);    // [string,    8] ��¥  
	InsertColumn4List(this, IDC_OUTBLOCK1, 2, "������				", FALSE, 12);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 3, "�����ɼ������ȣ       ", FALSE, 15);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 4, "�Ÿű���				", FALSE, 7);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 5, "�ֹ���				", FALSE, 13);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 6, "�����������ڵ�  ", FALSE, 10);    // [long  ,    4] IDX   
																			  // OutBlock2
	InsertColumn4List(this, IDC_OUTBLOCK2, 0, "���¸�				", FALSE, 40);    // [string,    8] ��¥          
	InsertColumn4List(this, IDC_OUTBLOCK2, 1, "��ȸ��				", FALSE, 10);    // [string,    10] ��¥    
	InsertColumn4List(this, IDC_OUTBLOCK2, 2, "���簡				", FALSE, 15);    // [long  ,    8] �ð�          
	InsertColumn4List(this, IDC_OUTBLOCK2, 3, "�ֹ����ɼ���          ", FALSE, 16);    // [long  ,    8] ��          
	InsertColumn4List(this, IDC_OUTBLOCK2, 4, "�ű��ֹ����ɼ���		", FALSE, 16);    // [long  ,    8] ����          
	InsertColumn4List(this, IDC_OUTBLOCK2, 5, "û���ֹ����ɼ���       ", FALSE, 16);    // [long  ,    8] ����    
	InsertColumn4List(this, IDC_OUTBLOCK2, 6, "��뿹�����űݾ�		", FALSE, 16);    // [long  ,   12] �����ŷ���  
	InsertColumn4List(this, IDC_OUTBLOCK2, 7, "��뿹���������űݾ�	", FALSE, 16);    // [long  ,   12] �ŷ����  
	InsertColumn4List(this, IDC_OUTBLOCK2, 8, "�ֹ����ɱݾ�			", FALSE, 16);    // [float ,  6.2] �������ص����
	InsertColumn4List(this, IDC_OUTBLOCK2, 9, "�����ֹ����ɱݾ�		", FALSE, 16);    // [float ,  6.2] �������ص����
}

//--------------------------------------------------------------------------------------
// ������ ��ȸ
//--------------------------------------------------------------------------------------
void CDlg_CEXAQ21200::RequestData(BOOL bNext)
{
	//-----------------------------------------------------------
	// �Ⱓ���ְ�(CEXAQ21200) ( attr,block,headtype=A )
	CEXAQ21200InBlock1	pckInBlock;

	TCHAR	szTrNo[] = "CEXAQ21200";

	CString s1 = _T("1");
	CString s2 = _T("00151751313");
	CString s3 = _T("0716");
	CString s4 = _T("1"); //1:�ܰ����
	CString s5 = _T("0");
	CString s6 = _T("0");
	CString s7 = _T("201M9317");
	CString s8 = _T("2"); // �ż�
	CString s9 = _T("0.25");
	CString s10 = _T("2"); //

							//-----------------------------------------------------------
							// ������ �ʱ�ȭ
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// ������ �Է�
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), s1, DATA_TYPE_LONG);	// �����ڵ�  
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), s2, DATA_TYPE_STRING);	// ���ֿ�����
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), s3, DATA_TYPE_STRING);	// ���ֿ�����
	SetPacketData(pckInBlock.QryTp, sizeof(pckInBlock.QryTp), s4, DATA_TYPE_STRING);	// ��¥      
	SetPacketData(pckInBlock.OrdAmt, sizeof(pckInBlock.OrdAmt), s5, DATA_TYPE_LONG);	// IDX       
	SetPacketData(pckInBlock.RatVal, sizeof(pckInBlock.RatVal), s6, DATA_TYPE_DOT, 2);	// �Ǽ�    
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), s7, DATA_TYPE_STRING);	// ���ֿ�����      
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), s8, DATA_TYPE_STRING);	// IDX       
	SetPacketData(pckInBlock.OrdPrc, sizeof(pckInBlock.OrdPrc), s9, DATA_TYPE_DOT, 2);	// �Ǽ�    
	SetPacketData(pckInBlock.ErxPrcCndiTpCode, sizeof(pckInBlock.ErxPrcCndiTpCode), s10, DATA_TYPE_STRING);	// ���ֿ�����  

	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_DATA ���� �´�.
		szTrNo,						// TR ��ȣ
		&pckInBlock,				// InBlock ������
		sizeof(pckInBlock),		// InBlock ������ ũ��
		bNext,						// ������ȸ ����
		"",							// ������ȸ Key
		30							// Timeout(��) : �ش� �ð�(��)���� �����Ͱ� ���� ������ Timeout�� �߻��Ѵ�. XM_TIMEOUT_DATA �޽����� �߻��Ѵ�.
		);

	((CListCtrl*)GetDlgItem(IDC_OUTBLOCK1))->DeleteAllItems();
	((CListCtrl*)GetDlgItem(IDC_OUTBLOCK2))->DeleteAllItems();

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
LRESULT CDlg_CEXAQ21200::OnXMReceiveData(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data�� ����
	if (wParam == REQUEST_DATA)
	{
		LPRECV_PACKET pRpData = (LPRECV_PACKET)lParam;

		if (strcmp(pRpData->szBlockName, NAME_CEXAQ21200OutBlock1) == 0)
		{
			//MessageBox("�������", "ok", MB_ICONSTOP);
			CListCtrl*		pList = (CListCtrl*)GetDlgItem(IDC_OUTBLOCK1);
			LPCEXAQ21200OutBlock1 pOutBlock = (LPCEXAQ21200OutBlock1)pRpData->lpData;

			int nItem = pList->InsertItem(pList->GetItemCount(), "");
			pList->SetItemText(nItem, 0, GetDispData(pOutBlock->QryTp, sizeof(pOutBlock->QryTp), DATA_TYPE_STRING));	
			pList->SetItemText(nItem, 1, GetDispData(pOutBlock->OrdAmt, sizeof(pOutBlock->OrdAmt), DATA_TYPE_LONG));	
			pList->SetItemText(nItem, 2, GetDispData(pOutBlock->RatVal, sizeof(pOutBlock->RatVal), DATA_TYPE_FLOAT, 2));
			pList->SetItemText(nItem, 3, GetDispData(pOutBlock->FnoIsuNo, sizeof(pOutBlock->FnoIsuNo), DATA_TYPE_STRING));	
			pList->SetItemText(nItem, 4, GetDispData(pOutBlock->BnsTpCode, sizeof(pOutBlock->BnsTpCode), DATA_TYPE_STRING));	
			pList->SetItemText(nItem, 5, GetDispData(pOutBlock->OrdPrc, sizeof(pOutBlock->OrdPrc), DATA_TYPE_FLOAT, 2));	
			pList->SetItemText(nItem, 6, GetDispData(pOutBlock->ErxPrcCndiTpCode, sizeof(pOutBlock->ErxPrcCndiTpCode), DATA_TYPE_STRING));	 
		}
		else if (strcmp(pRpData->szBlockName, NAME_CEXAQ21200OutBlock2) == 0)
		{
			CListCtrl*		 pList = (CListCtrl*)GetDlgItem(IDC_OUTBLOCK2);
			LPCEXAQ21200OutBlock2 pOutBlock = (LPCEXAQ21200OutBlock2)pRpData->lpData;	

			int nItem = pList->InsertItem(pList->GetItemCount(), "");
			pList->SetItemText(nItem, 0, GetDispData(pOutBlock->AcntNm, sizeof(pOutBlock->AcntNm), DATA_TYPE_STRING));	
			pList->SetItemText(nItem, 1, GetDispData(pOutBlock->QryDt, sizeof(pOutBlock->QryDt), DATA_TYPE_STRING)); 
			pList->SetItemText(nItem, 2, GetDispData(pOutBlock->NowPrc, sizeof(pOutBlock->NowPrc), DATA_TYPE_FLOAT, 2));	          
			pList->SetItemText(nItem, 3, GetDispData(pOutBlock->OrdAbleQty, sizeof(pOutBlock->OrdAbleQty), DATA_TYPE_LONG));       
			pList->SetItemText(nItem, 4, GetDispData(pOutBlock->NewOrdAbleQty, sizeof(pOutBlock->NewOrdAbleQty), DATA_TYPE_LONG));         
			pList->SetItemText(nItem, 5, GetDispData(pOutBlock->LqdtOrdAbleQty, sizeof(pOutBlock->LqdtOrdAbleQty), DATA_TYPE_LONG));      
			pList->SetItemText(nItem, 6, GetDispData(pOutBlock->UsePreargMgn, sizeof(pOutBlock->UsePreargMgn), DATA_TYPE_LONG));
			pList->SetItemText(nItem, 7, GetDispData(pOutBlock->UsePreargMnyMgn, sizeof(pOutBlock->UsePreargMnyMgn), DATA_TYPE_LONG));  
			pList->SetItemText(nItem, 8, GetDispData(pOutBlock->OrdAbleAmt, sizeof(pOutBlock->OrdAbleAmt), DATA_TYPE_LONG));		
			pList->SetItemText(nItem, 9, GetDispData(pOutBlock->MnyOrdAbleAmt, sizeof(pOutBlock->MnyOrdAbleAmt), DATA_TYPE_LONG));	
		}
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
LRESULT CDlg_CEXAQ21200::OnXMTimeoutData(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);

	return 0L;
}


void CDlg_CEXAQ21200::OnTimer(UINT_PTR nIDEvent)
{
	//switch (nIDEvent)
	//{
	//case 1:
	RequestData();
	//	break;
	//case 2:
	//	Request0167();
	//	break;
	//}

	CDialog::OnTimer(nIDEvent);
}