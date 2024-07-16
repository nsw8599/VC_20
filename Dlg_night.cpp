// Dlg_night.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Dlg_night.h"

#include "./Packet/t2830.h"			//옵션 Price
#include "./Packet/t2831.h"			//옵션 호가
#include "./Packet/t2816.h"			//선물 투자자종합
#include "./Packet/CEXAQ21200.h"	//주문가능수량
#include "./Packet/t8415.h"
#include "./Packet/t2813.h"			// 시간대별 투자자별 동향
#include "./Packet/CEXAQ21100.h"
#include "./Packet/CEXAQ21200.h"
#include "./Packet/CEXAQ31200.h"
#include "./Packet/CEXAT11100.h"
#include "./Packet/CEXAT11200.h"
#include "./Packet/CEXAT11300.h"
#include "./packet/CFOFQ02400.h"
#include "./packet/t0167.h"
#include "./packet/OVC.h"			// SNP
#include "./Packet/t2301.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
//#include <Eigen/Dense>
#include <thread>
#include <random>
#include <chrono>

using namespace std;
//using namespace Eigen;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlg_night dialog

IMPLEMENT_DYNCREATE(CDlg_night, CDialog)

CDlg_night::CDlg_night(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_night::IDD, pParent)
{
}


void CDlg_night::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INBLOCK_FOCODE, m_focode);
	DDX_Control(pDX, IDC_INBLOCK_FOCODE2, m_focode2);
	DDX_Control(pDX, IDC_2830OUTBLOCK, m_2830listctrl);
	DDX_Control(pDX, IDC_2830OUTBLOCK2, m_2830listctrl_);
	DDX_Control(pDX, IDC_2816OUTBLOCK, m_2816listctrl);
	DDX_Control(pDX, IDC_INBLOCK_QTY, m_qty);
	DDX_Control(pDX, IDC_INBLOCK_PRICE, m_ordprc);
	DDX_Control(pDX, IDC_INBLOCK_ORDNO, m_ordno);
	DDX_Control(pDX, IDC_TIME, m_stime);
	DDX_Control(pDX, IDC_INDEX, m_index);
	DDX_Control(pDX, IDC_PERSNP, m_persnp);
	DDX_Control(pDX, IDC_FORNBUY, m_fornbuy);
	DDX_Control(pDX, IDC_FORNBUY2, m_fornbuy2);
	DDX_Control(pDX, IDC_FORNBUY3, m_fornbuy3);
	DDX_Control(pDX, IDC_FORNBUY4, m_fornbuy4);
	DDX_Control(pDX, IDC_FORNBUY5, m_fornbuy5);
	DDX_Control(pDX, IDC_FORNBUY6, m_fornbuy6);
	DDX_Control(pDX, IDC_FORNBUY7, m_fornbuy7);
	DDX_Control(pDX, IDC_FORNBUY8, m_fornbuy8);
	DDX_Control(pDX, IDC_FORNBUY9, m_fornbuy9);
	DDX_Control(pDX, IDC_FORNBUY10, m_fornbuy10);
	DDX_Control(pDX, IDC_STSTXT, m_ststxt);
}

BEGIN_MESSAGE_MAP(CDlg_night, CDialog)
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceiveData)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeoutData)
	ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealData)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, &CDlg_night::OnBnClickedButtonRequest)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlg_night::OnBnClickedButtonStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_REQUEST2, &CDlg_night::OnBnClickedButtonRequest2)
	ON_BN_CLICKED(IDC_SAVE_CSV, &CDlg_night::OnBnClickedSaveCsv)
	ON_BN_CLICKED(IDC_BTTNPROFIT2, &CDlg_night::OnBnClickedBttnprofit2)
	ON_BN_CLICKED(IDC_BTTNPROFIT3, &CDlg_night::OnBnClickedBttnprofit3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDlg_night::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN19, &CDlg_night::OnDeltaposSpin19)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN18, &CDlg_night::OnDeltaposSpin18)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN20, &CDlg_night::OnDeltaposSpin20)
	ON_NOTIFY(NM_CLICK, IDC_2830OUTBLOCK, &CDlg_night::OnClick2830outblock)
	ON_NOTIFY(NM_CLICK, IDC_2830OUTBLOCK2, &CDlg_night::OnClick2830outblock2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN21, &CDlg_night::OnDeltaposSpin21)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN22, &CDlg_night::OnDeltaposSpin22)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_REQUEST11, &CDlg_night::OnBnClickedButtonRequest11)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_2830OUTBLOCK, &CDlg_night::OnCustomdraw2830outblock)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_2830OUTBLOCK2, &CDlg_night::OnCustomdraw2830outblock2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_night message handlers

BOOL CDlg_night::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitCtrls();
	m_focode.SetWindowTextA(CallCode);
	m_focode2.SetWindowTextA(PutCode);
	acnt = 5000000;
	lBalance = 0, lLqdt = 0;
	lCallQty = 0, lPutQty = 0;
	lCmpVol = 144;
	idx = 0;
    gIter = 0;

	bCall = TRUE, bPut = TRUE;

	bToken = FALSE;//옵션전광판 콜/풋코드를 받은뒤 bToken값을 1로 변경(코드 유지)
	bAutoToken = TRUE; //자동옵션매수 설정 on/off 볼린저밴드상하단 1포인트 이상 초과시

	fCallAvrPrc = 0.0, fPutAvrPrc = 0.0, fCmpPrc = 0.0;
	fCallOpen = 0.0, fPutOpen = 0.0;
    fCho9 = 0.0, fPho9 = 0.0;
    lCho9 = 0, lPho9 = 0;
	nCurMin = 0;

	CTime t = CTime::GetCurrentTime();
	strDate = t.Format("%Y%m%d");

	strMonth = "W2MON"; //yyyymm, 위클리 W1MON, W1THU, W3MON, W3THU, W4MON, W4THU *************************************************************************************************

	CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITSETUP); str.Format("%.2f", 0.2); pEdit1->SetWindowText(str);//옵션 기준가격
	pEdit2 = (CEdit*)GetDlgItem(IDC_EDITRANGE); str.Format("%.2f", 0.35); pEdit2->SetWindowText(str);//원하는 이익
	pEdit3 = (CEdit*)GetDlgItem(IDC_EDITRATIO); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
	pEdit4 = (CEdit*)GetDlgItem(IDC_EDITGAP); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격

	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC); str.Format("%.2f", 0.25); pEdit1->SetWindowText(str);//옵션 기준가격 설정 **************************************************************************************

	pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;

	m_ststxt.SetWindowTextA("Ready...");

	Request2301(strMonth);//옵션전광판

	lArFornBuy = new long[1320];
	memset(lArFornBuy, 0, 1320 * sizeof(long));

	return TRUE;  
}

void CDlg_night::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	delete[] lArFornBuy;
	lArFornBuy = NULL;

	while (!nQSellQty.empty()) nQSellQty.pop(); queue<int>().swap(nQSellQty);
	while (!fQSellPrc.empty()) fQSellPrc.pop(); queue<float>().swap(fQSellPrc);
}

//--------------------------------------------------------------------------------------
// 컨트롤 초기화
//--------------------------------------------------------------------------------------
void CDlg_night::InitCtrls()
{
	m_2816listctrl.InsertColumn(0, "   ", LVCFMT_LEFT, 80);
	m_2816listctrl.InsertColumn(1, "개인", LVCFMT_LEFT, 80);
	m_2816listctrl.InsertColumn(2, "외인", LVCFMT_LEFT, 80);
	m_2816listctrl.InsertColumn(3, "기관", LVCFMT_LEFT, 80);
	m_2816listctrl.InsertItem(0, "매수"); //ms
	m_2816listctrl.InsertItem(1, "매도"); //md
	m_2816listctrl.InsertItem(2, "순매수"); //svolume

	m_2830listctrl.InsertColumn(0, "필드명", LVCFMT_LEFT, 150);
	m_2830listctrl.InsertColumn(1, "데이터", LVCFMT_LEFT, 180);
	m_2830listctrl.InsertItem(0, "종목명"); //hname
	m_2830listctrl.InsertItem(1, "현재가"); //price
	m_2830listctrl.InsertItem(2, "전일대비"); //change
	m_2830listctrl.InsertItem(3, "주간종가"); //jnilclose
	m_2830listctrl.InsertItem(4, "등락율"); //diff
	m_2830listctrl.InsertItem(5, "거래량"); //volume
	m_2830listctrl.InsertItem(6, "거래대금"); //value
	m_2830listctrl.InsertItem(7, "시가"); //open
	m_2830listctrl.InsertItem(8, "고가"); //high
	m_2830listctrl.InsertItem(9, "저가"); //low
	m_2830listctrl.InsertItem(10, "KOSPI200지수"); // kospijisu
	m_2830listctrl.InsertItem(11, "야간선물현재가"); //cmeprice
	m_2830listctrl.InsertItem(12, "야간선물전일대비"); //cmechange
	m_2830listctrl.InsertItem(13, "야간선물등락율"); //cmediff
	m_2830listctrl.InsertItem(14, "단축코드"); //focode
    m_2830listctrl.InsertItem(15, "매도호가수량"); //focode
    m_2830listctrl.InsertItem(16, "매수호가수량"); //focode

	m_2830listctrl_.InsertColumn(0, "필드명", LVCFMT_LEFT, 150);
	m_2830listctrl_.InsertColumn(1, "데이터", LVCFMT_LEFT, 180);
	m_2830listctrl_.InsertItem(0, "종목명"); //hname
	m_2830listctrl_.InsertItem(1, "현재가"); //price
	m_2830listctrl_.InsertItem(2, "전일대비"); //change
	m_2830listctrl_.InsertItem(3, "주간종가"); //jnilclose
	m_2830listctrl_.InsertItem(4, "등락율"); //diff
	m_2830listctrl_.InsertItem(5, "거래량"); //volume
	m_2830listctrl_.InsertItem(6, "거래대금"); //value
	m_2830listctrl_.InsertItem(7, "시가"); //open
	m_2830listctrl_.InsertItem(8, "고가"); //high
	m_2830listctrl_.InsertItem(9, "저가"); //low
	m_2830listctrl_.InsertItem(10, "KOSPI200지수"); // kospijisu
	m_2830listctrl_.InsertItem(11, "야간선물현재가"); //cmeprice
	m_2830listctrl_.InsertItem(12, "야간선물전일대비"); //cmechange
	m_2830listctrl_.InsertItem(13, "야간선물등락율"); //cmediff
	m_2830listctrl_.InsertItem(14, "단축코드"); //focode
    m_2830listctrl_.InsertItem(15, "매도호가수량"); //focode
    m_2830listctrl_.InsertItem(16, "매수호가수량"); //focode
}

void CDlg_night::Request100(CString code, CString bns, BOOL bNext)//매수주문
{
	CEXAT11100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAT11100";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	// 데이터 입력
	CString prc; GetDlgItemTextA(IDC_INBLOCK_PRICE, prc);
	CString qty; GetDlgItemTextA(IDC_INBLOCK_QTY, qty);

	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), pwdnum, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), bns, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.ErxPrcCndiTpCode, sizeof(pckInBlock.ErxPrcCndiTpCode), "2", DATA_TYPE_STRING); //1:시장가 2:지정가
	SetPacketData(pckInBlock.OrdPrc, sizeof(pckInBlock.OrdPrc), prc, DATA_TYPE_DOT, 2);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), qty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		CString temp;
		temp.Format("%d", nRqID);
		MessageBox("조회실패"+ temp, "에러", MB_ICONSTOP);
	}
	ID100 = nRqID;
}

void CDlg_night::Request100_(CString code, CString bns, CString prc, int qty, BOOL bNext)
{
	CEXAT11100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAT11100";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	// 데이터 입력

	CString strQty;
	strQty.Format("%d", qty);

	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), pwdnum, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), bns, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.ErxPrcCndiTpCode, sizeof(pckInBlock.ErxPrcCndiTpCode), "2", DATA_TYPE_STRING); //1:시장가 2:지정가
	SetPacketData(pckInBlock.OrdPrc, sizeof(pckInBlock.OrdPrc), prc, DATA_TYPE_DOT, 2);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), strQty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);


	if (bns == "2")
	{
		if (code == CallCode)	lCallQty += (long)qty;
		if (code == PutCode)	lPutQty += (long)qty;
	}
	if (bns == "1")
	{
		if (code == CallCode)	lCallQty -= (long)qty;
		if (code == PutCode)	lPutQty -= (long)qty;
	}

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID100 = nRqID;
}

