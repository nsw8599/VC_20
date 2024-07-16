// Dlg_CFOAQ10100.cpp : implementation file
//

#include "stdafx.h"
#include "xingapi_sample.h"
#include "Dlg_CFOAQ10100.h"

#include "./Packet/CFOAQ10100.h"
//#include "./packet/t0167.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CFOAQ10100 dialog


IMPLEMENT_DYNCREATE(CDlg_CFOAQ10100, CDialog)

CDlg_CFOAQ10100::CDlg_CFOAQ10100(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CFOAQ10100::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_CFOAQ10100)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_CFOAQ10100::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CFOAQ10100)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_INBLOCK_CODE, m_code);
	DDX_Control(pDX, IDC_INBLOCK_PRICE, m_price);
	DDX_Control(pDX, IDC_OUTBLOCK1, m_ctrlOutBlock1);
	DDX_Control(pDX, IDC_OUTBLOCK2, m_ctrlOutBlock2);
}


BEGIN_MESSAGE_MAP(CDlg_CFOAQ10100, CDialog)
	//{{AFX_MSG_MAP(CDlg_CFOAQ10100)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceiveData)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeoutData)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST_NEXT, &CDlg_CFOAQ10100::OnBnClickedButtonRequestNext)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_CFOAQ10100 message handlers

BOOL CDlg_CFOAQ10100::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCtrls();
	//m_RecCnt="1";
	//m_AcntNo = "00151751313";
	//m_Pwd = "0716";
	//m_QryTp = "1"; //1:�ܰ����
	//m_OrdAmt = "1";
	//m_RatVal = "1";
	//m_BnsTpCode = "2"; // �ż�
	//m_FnoOrdprcPtnCode = "00"; //

	m_code.SetWindowTextA("201M9317");
	m_price.SetWindowTextA("0.25");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_CFOAQ10100::OnButtonRequest()
{
	RequestData();
	SetTimer(1, 5000, NULL);
}


void CDlg_CFOAQ10100::OnBnClickedButtonRequestNext()
{
	KillTimer(1);
}

//--------------------------------------------------------------------------------------
// ��Ʈ�� �ʱ�ȭ
//--------------------------------------------------------------------------------------
void CDlg_CFOAQ10100::InitCtrls()
{
	//-----------------------------------------------------------
	// OutBlock1
	InsertColumn4List(this, IDC_OUTBLOCK1, 0, "��ȸ����				", FALSE, 16);    // [long  ,    4] CNT   
	InsertColumn4List(this, IDC_OUTBLOCK1, 1, "�ֹ��ݾ�				", FALSE, 16);    // [string,    8] ��¥  
	InsertColumn4List(this, IDC_OUTBLOCK1, 2, "������				", FALSE, 19.8);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 3, "�����ɼ������ȣ       ", FALSE, 25);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 4, "�Ÿű���				", FALSE, 16);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 5, "�ֹ���				", FALSE, 13.2);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 6, "�����ɼ�ȣ�������ڵ�   ", FALSE, 25);    // [long  ,    4] IDX   
	// OutBlock2
	InsertColumn4List(this, IDC_OUTBLOCK2, 0, "���簡				", FALSE, 15.2);    // [long  ,    8] �ð�          
	InsertColumn4List(this, IDC_OUTBLOCK2, 1, "�ֹ����ɼ���          ", FALSE, 16);    // [long  ,    8] ��          
	InsertColumn4List(this, IDC_OUTBLOCK2, 2, "�ű��ֹ����ɼ���		", FALSE, 16);    // [long  ,    8] ����          
	InsertColumn4List(this, IDC_OUTBLOCK2, 3, "û���ֹ����ɼ���       ", FALSE, 16);    // [long  ,    8] ����    
	InsertColumn4List(this, IDC_OUTBLOCK2, 4, "��뿹�����űݾ�		", FALSE, 16);    // [long  ,   12] �����ŷ���  
	InsertColumn4List(this, IDC_OUTBLOCK2, 5, "��뿹���������űݾ�	", FALSE, 16);    // [long  ,   12] �ŷ����  
	InsertColumn4List(this, IDC_OUTBLOCK2, 6, "�ֹ����ɱݾ�			", FALSE, 16);    // [float ,  6.2] �������ص����
	InsertColumn4List(this, IDC_OUTBLOCK2, 7, "�����ֹ����ɱݾ�		", FALSE, 16);    // [float ,  6.2] �������ص����

}

