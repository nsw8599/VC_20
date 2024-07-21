// Dlg_0H0.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Dlg_EH0.h"

#include "./packet/EH0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlg_0H0 dialog

IMPLEMENT_DYNCREATE(CDlg_EH0, CDialog)

CDlg_EH0::CDlg_EH0(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_EH0::IDD, pParent)
{

}


void CDlg_EH0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTBLOCK, m_ctrlOutBlock);
	DDX_Control(pDX, IDC_EDIT_CODE, m_code);
}


BEGIN_MESSAGE_MAP(CDlg_EH0, CDialog)
	//	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealEH0)
END_MESSAGE_MAP()


// CDlg_EH0 message handlers


BOOL CDlg_EH0::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_code.SetWindowTextA("201M9312");
	m_strCode = "201M9312";
	// TODO:  Add extra initialization here
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlg_EH0::OnDestroy()
{
	UnadviseEH0();
	CDialog::OnDestroy();

	// TODO: Add your message handler code here


}


void CDlg_EH0::OnButtonRequest()
{
	// TODO: Add your control notification handler code here
	UnadviseEH0();
	AdviseEH0();
}

//--------------------------------------------------------------------------------------
// 컨트롤 초기화
//--------------------------------------------------------------------------------------
void CDlg_EH0::InitCtrls()
{
	//-------------------------------------------------------------------------
	// OutBlock
	m_ctrlOutBlock.InsertColumn(0, "필드  ", LVCFMT_LEFT, 150);
	m_ctrlOutBlock.InsertColumn(1, "데이터", LVCFMT_LEFT, 200);

	int nRow = 0;
	m_ctrlOutBlock.InsertItem(nRow++, "호가시간");
	m_ctrlOutBlock.InsertItem(nRow++, "매도호가1");
	m_ctrlOutBlock.InsertItem(nRow++, "매수호가1");
	m_ctrlOutBlock.InsertItem(nRow++, "매도호가수량1");
	m_ctrlOutBlock.InsertItem(nRow++, "매수호가수량1");
	m_ctrlOutBlock.InsertItem(nRow++, "매도호가2");
	m_ctrlOutBlock.InsertItem(nRow++, "매수호가2");
	m_ctrlOutBlock.InsertItem(nRow++, "매도호가수량2");
	m_ctrlOutBlock.InsertItem(nRow++, "매수호가수량2");
	m_ctrlOutBlock.InsertItem(nRow++, "매도호가3");
	m_ctrlOutBlock.InsertItem(nRow++, "매수호가3");
	m_ctrlOutBlock.InsertItem(nRow++, "매도호가수량3");
	m_ctrlOutBlock.InsertItem(nRow++, "매수호가수량3");
	m_ctrlOutBlock.InsertItem(nRow++, "매도호가총수량");
	m_ctrlOutBlock.InsertItem(nRow++, "매수호가총수량");
	m_ctrlOutBlock.InsertItem(nRow++, "단축코드");
}

//--------------------------------------------------------------------------------------
// 데이터 Advise
//--------------------------------------------------------------------------------------
void CDlg_EH0::AdviseEH0()
{
	TCHAR	szTrCode[] = "EH0";

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
		//sizeof(EH0_InBlock)		// 종목코드 길이
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
void CDlg_EH0::UnadviseEH0()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	if (m_strCode.IsEmpty())
	{
		return;
	}

	TCHAR	szTrCode[] = "EH0";

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		m_strCode,					// 종목코드
		m_strCode.GetLength()
		//sizeof(EH0_InBlock)		// 종목코드 길이
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
LRESULT CDlg_EH0::OnXMReceiveRealEH0(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;

	if (strcmp(pRealPacket->szTrCode, "EH0") == 0)
	{

		LPEH0_OutBlock pOutBlock = (LPEH0_OutBlock)pRealPacket->pszData;
		int nRow = 0;
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->hotime, sizeof(pOutBlock->hotime), DATA_TYPE_STRING));    // 호가시간
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_FLOAT, 2));    // 매도호가1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_FLOAT, 2));    // 매수호가1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));    // 매도호가수량1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));    // 매수호가수량1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho2, sizeof(pOutBlock->offerho2), DATA_TYPE_FLOAT, 2));    // 매도호가2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho2, sizeof(pOutBlock->bidho2), DATA_TYPE_FLOAT, 2));    // 매수호가2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem2, sizeof(pOutBlock->offerrem2), DATA_TYPE_LONG));    // 매도호가수량2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem2, sizeof(pOutBlock->bidrem2), DATA_TYPE_LONG));    // 매수호가수량2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho3, sizeof(pOutBlock->offerho3), DATA_TYPE_FLOAT, 2));    // 매도호가3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho3, sizeof(pOutBlock->bidho3), DATA_TYPE_FLOAT, 2));    // 매수호가3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem3, sizeof(pOutBlock->offerrem3), DATA_TYPE_LONG));    // 매도호가수량3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem3, sizeof(pOutBlock->bidrem3), DATA_TYPE_LONG));    // 매수호가수량3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->totofferrem, sizeof(pOutBlock->totofferrem), DATA_TYPE_LONG));    // 매도호가총수량
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->totbidrem, sizeof(pOutBlock->totbidrem), DATA_TYPE_LONG));    // 매수호가총수량
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->optcode, sizeof(pOutBlock->optcode), DATA_TYPE_STRING));    // 
	}
	return 0L;
}