// Dlg_CFOAT00100.cpp : implementation file
//

#include "stdafx.h"
#include "xingapi_sample.h"
#include "Dlg_CFOAT00300.h"

#include "./Packet/CFOAT00300.h"
//#include "./packet/t0167.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CFOAT00300 dialog


IMPLEMENT_DYNCREATE(CDlg_CFOAT00300, CDialog)

CDlg_CFOAT00300::CDlg_CFOAT00300(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CFOAT00300::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_CFOAT00300)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_CFOAT00300::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CFOAT00300)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_INBLOCK_CODE, m_code);
	DDX_Control(pDX, IDC_INBLOCK_ORGORDNO, m_orgordno);
	DDX_Control(pDX, IDC_OUTBLOCK1, m_ctrlOutBlock1);
	DDX_Control(pDX, IDC_OUTBLOCK2, m_ctrlOutBlock2);
	DDX_Control(pDX, IDC_INBLOCK_CANCQTY, m_cancqty);
}


BEGIN_MESSAGE_MAP(CDlg_CFOAT00300, CDialog)
	//{{AFX_MSG_MAP(CDlg_CFOAT00300)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceive300)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeout300)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_CFOAT00300 message handlers

BOOL CDlg_CFOAT00300::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCtrls();
	//m_RecCnt="1";
	//m_AcntNo = "00151751313";
	//m_Pwd = "0716";
	//m_QryTp = "1"; //1:잔고기준
	//m_OrdAmt = "1";
	//m_RatVal = "1";
	//m_BnsTpCode = "2"; // 매수
	//m_FnoOrdprcPtnCode = "00"; //

	m_code.SetWindowTextA("201M9317");
	m_orgordno.SetWindowTextA("");
	m_cancqty.SetWindowTextA("0");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_CFOAT00300::OnButtonRequest()
{
	Request300();
}

//--------------------------------------------------------------------------------------
// 컨트롤 초기화
//--------------------------------------------------------------------------------------
void CDlg_CFOAT00300::InitCtrls()
{
	//-----------------------------------------------------------
	// OutBlock1
	InsertColumn4List(this, IDC_OUTBLOCK1, 0, "옵션종목번호			", FALSE, 16);      
	InsertColumn4List(this, IDC_OUTBLOCK1, 1, "원주문번호				", FALSE, 16);      
	InsertColumn4List(this, IDC_OUTBLOCK1, 2, "취소수량				", FALSE, 16);      
																				  // OutBlock2
	InsertColumn4List(this, IDC_OUTBLOCK2, 0, "주문번호				", FALSE, 16);    // [long  ,    8] 시가          
	InsertColumn4List(this, IDC_OUTBLOCK2, 1, "주문가능금액          ", FALSE, 16);    // [long  ,    8] 고가          
	InsertColumn4List(this, IDC_OUTBLOCK2, 2, "현금주문가능금액		", FALSE, 16);    // [long  ,    8] 저가          
	InsertColumn4List(this, IDC_OUTBLOCK2, 3, "주문증거금				", FALSE, 16);    // [long  ,    8] 종가    
	InsertColumn4List(this, IDC_OUTBLOCK2, 4, "현금주문증거금			", FALSE, 16);    // [long  ,   12] 누적거래량  
	InsertColumn4List(this, IDC_OUTBLOCK2, 5, "주문가능수량			", FALSE, 16);    // [long  ,   12] 거래대금  

}

//--------------------------------------------------------------------------------------
// 데이터 조회
//--------------------------------------------------------------------------------------
void CDlg_CFOAT00300::Request300(BOOL bNext)
{
	//-----------------------------------------------------------
	// 기간별주가(CFOAT00300) ( attr,block,headtype=A )
	CFOAT00300InBlock1	pckInBlock;

	TCHAR	szTrNo[] = "CFOAT00300";

	//CString s1 = "1";
	CString s2 = "00151751313";
	CString s3 = "0716";
	//CString s4 = "1"; //1:일반,2:금액
	//CString s5 = "0";
	//CString s6 = "0";
	//CString s7 = "201M9317";
	//CString s8 = "2"; // 1:매도,2:매수
	//CString s10 = "00"; //00:지정가,03:시장가(주문가 0)

	CString s7;		GetDlgItemText(IDC_INBLOCK_CODE, s7); //종목번호
	//CString s9;		GetDlgItemText(IDC_INBLOCK_PRICE, s9);
	//CString s11;	GetDlgItemText(IDC_INBLOCK_QTY, s11);

	CString s12; 	GetDlgItemText(IDC_INBLOCK_ORGORDNO, s12); //취소할 주문번호
	CString s13; 	GetDlgItemText(IDC_INBLOCK_CANCQTY, s13);  //수량

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), s2, DATA_TYPE_STRING);	
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), s3, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), s7, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.OrgOrdNo, sizeof(pckInBlock.OrgOrdNo), s12, DATA_TYPE_LONG);
	SetPacketData(pckInBlock.CancQty, sizeof(pckInBlock.CancQty), s13, DATA_TYPE_LONG);

	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부
		"",							// 다음조회 Key
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
		);

	((CListCtrl*)GetDlgItem(IDC_OUTBLOCK1))->DeleteAllItems();
	((CListCtrl*)GetDlgItem(IDC_OUTBLOCK2))->DeleteAllItems();

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
}