void CDlg_night::Request100_(CString code, CString bns, float prc, int qty, BOOL bNext)
{
	CEXAT11100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAT11100";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	// 데이터 입력

	CString strQty;
	strQty.Format("%d", qty);
	CString strPrc; strPrc.Format("%.2f", prc);

	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), pwdnum, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), bns, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.ErxPrcCndiTpCode, sizeof(pckInBlock.ErxPrcCndiTpCode), "2", DATA_TYPE_STRING); //1:시장가 2:지정가
	SetPacketData(pckInBlock.OrdPrc, sizeof(pckInBlock.OrdPrc), strPrc, DATA_TYPE_DOT, 2);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), strQty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);


	if (bns == "2")
	{
		if (code == CallCode)	lCallQty += (long)qty;
		if (code == PutCode)	lPutQty += (long)qty;
	}
	if (bns == "1")
	{
		if (code == CallCode)	lCallQty -= (long)qty;
		if (code == PutCode)	lPutQty -= (long)qty;
	}

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID100 = nRqID;
}


void CDlg_night::Request200(CString code, BOOL bNext)//정정주문
{
	CEXAT11200InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAT11200";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	CString orgordno; GetDlgItemTextA(IDC_INBLOCK_ORDNO, orgordno);
	// 데이터 입력
	CString prc; GetDlgItemTextA(IDC_INBLOCK_PRICE, prc);
	CString qty; GetDlgItemTextA(IDC_INBLOCK_QTY, qty);
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);				// [string,   20] 계좌번호            
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), pwdnum, DATA_TYPE_STRING);							// [string,    8] 비밀번호            
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);					// [string,   12] 선물옵션종목번호    
	SetPacketData(pckInBlock.OrgOrdNo, sizeof(pckInBlock.OrgOrdNo), orgordno, DATA_TYPE_LONG);					// [long  ,   10] 원주문번호          
	SetPacketData(pckInBlock.OrdPrc, sizeof(pckInBlock.OrdPrc), prc, DATA_TYPE_DOT, 2);							// [double, 15.2] 주문가격        

																												// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID200 = nRqID;
}

void CDlg_night::Request300(CString code, CString orgordno, BOOL bNext)//취소주문
{
	CEXAT11300InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAT11300";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	// 데이터 입력
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), pwdnum, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.OrgOrdNo, sizeof(pckInBlock.OrgOrdNo), orgordno, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID300 = nRqID;
}

void CDlg_night::Request600(BOOL bNext)
{
	CEXAQ21100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAQ21100";
	char				szNextKey[] = "";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);						// [long  ,    5] 레코드갯수      
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);					// [string,   20] 계좌번호        
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), pwdnum, DATA_TYPE_STRING);						// [string,    8] 입력비밀번호   
	SetPacketData(pckInBlock.ChoicInptTpCode, sizeof(pckInBlock.ChoicInptTpCode), "1", DATA_TYPE_STRING);	// [string,    1] 1:계좌
	SetPacketData(pckInBlock.PrdtExecTpCode, sizeof(pckInBlock.PrdtExecTpCode), "2", DATA_TYPE_STRING);		// [string,    1] 체결구분   0:전체,1:체결,2:미체결     
	SetPacketData(pckInBlock.StnlnSeqTp, sizeof(pckInBlock.StnlnSeqTp), "1", DATA_TYPE_STRING);				// [string,    1] 정렬순서구분    0:순,1:역순

																											// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);


	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID600 = nRqID;
}

void CDlg_night::Request21200(CString code, BOOL bNext)
{
	CEXAQ21200InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAQ21200";
	char				szNextKey[] = "";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);	//   
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), pwdnum, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.QryTp, sizeof(pckInBlock.QryTp), "1", DATA_TYPE_STRING);	//  
	SetPacketData(pckInBlock.OrdAmt, sizeof(pckInBlock.OrdAmt), "0", DATA_TYPE_LONG);	//  
	SetPacketData(pckInBlock.RatVal, sizeof(pckInBlock.RatVal), "0", DATA_TYPE_DOT, 8);	// 비율    
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);	// 종목번호     
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), "1", DATA_TYPE_STRING);	// 매매구분      1:매도, 2:매수 
	SetPacketData(pckInBlock.OrdPrc, sizeof(pckInBlock.OrdPrc), "0.00", DATA_TYPE_DOT, 2);	// 주문가  
	SetPacketData(pckInBlock.ErxPrcCndiTpCode, sizeof(pckInBlock.ErxPrcCndiTpCode), "2", DATA_TYPE_STRING);	// 지정가  

	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	if (bNext == FALSE)
	{
		//m_600listctrl.DeleteAllItems();
	}

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID21200 = nRqID;
}

void CDlg_night::Request21200_(CString code, BOOL bNext)
{
	CEXAQ21200InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAQ21200";
	char				szNextKey[] = "";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);	//   
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), pwdnum, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.QryTp, sizeof(pckInBlock.QryTp), "1", DATA_TYPE_STRING);	//  
	SetPacketData(pckInBlock.OrdAmt, sizeof(pckInBlock.OrdAmt), "0", DATA_TYPE_LONG);	//  
	SetPacketData(pckInBlock.RatVal, sizeof(pckInBlock.RatVal), "0", DATA_TYPE_DOT, 8);	// 비율    
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);	// 종목번호     
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), "2", DATA_TYPE_STRING);	// 매매구분      1:매도, 2:매수 
	SetPacketData(pckInBlock.OrdPrc, sizeof(pckInBlock.OrdPrc), "0.00", DATA_TYPE_DOT, 2);	// 주문가  
	SetPacketData(pckInBlock.ErxPrcCndiTpCode, sizeof(pckInBlock.ErxPrcCndiTpCode), "2", DATA_TYPE_STRING);	// 지정가  

	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	if (bNext == FALSE)
	{
		//m_600listctrl.DeleteAllItems();
	}

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID21200 = nRqID;
}

void CDlg_night::Request31200(BOOL bNext)
{
	CEXAQ31200InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CEXAQ31200";
	char				szNextKey[] = "";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);	//   
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), acntnum, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.InptPwd, sizeof(pckInBlock.InptPwd), pwdnum, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.BalEvalTp, sizeof(pckInBlock.BalEvalTp), "1", DATA_TYPE_STRING);	//  
	SetPacketData(pckInBlock.FutsPrcEvalTp, sizeof(pckInBlock.FutsPrcEvalTp), "1", DATA_TYPE_STRING);	//    

	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	if (bNext == FALSE)
	{
		//m_600listctrl.DeleteAllItems();
	}

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID31200 = nRqID;
}

void CDlg_night::Request2816(BOOL bNext)
{
	t2816InBlock	pckInBlock;

	TCHAR			szTrNo[] = "t2816";
	char			szNextKey[] = "";

	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	SetPacketData(pckInBlock.dummy, sizeof(pckInBlock.dummy), "", DATA_TYPE_STRING);

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부 : 다음조회일 경우에 세팅한다.
		szNextKey,					// 다음조회 Key : Header Type이 B 일 경우엔 이전 조회때 받은 Next Key를 넣어준다.
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
		);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID2816 = nRqID;
}

void CDlg_night::Request2830(BOOL bNext)
{
	t2830InBlock	pckInBlock;

	TCHAR			szTrNo[] = "t2830";
	char			szNextKey[] = "";

	CString str_shcode; GetDlgItemText(IDC_INBLOCK_FOCODE, str_shcode);
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.focode, sizeof(pckInBlock.focode), str_shcode, DATA_TYPE_STRING);

	//블럭 지우기
	//((CListCtrl*)GetDlgItem(IDC_2830OUTBLOCK))->DeleteAllItems();

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부 : 다음조회일 경우에 세팅한다.
		szNextKey,					// 다음조회 Key : Header Type이 B 일 경우엔 이전 조회때 받은 Next Key를 넣어준다.
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
		);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "2830에러", MB_ICONSTOP);
	}
	ID2830 = nRqID;
}

void CDlg_night::Request2831(BOOL bNext)
{
    t2831InBlock	pckInBlock;

    TCHAR			szTrNo[] = "t2831";
    char			szNextKey[] = "";

    CString str_shcode; GetDlgItemText(IDC_INBLOCK_FOCODE, str_shcode);
    FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

    //-----------------------------------------------------------
    // 데이터 입력
    SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), str_shcode, DATA_TYPE_STRING);

    //블럭 지우기
    //((CListCtrl*)GetDlgItem(IDC_2830OUTBLOCK))->DeleteAllItems();

    //-----------------------------------------------------------
    // 데이터 전송
    int nRqID = g_iXingAPI.Request(
        GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
        szTrNo,						// TR 번호
        &pckInBlock,				// InBlock 데이터
        sizeof(pckInBlock),		// InBlock 데이터 크기
        bNext,						// 다음조회 여부 : 다음조회일 경우에 세팅한다.
        szNextKey,					// 다음조회 Key : Header Type이 B 일 경우엔 이전 조회때 받은 Next Key를 넣어준다.
        30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
    );

    //-----------------------------------------------------------
    // Request ID가 0보다 작을 경우에는 에러이다.
    if (nRqID < 0)
    {
        MessageBox("조회실패", "2830에러", MB_ICONSTOP);
    }
    ID2831 = nRqID;
}

void CDlg_night::Request2830_(BOOL bNext)
{
	t2830InBlock	pckInBlock;

	TCHAR			szTrNo[] = "t2830";
	char			szNextKey[] = "";

	CString str_shcode; GetDlgItemText(IDC_INBLOCK_FOCODE2, str_shcode);
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.focode, sizeof(pckInBlock.focode), str_shcode, DATA_TYPE_STRING);

	//블럭 지우기
	//((CListCtrl*)GetDlgItem(IDC_2830OUTBLOCK))->DeleteAllItems();

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부 : 다음조회일 경우에 세팅한다.
		szNextKey,					// 다음조회 Key : Header Type이 B 일 경우엔 이전 조회때 받은 Next Key를 넣어준다.
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "2831_에러", MB_ICONSTOP);
	}
	ID2830_ = nRqID;
}

void CDlg_night::Request2831_(BOOL bNext)
{
    t2831InBlock	pckInBlock;

    TCHAR			szTrNo[] = "t2831";
    char			szNextKey[] = "";

    CString str_shcode; GetDlgItemText(IDC_INBLOCK_FOCODE2, str_shcode);
    FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

    //-----------------------------------------------------------
    // 데이터 입력
    SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), str_shcode, DATA_TYPE_STRING);

    //블럭 지우기
    //((CListCtrl*)GetDlgItem(IDC_2830OUTBLOCK))->DeleteAllItems();

    //-----------------------------------------------------------
    // 데이터 전송
    int nRqID = g_iXingAPI.Request(
        GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
        szTrNo,						// TR 번호
        &pckInBlock,				// InBlock 데이터
        sizeof(pckInBlock),		// InBlock 데이터 크기
        bNext,						// 다음조회 여부 : 다음조회일 경우에 세팅한다.
        szNextKey,					// 다음조회 Key : Header Type이 B 일 경우엔 이전 조회때 받은 Next Key를 넣어준다.
        30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
    );

    //-----------------------------------------------------------
    // Request ID가 0보다 작을 경우에는 에러이다.
    if (nRqID < 0)
    {
        MessageBox("조회실패", "2831_에러", MB_ICONSTOP);
    }
    ID2831_ = nRqID;
}

void CDlg_night::Request2813(BOOL bNext)
{
	//투자자종합
	t2813InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t2813";

	// 데이터 취득
	int n1 = nCurMin * 2;
	CString strcnt;
	strcnt.Format("%d", n1);

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.gubun1, sizeof(pckInBlock.gubun1), "1", DATA_TYPE_STRING); //1:수량, 2:금액
	SetPacketData(pckInBlock.gubun2, sizeof(pckInBlock.gubun2), "0", DATA_TYPE_STRING); //0:금일, 1:전일
	SetPacketData(pckInBlock.cts_time, sizeof(pckInBlock.cts_time), " ", DATA_TYPE_STRING);
	SetPacketData(pckInBlock.cnt, sizeof(pckInBlock.cnt), strcnt, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.gubun3, sizeof(pckInBlock.gubun3), "C", DATA_TYPE_STRING);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	//((CListCtrl*)GetDlgItem(IDC_1601))->DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID2813 = nRqID;
}

