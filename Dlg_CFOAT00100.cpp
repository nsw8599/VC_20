// Dlg_CFOAQ10100.cpp : implementation file
//

#include "stdafx.h"
#include "xingapi_sample.h"
#include "Dlg_CFOAT00100.h"

#include "./Packet/CFOAT00100.h"
//#include "./packet/t0167.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CFOAT00100 dialog


IMPLEMENT_DYNCREATE(CDlg_CFOAT00100, CDialog)

CDlg_CFOAT00100::CDlg_CFOAT00100(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CFOAT00100::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_CFOAT00100)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_CFOAT00100::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CFOAT00100)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_INBLOCK_CODE, m_code);
	DDX_Control(pDX, IDC_INBLOCK_PRICE, m_price);
	DDX_Control(pDX, IDC_OUTBLOCK1, m_ctrlOutBlock1);
	DDX_Control(pDX, IDC_OUTBLOCK2, m_ctrlOutBlock2);
	DDX_Control(pDX, IDC_INBLOCK_QTY, m_qty);
}


BEGIN_MESSAGE_MAP(CDlg_CFOAT00100, CDialog)
	//{{AFX_MSG_MAP(CDlg_CFOAT00100)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceive100)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeout100)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_CFOAT00100 message handlers

BOOL CDlg_CFOAT00100::OnInitDialog()
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
	m_price.SetWindowTextA("0.20");
	m_qty.SetWindowTextA("0");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_CFOAT00100::OnButtonRequest()
{
	Request100();
}

//--------------------------------------------------------------------------------------
// ��Ʈ�� �ʱ�ȭ
//--------------------------------------------------------------------------------------
void CDlg_CFOAT00100::InitCtrls()
{
	//-----------------------------------------------------------
	// OutBlock1
	InsertColumn4List(this, IDC_OUTBLOCK1, 0, "�ɼ������ȣ			", FALSE, 16);    // [long  ,    4] CNT   
	InsertColumn4List(this, IDC_OUTBLOCK1, 1, "�Ÿű���				", FALSE, 16);    // [string,    8] ��¥  
	InsertColumn4List(this, IDC_OUTBLOCK1, 2, "�ֹ�����				", FALSE, 16.2);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 3, "�ֹ�����		       ", FALSE, 16);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 4, "�Ÿű���				", FALSE, 16);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 5, "�ֹ��Ϸù�ȣ			", FALSE, 16);    // [long  ,    4] IDX   
	// OutBlock2
	InsertColumn4List(this, IDC_OUTBLOCK2, 0, "�ֹ���ȣ				", FALSE, 16);    // [long  ,    8] �ð�          
	InsertColumn4List(this, IDC_OUTBLOCK2, 1, "�ֹ����ɱݾ�          ", FALSE, 16);    // [long  ,    8] ��          
	InsertColumn4List(this, IDC_OUTBLOCK2, 2, "�����ֹ����ɱݾ�		", FALSE, 16);    // [long  ,    8] ����          
	InsertColumn4List(this, IDC_OUTBLOCK2, 3, "�ֹ����ű�				", FALSE, 16);    // [long  ,    8] ����    
	InsertColumn4List(this, IDC_OUTBLOCK2, 4, "�����ֹ����ű�			", FALSE, 16);    // [long  ,   12] �����ŷ���  
	InsertColumn4List(this, IDC_OUTBLOCK2, 5, "�ֹ����ɼ���			", FALSE, 16);    // [long  ,   12] �ŷ����  

}