//--------------------------------------------------------------------------------------
// ������ ��ȸ
//--------------------------------------------------------------------------------------
void CDlg_CFOAQ10100::RequestData(BOOL bNext)
{
	//-----------------------------------------------------------
	// �Ⱓ���ְ�(CFOAQ10100) ( attr,block,headtype=A )
	CFOAQ10100InBlock1	pckInBlock;

	TCHAR	szTrNo[] = "CFOAQ10100";

	CString s1 = "1";
	CString s2 = "00151751313";
	CString s3 = "0716";
	CString s4 = "1"; //1:�Ϲ�,2:�ݾ�
	CString s5 = "0";
	CString s6 = "0";
	//CString s7 = "201M9317";
	CString s8 = "2"; // 1:�ŵ�,2:�ż�
	//CString s9 = "0.25";
	CString s10 = "00"; //00:������,03:���尡(�ֹ��� 0)
	CString s7;		GetDlgItemText(IDC_INBLOCK_CODE, s7);           
	CString s9;		GetDlgItemText(IDC_INBLOCK_PRICE, s9);         

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
	SetPacketData(pckInBlock.RatVal, sizeof(pckInBlock.RatVal), s6, DATA_TYPE_DOT,8);	// �Ǽ�    
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), s7, DATA_TYPE_STRING);	// ���ֿ�����      
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), s8, DATA_TYPE_STRING);	// IDX       
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), s9, DATA_TYPE_DOT,2);	// �Ǽ�    
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), s10, DATA_TYPE_STRING);	// ���ֿ�����  

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
LRESULT CDlg_CFOAQ10100::OnXMReceiveData(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data�� ����
	if (wParam == REQUEST_DATA)
	{
		typedef struct
		{
			CFOAQ10100OutBlock1	outBlock1;
			CFOAQ10100OutBlock2	outBlock2;
		} CFOAQ10100AllOutBlock, *LPCFOAQ10100AllOutBlock;

		LPRECV_PACKET			pRpData = (LPRECV_PACKET)lParam;
		LPCFOAQ10100AllOutBlock pAllOutBlock = (LPCFOAQ10100AllOutBlock)pRpData->lpData;
		int						nDataLength = pRpData->nDataLength;
		int						nCol;

		//------------------------------------------------
		// OutBlock1
		nDataLength -= sizeof(CFOAQ10100OutBlock1);
		if (nDataLength < 0)
		{
			return 0L;
		}

		nCol = 0;
		m_ctrlOutBlock1.InsertItem(0, "");
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.QryTp, sizeof(pAllOutBlock->outBlock1.QryTp), DATA_TYPE_STRING));    // [long  ,    5] ���ڵ尹��          
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.OrdAmt, sizeof(pAllOutBlock->outBlock1.OrdAmt), DATA_TYPE_LONG));    // [string,    2] �ֹ������ڵ�        
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.RatVal, sizeof(pAllOutBlock->outBlock1.RatVal), DATA_TYPE_DOT,8));    // [string,   20] ���¹�ȣ            
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoIsuNo, sizeof(pAllOutBlock->outBlock1.FnoIsuNo), DATA_TYPE_STRING));    // [string,    8] ��й�ȣ            
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.BnsTpCode, sizeof(pAllOutBlock->outBlock1.BnsTpCode), DATA_TYPE_STRING));    // [string,   12] �����ɼ������ȣ    
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoOrdPrc, sizeof(pAllOutBlock->outBlock1.FnoOrdPrc), DATA_TYPE_DOT,2));    // [string,    2] �����ɼ��ֹ������ڵ�  
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoOrdprcPtnCode, sizeof(pAllOutBlock->outBlock1.FnoOrdprcPtnCode), DATA_TYPE_STRING));    // [long  ,   10] ���ֹ���ȣ   

																																							  //------------------------------------------------
																																							  // OutBlock1
		nDataLength -= sizeof(CFOAQ10100OutBlock2);
		if (nDataLength < 0)
		{
			return 0L;
		}

		nCol = 0;
		m_ctrlOutBlock2.InsertItem(0, "");
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.FnoNowPrc, sizeof(pAllOutBlock->outBlock2.FnoNowPrc), DATA_TYPE_DOT,2));    // [long  ,    5] ���ڵ尹��      
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleQty, sizeof(pAllOutBlock->outBlock2.OrdAbleQty), DATA_TYPE_LONG));    // [long  ,   10] �ֹ���ȣ        
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.NewOrdAbleQty, sizeof(pAllOutBlock->outBlock2.NewOrdAbleQty), DATA_TYPE_LONG));
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.LqdtOrdAbleQty, sizeof(pAllOutBlock->outBlock2.LqdtOrdAbleQty), DATA_TYPE_LONG));
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.UsePreargMgn, sizeof(pAllOutBlock->outBlock2.UsePreargMgn), DATA_TYPE_LONG));
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.UsePreargMnyMgn, sizeof(pAllOutBlock->outBlock2.UsePreargMnyMgn), DATA_TYPE_LONG));    // [long  ,   16] �ֹ����ɱݾ�    
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleAmt, sizeof(pAllOutBlock->outBlock2.OrdAbleAmt), DATA_TYPE_LONG));    // [long  ,   16] �����ֹ����ɱݾ�
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.MnyOrdAbleAmt, sizeof(pAllOutBlock->outBlock2.MnyOrdAbleAmt), DATA_TYPE_LONG));    // [long  ,   16] �ֹ����ű�        
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
LRESULT CDlg_CFOAQ10100::OnXMTimeoutData(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);
	GetParent()->SendMessage(WMU_SET_MESSAGE, (WPARAM)"", (LPARAM)"Timeout");

	return 0L;
}




void CDlg_CFOAQ10100::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		RequestData();
		break;
	//case 2:
	//	Request0167();
	//	break;
	}
	CDialog::OnTimer(nIDEvent);
}