//--------------------------------------------------------------------------------------
// 데이터를 받음
//--------------------------------------------------------------------------------------
LRESULT CDlg_night::OnXMReceiveData(WPARAM wParam, LPARAM lParam)
{
	if (wParam == REQUEST_DATA)
	{
		LPRECV_PACKET pRpData = (LPRECV_PACKET)lParam;
		if (pRpData->nRqID == ID2816)
			Receive2816(pRpData);
		if (pRpData->nRqID == ID2830)
			Receive2830(pRpData);
		if (pRpData->nRqID == ID2830_)
			Receive2830_(pRpData);
        if (pRpData->nRqID == ID2831)
            Receive2831(pRpData);
        if (pRpData->nRqID == ID2831_)
            Receive2831_(pRpData);
		if (pRpData->nRqID == ID100)
			Receive100(pRpData);
		if (pRpData->nRqID == ID600)
			Receive600(pRpData);
		if (pRpData->nRqID == ID21200)
			Receive21200(pRpData);
		if (pRpData->nRqID == ID31200)
			Receive31200(pRpData);
		if (pRpData->nRqID == ID0167)
			Receive0167(pRpData);
		if (pRpData->nRqID == ID2813)
			Receive2813(pRpData);
		if (pRpData->nRqID == ID2301)
			Receive2301(pRpData);
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

void CDlg_night::Receive31200(LPRECV_PACKET pRpData)// header B type
{
	//-------------------------------------------------------------------------------------
	// 보유옵션 평가액
	LPBYTE			lpData = pRpData->lpData;
	int				nDataLength = pRpData->nDataLength;
	int				nOffset = 0;
	int				nBlockSize = 0;
	int				nCol = 0;
	int				nRow = 0;
	int				nCount = 0;
	char			szCount[6] = { 0 };

	// 연속키를 저장한다.
	strcpy_s(m_szContKey, pRpData->szContKey);
	//GetDlgItem(IDC_BUTTON_REQUEST_NEXT)->EnableWindow(pRpData->cCont[0] == 'Y');

	//------------------------------------------------
	// OutBlock1
	nBlockSize = sizeof(CEXAQ31200OutBlock1);
	nDataLength -= nBlockSize;
	// 받은 데이터 크기가 Block 크기보다 작다면 처리하지 않는다.
	if (nDataLength < 0)		return;

	LPCEXAQ31200OutBlock1 pOutBlock1 = (LPCEXAQ31200OutBlock1)(lpData + nOffset);
	nOffset += nBlockSize;

	nCol = 0;
	//------------------------------------------------
	// OutBlock2
	// 받은 데이터 크기가 Block 크기보다 작다면 처리하지 않는다.
	nBlockSize = sizeof(CEXAQ31200OutBlock2);
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	LPCEXAQ31200OutBlock2 pOutBlock2 = (LPCEXAQ31200OutBlock2)(lpData + nOffset);
	nOffset += nBlockSize;

	// OutBlock3
	// Count 계산
	nBlockSize = 5;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	CopyMemory(szCount, lpData + nOffset, 5);
	nCount = atoi(szCount);
	nOffset += nBlockSize;

	// Data
	nBlockSize = sizeof(CEXAQ31200OutBlock3) * nCount;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	LPCEXAQ31200OutBlock3 pOutBlock3 = (LPCEXAQ31200OutBlock3)(lpData + nOffset);
	nOffset += nBlockSize;

	for (int i = 0; i < nCount; i++)
	{
		if (GetDispData(pOutBlock3->FnoIsuNo, sizeof(pOutBlock3->FnoIsuNo), DATA_TYPE_STRING) == CallCode)
		{
			CString str1, str2;
			str1 = GetDispData(pOutBlock3->UnsttQty, sizeof(pOutBlock3->UnsttQty), DATA_TYPE_LONG);//미결제수량(총수량 lCallQty, lPutQty)
			str2 = GetDispData(pOutBlock3->FnoAvrPrc, sizeof(pOutBlock3->FnoAvrPrc), DATA_TYPE_DOT, 8);//평단가(fCallAvrPrc, fPutAvrPrc)

			CEdit *pEdit1, *pEdit2;
			pEdit1 = (CEdit*)GetDlgItem(IDC_CALLQTY); //********************************************************************* 콜 수량
			lCallQty = atol(str1);
			if (GetDispData(pOutBlock3->BnsTpCode, sizeof(pOutBlock3->BnsTpCode), DATA_TYPE_STRING) == "1")
			{
				lCallQty = lCallQty * -1;
				str1 = "-" + str1;
			}
			pEdit1->SetWindowText(str1);

			pEdit2 = (CEdit*)GetDlgItem(IDC_CALLPRICE2);
			fCallAvrPrc = (float)atof(str2);
			CString c1; c1.Format("%.3f", fCallAvrPrc);
			pEdit2->SetWindowText(c1);

			pEdit1 = NULL, pEdit2 = NULL;
		}

		if (GetDispData(pOutBlock3->FnoIsuNo, sizeof(pOutBlock3->FnoIsuNo), DATA_TYPE_STRING) == PutCode)
		{
			CString str1, str2;
			str1 = GetDispData(pOutBlock3->UnsttQty, sizeof(pOutBlock3->UnsttQty), DATA_TYPE_LONG);//미결제수량(총수량 lCallQty, lPutQty)
			str2 = GetDispData(pOutBlock3->FnoAvrPrc, sizeof(pOutBlock3->FnoAvrPrc), DATA_TYPE_DOT, 8);//평단가(fCallAvrPrc, fPutAvrPrc)

			CEdit *pEdit1, *pEdit2;
			pEdit1 = (CEdit*)GetDlgItem(IDC_PUTQTY);//********************************************************************* 풋 수량
			lPutQty = atol(str1);
			if (GetDispData(pOutBlock3->BnsTpCode, sizeof(pOutBlock3->BnsTpCode), DATA_TYPE_STRING) == "1")
			{
				lPutQty = lPutQty * -1;
				str1 = "-" + str1;
			}
			pEdit1->SetWindowText(str1);

			pEdit2 = (CEdit*)GetDlgItem(IDC_PUTPRICE2);
			fPutAvrPrc = (float)atof(str2);
			CString c1; c1.Format("%.3f", fPutAvrPrc);
			pEdit2->SetWindowText(c1);

			pEdit1 = NULL, pEdit2 = NULL;
		}		
		
	}

	return;
}

void CDlg_night::Receive100(LPRECV_PACKET pRpData)
{
	typedef struct
	{
		CEXAT11100OutBlock1	outBlock1;
		CEXAT11100OutBlock2	outBlock2;
	} CEXAT11100AllOutBlock, *LPCEXAT11100AllOutBlock;

	LPCEXAT11100AllOutBlock pAllOutBlock = (LPCEXAT11100AllOutBlock)pRpData->lpData;
	int						nDataLength = pRpData->nDataLength;
	//int						nCol;

	//------------------------------------------------
	// OutBlock1
	nDataLength -= sizeof(CEXAT11100OutBlock1);
	if (nDataLength < 0)
	{
		return;
	}

	//nCol = 0;
	//int nRow = m_100listctrl.InsertItem(m_100listctrl.GetItemCount(), "");
	//m_100listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoIsuNo, sizeof(pAllOutBlock->outBlock1.FnoIsuNo), DATA_TYPE_STRING));		// 옵션종목번호      
	//m_100listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock1.OrdPrc, sizeof(pAllOutBlock->outBlock1.OrdPrc), DATA_TYPE_DOT, 2));			// 주문가격            
	//m_100listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock1.OrdQty, sizeof(pAllOutBlock->outBlock1.OrdQty), DATA_TYPE_LONG));			// 주문수량     
	//m_100listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdNo, sizeof(pAllOutBlock->outBlock2.OrdNo), DATA_TYPE_LONG));				// 주문번호     
	////m_100listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock2.MnyOrdAbleAmt, sizeof(pAllOutBlock->outBlock2.MnyOrdAbleAmt), DATA_TYPE_LONG));    // 현금주문가능금액    
	////m_100listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock2.MnyOrdMgn, sizeof(pAllOutBlock->outBlock2.MnyOrdMgn), DATA_TYPE_LONG));    // 현금주문증거금    
}

void CDlg_night::Receive21200(LPRECV_PACKET pRpData)
{
	typedef struct
	{
		CEXAQ21200OutBlock1	outBlock1;
		CEXAQ21200OutBlock2	outBlock2;
	} CEXAQ21200AllOutBlock, *LPCEXAQ21200AllOutBlock;

	LPCEXAQ21200AllOutBlock pAllOutBlock = (LPCEXAQ21200AllOutBlock)pRpData->lpData;
	int						nDataLength = pRpData->nDataLength;
	//int						nCol;

    CString str1, str2, str3;
	//------------------------------------------------ OutBlock1
	nDataLength -= sizeof(CEXAQ21200OutBlock1);
	if (nDataLength < 0)
	{
		return;
	}
	//str3 = GetDispData(pAllOutBlock->outBlock1.FnoIsuNo, sizeof(pAllOutBlock->outBlock1.FnoIsuNo), DATA_TYPE_STRING);// [string,   12] 선물옵션종목번호	

																																
	//------------------------------------------------ OutBlock2
	nDataLength -= sizeof(CEXAQ21200OutBlock2);
	if (nDataLength < 0)
	{
		return;
	}

	//if (str3 == CallCode) {
	str1 = GetDispData(pAllOutBlock->outBlock2.LqdtOrdAbleQty, sizeof(pAllOutBlock->outBlock2.LqdtOrdAbleQty), DATA_TYPE_LONG);//청산가능
	
	str2 = GetDispData(pAllOutBlock->outBlock2.OrdAbleAmt, sizeof(pAllOutBlock->outBlock2.OrdAbleAmt), DATA_TYPE_LONG);//주문가능금액


	lLqdt = atol(str1);
	CEdit *pEdit1, *pEdit2;
	pEdit1 = (CEdit*)GetDlgItem(IDC_LQDTQTY); // ************************************************************************* 청산가능 수량
	pEdit1->SetWindowText(str1);

	lBalance = atol(str2);      lBalance /= 3;
    str2.Format("%d", lBalance);
    pEdit2 = (CEdit*)GetDlgItem(IDC_BUDGET2); pEdit2->SetWindowText(str2);

	pEdit1 = NULL, pEdit2 = NULL;

	if (lLqdt == 0 && lLqdt == lCallQty + lPutQty)
	{
		bCall = TRUE;
		bPut = TRUE;
	}

}

void CDlg_night::Receive600(LPRECV_PACKET pRpData)
{
	typedef struct
	{
		CEXAQ21100OutBlock1	outBlock1;
		CEXAQ21100OutBlock2	outBlock2;
		char				sCountOutBlock3[5];
		CEXAQ21100OutBlock3	outBlock3[1];
	} CEXAQ21100AllOutBlock, *LPCEXAQ21100AllOutBlock;

	LPCEXAQ21100AllOutBlock pAllOutBlock = (LPCEXAQ21100AllOutBlock)pRpData->lpData;

	int						nDataLength = pRpData->nDataLength;
	//int						nCol;
	//int						nRow;
	int						nCount;
	char					szCount[6] = { 0 };

	//strcpy(m_szContKey, pRpData->szContKey);
	//GetDlgItem(IDC_BUTTON_REQUEST_3)->EnableWindow(pRpData->cCont[0] == 'Y');

	// OutBlock2
	nDataLength -= sizeof(CEXAQ21100OutBlock2);
	if (nDataLength < 0)
	{
		return;
	}
	//CEdit *pEdit1;
	//pEdit1 = (CEdit*)GetDlgItem(IDC_INBLOCK_QTY);
	//pEdit1->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OrdQty, sizeof(pAllOutBlock->outBlock2.OrdQty), DATA_TYPE_LONG));
	//pEdit1->SetWindowText(GetDispData(pAllOutBlock->outBlock2.ExecQty, sizeof(pAllOutBlock->outBlock2.ExecQty), DATA_TYPE_LONG));

	// OutBlock3

	// Count 계산
	nDataLength -= 5;
	if (nDataLength < 0)
	{
		return;
	}

	CopyMemory(szCount, pAllOutBlock->sCountOutBlock3, 5);
	nCount = atoi(szCount);

	// Data
	nDataLength -= sizeof(CEXAQ21100OutBlock3) * nCount;
	if (nDataLength < 0)
	{
		return;
	}

	for (int i = 0; i<nCount; i++)
	{
		//nCol = 0;
		//nRow = m_600listctrl.InsertItem(m_600listctrl.GetItemCount(), "");
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG));			// [long  ,   10] 주문번호              
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING));    // [string,   12] 선물옵션종목번호   
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsTpNm, sizeof(pAllOutBlock->outBlock3[i].BnsTpNm), DATA_TYPE_STRING));		// [string,   10] 매매구분                
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].MrcTpNm, sizeof(pAllOutBlock->outBlock3[i].MrcTpNm), DATA_TYPE_STRING));		// [string,   10] 정정취소구분명          
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdPrc, sizeof(pAllOutBlock->outBlock3[i].OrdPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 주문가                  
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdQty, sizeof(pAllOutBlock->outBlock3[i].OrdQty), DATA_TYPE_LONG));			// [long  ,   16] 주문수량              
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecPrc, sizeof(pAllOutBlock->outBlock3[i].ExecPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 체결가                  
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecQty, sizeof(pAllOutBlock->outBlock3[i].ExecQty), DATA_TYPE_LONG));		// [long  ,   16] 체결수량            
		//m_600listctrl.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG));		// [long  ,   16] 미체결수량     

        if ((GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING) == CallCode) || (GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING) == PutCode))
        {
            CString str1, str2;
            str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
            str2 = GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING);			// [string,   12] 선물옵션종목번호	
            //if (str2==CallCode)	str4 = m_2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
            //if (str2==PutCode)	str4 = m_2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
            //Request200(str2, str1, str4, str3);
            Request300(str2, str1);
        }
	}
}