//--------------------------------------------------------------------------------------
// 데이터를 받음
//--------------------------------------------------------------------------------------
LRESULT CDlg_CFOAT00300::OnXMReceive300(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data를 받음
	if (wParam == REQUEST_DATA)
	{
		typedef struct
		{
			CFOAT00300OutBlock1	outBlock1;
			CFOAT00300OutBlock2	outBlock2;
		} CFOAT00300AllOutBlock, *LPCFOAT00300AllOutBlock;

		LPRECV_PACKET			pRpData = (LPRECV_PACKET)lParam;
		LPCFOAT00300AllOutBlock pAllOutBlock = (LPCFOAT00300AllOutBlock)pRpData->lpData;
		int						nDataLength = pRpData->nDataLength;
		int						nCol;

		//------------------------------------------------
		// OutBlock1
		nDataLength -= sizeof(CFOAT00300OutBlock1);
		if (nDataLength < 0)
		{
			return 0L;
		}

		nCol = 0;
		m_ctrlOutBlock1.InsertItem(0, "");
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoIsuNo, sizeof(pAllOutBlock->outBlock1.FnoIsuNo), DATA_TYPE_STRING));            
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.OrgOrdNo, sizeof(pAllOutBlock->outBlock1.OrgOrdNo), DATA_TYPE_LONG));         
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.CancQty, sizeof(pAllOutBlock->outBlock1.CancQty), DATA_TYPE_LONG));   

																																							//------------------------------------------------
																																							// OutBlock1
		nDataLength -= sizeof(CFOAT00300OutBlock2);
		if (nDataLength < 0)
		{
			return 0L;
		}

		nCol = 0;
		m_ctrlOutBlock2.InsertItem(0, "");
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdNo, sizeof(pAllOutBlock->outBlock2.OrdNo), DATA_TYPE_LONG));    // 주문번호     
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleAmt, sizeof(pAllOutBlock->outBlock2.OrdAbleAmt), DATA_TYPE_LONG));    // 주문가능금액        
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.MnyOrdAbleAmt, sizeof(pAllOutBlock->outBlock2.MnyOrdAbleAmt), DATA_TYPE_LONG)); //현금주문가능금액
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdMgn, sizeof(pAllOutBlock->outBlock2.OrdMgn), DATA_TYPE_LONG)); //주문증거금
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.MnyOrdMgn, sizeof(pAllOutBlock->outBlock2.MnyOrdMgn), DATA_TYPE_LONG)); //현금주문증거금
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleQty, sizeof(pAllOutBlock->outBlock2.OrdAbleQty), DATA_TYPE_LONG));    // 주문가능수량    
	}

	//-------------------------------------------------------------------------------------
	// 메시지를 받음
	else if (wParam == MESSAGE_DATA)
	{
		LPMSG_PACKET pMsg = (LPMSG_PACKET)lParam;

		CString strMsg((char*)pMsg->lpszMessageData, pMsg->nMsgLength);
		GetParent()->SendMessage(WMU_SET_MESSAGE, (WPARAM)pMsg->szMsgCode, (LPARAM)(LPCTSTR)strMsg);

		g_iXingAPI.ReleaseMessageData(lParam);
	}

	//-------------------------------------------------------------------------------------
	// System Error를 받음
	else if (wParam == SYSTEM_ERROR_DATA)
	{
		LPMSG_PACKET pMsg = (LPMSG_PACKET)lParam;

		CString strMsg((char*)pMsg->lpszMessageData, pMsg->nMsgLength);
		GetParent()->SendMessage(WMU_SET_MESSAGE, (WPARAM)pMsg->szMsgCode, (LPARAM)(LPCTSTR)strMsg);

		g_iXingAPI.ReleaseMessageData(lParam);
	}

	//-------------------------------------------------------------------------------------
	// Release Data를 받음
	else if (wParam == RELEASE_DATA)
	{
		g_iXingAPI.ReleaseRequestData((int)lParam);
	}

	return 0L;
}

//--------------------------------------------------------------------------------------
// Timeout 발생
//--------------------------------------------------------------------------------------
LRESULT CDlg_CFOAT00300::OnXMTimeout300(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);
	GetParent()->SendMessage(WMU_SET_MESSAGE, (WPARAM)"", (LPARAM)"Timeout");

	return 0L;
}
