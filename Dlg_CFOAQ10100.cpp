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
	//m_QryTp = "1"; //1:잔고기준
	//m_OrdAmt = "1";
	//m_RatVal = "1";
	//m_BnsTpCode = "2"; // 매수
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
// 컨트롤 초기화
//--------------------------------------------------------------------------------------
void CDlg_CFOAQ10100::InitCtrls()
{
	//-----------------------------------------------------------
	// OutBlock1
	InsertColumn4List(this, IDC_OUTBLOCK1, 0, "조회구분				", FALSE, 16);    // [long  ,    4] CNT   
	InsertColumn4List(this, IDC_OUTBLOCK1, 1, "주문금액				", FALSE, 16);    // [string,    8] 날짜  
	InsertColumn4List(this, IDC_OUTBLOCK1, 2, "비율값				", FALSE, 19.8);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 3, "선물옵션종목번호       ", FALSE, 25);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 4, "매매구분				", FALSE, 16);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 5, "주문가				", FALSE, 13.2);    // [long  ,    4] IDX   
	InsertColumn4List(this, IDC_OUTBLOCK1, 6, "선물옵션호가유형코드   ", FALSE, 25);    // [long  ,    4] IDX   
	// OutBlock2
	InsertColumn4List(this, IDC_OUTBLOCK2, 0, "현재가				", FALSE, 15.2);    // [long  ,    8] 시가          
	InsertColumn4List(this, IDC_OUTBLOCK2, 1, "주문가능수량          ", FALSE, 16);    // [long  ,    8] 고가          
	InsertColumn4List(this, IDC_OUTBLOCK2, 2, "신규주문가능수량		", FALSE, 16);    // [long  ,    8] 저가          
	InsertColumn4List(this, IDC_OUTBLOCK2, 3, "청산주문가능수량       ", FALSE, 16);    // [long  ,    8] 종가    
	InsertColumn4List(this, IDC_OUTBLOCK2, 4, "사용예정증거금액		", FALSE, 16);    // [long  ,   12] 누적거래량  
	InsertColumn4List(this, IDC_OUTBLOCK2, 5, "사용예정현금증거금액	", FALSE, 16);    // [long  ,   12] 거래대금  
	InsertColumn4List(this, IDC_OUTBLOCK2, 6, "주문가능금액			", FALSE, 16);    // [float ,  6.2] 저가기준등락율
	InsertColumn4List(this, IDC_OUTBLOCK2, 7, "현금주문가능금액		", FALSE, 16);    // [float ,  6.2] 저가기준등락율

}

//--------------------------------------------------------------------------------------
// 데이터 조회
//--------------------------------------------------------------------------------------
void CDlg_CFOAQ10100::RequestData(BOOL bNext)
{
	//-----------------------------------------------------------
	// 기간별주가(CFOAQ10100) ( attr,block,headtype=A )
	CFOAQ10100InBlock1	pckInBlock;

	TCHAR	szTrNo[] = "CFOAQ10100";

	CString s1 = "1";
	CString s2 = "00151751313";
	CString s3 = "0716";
	CString s4 = "1"; //1:일반,2:금액
	CString s5 = "0";
	CString s6 = "0";
	//CString s7 = "201M9317";
	CString s8 = "2"; // 1:매도,2:매수
	//CString s9 = "0.25";
	CString s10 = "00"; //00:지정가,03:시장가(주문가 0)
	CString s7;		GetDlgItemText(IDC_INBLOCK_CODE, s7);           
	CString s9;		GetDlgItemText(IDC_INBLOCK_PRICE, s9);         

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), s1, DATA_TYPE_LONG);	// 단축코드  
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), s2, DATA_TYPE_STRING);	// 일주월구분
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), s3, DATA_TYPE_STRING);	// 일주월구분
	SetPacketData(pckInBlock.QryTp, sizeof(pckInBlock.QryTp), s4, DATA_TYPE_STRING);	// 날짜      
	SetPacketData(pckInBlock.OrdAmt, sizeof(pckInBlock.OrdAmt), s5, DATA_TYPE_LONG);	// IDX       
	SetPacketData(pckInBlock.RatVal, sizeof(pckInBlock.RatVal), s6, DATA_TYPE_DOT,8);	// 건수    
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), s7, DATA_TYPE_STRING);	// 일주월구분      
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), s8, DATA_TYPE_STRING);	// IDX       
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), s9, DATA_TYPE_DOT,2);	// 건수    
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), s10, DATA_TYPE_STRING);	// 일주월구분  

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
LRESULT CDlg_CFOAQ10100::OnXMReceiveData(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data를 받음
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
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.QryTp, sizeof(pAllOutBlock->outBlock1.QryTp), DATA_TYPE_STRING));    // [long  ,    5] 레코드갯수          
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.OrdAmt, sizeof(pAllOutBlock->outBlock1.OrdAmt), DATA_TYPE_LONG));    // [string,    2] 주문시장코드        
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.RatVal, sizeof(pAllOutBlock->outBlock1.RatVal), DATA_TYPE_DOT,8));    // [string,   20] 계좌번호            
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoIsuNo, sizeof(pAllOutBlock->outBlock1.FnoIsuNo), DATA_TYPE_STRING));    // [string,    8] 비밀번호            
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.BnsTpCode, sizeof(pAllOutBlock->outBlock1.BnsTpCode), DATA_TYPE_STRING));    // [string,   12] 선물옵션종목번호    
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoOrdPrc, sizeof(pAllOutBlock->outBlock1.FnoOrdPrc), DATA_TYPE_DOT,2));    // [string,    2] 선물옵션주문유형코드  
		m_ctrlOutBlock1.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoOrdprcPtnCode, sizeof(pAllOutBlock->outBlock1.FnoOrdprcPtnCode), DATA_TYPE_STRING));    // [long  ,   10] 원주문번호   

																																							  //------------------------------------------------
																																							  // OutBlock1
		nDataLength -= sizeof(CFOAQ10100OutBlock2);
		if (nDataLength < 0)
		{
			return 0L;
		}

		nCol = 0;
		m_ctrlOutBlock2.InsertItem(0, "");
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.FnoNowPrc, sizeof(pAllOutBlock->outBlock2.FnoNowPrc), DATA_TYPE_DOT,2));    // [long  ,    5] 레코드갯수      
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleQty, sizeof(pAllOutBlock->outBlock2.OrdAbleQty), DATA_TYPE_LONG));    // [long  ,   10] 주문번호        
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.NewOrdAbleQty, sizeof(pAllOutBlock->outBlock2.NewOrdAbleQty), DATA_TYPE_LONG));
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.LqdtOrdAbleQty, sizeof(pAllOutBlock->outBlock2.LqdtOrdAbleQty), DATA_TYPE_LONG));
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.UsePreargMgn, sizeof(pAllOutBlock->outBlock2.UsePreargMgn), DATA_TYPE_LONG));
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.UsePreargMnyMgn, sizeof(pAllOutBlock->outBlock2.UsePreargMnyMgn), DATA_TYPE_LONG));    // [long  ,   16] 주문가능금액    
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleAmt, sizeof(pAllOutBlock->outBlock2.OrdAbleAmt), DATA_TYPE_LONG));    // [long  ,   16] 현금주문가능금액
		m_ctrlOutBlock2.SetItemText(0, nCol++, GetDispData(pAllOutBlock->outBlock2.MnyOrdAbleAmt, sizeof(pAllOutBlock->outBlock2.MnyOrdAbleAmt), DATA_TYPE_LONG));    // [long  ,   16] 주문증거금        
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