void CDlg_night::Receive2816(LPRECV_PACKET pRpData)
{
	if (strcmp(pRpData->szBlockName, NAME_t2816OutBlock1) == 0)
	{
		LPt2816OutBlock1 pOutBlock = (LPt2816OutBlock1)pRpData->lpData;

		m_2816listctrl.SetItemText(0, 1, GetDispData(pOutBlock->ms_08, sizeof(pOutBlock->ms_08), DATA_TYPE_LONG));
		m_2816listctrl.SetItemText(1, 1, GetDispData(pOutBlock->md_08, sizeof(pOutBlock->md_08), DATA_TYPE_LONG));
		m_2816listctrl.SetItemText(2, 1, GetDispData(pOutBlock->svolume_08, sizeof(pOutBlock->svolume_08), DATA_TYPE_LONG)); 
		m_2816listctrl.SetItemText(0, 2, GetDispData(pOutBlock->ms_17, sizeof(pOutBlock->ms_17), DATA_TYPE_LONG));
		m_2816listctrl.SetItemText(1, 2, GetDispData(pOutBlock->md_17, sizeof(pOutBlock->md_17), DATA_TYPE_LONG));
		m_2816listctrl.SetItemText(2, 2, GetDispData(pOutBlock->svolume_17, sizeof(pOutBlock->svolume_17), DATA_TYPE_LONG));
		m_2816listctrl.SetItemText(0, 3, GetDispData(pOutBlock->ms_18, sizeof(pOutBlock->ms_18), DATA_TYPE_LONG));
		m_2816listctrl.SetItemText(1, 3, GetDispData(pOutBlock->md_18, sizeof(pOutBlock->md_18), DATA_TYPE_LONG));
		m_2816listctrl.SetItemText(2, 3, GetDispData(pOutBlock->svolume_18, sizeof(pOutBlock->svolume_18), DATA_TYPE_LONG));
	}
}