//--------------------------------------------------------------------------------------
// ������ ��ȸ
//--------------------------------------------------------------------------------------
void CDlg_CFOAT00100::Request100(BOOL bNext, CString a, CString b)
{
	//-----------------------------------------------------------
	// �Ⱓ���ְ�(CFOAT00100) ( attr,block,headtype=A )
	CFOAT00100InBlock1	pckInBlock;

	TCHAR	szTrNo[] = "CFOAT00100";

	//CString s1 = "1";
	CString s2 = "00151751313";
	CString s3 = "0716";
	//CString s4 = "1"; //1:�Ϲ�,2:�ݾ�
	//CString s5 = "0";
	//CString s6 = "0";
	//CString s7 = "201M9317";
	CString s8 = a; // 1:�ŵ�,2:�ż�
	CString s10 = b; //00:������,03:���尡(�ֹ��� 0)
	
	CString s7;		GetDlgItemText(IDC_INBLOCK_CODE, s7);
	CString s9;		GetDlgItemText(IDC_INBLOCK_PRICE, s9);
	CString s11;	GetDlgItemText(IDC_INBLOCK_QTY, s11);

	//-----------------------------------------------------------
	// ������ �ʱ�ȭ
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// ������ �Է�
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), s2, DATA_TYPE_STRING);	// ���ֿ�����
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), s3, DATA_TYPE_STRING);	  
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), s7, DATA_TYPE_STRING);	// ���ֿ�����      
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), s8, DATA_TYPE_STRING);	
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), s10, DATA_TYPE_STRING);      
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), s9, DATA_TYPE_DOT, 2);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), s11, DATA_TYPE_LONG);	

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
LRESULT CDlg_CFOAT00100::OnXMReceive100(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data�� ����
	if (wParam == REQUEST_DATA)
	{
		typedef struct
		{
			CFOAT00100OutBlock1	outBlock1;
			CFOAT00100OutBlock2	outBlock2;
		} CFOAT00100AllOutBlock, *LPCFOAT00100AllOutBlock;

		LPRECV_PACKET			pRpData = (LPRECV_PACKET)lParam;
		LPCFOAT00100AllOutBlock pAllOutBlock = (LPCFOAT00100AllOutBlock)pRpData->lpData;
		int						nDataLength = pRpData->nDataLength;
		int						nCol;

		//------------------------------------------------
		// OutBlock1
		nDataLength -= sizeof(CFOAT00100OutBlock1);
		if (nDataLength < 0)
		{
			return 0L;
		}

		nCol = 0;
		m_ctrlOutBlock1.InsertItem(0, "");
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoIsuNo, sizeof(pAllOutBlock->outBlock1.FnoIsuNo), DATA_TYPE_STRING));    // �ɼ������ȣ         
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.BnsTpCode, sizeof(pAllOutBlock->outBlock1.BnsTpCode), DATA_TYPE_STRING));    // �Ÿű���        
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoOrdPrc, sizeof(pAllOutBlock->outBlock1.FnoOrdPrc), DATA_TYPE_DOT, 2));    // �ֹ�����            
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.OrdQty, sizeof(pAllOutBlock->outBlock1.OrdQty), DATA_TYPE_LONG));    // �ֹ�����            
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.BnsTpCode, sizeof(pAllOutBlock->outBlock1.BnsTpCode), DATA_TYPE_STRING));    // �Ÿű���   
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.OrdSeqno, sizeof(pAllOutBlock->outBlock1.OrdSeqno), DATA_TYPE_LONG));    // �ֹ��Ϸù�ȣ  

																																											  //------------------------------------------------
																																											  // OutBlock1
		nDataLength -= sizeof(CFOAT00100OutBlock2);
		if (nDataLength < 0)
		{
			return 0L;
		}

		nCol = 0;
		m_ctrlOutBlock2.InsertItem(0, "");
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdNo, sizeof(pAllOutBlock->outBlock2.OrdNo), DATA_TYPE_LONG));    // �ֹ���ȣ     
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleAmt, sizeof(pAllOutBlock->outBlock2.OrdAbleAmt), DATA_TYPE_LONG));    // �ֹ����ɱݾ�        
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.MnyOrdAbleAmt, sizeof(pAllOutBlock->outBlock2.MnyOrdAbleAmt), DATA_TYPE_LONG)); //�����ֹ����ɱݾ�
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdMgn, sizeof(pAllOutBlock->outBlock2.OrdMgn), DATA_TYPE_LONG)); //�ֹ����ű�
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.MnyOrdMgn, sizeof(pAllOutBlock->outBlock2.MnyOrdMgn), DATA_TYPE_LONG)); //�����ֹ����ű�
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleQty, sizeof(pAllOutBlock->outBlock2.OrdAbleQty), DATA_TYPE_LONG));    // �ֹ����ɼ���    
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
LRESULT CDlg_CFOAT00100::OnXMTimeout100(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);
	GetParent()->SendMessage(WMU_SET_MESSAGE, (WPARAM)"", (LPARAM)"Timeout");

	return 0L;
}
