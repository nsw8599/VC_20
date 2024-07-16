// Dlg_0C0.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Dlg_OC0.h"

#include "./packet/OC0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlg_0C0 dialog

IMPLEMENT_DYNCREATE(CDlg_OC0, CDialog)

CDlg_OC0::CDlg_OC0(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_OC0::IDD, pParent)
{

}


void CDlg_OC0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTBLOCK, m_ctrlOutBlock);
	DDX_Control(pDX, IDC_EDIT_CODE, m_code);
}


BEGIN_MESSAGE_MAP(CDlg_OC0, CDialog)
	//	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealData)
END_MESSAGE_MAP()


// CDlg_OC0 message handlers


BOOL CDlg_OC0::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_strCode = "201MA322";
	m_code.SetWindowTextA(m_strCode);
	// TODO:  Add extra initialization here
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlg_OC0::OnDestroy()
{
	UnadviseData();
	CDialog::OnDestroy();

	// TODO: Add your message handler code here


}


void CDlg_OC0::OnButtonRequest()
{
	// TODO: Add your control notification handler code here
	UnadviseData();
	AdviseData();
}



//--------------------------------------------------------------------------------------
// 컨트롤 초기화
//--------------------------------------------------------------------------------------
void CDlg_OC0::InitCtrls()
{
	//-------------------------------------------------------------------------
	// OutBlock
	m_ctrlOutBlock.InsertColumn(0, "필드  ", LVCFMT_LEFT, 150);
	m_ctrlOutBlock.InsertColumn(1, "데이터", LVCFMT_LEFT, 200);

	int nRow = 0;
	m_ctrlOutBlock.InsertItem(nRow++, "체결시간          ");
	m_ctrlOutBlock.InsertItem(nRow++, "전일대비구분      ");
	m_ctrlOutBlock.InsertItem(nRow++, "전일대비          ");
	m_ctrlOutBlock.InsertItem(nRow++, "등락율            ");
	m_ctrlOutBlock.InsertItem(nRow++, "현재가            ");
	m_ctrlOutBlock.InsertItem(nRow++, "시가              ");
	m_ctrlOutBlock.InsertItem(nRow++, "고가              ");
	m_ctrlOutBlock.InsertItem(nRow++, "저가              ");
	m_ctrlOutBlock.InsertItem(nRow++, "체결구분          ");
	m_ctrlOutBlock.InsertItem(nRow++, "체결량            ");
	m_ctrlOutBlock.InsertItem(nRow++, "누적거래량        ");
	m_ctrlOutBlock.InsertItem(nRow++, "누적거래대금      ");
	m_ctrlOutBlock.InsertItem(nRow++, "매도누적체결량    ");
	m_ctrlOutBlock.InsertItem(nRow++, "매도누적체결건수  ");
	m_ctrlOutBlock.InsertItem(nRow++, "매수누적체결량    ");
	m_ctrlOutBlock.InsertItem(nRow++, "매수누적체결건수  ");
	m_ctrlOutBlock.InsertItem(nRow++, "체결강도          ");
	m_ctrlOutBlock.InsertItem(nRow++, "매도호가1         ");
	m_ctrlOutBlock.InsertItem(nRow++, "매수호가1         ");
	m_ctrlOutBlock.InsertItem(nRow++, "미결제약정수량    ");
	m_ctrlOutBlock.InsertItem(nRow++, "KOSPI200지수      ");
	m_ctrlOutBlock.InsertItem(nRow++, "KOSPI등가            ");
	m_ctrlOutBlock.InsertItem(nRow++, "이론가            ");
	m_ctrlOutBlock.InsertItem(nRow++, "내재변동성         ");
	m_ctrlOutBlock.InsertItem(nRow++, "미결제약정증감         ");
	m_ctrlOutBlock.InsertItem(nRow++, "시간가치    ");
	m_ctrlOutBlock.InsertItem(nRow++, "장운영정보        ");
	m_ctrlOutBlock.InsertItem(nRow++, "전일동시간대거래량");
	m_ctrlOutBlock.InsertItem(nRow++, "단축코드          ");
}

//--------------------------------------------------------------------------------------
// 데이터 Advise
//--------------------------------------------------------------------------------------
void CDlg_OC0::AdviseData()
{
	TCHAR	szTrCode[] = "OC0";

	//-----------------------------------------------------------
	// 데이터 취득
	CString strCode; GetDlgItemText(IDC_EDIT_CODE, strCode);

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		strCode,					// 종목코드
		strCode.GetLength()
		//sizeof(OC0_InBlock)		// 종목코드 길이
		);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	else
	{
		m_strCode = strCode;
	}
}