void CDlg_night::Receive2830(LPRECV_PACKET pRpData)
{
	if (strcmp(pRpData->szBlockName, NAME_t2830OutBlock) == 0)
	{

		LPt2830OutBlock pOutBlock = (LPt2830OutBlock)pRpData->lpData;
		m_2830listctrl.SetItemText(0, 1, GetDispData(pOutBlock->hname, sizeof(pOutBlock->hname), DATA_TYPE_STRING));
		m_2830listctrl.SetItemText(1, 1, GetDispData(pOutBlock->price, sizeof(pOutBlock->price), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(2, 1, GetDispData(pOutBlock->change, sizeof(pOutBlock->change), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(3, 1, GetDispData(pOutBlock->jnilclose, sizeof(pOutBlock->jnilclose), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(4, 1, GetDispData(pOutBlock->diff, sizeof(pOutBlock->diff), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(5, 1, GetDispData(pOutBlock->volume, sizeof(pOutBlock->volume), DATA_TYPE_LONG));
		m_2830listctrl.SetItemText(6, 1, GetDispData(pOutBlock->value, sizeof(pOutBlock->value), DATA_TYPE_LONG));
		m_2830listctrl.SetItemText(7, 1, GetDispData(pOutBlock->open, sizeof(pOutBlock->open), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(8, 1, GetDispData(pOutBlock->high, sizeof(pOutBlock->high), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(9, 1, GetDispData(pOutBlock->low, sizeof(pOutBlock->low), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(10, 1, GetDispData(pOutBlock->kospijisu, sizeof(pOutBlock->kospijisu), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(11, 1, GetDispData(pOutBlock->cmeprice, sizeof(pOutBlock->cmeprice), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(12, 1, GetDispData(pOutBlock->cmechange, sizeof(pOutBlock->cmechange), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(13, 1, GetDispData(pOutBlock->cmediff, sizeof(pOutBlock->cmediff), DATA_TYPE_FLOAT, 2));
		m_2830listctrl.SetItemText(14, 1, GetDispData(pOutBlock->focode, sizeof(pOutBlock->focode), DATA_TYPE_STRING));
	}
}

void CDlg_night::Receive2831(LPRECV_PACKET pRpData)
{
    if (strcmp(pRpData->szBlockName, NAME_t2831OutBlock) == 0)
    {

        LPt2831OutBlock pOutBlock = (LPt2831OutBlock)pRpData->lpData;
        m_2830listctrl.SetItemText(15, 1, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));
        m_2830listctrl.SetItemText(16, 1, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));
    }
}


void CDlg_night::Receive2830_(LPRECV_PACKET pRpData)
{
	if (strcmp(pRpData->szBlockName, NAME_t2830OutBlock) == 0)
	{

		LPt2830OutBlock pOutBlock = (LPt2830OutBlock)pRpData->lpData;
		m_2830listctrl_.SetItemText(0, 1, GetDispData(pOutBlock->hname, sizeof(pOutBlock->hname), DATA_TYPE_STRING));
		m_2830listctrl_.SetItemText(1, 1, GetDispData(pOutBlock->price, sizeof(pOutBlock->price), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(2, 1, GetDispData(pOutBlock->change, sizeof(pOutBlock->change), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(3, 1, GetDispData(pOutBlock->jnilclose, sizeof(pOutBlock->jnilclose), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(4, 1, GetDispData(pOutBlock->diff, sizeof(pOutBlock->diff), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(5, 1, GetDispData(pOutBlock->volume, sizeof(pOutBlock->volume), DATA_TYPE_LONG));
		m_2830listctrl_.SetItemText(6, 1, GetDispData(pOutBlock->value, sizeof(pOutBlock->value), DATA_TYPE_LONG));
		m_2830listctrl_.SetItemText(7, 1, GetDispData(pOutBlock->open, sizeof(pOutBlock->open), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(8, 1, GetDispData(pOutBlock->high, sizeof(pOutBlock->high), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(9, 1, GetDispData(pOutBlock->low, sizeof(pOutBlock->low), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(10, 1, GetDispData(pOutBlock->kospijisu, sizeof(pOutBlock->kospijisu), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(11, 1, GetDispData(pOutBlock->cmeprice, sizeof(pOutBlock->cmeprice), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(12, 1, GetDispData(pOutBlock->cmechange, sizeof(pOutBlock->cmechange), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(13, 1, GetDispData(pOutBlock->cmediff, sizeof(pOutBlock->cmediff), DATA_TYPE_FLOAT, 2));
		m_2830listctrl_.SetItemText(14, 1, GetDispData(pOutBlock->focode, sizeof(pOutBlock->focode), DATA_TYPE_STRING));
	}
}

void CDlg_night::Receive2831_(LPRECV_PACKET pRpData)
{
    if (strcmp(pRpData->szBlockName, NAME_t2831OutBlock) == 0)
    {

        LPt2831OutBlock pOutBlock = (LPt2831OutBlock)pRpData->lpData;
        m_2830listctrl_.SetItemText(15, 1, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));
        m_2830listctrl_.SetItemText(16, 1, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));
    }
}


void CDlg_night::Receive2813(LPRECV_PACKET pRpData)//시간대별 투자자 추이 header A type
{
	if (strcmp(pRpData->szBlockName, NAME_t2813OutBlock) == 0)
	{
		LPt2813OutBlock pOutBlock = (LPt2813OutBlock)pRpData->lpData;
	}

	else if (strcmp(pRpData->szBlockName, NAME_t2813OutBlock1) == 0)
	{
		LPt2813OutBlock1 pOutBlock1 = (LPt2813OutBlock1)pRpData->lpData;
		int	nCount = pRpData->nDataLength / sizeof(t2813OutBlock1);
		for (int i = 0; i < nCount; i++)
		{
			lArFornBuy[nCount - i - 1] = atol(GetDispData(pOutBlock1[i].sv_17, sizeof(pOutBlock1[i].sv_17), DATA_TYPE_LONG));
		}
		for (int i = 1; i < nCount; i++)
		{
			lArFornBuy[i] = lArFornBuy[i] + lArFornBuy[i - 1];
		}
	}
}

//--------------------------------------------------------------------------------------
// Timeout 발생
//--------------------------------------------------------------------------------------
LRESULT CDlg_night::OnXMTimeoutData(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);

	return 0L;
}

void CDlg_night::OnBnClickedButtonRequest()
{
	//Request2816();//투자자종합
	Request2830();//야간 콜옵션 시가조회
	Request2830_();//야간 풋옵션 시가조회
    Request2831();//야간 콜옵션 호가조회
    Request2831_();//야간 풋옵션 호가조회
	//AdviseOVC();//snp
	//SetTimer(1, 3000, NULL); //2816 투자자(3초)
    SetTimer(4, 1000, NULL);//getdata()
	SetTimer(2, 1000, NULL); //2830 Price조회(제한없음)
	SetTimer(6, 1000, NULL); //2830_ Price조회(제한없음)
    SetTimer(9, 1000, NULL); //2831 콜 호가 조회(제한없음)
    SetTimer(10, 1000, NULL); //2831_ 풋 호가 조회(제한없음)
	// TODO: Add your control notification handler code here
}


void CDlg_night::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	KillTimer(5);
	KillTimer(6);
	UnadviseOVC();
}

void CDlg_night::OnBnClickedButtonRequest2()
{
	// TODO: Add your control notification handler code here
	Request31200();
	if (lCallQty > 0) Request21200(CallCode);
	if (lCallQty < 0) Request21200_(CallCode);
	if (lPutQty > 0) Request21200(PutCode);
	if (lPutQty < 0) Request21200_(PutCode);	
	if (lCallQty==0 && lPutQty==0) Request21200(CallCode);
}

void CDlg_night::Request0167(BOOL bNext)
{
	//-----------------------------------------------------------
	// 서버시간(t0167) 조회
	t0167InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t0167";

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.id, sizeof(pckInBlock.id), "0", DATA_TYPE_STRING);	// 단축코드  

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 10);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID0167 = nRqID;
}


void CDlg_night::Receive0167(LPRECV_PACKET pRpData)
{
	if (strcmp(pRpData->szBlockName, NAME_t0167OutBlock) == 0)
	{
		LPt0167OutBlock pOutBlock = (LPt0167OutBlock)pRpData->lpData;
		CString str = pOutBlock->time; //서버시간
		strTime = str.Left(6);

		int sec = atoi(str.Mid(4, 2));
		int min = atoi(str.Mid(2, 2));
		int hour = atoi(str.Left(2));
		nCorrectTime = hour * 3600 + min * 60 + sec;
		CTime t = CTime::GetCurrentTime();
		int sec2 = t.GetSecond();
		int min2 = t.GetMinute();
		int hour2 = t.GetHour();
		int time = hour2 * 3600 + min2 * 60 + sec2;
		nCorrectTime -= time; //서버시간-컴퓨터시간
		m_stime.SetWindowText(strTime);
	}
}

void CDlg_night::Request2301(CString date, BOOL bNext)
{
	//투자자종합
	t2301InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t2301";

	// 데이터 취득
	//CString str_gubun1 = "201901";
	CString str_gubun2 = (strMonth.Left(1) == "W") ? "W" : "G"; //G:정규 M:미니 W:위클리 

								// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.yyyymm, sizeof(pckInBlock.yyyymm), date, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.gubun, sizeof(pckInBlock.gubun), str_gubun2, DATA_TYPE_STRING);
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	//((CListCtrl*)GetDlgItem(IDC_1601))->DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패2301", "2301에러", MB_ICONSTOP);
	ID2301 = nRqID;
}


void CDlg_night::Receive2301(LPRECV_PACKET pRpData)//옵션전광판 header A type
{
	CString strRef;
	GetDlgItemTextA(IDC_EDITPRC, strRef);
	float fRef = (float)atof(strRef);																		// 기준가격

	CString cd, pd, cg, pg, ci, pi, cv, pv, ct, pt;
	if (strcmp(pRpData->szBlockName, NAME_t2301OutBlock) == 0)										//선물코드
	{
		LPt2301OutBlock pOutBlock = (LPt2301OutBlock)pRpData->lpData;
		FutureCode = GetDispData(pOutBlock->gmshcode, sizeof(pOutBlock->gmshcode), DATA_TYPE_STRING);
		//FutureCode.Replace("105", "101");
	}

	else if ((strcmp(pRpData->szBlockName, NAME_t2301OutBlock1) == 0) && bToken)			//********************************************콜옵션
	{
		LPt2301OutBlock1 pOutBlock1 = (LPt2301OutBlock1)pRpData->lpData;


		int	nCount = pRpData->nDataLength / sizeof(t2301OutBlock1);				// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
		CString s1, s2, s3, s4, s5, s6, s7, s8;

		for (int i = 0; i < nCount; i++)
		{

			s1 = GetDispData(pOutBlock1[i].price, sizeof(pOutBlock1[i].price), DATA_TYPE_FLOAT, 2); //f1 = atof(s1);
			s2 = GetDispData(pOutBlock1[i].optcode, sizeof(pOutBlock1[i].optcode), DATA_TYPE_STRING);
			s3 = GetDispData(pOutBlock1[i].iv, sizeof(pOutBlock1[i].iv), DATA_TYPE_FLOAT, 2); //f3 = atof(s3);
			s4 = GetDispData(pOutBlock1[i].delt, sizeof(pOutBlock1[i].delt), DATA_TYPE_FLOAT, 2); //f4 = atof(s4);
			s5 = GetDispData(pOutBlock1[i].gama, sizeof(pOutBlock1[i].gama), DATA_TYPE_FLOAT, 2); //f5 = atof(s5);
			s6 = GetDispData(pOutBlock1[i].ceta, sizeof(pOutBlock1[i].ceta), DATA_TYPE_FLOAT, 2); //f6 = atof(s6);
			s7 = GetDispData(pOutBlock1[i].vega, sizeof(pOutBlock1[i].vega), DATA_TYPE_FLOAT, 2); //f7 = atof(s7);
			s8 = GetDispData(pOutBlock1[i].open, sizeof(pOutBlock1[i].open), DATA_TYPE_FLOAT, 2); //f7 = atof(s7);
			if (s2 == CallCode)
			{
				strCallPrc = s1;
				strCallDelta = s4;
				fCallOpen = (float)atof(s8);
			}
		}
	}

	else if ((strcmp(pRpData->szBlockName, NAME_t2301OutBlock1) == 0) && !bToken)			//
	{
		LPt2301OutBlock1 pOutBlock1 = (LPt2301OutBlock1)pRpData->lpData;


		int	nCount = pRpData->nDataLength / sizeof(t2301OutBlock1);				// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
		vector<float> fVecPrice(0); // 0개의 float형 vector 선언
		vector<CString> strVecOptcode(0), strVecPrice(0);
		vector<CString> strVecIV(0), strVecDelta(0), strVecGamma(0), strVecTheta(0), strVecVega(0), strVecOpen(0);
		CString s1, s2, s3, s4, s5, s6, s7, s8; float f1;

		for (int i = 0; i < nCount; i++)
		{

			s1 = GetDispData(pOutBlock1[i].price, sizeof(pOutBlock1[i].price), DATA_TYPE_FLOAT, 2); f1 = (float)atof(s1);
			s2 = GetDispData(pOutBlock1[i].optcode, sizeof(pOutBlock1[i].optcode), DATA_TYPE_STRING);
			s3 = GetDispData(pOutBlock1[i].iv, sizeof(pOutBlock1[i].iv), DATA_TYPE_FLOAT, 2); //f3 = atof(s3);
			s4 = GetDispData(pOutBlock1[i].delt, sizeof(pOutBlock1[i].delt), DATA_TYPE_FLOAT, 2); //f4 = atof(s4);
			s5 = GetDispData(pOutBlock1[i].gama, sizeof(pOutBlock1[i].gama), DATA_TYPE_FLOAT, 2); //f5 = atof(s5);
			s6 = GetDispData(pOutBlock1[i].ceta, sizeof(pOutBlock1[i].ceta), DATA_TYPE_FLOAT, 2); //f6 = atof(s6);
			s7 = GetDispData(pOutBlock1[i].vega, sizeof(pOutBlock1[i].vega), DATA_TYPE_FLOAT, 2); //f7 = atof(s7);
			s8 = GetDispData(pOutBlock1[i].open, sizeof(pOutBlock1[i].open), DATA_TYPE_FLOAT, 2);
			if (f1 >= (0.01*fRef) && f1 < (20 * fRef))
			{
				fVecPrice.push_back(abs(f1 - fRef)); //0.3에 가까운 값을 구하기 위해 빼줌
				strVecPrice.push_back(s1);
				strVecOptcode.push_back(s2);
				strVecIV.push_back(s3);
				strVecDelta.push_back(s4);
				strVecGamma.push_back(s5);
				strVecTheta.push_back(s6);
				strVecVega.push_back(s7);
				strVecOpen.push_back(s8);
			}
		}

		vector <float>::iterator it = min_element(begin(fVecPrice), end(fVecPrice));				// 0.3에 가장 가까운 최소값을 구함
		CallCode = strVecOptcode.at(distance(begin(fVecPrice), it));								// 그 위치의 옵션코드를 저장함
		CallCode2 = strVecOptcode.at(distance(begin(fVecPrice), it) + 1);
		CallCode3 = strVecOptcode.at(distance(begin(fVecPrice), it) + 2);
		strCallPrc = strVecPrice.at(distance(begin(fVecPrice), it));
		fCallOpen = (float)atof(strVecOpen.at(distance(begin(fVecPrice), it)));

		fVecPrice.clear(); vector<float>().swap(fVecPrice);
		strVecOptcode.clear(); vector<CString>().swap(strVecOptcode);
		strVecPrice.clear(); vector<CString>().swap(strVecPrice);
		strVecIV.clear(); vector<CString>().swap(strVecIV);
		strVecDelta.clear(); vector<CString>().swap(strVecDelta);
		strVecGamma.clear(); vector<CString>().swap(strVecGamma);
		strVecTheta.clear(); vector<CString>().swap(strVecTheta);
		strVecVega.clear(); vector<CString>().swap(strVecVega);
		strVecOpen.clear(); vector<CString>().swap(strVecOpen);
	}

	else if ((strcmp(pRpData->szBlockName, NAME_t2301OutBlock2) == 0) && bToken)			//*********************************************풋옵션
	{
		LPt2301OutBlock2 pOutBlock2 = (LPt2301OutBlock2)pRpData->lpData;

		int	nCount = pRpData->nDataLength / sizeof(t2301OutBlock2);				// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
		CString s1, s2, s3, s4, s5, s6, s7, s8;

		for (int i = 0; i < nCount; i++)
		{

			s1 = GetDispData(pOutBlock2[i].price, sizeof(pOutBlock2[i].price), DATA_TYPE_FLOAT, 2); //f1 = (float)atof(s1);
			s2 = GetDispData(pOutBlock2[i].optcode, sizeof(pOutBlock2[i].optcode), DATA_TYPE_STRING);
			s3 = GetDispData(pOutBlock2[i].iv, sizeof(pOutBlock2[i].iv), DATA_TYPE_FLOAT, 2); //f3 = atof(s3);
			s4 = GetDispData(pOutBlock2[i].delt, sizeof(pOutBlock2[i].delt), DATA_TYPE_FLOAT, 2); //f4 = atof(s4);
			s5 = GetDispData(pOutBlock2[i].gama, sizeof(pOutBlock2[i].gama), DATA_TYPE_FLOAT, 2); //f5 = atof(s5);
			s6 = GetDispData(pOutBlock2[i].ceta, sizeof(pOutBlock2[i].ceta), DATA_TYPE_FLOAT, 2); //f6 = atof(s6);
			s7 = GetDispData(pOutBlock2[i].vega, sizeof(pOutBlock2[i].vega), DATA_TYPE_FLOAT, 2); //f7 = atof(s7);
			s8 = GetDispData(pOutBlock2[i].open, sizeof(pOutBlock2[i].open), DATA_TYPE_FLOAT, 2);
			if (s2 == PutCode)
			{
				strPutPrc = s1;
				strPutDelta = s4;
				fPutOpen = (float)atof(s8);
			}
		}
	}

	else if ((strcmp(pRpData->szBlockName, NAME_t2301OutBlock2) == 0) && !bToken)			//풋옵션
	{
		LPt2301OutBlock2 pOutBlock2 = (LPt2301OutBlock2)pRpData->lpData;

		int	nCount = pRpData->nDataLength / sizeof(t2301OutBlock2);				// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
		vector<float> fVecPrice(0); // 0개의 float형 vector 선언
		vector<CString> strVecOptcode(0), strVecPrice(0);
		vector<CString> strVecIV(0), strVecDelta(0), strVecGamma(0), strVecTheta(0), strVecVega(0), strVecOpen(0);
		CString s1, s2, s3, s4, s5, s6, s7, s8; float f1;

		for (int i = 0; i < nCount; i++)
		{

			s1 = GetDispData(pOutBlock2[i].price, sizeof(pOutBlock2[i].price), DATA_TYPE_FLOAT, 2); f1 = (float)atof(s1);
			s2 = GetDispData(pOutBlock2[i].optcode, sizeof(pOutBlock2[i].optcode), DATA_TYPE_STRING);
			s3 = GetDispData(pOutBlock2[i].iv, sizeof(pOutBlock2[i].iv), DATA_TYPE_FLOAT, 2); //f3 = atof(s3);
			s4 = GetDispData(pOutBlock2[i].delt, sizeof(pOutBlock2[i].delt), DATA_TYPE_FLOAT, 2); //f4 = atof(s4);
			s5 = GetDispData(pOutBlock2[i].gama, sizeof(pOutBlock2[i].gama), DATA_TYPE_FLOAT, 2); //f5 = atof(s5);
			s6 = GetDispData(pOutBlock2[i].ceta, sizeof(pOutBlock2[i].ceta), DATA_TYPE_FLOAT, 2); //f6 = atof(s6);
			s7 = GetDispData(pOutBlock2[i].vega, sizeof(pOutBlock2[i].vega), DATA_TYPE_FLOAT, 2); //f7 = atof(s7);
			s8 = GetDispData(pOutBlock2[i].open, sizeof(pOutBlock2[i].open), DATA_TYPE_FLOAT, 2);
			if (f1 >= (0.01 * fRef) && f1 < (20 * fRef))
			{
				fVecPrice.push_back(abs(f1 - fRef)); //0.3에 가까운 값을 구하기 위해 빼줌
				strVecPrice.push_back(s1);
				strVecOptcode.push_back(s2);
				strVecIV.push_back(s3);
				strVecDelta.push_back(s4);
				strVecGamma.push_back(s5);
				strVecTheta.push_back(s6);
				strVecVega.push_back(s7);
				strVecOpen.push_back(s8);
			}
		}
		vector <float>::iterator it = min_element(begin(fVecPrice), end(fVecPrice));		// 0.3에 가장 가까운 최소값을 구함
		PutCode = strVecOptcode.at(distance(begin(fVecPrice), it));							// 그 위치의 옵션코드를 저장함
		PutCode2 = strVecOptcode.at(distance(begin(fVecPrice), it) - 1);
		PutCode3 = strVecOptcode.at(distance(begin(fVecPrice), it) - 2);
		strPutPrc = strVecPrice.at(distance(begin(fVecPrice), it));
		fPutOpen = (float)atof(strVecOpen.at(distance(begin(fVecPrice), it)));
		bToken = TRUE;

		fVecPrice.clear(); vector<float>().swap(fVecPrice);
		strVecOptcode.clear(); vector<CString>().swap(strVecOptcode);
		strVecPrice.clear(); vector<CString>().swap(strVecPrice);
		strVecIV.clear(); vector<CString>().swap(strVecIV);
		strVecDelta.clear(); vector<CString>().swap(strVecDelta);
		strVecGamma.clear(); vector<CString>().swap(strVecGamma);
		strVecTheta.clear(); vector<CString>().swap(strVecTheta);
		strVecVega.clear(); vector<CString>().swap(strVecVega);
		strVecOpen.clear(); vector<CString>().swap(strVecOpen);
	}

	//CallCode.Replace("205", "201");
	//PutCode.Replace("305", "301");
	m_focode.SetWindowTextA(CallCode);
	m_focode2.SetWindowTextA(PutCode);
	//m_callcode2.SetWindowTextA(CallCode2);
	//m_putcode2.SetWindowTextA(PutCode2);
	//m_callcode3.SetWindowTextA(CallCode3);
	//m_putcode3.SetWindowTextA(PutCode3);
}

void CDlg_night::getData()
{
	// 시간 처리 ******************************************************************
	Request0167();
	CTime t = CTime::GetCurrentTime();
	CString strDate = t.Format("%H%M%S");

	t += CTimeSpan(0, 0, 0, nCorrectTime);
	int sec = t.GetSecond();
	int min = t.GetMinute();
	int hour = t.GetHour();
	if (hour >= 0 && hour < 6) hour += 24;
	nCurMin = (hour - 18) * 60 + min;

	// We provide some visual feedback to the latest numbers generated, so you can see the
	// data being generated.
	CString str, strCHo9, strPHo9;
	str.Format("%d", idx);
	m_index.SetWindowText(str);	

    strCHo9 = m_2830listctrl.GetItemText(1, 1);			fCho9 = (float)atof(strCHo9);										    // 매수호가1(콜)	
    strPHo9 = m_2830listctrl_.GetItemText(1, 1);		fPho9 = (float)atof(strPHo9);										    // 매수호가1(풋)	
    lCho9 = atol(m_2830listctrl.GetItemText(16, 1));							// 매수호가수량1(콜)	
    lPho9 = atol(m_2830listctrl_.GetItemText(16, 1));							// 매수호가수량1(풋)	

	if (nCurMin < 660)
	{

		if (idx % 10 == 0)
		{
			Request31200(); //평단가, 수량(lCallQty, lPutQty)
		}

		//if (idx % 10 == 1)
		//{
		//	Request2813(); // 외국인 매매동향
		//}

		if (idx % 10 == 3)
		{
			if (lCallQty > 0) Request21200(CallCode);//선옵 주문가능수량/금액 조회(청산가능, 신규주문가능금액 : lLqdt, lBalance) 매도가능
			if (lCallQty < 0) Request21200_(CallCode);//매수로 청산 가능(양매도시)
			if (lCallQty == 0 && lPutQty == 0) Request21200(CallCode);

		}

		//if (sec % 60 == 5)
		//{
		//	// 외인 기관 추세 ***************************************************************************** 1분전 데이터 표출
		//	if (nCurMin > 60)
		//	{
		//		str.Format("%d", lArFornBuy[nCurMin * 2 - 121]);			m_fornbuy.SetWindowText(str);	// 외인 선물 -1h
		//		if (nCurMin > 120)
		//		{
		//			str.Format("%d", lArFornBuy[nCurMin * 2 - 241]);			m_fornbuy2.SetWindowText(str);	// 외인 선물 -2h
		//			if (nCurMin > 180)
		//			{
		//				str.Format("%d", lArFornBuy[nCurMin * 2 - 361]);			m_fornbuy3.SetWindowText(str);	// 외인 선물 -3h
		//				if (nCurMin > 240)
		//				{
		//					str.Format("%d", lArFornBuy[nCurMin * 2 - 481]);			m_fornbuy4.SetWindowText(str);	// 외인 선물 -4h
		//					if (nCurMin > 300)
		//					{
		//						str.Format("%d", lArFornBuy[nCurMin * 2 - 601]);			m_fornbuy5.SetWindowText(str);	// 외인 선물 -5h
		//						if (nCurMin > 360)
		//						{
		//							str.Format("%d", lArFornBuy[nCurMin * 2 - 721]);			m_fornbuy6.SetWindowText(str);	// 외인 선물 -6h
		//							if (nCurMin > 420)
		//							{
		//								str.Format("%d", lArFornBuy[nCurMin * 2 - 841]);			m_fornbuy7.SetWindowText(str);	// 외인 선물 -7h
		//								if (nCurMin > 480)
		//								{
		//									str.Format("%d", lArFornBuy[nCurMin * 2 - 961]);			m_fornbuy8.SetWindowText(str);	// 외인 선물 -8h
		//									if (nCurMin > 540)
		//									{
		//										str.Format("%d", lArFornBuy[nCurMin * 2 - 1081]);			m_fornbuy9.SetWindowText(str);	// 외인 선물 -9h
		//										if (nCurMin > 600)
		//										{
		//											str.Format("%d", lArFornBuy[nCurMin * 2 - 1201]);			m_fornbuy10.SetWindowText(str);	// 외인 선물 -10h
		//										}
		//									}
		//								}
		//							}
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}

		if (idx % 10 == 6)
		{
			if (lPutQty > 0) Request21200(PutCode);
			if (lPutQty < 0) Request21200_(PutCode);
		}
	}
	
	if (nCurMin == 660 && sec > 0 && sec < 5)
	{

		KillTimer(1);
		KillTimer(2);
		KillTimer(4);
		KillTimer(5);
		KillTimer(6);
		UnadviseOVC();
	}

	idx++;
}

void CDlg_night::ExportToCSVFile()
{
	ofstream myfile("trend.csv");
	if (myfile.is_open())
	{
		myfile << "시간, 개인, 외인, 기관\n";

		for (int count = 0; count < idx; count++) 
		{
		}

		myfile.close();
	}
	else cout << "Unable to open file";
	return;
}

void CDlg_night::OnBnClickedSaveCsv()
{
	// TODO: Add your control notification handler code here
	ExportToCSVFile();
}

void CDlg_night::BuyOption()
{
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHCKOPTION))->GetCheck();
	CString temp1, temp2, temp4, temp5;
	GetDlgItemTextA(IDC_EDITSETUP, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITRANGE, temp2); // 얻을 이익
	GetDlgItemTextA(IDC_EDITRATIO, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITGAP, temp5); // 매수간격 0.02

	CString str1, str2;
	str1 = m_2830listctrl.GetItemText(1, 1); float fCallPrice = (float)atof(str1);			// 현재가(콜) 매도가능 현재가(매수호가1)	
	str2 = m_2830listctrl_.GetItemText(1, 1); float fPutPrice = (float)atof(str2);			// 현재가(풋)	

	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

	// ******************************************************** 청산가격 자동 조정(평균가로 조정) 소수점 두자리
	CString strPrc;
	bOption ? GetDlgItemTextA(IDC_PUTPRICE2, strPrc) : GetDlgItemTextA(IDC_CALLPRICE2, strPrc);
	float fAvrPrc = (float)atof(strPrc);
	if (fAvrPrc < fPrc && fAvrPrc > fPrc - 0.2) //20틱
	{
		fAvrPrc = roundf(fAvrPrc * 100) / 100; // 소수점 두자리 반올림
		strPrc.Format("%.2f", fAvrPrc);
		CEdit *pEdit1;
		pEdit1 = (CEdit*)GetDlgItem(IDC_EDITSETUP);
		pEdit1->SetWindowText(strPrc);
		pEdit1 = NULL;
	}

	int nPer = atoi(temp4);
	int iter = 100 / nPer;

	if (bPut && bOption && (fPutPrice < fPrc + 0.05))							//buy put
	{
		for (int i = 0; i < iter; ++i)
		{
			BuyPut(fPrc - ((float)i)*fGap, 10, nPer);
		}
		bPut = FALSE;
	}
	if (!bPut && bOption && (fPutPrice > (fPrc + fProfit+0.1)) && lLqdt == 0)	//cancel buying put
	{
		Request600(); // 매수매도주문 모두 취소
		bPut = TRUE;
	}

	if (bCall && !bOption && (fCallPrice < fPrc + 0.05))						// buy call
	{	
		for (int i = 0; i < iter; ++i)
		{
			BuyCall(fPrc - ((float)i)*fGap, 10, nPer);
		}
		bCall = FALSE;
	}
	if (!bCall && !bOption && (fCallPrice > (fPrc + fProfit+0.1)) && lLqdt == 0) //cancel buying call
	{
		Request600(); // 매수매도주문 모두 취소
		bCall = TRUE;
	}

	// 여러개 가격으로 순차적으로 매도(10개씩)
	if (lLqdt > 0) //청산가능물량이 있고 가격옵션일 경우
	{
		if (lCallQty > 0 && !bOption && (fCallPrice == fQSellPrc.front()) && fQSellPrc.size() > 0 && nQSellQty.size() > 0)				//콜옵션보유수가 있을경우
		{
			Request100_(CallCode, "1", fQSellPrc.front(), nQSellQty.front());
			fQSellPrc.pop();
			nQSellQty.pop();
			bCall = TRUE;
		}

		if (lPutQty > 0 && bOption && (fPutPrice == fQSellPrc.front()) && fQSellPrc.size() > 0 && nQSellQty.size() > 0)				//풋옵션보유수가 있을경우
		{
			Request100_(PutCode, "1", fQSellPrc.front(), nQSellQty.front());
			fQSellPrc.pop();
			nQSellQty.pop();
			bPut = TRUE;
		}
	}
}

void CDlg_night::BuyOption0() // 정해진 가격에 사고 팔기 + 매수물량 감추기
{
    BOOL bOption = ((CButton*)GetDlgItem(IDC_CHCKOPTION))->GetCheck();
    CString temp1, temp2, temp4, temp5;
    GetDlgItemTextA(IDC_EDITSETUP, temp1); // 매수가격
    GetDlgItemTextA(IDC_EDITRANGE, temp2); // 얻을 이익
    GetDlgItemTextA(IDC_EDITRATIO, temp4); // 매수량 기본 100%
    GetDlgItemTextA(IDC_EDITGAP, temp5); // 매수간격 0.02

    float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

    int nPer = atoi(temp4);//매수 %
    int iter = 100 / nPer; //

    if (iter > 0)
    {
        if (gIter > 0)
        {
            // 구매예산 수정(210522 수정)
            nPer = (int)(100 / gIter);
            // ******************************************************************************************************* 매수
            if (bPut && bOption && (fPho9 < fPrc - ((float)iter - (float)gIter) * fGap))//buy put
            {
                BuyPutR(fPrc - ((float)iter - (float)gIter) * fGap, nPer);
                gIter -= 1;
                if (gIter == 0) bPut = FALSE;
            }
            if (!bPut && bOption && (fPho9 > (fPrc + fProfit)) && lLqdt == 0) //cancel buying put ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
            {
                Request600(); // 매수매도주문 모두 취소
                bPut = TRUE;
            }

            if (bCall && !bOption && (fCho9 < fPrc - ((float)iter - (float)gIter) * fGap))// buy call
            {
                BuyCallR(fPrc - ((float)iter - (float)gIter) * fGap, nPer);
                gIter -= 1;
                if (gIter == 0) bCall = FALSE;
            }
            if (!bCall && !bOption && (fCho9 > (fPrc + fProfit)) && lLqdt == 0) //cancel buying call ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
            {
                Request600(); // 매수매도주문 모두 취소
                bCall = TRUE;
            }
        }
    }

    // ******************************************************************************************************* 청산
    
    if ((lLqdt > 0) ) //청산가능물량이 있고 가격옵션일 경우
    {
        int input = lCallQty + lPutQty; // Example input
        const int step = 20;
        const int MAX_DIVISOR_VALUE = (input / step) * step; // Largest multiple of 20 less than or equal to input


        if (!bOption && lCallQty > 0 && (fCho9 >= (fPrc + fProfit)))				//풋옵션 노체크시(콜옵션) 콜옵션보유수가 있을경우
        {
            if (lCallQty < 10 && lLqdt == lCallQty + lPutQty && lCallQty < lCho9)
            {
                Request100_(CallCode, "1", fPrc + fProfit, (int)lCallQty);
                bCall = TRUE;
                OnBnClickedBttnprofit3();//kill
                SetPrice(); //기본 per = 50 % 적용
            }
            else
            {
                int maxDivisors = MAX_DIVISOR_VALUE / step;
                int* divisors = new int[maxDivisors];

                for (int i = 0; i < maxDivisors; ++i)
                {
                    divisors[i] = step * (i + 1);
                }

                for (int i = 0; i < maxDivisors; ++i)
                {
                    if (lCallQty < divisors[i])
                    {
                        int divisor = (i + 1) * 4; // 2, 4, 6, ..., 30
                        if (lCallQty / divisor < lCho9 || fCho9 >= fPrc + fProfit + 0.05f)
                        {
                            Request100_(CallCode, "1", fPrc + fProfit, (int)(lCallQty / divisor));
                        }
                        delete[] divisors; // Clean up dynamically allocated memory
                        return;
                    }
                }

                // Handle lCallQty >= MAX_DIVISOR_VALUE
                int divisor = (maxDivisors + 1) * 4;
                if (lCallQty / divisor < lCho9)
                {
                    Request100_(CallCode, "1", fPrc + fProfit, (int)(lCallQty / divisor));
                }

                delete[] divisors; // Clean up dynamically allocated memory
            }
        }

        if (bOption && lPutQty > 0 && (fPho9 >= (fPrc + fProfit)))					//풋옵션 체크시 풋옵션보유수가 있을경우
        {
            if (lPutQty < 10 && lLqdt == lCallQty + lPutQty && lPutQty < lPho9)
            {
                Request100_(PutCode, "1", fPrc + fProfit, (int)lPutQty);
                bPut = TRUE;
                OnBnClickedBttnprofit3();//kill
                SetPrice(); //기본 per = 50 % 적용
            }
            else
            {
                int maxDivisors = MAX_DIVISOR_VALUE / step;
                int* divisors = new int[maxDivisors];

                for (int i = 0; i < maxDivisors; ++i)
                {
                    divisors[i] = step * (i + 1);
                }

                for (int i = 0; i < maxDivisors; ++i)
                {
                    if (lPutQty < divisors[i])
                    {
                        int divisor = (i + 1) * 4; // 2, 4, 6, ..., 20
                        if (lPutQty / divisor < lPho9 || fPho9 >= fPrc + fProfit + 0.05f)
                        {
                            Request100_(PutCode, "1", fPrc + fProfit, (int)(lPutQty / divisor));
                        }
                        delete[] divisors; // Clean up dynamically allocated memory
                        return;
                    }
                }

                // Handle lCallQty >= MAX_DIVISOR_VALUE
                int divisor = (maxDivisors + 1) * 4;
                if (lPutQty / divisor < lPho9)
                {
                    Request100_(PutCode, "1", fPrc + fProfit, (int)(lPutQty / divisor));
                }

                delete[] divisors; // Clean up dynamically allocated memory
            }
        }
    }


    //if ((lLqdt > 0) && (nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
    //{
    //	if (lCallQty > 0)		//콜옵션보유수가 있을경우
    //	{
    //		for (int i = 0; i < iter; ++i)
    //		{
    //			SellCall(fPrc + fProfit + ((float)i * 0.01), 10, nPer);
    //		}
    //		bCall = TRUE;
    //	}

    //	if (lPutQty > 0)			//풋옵션보유수가 있을경우
    //	{
    //		for (int i = 0; i < iter; ++i)
    //		{
    //			SellPut(fPrc + fProfit + ((float)i * 0.01), 10, nPer);
    //		}
    //		bPut = TRUE;
    //	}
    //}
}


void CDlg_night::BuyOption1()
{
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHCKOPTION))->GetCheck();
	CString temp1, temp2, temp4, temp5;
	GetDlgItemTextA(IDC_EDITSETUP, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITRANGE, temp2); // 얻을 이익
	GetDlgItemTextA(IDC_EDITRATIO, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITGAP, temp5); // 매수간격 0.02

	CString str1, str2;
	str1 = m_2830listctrl.GetItemText(1, 1); float fCallPrice = (float)atof(str1);			// 현재가(콜) 매도가능 현재가(매수호가1)	
	str2 = m_2830listctrl_.GetItemText(1, 1); float fPutPrice = (float)atof(str2);			// 현재가(풋)	

	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

	//if (lForVol > lCmpVol)
	//{
	//	Request100_(CallCode, "2", fCallPrc, 2); //40개라면,,,2개씩 20번 (순매수 50*20 = 1000억)
	//	lCmpVol += 72;//50%(1.14*50)
	//}

	if (!bOption)						// buy call
	{
		for (int i = 0; i < 10; ++i)
		{
			//BuyCall(fPrc, 10, 5);
			Request100_(CallCode, "2", fPrc, 10);
		}
	}

}


void CDlg_night::OnBnClickedBttnprofit2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString temp4;
    GetDlgItemTextA(IDC_EDITRATIO, temp4); // 매수량 기본 %

    int nPer = atoi(temp4);//매수 %
    gIter = 100 / nPer; //

    //nSellOption = 1;
    SetTimer(8, 1500, NULL); // BuyOption0();//자동매수매도_매수잔량감추기
	//SetSell(); // 기본 10개로 큐 세팅 + BuyOption 함수 호출	

	m_ststxt.SetWindowTextA("Running1...");
	
}

void CDlg_night::SetBuy(int qty)
{
	// 여러개 가격으로 순차적으로 매수(기본 10개씩)
	CString temp1, temp2, temp4, temp5;
	GetDlgItemTextA(IDC_EDITSETUP, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITRANGE, temp2); // 얻을 이익
	GetDlgItemTextA(IDC_EDITRATIO, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITGAP, temp5); // 매수간격 0.02

	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

	int nPer = atoi(temp4);
	int iter = 100 / nPer;

	for (int i = 0; i < iter; ++i)
	{
		fQBuyPrc.push(fPrc - i * fGap);
	}

	for (int i = 0; i < iter; ++i)
	{
		long l0 = lBalance / (long)((fPrc - i * fGap) * 250000);
		l0 = (l0 * nPer) / 100;
		lBalance -= static_cast<long>((fPrc - i * fGap) * 250000 * l0);
		nQBuyQty.push((long)l0);
	}

	int quota = lLqdt / qty;
	int remainder = lLqdt % qty;

	if (lLqdt > qty)
	{
		for (int i = 0; i < quota; ++i)
		{
			nQSellQty.push(qty);
		}
        nQSellQty.push(remainder);
	}
	else
	{
        nQSellQty.push((int)lLqdt);
	}

	if (remainder != 0) quota += 1;
	for (int i = 0; i < quota; ++i)
	{
		fQSellPrc.push(fPrc + fProfit + i * 0.01f);
	}

	SetTimer(5, 3000, NULL); //BuyOption 함수 호출	
}

void CDlg_night::SetSell(int qty) // 여러개 가격으로 순차적으로 매도(기본 10개씩)
{
	
	CString temp1, temp2, temp4, temp5;
	GetDlgItemTextA(IDC_EDITSETUP, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITRANGE, temp2); // 얻을 이익
	GetDlgItemTextA(IDC_EDITRATIO, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITGAP, temp5); // 매수간격 0.01

	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

	int nPer = atoi(temp4);
	int iter = 100 / nPer;

	for (int i = 0; i < iter; ++i)
	{
		fQBuyPrc.push(fPrc - i * fGap);
	}

	for (int i = 0; i < iter; ++i)
	{
		long l0 = lBalance / (long)((fPrc - i * fGap) * 250000); //구매가능 개수
		l0 = (l0 * nPer) / 100;
		lBalance -= static_cast<long>((fPrc - i * fGap) * 250000 * l0); // 남은 돈
		nQBuyQty.push((long)l0);
	}

	int quota = lLqdt / qty;
	int remainder = lLqdt % qty;

	if (lLqdt > qty) 
	{
		for (int i = 0; i < quota; ++i)
		{
            nQSellQty.push(qty);
		}
        nQSellQty.push(remainder);
	}
	else
	{
        nQSellQty.push((int)lLqdt);
	}

	if (remainder != 0) quota += 1;
	for (int i = 0; i < quota; ++i)
	{
		fQSellPrc.push(fPrc + fProfit + i * 0.01f);
	}	

	SetTimer(5, 3000, NULL); //BuyOption 함수 호출	
}

void CDlg_night::OnBnClickedBttnprofit3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(5);
	Request600(); // 매수매도주문 모두 취소
	bCall = TRUE, bPut = TRUE; 
	m_ststxt.SetWindowTextA("Stop...");

	while (!nQSellQty.empty()) nQSellQty.pop(); queue<int>().swap(nQSellQty);
	while (!fQSellPrc.empty()) fQSellPrc.pop(); queue<float>().swap(fQSellPrc);
	while (!nQBuyQty.empty()) nQBuyQty.pop(); queue<int>().swap(nQBuyQty);
	while (!fQBuyPrc.empty()) fQBuyPrc.pop(); queue<float>().swap(fQBuyPrc);

	KillTimer(7);
}

void CDlg_night::BuyCall(float fprc, int amnt, int per)
{
	//Request10100();//주문가능수량/금액 조회
	//Sleep(150);

    if (lBalance == 0 || fprc < 0.01f) return;

	long l0 = static_cast<long>(lBalance / (fprc * 250000));
    int n0 = (int)l0;
	if (l0 == 0)
		return;

	n0 = (n0*per) / 100;

	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (n0 > amnt)
	{
		for (int i = 0; i < quota; ++i)
		{
			Request100_(CallCode, "2", fprc, amnt);
			Sleep(80);
		}
		Request100_(CallCode, "2", fprc, remainder);
	}
	else
	{
		Request100_(CallCode, "2", fprc, n0);
	}


	return;
}


void CDlg_night::BuyCallR(float fprc, int per)
{
    //Request10100();//주문가능수량/금액 조회
    //Sleep(150);

    if (lBalance == 0 || fprc < 0.01f) return;

    long l0 = static_cast<long>(lBalance / (fprc * 250000));
    int n0 = (int)l0;
    if (l0 == 0)
        return;

    int totalOrders = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> qtyDist(1, 2);
    std::uniform_real_distribution<> timeDist(0.05, 0.1);

    while (totalOrders < n0)
    {
        int orderQty = qtyDist(gen);
        if (totalOrders + orderQty > n0)
        {
            orderQty = n0 - totalOrders;
        }

        Request100_(CallCode, "2", fprc, orderQty);
        totalOrders += orderQty;

        if (totalOrders < n0) // No need to sleep if we've reached the total quantity
        {
            double sleepTime = timeDist(gen);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime * 1000)));
        }
    }

    return;
}

void CDlg_night::BuyPut(float fprc, int amnt, int per)
{
	//Request10100();//주문가능수량/금액 조회
	//Sleep(150);

	if (lBalance == 0) return;

	long l0 = static_cast<long>(lBalance / (fprc * 250000));
	if (l0 == 0)
		return;

	int n0 = (int)l0;
	n0 = (n0 * per) / 100;
	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (n0 > amnt)
	{
		for (int i = 0; i < quota; ++i)
		{
			Request100_(PutCode, "2", fprc, amnt);
			Sleep(80);
		}
		Request100_(PutCode, "2", fprc, remainder);
	}
	else
	{
		Request100_(PutCode, "2", fprc, n0);
	}

	return;
}


void CDlg_night::BuyPutR(float fprc, int per)
{
    //Request10100();//주문가능수량/금액 조회
    //Sleep(150);

    if (lBalance == 0) return;

    long l0 = static_cast<long>(lBalance / (fprc * 250000));
    int n0 = (int)l0;
    if (n0 == 0) return;

    n0 = (n0 * per) / 100;
    if (n0 == 0) return;

    int totalOrders = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> qtyDist(1, 2);
    std::uniform_real_distribution<> timeDist(0.05, 0.1);

    while (totalOrders < n0)
    {
        int orderQty = qtyDist(gen);
        if (totalOrders + orderQty > n0)
        {
            orderQty = n0 - totalOrders;
        }

        Request100_(PutCode, "2", fprc, orderQty);
        totalOrders += orderQty;

        if (totalOrders < n0) // No need to sleep if we've reached the total quantity
        {
            double sleepTime = timeDist(gen);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime * 1000)));
        }
    }

    return;
}

void CDlg_night::SetPrice(int per) // 기본 per=50% 적용
{
    BOOL bOption = ((CButton*)GetDlgItem(IDC_CHCKOPTION))->GetCheck();

    CString str1, str2;
    bOption ? str1 = m_2830listctrl.GetItemText(9, 1) : str1 = m_2830listctrl.GetItemText(9, 1);

    float f1 = (float)atof(str1); // 현재 매수1호가
    f1 *= (float)(100 - per);
    f1 = roundf(f1) / 100; // 소수점2자리 반올림
    str1.Format("%.2f", f1);

    GetDlgItemTextA(IDC_EDITRANGE, str2);
    float f2 = (float)atof(str2);
    f2 *= (float)(100 - per);
    f2 = roundf(f2) / 100; // 소수점2자리 반올림
    str2.Format("%.2f", f2);

    CEdit* pEdit1;
    pEdit1 = (CEdit*)GetDlgItem(IDC_EDITSETUP); pEdit1->SetWindowText(str1);
    pEdit1 = (CEdit*)GetDlgItem(IDC_EDITRANGE); pEdit1->SetWindowText(str2);
    pEdit1 = NULL;
}


void CDlg_night::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 1:
		Request2816();//투자자 종합
		break;
	case 2:
		Request2830();//OptPrc조회
		break;
	case 3:
		break;
	case 4:
		getData();
		break;
	case 5:
		BuyOption();//구매알고리즘
		break;
	case 6:
		Request2830_();//OptPrc조회
		break;
	case 7:
		BuyOption1();//구매알고리즘
		break;
    case 8:
        BuyOption0();//자동매수매도_매수잔량감추기
        break;
    case 9:
        Request2831();//콜 호가 조회
        break;
    case 10:
        Request2831_();//풋 호가 조회
        break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlg_night::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	while (!nQSellQty.empty()) nQSellQty.pop();
	while (!fQSellPrc.empty()) fQSellPrc.pop();

	CString str;
	GetDlgItemTextA(IDC_EDITSETUP, str);
	float f1 = (float)atof(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		f1 += 0.01f;
	}
	else // 하 버튼
	{
		f1 -= 0.01f;
	}

	str.Format("%.2f", f1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITSETUP); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	//SetSell();

	*pResult = 0;
}


void CDlg_night::OnDeltaposSpin19(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	while (!nQSellQty.empty()) nQSellQty.pop();
	while (!fQSellPrc.empty()) fQSellPrc.pop();

	CString str;
	GetDlgItemTextA(IDC_EDITRANGE, str);
	float f1 = (float)atof(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		f1 += 0.01f;
	}
	else // 하 버튼
	{
		f1 -= 0.01f;
	}

	str.Format("%.2f", f1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITRANGE); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	//SetSell();

	*pResult = 0;
}


void CDlg_night::OnDeltaposSpin18(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITGAP, str);
	float f1 = (float)atof(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		f1 += 0.01f;
	}
	else // 하 버튼
	{
		f1 -= 0.01f;
	}

	str.Format("%.2f", f1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITGAP); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_night::OnDeltaposSpin20(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITRATIO, str);
	int n1 = atoi(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		n1 += 1;
	}
	else // 하 버튼
	{
		n1 -= 1;
	}

	str.Format("%d", n1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITRATIO); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_night::OnClick2830outblock(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;
	CString str = m_2830listctrl.GetItemText(index, 1); //0부터 시작

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITSETUP); pEdit1->SetWindowText(str);

	((CButton*)GetDlgItem(IDC_CHCKOPTION))->SetCheck(0);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_night::OnClick2830outblock2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;
	CString str = m_2830listctrl_.GetItemText(index, 1); //0부터 시작

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITSETUP); pEdit1->SetWindowText(str);

	((CButton*)GetDlgItem(IDC_CHCKOPTION))->SetCheck(1);//풋 체크
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_night::OnDeltaposSpin21(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, str2;
	GetDlgItemTextA(IDC_INBLOCK_FOCODE, str);
	int n1 = (int)atof(str.Right(3));

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		(n1 % 5) ? n1 += 3 : n1 += 2;
	}
	else // 하 버튼
	{
		(n1 % 5) ? n1 -= 2 : n1 -= 3;
	}

	str2.Format("%d", n1);
	str = str.Left(5) + str2;
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_INBLOCK_FOCODE); pEdit1->SetWindowText(str);
	CallCode = str;
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_night::OnDeltaposSpin22(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, str2;
	GetDlgItemTextA(IDC_INBLOCK_FOCODE2, str);
	int n1 = (int)atof(str.Right(3));

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		(n1 % 5) ? n1 += 3 : n1 += 2;
	}
	else // 하 버튼
	{
		(n1 % 5) ? n1 -= 2 : n1 -= 3;
	}

	str2.Format("%d", n1);
	str = str.Left(5) + str2;
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_INBLOCK_FOCODE2); pEdit1->SetWindowText(str);
	PutCode = str;
	pEdit1 = NULL;
	*pResult = 0;
}

void CDlg_night::AdviseOVC()
{
	//선물 실시간
	TCHAR	szTrCode[] = "OVC";

	//-----------------------------------------------------------
	// 데이터 취득
	CString sym = "ESH19   ";
	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		sym,					// 종목코드
		8		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "FCO에러", MB_ICONSTOP);
}

void CDlg_night::UnadviseOVC()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	TCHAR	szTrCode[] = "OVC";

	CString sym = "ESH19   ";
	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		sym,					// 종목코드
		8		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "에러", MB_ICONSTOP);
}


LRESULT CDlg_night::OnXMReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;
	
	if (strcmp(pRealPacket->szTrCode, "OVC") == 0)
	{
		LPOVC_OutBlock pOutBlock = (LPOVC_OutBlock)pRealPacket->pszData;
		if (strcmp(GetDispData(pOutBlock->symbol, sizeof(pOutBlock->symbol), DATA_TYPE_STRING), "ESH19") == 0)//SNP
			m_persnp.SetWindowTextA(GetDispData(pOutBlock->chgrate, sizeof(pOutBlock->chgrate), DATA_TYPE_DOT, 2) + "%"); //전일대비등락율

		//if (strcmp(GetDispData(pOutBlock->symbol, sizeof(pOutBlock->symbol), DATA_TYPE_STRING), "FESXH19") == 0)//EURO
		//	m_futureeuro.SetWindowTextA(GetDispData(pOutBlock->chgrate, sizeof(pOutBlock->chgrate), DATA_TYPE_DOT, 2) + "%"); //전일대비등락율

	}

	return 0L;
}


HBRUSH CDlg_night::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		if (pWnd->GetDlgCtrlID() == IDC_TIME || pWnd->GetDlgCtrlID() == IDC_PERSNP)
		{
			pDC->SetTextColor(RGB(255, 0, 0));//red
		}

		if (pWnd->GetDlgCtrlID() == IDC_STSTXT)
		{
			pDC->SetTextColor(RGB(255, 0, 255));//magenta
		}

		if (pWnd->GetDlgCtrlID() == IDC_CALLQTY || pWnd->GetDlgCtrlID() == IDC_PUTQTY || pWnd->GetDlgCtrlID() == IDC_CALLPRICE2 || pWnd->GetDlgCtrlID() == IDC_PUTPRICE2
			|| pWnd->GetDlgCtrlID() == IDC_LQDTQTY || pWnd->GetDlgCtrlID() == IDC_BUDGET2)
		{
			pDC->SetTextColor(RGB(0, 0, 255));//blue
		}

		if (pWnd->GetDlgCtrlID() == IDC_FORNBUY || pWnd->GetDlgCtrlID() == IDC_FORNBUY2 || pWnd->GetDlgCtrlID() == IDC_FORNBUY3 || pWnd->GetDlgCtrlID() == IDC_FORNBUY4
			|| pWnd->GetDlgCtrlID() == IDC_FORNBUY5 || pWnd->GetDlgCtrlID() == IDC_FORNBUY6 || pWnd->GetDlgCtrlID() == IDC_FORNBUY7 || pWnd->GetDlgCtrlID() == IDC_FORNBUY8
			|| pWnd->GetDlgCtrlID() == IDC_FORNBUY9 || pWnd->GetDlgCtrlID() == IDC_FORNBUY10)
		{
			pDC->SetTextColor(RGB(148, 0, 211));//dark violet
			//pDC->SetBkColor(RGB(171, 130, 255));
		}
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CDlg_night::OnBnClickedBttnprofit5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(7, 1000, NULL); //BuyOption1();
	m_ststxt.SetWindowTextA("Running2...");
}


void CDlg_night::OnBnClickedButtonRequest11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//ExportToCSVFile();
	bToken = FALSE;
	bCall = FALSE, bPut = FALSE;
	Request2301(strMonth);
}


void CDlg_night::OnCustomdraw2830outblock(NMHDR* pNMHDR, LRESULT* pResult)
{
    CString strType;
    BOOL bErrorFlag = FALSE;
    BOOL bWarnningFlag = FALSE;
    BOOL bWarnning2Flag = FALSE;

    NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

    strType = m_2830listctrl.GetItemText(pLVCD->nmcd.dwItemSpec, 0);

    if ((strType.Find(_T("현재가")) != -1))
    {
        bErrorFlag = TRUE;
    }

    if ((strType.Find(_T("매도호가수량")) != -1))
    {
        bWarnningFlag = TRUE;
    }

    if ((strType.Find(_T("매수호가수량")) != -1))
    {
        bWarnning2Flag = TRUE;
    }
    *pResult = 0;

    if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
        *pResult = CDRF_NOTIFYITEMDRAW;

    else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
    {
        if (bErrorFlag)
        {
            pLVCD->clrText = RGB(255, 0, 0);  // 글자 색 변경 
            //pLVCD->clrTextBk = RGB(0, 0, 0);  // 배경 색 변경 
        }
        else if (bWarnningFlag)
        {
            pLVCD->clrText = RGB(0, 0, 255);
            //pLVCD->clrTextBk = RGB(237, 255, 255);
        }
        else if (bWarnning2Flag)
        {
            pLVCD->clrText = RGB(148, 0, 211);
            //pLVCD->clrTextBk = RGB(237, 255, 255);
        }
        else
        {
            pLVCD->clrText = RGB(0, 0, 0);
        }

        *pResult = CDRF_DODEFAULT;
    }
}


void CDlg_night::OnCustomdraw2830outblock2(NMHDR* pNMHDR, LRESULT* pResult)
{
    CString strType;
    BOOL bErrorFlag = FALSE;
    BOOL bWarnningFlag = FALSE;
    BOOL bWarnning2Flag = FALSE;

    NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

    strType = m_2830listctrl_.GetItemText(pLVCD->nmcd.dwItemSpec, 0);

    if ((strType.Find(_T("현재가")) != -1))
    {
        bErrorFlag = TRUE;
    }

    if ((strType.Find(_T("매도호가수량")) != -1))
    {
        bWarnningFlag = TRUE;
    }

    if ((strType.Find(_T("매수호가수량")) != -1))
    {
        bWarnning2Flag = TRUE;
    }
    *pResult = 0;

    if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
        *pResult = CDRF_NOTIFYITEMDRAW;

    else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
    {
        if (bErrorFlag)
        {
            pLVCD->clrText = RGB(255, 0, 0);  // 글자 색 변경 
            //pLVCD->clrTextBk = RGB(0, 0, 0);  // 배경 색 변경 
        }
        else if (bWarnningFlag)
        {
            pLVCD->clrText = RGB(0, 0, 255);
            //pLVCD->clrTextBk = RGB(237, 255, 255);
        }
        else if (bWarnning2Flag)
        {
            pLVCD->clrText = RGB(148, 0, 211);
            //pLVCD->clrTextBk = RGB(237, 255, 255);
        }
        else
        {
            pLVCD->clrText = RGB(0, 0, 0);
        }

        *pResult = CDRF_DODEFAULT;
    }
}