//--------------------------------------------------------------------------------------
// 데이터 Unadvise
//--------------------------------------------------------------------------------------
void CDlg_OC0::UnadviseData()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	if (m_strCode.IsEmpty())
	{
		return;
	}

	TCHAR	szTrCode[] = "OC0";

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		m_strCode,					// 종목코드
		m_strCode.GetLength()
		//sizeof(OC0_InBlock)		// 종목코드 길이
		);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	else
	{
		m_strCode.Empty();
	}

}

//--------------------------------------------------------------------------------------
// 데이터를 받음
//--------------------------------------------------------------------------------------
LRESULT CDlg_OC0::OnXMReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;

	if (strcmp(pRealPacket->szTrCode, "OC0") == 0)
	{
		LPOC0_OutBlock pOutBlock = (LPOC0_OutBlock)pRealPacket->pszData;
		int nRow = 0;
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->chetime, sizeof(pOutBlock->chetime), DATA_TYPE_STRING));    // 체결시간          
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->sign, sizeof(pOutBlock->sign), DATA_TYPE_STRING));    // 전일대비구분      
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->change, sizeof(pOutBlock->change), DATA_TYPE_FLOAT, 2));    // 전일대비          
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->drate, sizeof(pOutBlock->drate), DATA_TYPE_FLOAT, 2));    // 등락율            
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->price, sizeof(pOutBlock->price), DATA_TYPE_FLOAT, 2));    // 현재가            
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->open, sizeof(pOutBlock->open), DATA_TYPE_FLOAT, 2));    // 시가              
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->high, sizeof(pOutBlock->high), DATA_TYPE_FLOAT, 2));    // 고가              
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->low, sizeof(pOutBlock->low), DATA_TYPE_FLOAT, 2));    // 저가              
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->cgubun, sizeof(pOutBlock->cgubun), DATA_TYPE_STRING));    // 체결구분          
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->cvolume, sizeof(pOutBlock->cvolume), DATA_TYPE_LONG));    // 체결량            
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->volume, sizeof(pOutBlock->volume), DATA_TYPE_LONG));    // 누적거래량        
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->value, sizeof(pOutBlock->value), DATA_TYPE_LONG));    // 누적거래대금      
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->mdvolume, sizeof(pOutBlock->mdvolume), DATA_TYPE_LONG));    // 매도누적체결량    
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->mdchecnt, sizeof(pOutBlock->mdchecnt), DATA_TYPE_LONG));    // 매도누적체결건수  
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->msvolume, sizeof(pOutBlock->msvolume), DATA_TYPE_LONG));    // 매수누적체결량    
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->mschecnt, sizeof(pOutBlock->mschecnt), DATA_TYPE_LONG));    // 매수누적체결건수  
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->cpower, sizeof(pOutBlock->cpower), DATA_TYPE_FLOAT, 2));    // 체결강도          
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_FLOAT, 2));    // 매도호가1         
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_FLOAT, 2));    // 매수호가1         
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->openyak, sizeof(pOutBlock->openyak), DATA_TYPE_LONG));    // 미결제약정수량    
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->k200jisu, sizeof(pOutBlock->k200jisu), DATA_TYPE_FLOAT, 2));    // KOSPI200지수      
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->eqva, sizeof(pOutBlock->eqva), DATA_TYPE_FLOAT, 2));    // 이론가            
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->theoryprice, sizeof(pOutBlock->theoryprice), DATA_TYPE_FLOAT, 2));    // 괴리율            
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->impv, sizeof(pOutBlock->impv), DATA_TYPE_FLOAT, 2));    // 시장BASIS         
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->openyakcha, sizeof(pOutBlock->openyakcha), DATA_TYPE_LONG));    // 이론BASIS         
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->timevalue, sizeof(pOutBlock->timevalue), DATA_TYPE_FLOAT,2));    // 미결제약정증감    
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->jgubun, sizeof(pOutBlock->jgubun), DATA_TYPE_STRING));    // 장운영정보        
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->jnilvolume, sizeof(pOutBlock->jnilvolume), DATA_TYPE_LONG));    // 전일동시간대거래량
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->optcode, sizeof(pOutBlock->optcode), DATA_TYPE_STRING));    // 단축코드          
	}

	return 0L;
}
