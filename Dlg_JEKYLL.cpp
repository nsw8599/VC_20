// Dlg_JEKYLL.cpp : implementation file
//
//int GetTRCountRequest(TRCode) :  10분내 요청한 TR의 총 횟수를 리턴

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Dlg_JEKYLL.h"

#include "./Packet/t2105.h"
#include "./Packet/t2301.h"
#include "./Packet/t1601.h"
#include "./packet/t1602.h"
#include "./Packet/t8415.h"
#include "./Packet/o3103.h"
#include "./packet/t0167.h"
#include "./packet/t0441.h"
#include "./packet/t2421.h"//미결제약정추이
#include "./packet/t1662.h"//프로그램매매차트(베이시스)
#include "./Packet/CFOAQ00600.h"
#include "./packet/CFOAQ10100.h"
#include "./Packet/CFOAT00100.h"
#include "./Packet/CFOAT00200.h"
#include "./Packet/CFOAT00300.h"
#include "./packet/CFOFQ02400.h"
#include "./packet/FC0.h"
#include "./packet/FH0.h"
#include "./packet/BMT.h"
#include "./packet/OVC.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <thread>
#include <random>
#include <chrono>

using namespace std;

#include <condition_variable>
std::condition_variable cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_JEKYLL dialog

IMPLEMENT_DYNCREATE(CDlg_JEKYLL, CDialog)

CDlg_JEKYLL::CDlg_JEKYLL(CWnd* pParent)
{
}

void CDlg_JEKYLL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_JEKYLL)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CALLCODE, m_callcode);
	//DDX_Control(pDX, IDC_CALLCODE2, m_callcode2);
	//DDX_Control(pDX, IDC_CALLCODE3, m_callcode3);
	DDX_Control(pDX, IDC_PUTCODE, m_putcode);
	//DDX_Control(pDX, IDC_PUTCODE2, m_putcode2);
	//DDX_Control(pDX, IDC_PUTCODE3, m_putcode3);
	DDX_Control(pDX, IDC_2105, m_lst2105);
	DDX_Control(pDX, IDC_1601, m_lst1601);
	DDX_Control(pDX, IDC_QTY, m_qty);
	DDX_Control(pDX, IDC_2105_2, m_lst2105_);
	DDX_Control(pDX, IDC_2105_3, m_lst2105__);
	DDX_Control(pDX, IDC_PRC, m_prc);
	DDX_Control(pDX, IDC_ORGORDNO, m_orgordno);
	DDX_Control(pDX, IDC_PRC2, m_prc2);
	DDX_Control(pDX, IDC_QTY2, m_qty2);
	DDX_Control(pDX, IDC_ORGORDNO2, m_orgordno2);
	DDX_Control(pDX, IDC_CALLPRC, m_callprc);
	DDX_Control(pDX, IDC_CALLHIGH, m_callhigh);
	DDX_Control(pDX, IDC_CALLLOW, m_calllow);
	DDX_Control(pDX, IDC_CALLHIGH2, m_callhigh2);
	DDX_Control(pDX, IDC_CALLLOW2, m_calllow2);
	DDX_Control(pDX, IDC_PUTPRC, m_putprc);
	DDX_Control(pDX, IDC_PUTHIGH, m_puthigh);
	DDX_Control(pDX, IDC_PUTLOW, m_putlow);
	DDX_Control(pDX, IDC_PUTHIGH2, m_puthigh2);
	DDX_Control(pDX, IDC_PUTLOW2, m_putlow2);
	DDX_Control(pDX, IDC_STIME, m_time);
	DDX_Control(pDX, IDC_IDX, m_idx);
	DDX_Control(pDX, IDC_CURMIN, m_curmin);
	DDX_Control(pDX, IDC_LQDT, m_lqdt);
	DDX_Control(pDX, IDC_NEWORD, m_neword);
	DDX_Control(pDX, IDC_K200, m_k200);
	DDX_Control(pDX, IDC_FUTURE, m_future);
	DDX_Control(pDX, IDC_FUTURESNP, m_futuresnp);
	DDX_Control(pDX, IDC_AVRPRC, m_avrprc);
	DDX_Control(pDX, IDC_AVRPRC2, m_avrprc2);
    DDX_Control(pDX, IDC_AVRPRC21, m_avrprc21);
    DDX_Control(pDX, IDC_AVRPRC22, m_avrprc22);
	DDX_Control(pDX, IDC_AVRPRC3, m_avrprc3);
    DDX_Control(pDX, IDC_AVRPRC31, m_avrprc31);
    DDX_Control(pDX, IDC_AVRPRC32, m_avrprc32);
	DDX_Control(pDX, IDC_CURVALUE, m_curvalue);
    DDX_Control(pDX, IDC_CURVALUE2, m_curvalue2);
    DDX_Control(pDX, IDC_CURVALUE21, m_curvalue21);
    DDX_Control(pDX, IDC_CURVALUE22, m_curvalue22);
	DDX_Control(pDX, IDC_CURVALUE4, m_curvalue4);
	DDX_Control(pDX, IDC_AVRPRCF, m_avrprcf);
	DDX_Control(pDX, IDC_AVRPRC2F, m_avrprc2f);
    DDX_Control(pDX, IDC_AVRPRC21F, m_avrprc21f);
    DDX_Control(pDX, IDC_AVRPRC22F, m_avrprc22f);
	DDX_Control(pDX, IDC_AVRPRC3F, m_avrprc3f);
    DDX_Control(pDX, IDC_AVRPRC31F, m_avrprc31f);
    DDX_Control(pDX, IDC_AVRPRC32F, m_avrprc32f);
	DDX_Control(pDX, IDC_CURVALUEF, m_curvaluef);
	DDX_Control(pDX, IDC_CURVALUEF4, m_curvaluef4);
	DDX_Control(pDX, IDC_FCHG, m_futurechange);
	DDX_Control(pDX, IDC_FCHG2, m_futurechange2);
	DDX_Control(pDX, IDC_DDAY, strDday);
	DDX_Control(pDX, IDC_BCALL, m_bcall);
	DDX_Control(pDX, IDC_BPUT, m_bput);
	DDX_Control(pDX, IDC_BCANCEL, m_bcancel);
	DDX_Control(pDX, IDC_NPROFIT, m_nprofit);
	DDX_Control(pDX, IDC_FVOL, m_fvol);
	DDX_Control(pDX, IDC_FVOL2, m_fvol2);
	DDX_Control(pDX, IDC_CANCELTIME, m_ncanceltime);
	DDX_Control(pDX, IDC_FTRAIL, m_ftrail);
	DDX_Control(pDX, IDC_FVOL3, m_fvol3);
	DDX_Control(pDX, IDC_FVOL4, m_fvol4);
	DDX_Control(pDX, IDC_LREM, m_lrem);
	DDX_Control(pDX, IDC_LREM2, m_lrem2);
	DDX_Control(pDX, IDC_LREM3, m_lrem3);
	DDX_Control(pDX, IDC_LREM5, m_lrem5);
	DDX_Control(pDX, IDC_LREM6, m_lrem6);
	DDX_Control(pDX, IDC_PERCENTD3, m_percentd3);
	DDX_Control(pDX, IDC_PERCENTD4, m_percentd4);
	DDX_Control(pDX, IDC_FUTURE60MA, m_future60ma);
	DDX_Control(pDX, IDC_20MSMA, m_20msma);
	DDX_Control(pDX, IDC_SD, m_sd);
	DDX_Control(pDX, IDC_20MSMA2, m_20msma2);
	DDX_Control(pDX, IDC_SD2, m_sd2);
	DDX_Control(pDX, IDC_BOLGR20, m_bolgr20);
	DDX_Control(pDX, IDC_BOLGR10M, m_bolgr10m);
	DDX_Control(pDX, IDC_PERCENTD5, m_percentd5);
	DDX_Control(pDX, IDC_PERCENTD9, m_percentd9);
	DDX_Control(pDX, IDC_PERCENTD10, m_percentd10);
	DDX_Control(pDX, IDC_PERCENTD11, m_percentd11);
	DDX_Control(pDX, IDC_PERCENTD12, m_percentd12);
	DDX_Control(pDX, IDC_CPOWER, m_cpower);//체결강도
	DDX_Control(pDX, IDC_TAUTO, m_tauto);//오토 텍스트
	DDX_Control(pDX, IDC_TST, m_tst);//오토 텍스트
	DDX_Control(pDX, IDC_TST2, m_tst2);//오토 텍스트
	DDX_Control(pDX, IDC_TST3, m_tst3);//오토 텍스트
	DDX_Control(pDX, IDC_TST4, m_tst4);//오토 텍스트
	DDX_Control(pDX, IDC_TST5, m_tst5);//오토 텍스트
	DDX_Control(pDX, IDC_TST6, m_tst6);//오토 텍스트
	DDX_Control(pDX, IDC_TST7, m_tst7);//오토 텍스트
}

BEGIN_MESSAGE_MAP(CDlg_JEKYLL, CDialog)
	//{{AFX_MSG_MAP(CDlg_JEKYLL)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceiveData)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeoutData)
	ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealData)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, &CDlg_JEKYLL::OnBnClickedButtonRequest)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlg_JEKYLL::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST4, &CDlg_JEKYLL::OnBnClickedButtonRequest4)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST2, &CDlg_JEKYLL::OnBnClickedButtonRequest2)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST3, &CDlg_JEKYLL::OnBnClickedButtonRequest3)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST7, &CDlg_JEKYLL::OnBnClickedButtonRequest7)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST5, &CDlg_JEKYLL::OnBnClickedButtonRequest5)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST6, &CDlg_JEKYLL::OnBnClickedButtonRequest6)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST10, &CDlg_JEKYLL::OnBnClickedButtonRequest10)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST11, &CDlg_JEKYLL::OnBnClickedButtonRequest11)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST12, &CDlg_JEKYLL::OnBnClickedButtonRequest12)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST14, &CDlg_JEKYLL::OnBnClickedButtonRequest14)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST13, &CDlg_JEKYLL::OnBnClickedButtonRequest13)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST19, &CDlg_JEKYLL::OnBnClickedButtonRequest19)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST20, &CDlg_JEKYLL::OnBnClickedButtonRequest20)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST21, &CDlg_JEKYLL::OnBnClickedButtonRequest21)
	ON_WM_TIMER()
	//ON_NOTIFY(NM_CLICK, IDC_600, &CDlg_JEKYLL::OnNMClick600)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTONPROFIT, &CDlg_JEKYLL::OnBnClickedButtonprofit)
	ON_BN_CLICKED(IDC_BUTTONPROFIT2, &CDlg_JEKYLL::OnBnClickedButtonprofit2)
	ON_BN_CLICKED(IDC_BUTTONPROFIT3, &CDlg_JEKYLL::OnBnClickedButtonprofit3)
	ON_BN_CLICKED(IDC_BUTTONPROFIT9, &CDlg_JEKYLL::OnBnClickedButtonprofit9)
	ON_BN_CLICKED(IDC_BUTTONPROFIT11, &CDlg_JEKYLL::OnBnClickedButtonprofit11)
	ON_BN_CLICKED(IDC_BUTTONPROFIT16, &CDlg_JEKYLL::OnBnClickedButtonprofit16)
	ON_BN_CLICKED(IDC_BUTTONPROFIT17, &CDlg_JEKYLL::OnBnClickedButtonprofit17)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_1601, OnCustomdrawList)// 2번째 인자 : List Control ID, 3번째 인자 : 실행할 함수
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_2105, OnCustomdrawList2105)// 2번째 인자 : List Control ID, 3번째 인자 : 실행할 함수
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_2105_2, OnCustomdrawList2105B)// 2번째 인자 : List Control ID, 3번째 인자 : 실행할 함수
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_2105_3, OnCustomdrawList2105C)// 2번째 인자 : List Control ID, 3번째 인자 : 실행할 함수
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CDlg_JEKYLL::OnDeltaposSpin3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CDlg_JEKYLL::OnDeltaposSpin4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &CDlg_JEKYLL::OnDeltaposSpin5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CDlg_JEKYLL::OnDeltaposSpin6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDlg_JEKYLL::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CDlg_JEKYLL::OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, &CDlg_JEKYLL::OnDeltaposSpin7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN8, &CDlg_JEKYLL::OnDeltaposSpin8)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST8, &CDlg_JEKYLL::OnBnClickedButtonRequest8)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST9, &CDlg_JEKYLL::OnBnClickedButtonRequest9)
	ON_BN_CLICKED(IDC_BUTTONPROFIT18, &CDlg_JEKYLL::OnBnClickedButtonprofit18)
	ON_BN_CLICKED(IDC_BUTTONPROFIT19, &CDlg_JEKYLL::OnBnClickedButtonprofit19)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN11, &CDlg_JEKYLL::OnDeltaposSpin11)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN12, &CDlg_JEKYLL::OnDeltaposSpin12)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN16, &CDlg_JEKYLL::OnDeltaposSpin16)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN17, &CDlg_JEKYLL::OnDeltaposSpin17)
	ON_BN_CLICKED(IDC_BUTTONPROFIT4, &CDlg_JEKYLL::OnBnClickedButtonprofit4)
	ON_NOTIFY(NM_CLICK, IDC_2105, &CDlg_JEKYLL::OnClick2105)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN13, &CDlg_JEKYLL::OnDeltaposSpin13)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN14, &CDlg_JEKYLL::OnDeltaposSpin14)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN9, &CDlg_JEKYLL::OnDeltaposSpin9)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN24, &CDlg_JEKYLL::OnDeltaposSpin24)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN10, &CDlg_JEKYLL::OnDeltaposSpin10)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN26, &CDlg_JEKYLL::OnDeltaposSpin26)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN23, &CDlg_JEKYLL::OnDeltaposSpin23)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN25, &CDlg_JEKYLL::OnDeltaposSpin25)
	ON_NOTIFY(NM_CLICK, IDC_2105_2, &CDlg_JEKYLL::OnClick21052)
	ON_NOTIFY(NM_CLICK, IDC_2105_3, &CDlg_JEKYLL::OnClick21053)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN27, &CDlg_JEKYLL::OnDeltaposSpin27)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN28, &CDlg_JEKYLL::OnDeltaposSpin28)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN29, &CDlg_JEKYLL::OnDeltaposSpin29)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN30, &CDlg_JEKYLL::OnDeltaposSpin30)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN31, &CDlg_JEKYLL::OnDeltaposSpin31)
	ON_BN_CLICKED(IDC_CHECKOPTION1, &CDlg_JEKYLL::OnClickedCheckoption1)
	ON_BN_CLICKED(IDC_CHECKOPTION2, &CDlg_JEKYLL::OnClickedCheckoption2)
	ON_BN_CLICKED(IDC_CHECKOPTION3, &CDlg_JEKYLL::OnClickedCheckoption3)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN15, &CDlg_JEKYLL::OnDeltaposSpin15)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN32, &CDlg_JEKYLL::OnDeltaposSpin32)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN33, &CDlg_JEKYLL::OnDeltaposSpin33)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN34, &CDlg_JEKYLL::OnDeltaposSpin34)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_JEKYLL message handlers

BOOL CDlg_JEKYLL::OnInitDialog()//추가 공휴일 있을경우 설정필요
{
	CDialog::OnInitDialog();
	InitCtrls();

	CString str; CEdit* pEdit1, * pEdit2, * pEdit3, * pEdit4;

	CTime t = CTime::GetCurrentTime(); // ****************************************************************************** 오늘과 어제 날짜를 구하는 코드
	strDate = t.Format("%Y%m%d");

	// 요일을 구하는 코드 (일요일=1, 월요일=2, ..., 토요일=7)
	int nToday = t.GetDayOfWeek();

	CTime tYesterday;
	CTimeSpan oneDay(1, 0, 0, 0); // 1일을 나타내는 CTimeSpan 객체

	// 요일에 따른 어제의 날짜를 구하는 조건문
	if (nToday == 2) { // 오늘이 월요일인 경우
		tYesterday = t - CTimeSpan(3, 0, 0, 0); // 3일 전 (금요일)
	}
	else if (nToday == 1) { // 오늘이 일요일인 경우
		tYesterday = t - CTimeSpan(2, 0, 0, 0); // 2일 전 (금요일)
	}
	else { // 평일인 경우
		tYesterday = t - oneDay; // 1일 전
	}
	strDateY = tYesterday.Format("%Y%m%d");

	// ******************************************************************************************************************* 오늘과 어제 날짜를 구하는 코드
	// 
	// Initialize checkboxes to unchecked
	((CButton*)GetDlgItem(IDC_CHECKOPTION1))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_CHECKOPTION2))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECKOPTION3))->SetCheck(BST_UNCHECKED);

	// Set initial count to 0
	nCheckedCount = 1;
	str.Format("%d", nCheckedCount);
	pEdit1 = (CEdit*)GetDlgItem(IDC_TST8); pEdit1->SetWindowText(str);// nCheckedCount 확인

	fFutPrc = 0.0;

	bSetPrice = FALSE; // 토큰 code2/code3 가격 세팅 한번만

	nSellOption = 0;//0:nProfit, 1:fProfit

	// 잔량
	lRemQty = 0, lRemHighest = -10000, lRemLowest = 10000;
	lRemHtime = 0, lRemLtime = 0;

	// 최고가
	fmaxCHo = 0.0, fmaxPHo = 0.0;
	nCtime = 0, nPtime = 0;

	// 양매도 수량
	nCall = 0, nPut = 0;

	// 시뮬레이션 변수
	fSimCPrc = 0.0, fSimPPrc = 0.0;
	nCqty = 0, nPqty = 0;
	nSelltime = 0, nCase = 0, nBuytime = 0;
	bTrail = 0, bCC = 0;

	// CheckCondition 변수
	bCCoption = 0, bCCact = 0; //Call, deact
	fCCprc = 0.0, fpreCCprc = 0.0; //가격
	nCCamnt = 0, nCCmin=0;//수량, 시작시간

	// 콜풋 현재가
	fCho8 = 0.0, fCho9 = 0.0, fPho8 = 0.0, fPho9 = 0.0;
	lCho8 = 0, lPho8 = 0, lCho9 = 0, lPho9 = 0;


	pEdit1 = (CEdit*)GetDlgItem(IDC_REF); str.Format("%.2f",0.77); pEdit1->SetWindowText(str);//옵션 기준가격 설정 **************************************************************************************

	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); str.Format("%.2f", 1.0); pEdit1->SetWindowText(str);//기준가격 1.43
	pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", 1.00); pEdit2->SetWindowText(str);//원하는 이익
	pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
	pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격

	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); str.Format("%.2f", 0.5); pEdit1->SetWindowText(str);//기준가격 0.50
	pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC7); str.Format("%.2f", 0.5); pEdit2->SetWindowText(str);//원하는 이익
	pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC9); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격

	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); str.Format("%.2f", 0.25); pEdit1->SetWindowText(str);//기준가격 0.13
	pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC11); str.Format("%.2f", 0.25); pEdit2->SetWindowText(str);//원하는 이익
	//pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC12); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 
	pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC13); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격

	pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC8); str.Format("%d", 30); pEdit3->SetWindowText(str);// 기준가격을 해당 %로 낮춤
	pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC14); str.Format("%d", 50); pEdit3->SetWindowText(str);//공통 이익률 %

	bToken = FALSE;//옵션전광판 콜/풋코드를 받은뒤 bToken값을 1로 변경(코드 유지)
	bAutoToken = TRUE; //자동옵션매수 설정 on/off 볼린저밴드상하단 1포인트 이상 초과시
	bCall = TRUE, bPut = TRUE;
	bCancel = FALSE;//구매취소 비활성화

	bFC0 = 1;//FC0에서 거래량 데이터 시작되면 CNCT7 버튼누름

	nCancelTime = 0, nSaveTime = 0;
	CString strInit;	strInit.Format("%d", nCancelTime); m_ncanceltime.SetWindowTextA(strInit);

	//bSearch = TRUE;
	fTrailingHigh = 0.0, fHighest = 0.0, fLowest = 0.0;
	CString ctrail; ctrail.Format("%.3f", fTrailingHigh); m_ftrail.SetWindowTextA(ctrail);

	// 이익률 설정하기  ****************************************************************************************************************
	nProfit = 200; nGoalTrend = 70; nGoalFlat = 15;
	lLqdt = 0, lNewSell = -1, lCallAvrPrc = 0, lPutAvrPrc = 0, lBalance = 0, lMaxBalance = 0, fCallHigh = 0.0, fCallLow = 10.0, fPutHigh = 0.0, fPutLow = 10.0;
	fCallSellPrc = 0.0, fPutSellPrc = 0.0;
	fCallOpen = 0.0, fPutOpen = 0.0;
	nCorrectTime = 0;
	if (nProfit > 20)
		((CButton*)GetDlgItem(IDC_CHECKTRAIL))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_CHECKTRAIL))->SetCheck(0);

	// ************************************************************************************************************************************  strMonth 코드 구하기
	CTime currentTime = CTime::GetCurrentTime();
	int year = currentTime.GetYear();
	int month = currentTime.GetMonth();
	int day = currentTime.GetDay();
	int hour = currentTime.GetHour();

	// Increase the day by 1 if the time is after 16:00
	CTime adjustedTime = currentTime;
	if (hour >= 16) {
		adjustedTime = currentTime + oneDay;
		day = adjustedTime.GetDay();
	}
	CTime date(year, month, 1, 0, 0, 0);
	int weekday = date.GetDayOfWeek(); // Sunday=1, Monday=2, ..., Saturday=7

	if (weekday > 5 || weekday < 3)// 목요일보다 크거나 화요일보다 작으면( 금, 토, 일, 월) 첫번째 월요일이 먼저 시작함
		strMonth = "W1MON";
	else strMonth = "W1THU";

	int nMonday = 1;
	int nThursday = 1;

	if (day > 1) {
		for (int d = 2; d <= day; ++d) {
			CTime dateY(year, month, d - 1, 0, 0, 0);
			int weekdayY = dateY.GetDayOfWeek(); // Sunday=1, Monday=2, ..., Saturday=7
			if (weekdayY == 2) { // 어제가 월요일이면 목요일로 설정
				strMonth.Format(_T("W%dTHU"), nThursday);
				++nMonday;
			}
			else if (weekdayY == 5) { // 어제가 목요일이면 월요일로 설정
				strMonth.Format(_T("W%dMON"), nMonday);
				++nThursday;
			}
		}
		if (strMonth == "W2THU")
		{
			strMonth = adjustedTime.Format(_T("%Y%m"));
		}
	}
	//strMonth = "W2MON"; //************************************************************************************************************* 월설정
	//pEdit1 = (CEdit*)GetDlgItem(IDC_TST2); pEdit1->SetWindowText(strMonth);// strMonth 확인

	// nCurMin 값 초기화
	nCurMin = 411;
	nCurSec = 0;

	// 선물코드 및 0.3에 가까운 옵션코드 계산하여 각종 파라미터 저장 --------------------------------

	Request2301(strMonth);//옵션전광판

	m_avrprc2.SetWindowTextA("0");
	m_avrprc2f.SetWindowTextA("0");

	m_tauto.SetWindowTextA("Ready");

	// moment 매수 매도 초기화
	((CButton*)GetDlgItem(IDC_CHECKMOMENT))->SetCheck(0);

	ofstream myfileGetdata("FindMoment.csv");								// 속도 감시
	if (myfileGetdata.is_open())
	{
		myfileGetdata << "시간, 매수체결량, +속도, 매도체결량, -속도, 잔량, 콜8, 수량8, 풋8, 수량8, 콜경과시간, 콜평균시간, 풋경과시간, 풋평균시간\n";
	}
	myfileGetdata.close();

	ofstream myfileRecording("RecordOrder.csv");								// 주문 기록
	if (myfileRecording.is_open())
	{
		myfileRecording << "시간, 매수매도, 코드, 가격, 수량\n";
	}
	myfileRecording.close();	


	ofstream myfileRecording2("RecordOrder2.csv");								// 시뮬레이션 주문기록
	if (myfileRecording2.is_open())
	{
		myfileRecording2 << "시간, 매수매도, 코드, 가격, 수량\n";
	}
	myfileRecording2.close();


	nIndex = 0;
	nBuyTestCount = 0;

	f60mEMAY = 0.0;

	gIter = new int[3];
	strArTime1602 = new CString[830];
	CallCode = new CString[5];
	PutCode = new CString[5];
	lCallQty = new long[5];
	lPutQty = new long[5];
	fCallAvrPrc = new float[5];
	fPutAvrPrc = new float[5];
	lArForVol = new long[830];
	lArSecVol = new long[830];
	lArForVol2 = new long[420];
	lArSecVol2 = new long[420];
	lArForVol5m = new long[420];
	lArSecVol5m = new long[420];
	lArKoForVol = new long[830];
	lArKoSecVol = new long[830];
	lArKoForVol2 = new long[420];
	lArKoSecVol2 = new long[420];
	lArKoForVol5m = new long[420];
	lArKoSecVol5m = new long[420];

	lArRemClose = new long[420];
	lArRemHigh = new long[420];
	lArRemLow = new long[420];

	strArTime8415 = new CString[420];
	fArOpen = new float[420];
	fArClose = new float[420];
	fArCloseY = new float[411];
	fArHigh = new float[420];
	fArLow = new float[420];

	fArCClose = new float[420];
	fArPClose = new float[420];

	fAr10mOpen = new float[42];
	fAr10mClose = new float[42];
	fAr10mHigh = new float[42];
	fAr10mLow = new float[42];

	fAr10mCloseY = new float[42];
	fAr10mHighY = new float[42];
	fAr10mLowY = new float[42];
	fAr10mKY = new float[42];
	fAr10mDY = new float[42];
	fAr10mSlowDY = new float[42];

	fArWidth = new float[420];
	lArVol = new long[420];
	lArVol2 = new long[420];
	fAr10mK = new float[42];
	fAr10mD = new float[42];
	fAr10mSlowD = new float[42];

	fAr10m20mSMA = new float[42];
	fAr10m20mSMAY = new float[42];
	fAr10m20mSD = new float[42];
	fAr10m20mSDY = new float[42];

	fAr20mSMA = new float[420];
	fAr20mSMAY = new float[411];
	fAr20mSD = new float[420];
	fAr60mSMA = new float[420];
	fArMin60m = new float[420];
	fArMax60m = new float[420];
	fArMax30m = new float[420];
	fArMin30m = new float[420];

	nArUpdateHigh = new int[420];
	nArUpdateLow = new int[420];
	nArMax30m = new int[420];
	nArMin30m = new int[420];

	fArSNPClose = new float[60];
	fArSNPHigh = new float[60];
	fArSNPLow = new float[60];
	fArSNPK = new float[60];
	fArSNPD = new float[60];
	fArSNPSlowD = new float[60];
	fArSNP20mSMA = new float[60];
	fArSNP20mSD = new float[60];

	memset(gIter, 0, 3 * sizeof(int));

	memset(fCallAvrPrc, 0, 5 * sizeof(float));
	memset(fPutAvrPrc, 0, 5 * sizeof(float));

	memset(fArOpen, 0, 420 * sizeof(float));
	memset(fArClose, 0, 420 * sizeof(float));
	memset(fArHigh, 0, 420 * sizeof(float));
	memset(fArLow, 0, 420 * sizeof(float));

	memset(fArCClose, 0, 420 * sizeof(float));
	memset(fArPClose, 0, 420 * sizeof(float));

	memset(fArCloseY, 0, 411 * sizeof(float));
	memset(fAr10mOpen, 0, 42 * sizeof(float));
	memset(fAr10mClose, 0, 42 * sizeof(float));
	memset(fAr10mHigh, 0, 42 * sizeof(float));
	memset(fAr10mLow, 0, 42 * sizeof(float));

	memset(fAr10mCloseY, 0, 42 * sizeof(float));
	memset(fAr10mHighY, 0, 42 * sizeof(float));
	memset(fAr10mLowY, 0, 42 * sizeof(float));
	memset(fAr10mKY, 0, 42 * sizeof(float));
	memset(fAr10mDY, 0, 42 * sizeof(float));
	memset(fAr10mSlowDY, 0, 42 * sizeof(float));

	memset(fArWidth, 0, 420 * sizeof(float));
	memset(fAr10mK, 0, 42 * sizeof(float));
	memset(fAr10mD, 0, 42 * sizeof(float));
	memset(fAr10mSlowD, 0, 42 * sizeof(float));

	memset(fAr10m20mSMA, 0, 42 * sizeof(float));
	memset(fAr10m20mSMAY, 0, 42 * sizeof(float));
	memset(fAr10m20mSD, 0, 42 * sizeof(float));
	memset(fAr10m20mSDY, 0, 42 * sizeof(float));

	memset(fAr20mSMA, 0, 420 * sizeof(float));
	memset(fAr20mSMAY, 0, 411 * sizeof(float));
	memset(fAr20mSD, 0, 420 * sizeof(float));
	memset(fAr60mSMA, 0, 420 * sizeof(float));
	memset(fArMin60m, 0, 420 * sizeof(float));
	memset(fArMax60m, 0, 420 * sizeof(float));
	memset(fArMax30m, 0, 420 * sizeof(float));
	memset(fArMin30m, 0, 420 * sizeof(float));

	memset(lCallQty, 0, 3 * sizeof(long));
	memset(lPutQty, 0, 3 * sizeof(long));
	memset(lArVol, 0, 420 * sizeof(long));
	memset(lArVol2, 0, 420 * sizeof(long));

	memset(lArForVol, 0, 830 * sizeof(long));
	memset(lArSecVol, 0, 830 * sizeof(long));
	memset(lArForVol2, 0, 420 * sizeof(long));
	memset(lArSecVol2, 0, 420 * sizeof(long));
	memset(lArForVol5m, 0, 420 * sizeof(long));
	memset(lArSecVol5m, 0, 420 * sizeof(long));

	memset(lArKoForVol, 0, 830 * sizeof(long));
	memset(lArKoSecVol, 0, 830 * sizeof(long));
	memset(lArKoForVol2, 0, 420 * sizeof(long));
	memset(lArKoSecVol2, 0, 420 * sizeof(long));
	memset(lArKoForVol5m, 0, 420 * sizeof(long));
	memset(lArKoSecVol5m, 0, 420 * sizeof(long));

	memset(lArRemClose, 0, 420 * sizeof(long));
	memset(lArRemHigh, 0, 420 * sizeof(long));
	memset(lArRemLow, 0, 420 * sizeof(long));

	memset(nArUpdateHigh, 0, 420 * sizeof(int));
	memset(nArUpdateLow, 0, 420 * sizeof(int));
	memset(nArMax30m, 0, 420 * sizeof(int));
	memset(nArMin30m, 0, 420 * sizeof(int));

	memset(fArSNPClose, 0, 60 * sizeof(float));
	memset(fArSNPHigh, 0, 60 * sizeof(float));
	memset(fArSNPLow, 0, 60 * sizeof(float));
	memset(fArSNPK, 0, 60 * sizeof(float));
	memset(fArSNPD, 0, 60 * sizeof(float));
	memset(fArSNPSlowD, 0, 60 * sizeof(float));
	memset(fArSNP20mSMA, 0, 60 * sizeof(float));
	memset(fArSNP20mSD, 0, 60 * sizeof(float));


	pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_JEKYLL::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	KillTimer(5);
	KillTimer(6);
	KillTimer(7);
	KillTimer(8);
	KillTimer(9);
	KillTimer(10);
	KillTimer(11);
	KillTimer(12);
	KillTimer(13);
	KillTimer(14);
	KillTimer(15);
	KillTimer(16);
	KillTimer(17);
	KillTimer(18);

	UnadviseFC0();
	UnadviseFH0();
	UnadviseOVC();
	UnadviseOVC2();
	//UnadviseBMT();
	//UnadviseBMT2();

	delete[] gIter;
	delete[] strArTime8415;	delete[] strArTime1602; delete[] CallCode; delete[] PutCode;
	delete[] fCallAvrPrc; delete[] fPutAvrPrc;
	delete[] fArOpen;	delete[] fArClose;	delete[] fArCloseY;	delete[] fArHigh;	delete[] fArLow;	delete[] fAr10mOpen;	delete[] fAr10mClose;	delete[] fAr10mHigh;	delete[] fAr10mLow;
	delete[] fArCClose; delete[] fArPClose;
	delete[] fArWidth;	delete[] fAr10mCloseY;	delete[] fAr10mHighY;	delete[] fAr10mLowY;	delete[] fAr10mKY;	delete[] fAr10mDY;	delete[] fAr10mSlowDY;
	delete[] fAr10mK;	delete[] fAr10mD;  delete[] fAr10mSlowD;  delete[] fAr20mSMA; delete[] fAr20mSMAY; delete[] fAr20mSD; delete[] fAr10m20mSMA; delete[] fAr10m20mSMAY; delete[] fAr10m20mSD; delete[] fAr10m20mSDY;
	delete[] fAr60mSMA; delete[] fArMin60m; delete[] fArMax60m;
	delete[] fArMax30m; delete[] fArMin30m;
	delete[] lCallQty; delete[] lPutQty;
	delete[] lArKoForVol;	delete[] lArKoSecVol;		delete[] lArForVol;	delete[] lArSecVol;		delete[] lArVol; delete[] lArVol2;  delete[] lArRemClose; delete[] lArRemHigh; delete[] lArRemLow;
	delete[] lArKoForVol2;	delete[] lArKoSecVol2;	delete[] lArKoForVol5m;	delete[] lArKoSecVol5m;
	delete[] lArForVol2;	delete[] lArSecVol2;	delete[] lArForVol5m;	delete[] lArSecVol5m;
	delete[] nArUpdateHigh; delete[] nArUpdateLow;  delete[] nArMax30m; delete[] nArMin30m;
	delete[] fArSNPClose;	delete[] fArSNPHigh;	delete[] fArSNPLow; delete[] fArSNPK;	delete[] fArSNPD;  delete[] fArSNPSlowD; delete[] fArSNP20mSMA; delete[] fArSNP20mSD;

	gIter = NULL;
	strArTime8415 = NULL;	strArTime1602 = NULL; CallCode = NULL; PutCode = NULL;
	fCallAvrPrc = NULL; fPutAvrPrc = NULL;
	fArOpen = NULL;	fArClose = NULL;	fArCloseY = NULL; fArHigh = NULL;	fArLow = NULL;	fAr10mOpen = NULL;	fAr10mClose = NULL;	fAr10mHigh = NULL;	fAr10mLow = NULL;
	fArCClose = NULL; fArPClose = NULL;
	fArWidth = NULL;	 fAr10mCloseY = NULL;	fAr10mHighY = NULL;	fAr10mLowY = NULL; fAr10mKY = NULL; fAr10mDY = NULL; fAr10mSlowDY = NULL;
	fAr10mK = NULL;	fAr10mD = NULL; fAr10mSlowD = NULL;	fAr20mSMA = NULL; fAr20mSMAY = NULL; fAr20mSD = NULL; fAr10m20mSMA = NULL; fAr10m20mSMAY = NULL; fAr10m20mSD = NULL; fAr10m20mSDY = NULL;
	fAr60mSMA = NULL; fArMin60m = NULL; fArMax60m = NULL;
	fArMax30m = NULL; fArMin30m = NULL;
	lCallQty = NULL; lPutQty = NULL;
	lArKoForVol = NULL;	lArKoSecVol = NULL;	lArForVol = NULL;	lArSecVol = NULL;	lArVol = NULL; lArVol2 = NULL;  lArRemClose = NULL; lArRemHigh = NULL; lArRemLow = NULL;
	lArKoForVol2 = NULL;	lArKoSecVol2 = NULL;	lArKoForVol5m = NULL;	lArKoSecVol5m = NULL;
	lArForVol2 = NULL;	lArSecVol2 = NULL;	lArForVol5m = NULL;	lArSecVol5m = NULL;
	nArUpdateHigh = NULL; nArUpdateLow = NULL;  nArMax30m = NULL; nArMin30m = NULL;
	fArSNPClose = NULL;	fArSNPHigh = NULL;	fArSNPLow = NULL; fArSNPK = NULL;	fArSNPD = NULL; fArSNPSlowD = NULL; fArSNP20mSMA = NULL; fArSNP20mSD = NULL;

	while (!fQCHo.empty()) fQCHo.pop();  queue<float>().swap(fQCHo);
	while (!fQPHo.empty()) fQPHo.pop(); queue<float>().swap(fQPHo);
	while (!lQRem.empty()) lQRem.pop(); queue<long>().swap(lQRem);
	while (!lQvol1.empty()) lQvol1.pop(); queue<long>().swap(lQvol1);
	while (!lQvol2.empty()) lQvol2.pop(); queue<long>().swap(lQvol2);
	while (!strQtime1.empty()) strQtime1.pop(); queue<CString>().swap(strQtime1);
	while (!strQtime2.empty()) strQtime2.pop(); queue<CString>().swap(strQtime2);
	while (!fQprc.empty()) fQprc.pop(); queue<float>().swap(fQprc);
	while (!CmpQtime1.empty()) CmpQtime1.pop(); queue<int>().swap(CmpQtime1);
	while (!CmpQtime2.empty()) CmpQtime2.pop(); queue<int>().swap(CmpQtime2);
	while (!CmpQvol1.empty()) CmpQvol1.pop(); queue<int>().swap(CmpQvol1);
	while (!CmpQvol2.empty()) CmpQvol2.pop(); queue<int>().swap(CmpQvol2);
	while (!nQSellQty.empty()) nQSellQty.pop(); queue<int>().swap(nQSellQty);
	while (!fQSellPrc.empty()) fQSellPrc.pop(); queue<float>().swap(fQSellPrc);
	// TODO: Add your message handler code here
}

BOOL CDlg_JEKYLL::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	KillTimer(5);
	KillTimer(6);
	KillTimer(7);
	KillTimer(8);
	KillTimer(9);
	KillTimer(10);
	KillTimer(11);
	KillTimer(12);
	KillTimer(13);
	KillTimer(14);
	KillTimer(15);
	KillTimer(16);
	KillTimer(17);
	KillTimer(18);

	UnadviseFC0();
	UnadviseFH0();
	UnadviseOVC();
	UnadviseOVC2();
	//UnadviseBMT();
	//UnadviseBMT2();

	delete[] gIter;
	delete[] strArTime8415;	delete[] strArTime1602; delete[] CallCode; delete[] PutCode;
	delete[] fCallAvrPrc; delete[] fPutAvrPrc;
	delete[] fArOpen;	delete[] fArClose;	delete[] fArCloseY;	delete[] fArHigh;	delete[] fArLow;	delete[] fAr10mOpen;	delete[] fAr10mClose;	delete[] fAr10mHigh;	delete[] fAr10mLow;
	delete[] fArCClose; delete[] fArPClose;
	delete[] fArWidth;	delete[] fAr10mCloseY;	delete[] fAr10mHighY;	delete[] fAr10mLowY;	delete[] fAr10mKY;	delete[] fAr10mDY;	delete[] fAr10mSlowDY;
	delete[] fAr10mK;	delete[] fAr10mD;  delete[] fAr10mSlowD;  delete[] fAr20mSMA; delete[] fAr20mSMAY; delete[] fAr20mSD; delete[] fAr10m20mSMA; delete[] fAr10m20mSMAY; delete[] fAr10m20mSD; delete[] fAr10m20mSDY;
	delete[] fAr60mSMA; delete[] fArMin60m; delete[] fArMax60m;
	delete[] fArMax30m; delete[] fArMin30m;
	delete[] lCallQty; delete[] lPutQty;
	delete[] lArKoForVol;	delete[] lArKoSecVol;		delete[] lArForVol;	delete[] lArSecVol;		delete[] lArVol; delete[] lArVol2;  delete[] lArRemClose; delete[] lArRemHigh; delete[] lArRemLow;
	delete[] lArKoForVol2;	delete[] lArKoSecVol2;	delete[] lArKoForVol5m;	delete[] lArKoSecVol5m;
	delete[] lArForVol2;	delete[] lArSecVol2;	delete[] lArForVol5m;	delete[] lArSecVol5m;
	delete[] nArUpdateHigh; delete[] nArUpdateLow;  delete[] nArMax30m; delete[] nArMin30m;
	delete[] fArSNPClose;	delete[] fArSNPHigh;	delete[] fArSNPLow; delete[] fArSNPK;	delete[] fArSNPD;  delete[] fArSNPSlowD; delete[] fArSNP20mSMA; delete[] fArSNP20mSD;

	gIter = NULL;
	strArTime8415 = NULL;	strArTime1602 = NULL; CallCode = NULL; PutCode = NULL;
	fCallAvrPrc = NULL; fPutAvrPrc = NULL;
	fArOpen = NULL;	fArClose = NULL;	fArCloseY = NULL; fArHigh = NULL;	fArLow = NULL;	fAr10mOpen = NULL;	fAr10mClose = NULL;	fAr10mHigh = NULL;	fAr10mLow = NULL;
	fArCClose = NULL; fArPClose = NULL;
	fArWidth = NULL;	 fAr10mCloseY = NULL;	fAr10mHighY = NULL;	fAr10mLowY = NULL; fAr10mKY = NULL; fAr10mDY = NULL; fAr10mSlowDY = NULL;
	fAr10mK = NULL;	fAr10mD = NULL; fAr10mSlowD = NULL;	fAr20mSMA = NULL; fAr20mSMAY = NULL; fAr20mSD = NULL; fAr10m20mSMA = NULL; fAr10m20mSMAY = NULL; fAr10m20mSD = NULL; fAr10m20mSDY = NULL;
	fAr60mSMA = NULL; fArMin60m = NULL; fArMax60m = NULL;
	fArMax30m = NULL; fArMin30m = NULL;
	lCallQty = NULL; lPutQty = NULL;
	lArKoForVol = NULL;	lArKoSecVol = NULL;	lArForVol = NULL;	lArSecVol = NULL;	lArVol = NULL; lArVol2 = NULL;  lArRemClose = NULL; lArRemHigh = NULL; lArRemLow = NULL;
	lArKoForVol2 = NULL;	lArKoSecVol2 = NULL;	lArKoForVol5m = NULL;	lArKoSecVol5m = NULL;
	lArForVol2 = NULL;	lArSecVol2 = NULL;	lArForVol5m = NULL;	lArSecVol5m = NULL;
	nArUpdateHigh = NULL; nArUpdateLow = NULL;  nArMax30m = NULL; nArMin30m = NULL;
	fArSNPClose = NULL;	fArSNPHigh = NULL;	fArSNPLow = NULL; fArSNPK = NULL;	fArSNPD = NULL; fArSNPSlowD = NULL; fArSNP20mSMA = NULL; fArSNP20mSD = NULL;


	while (!fQCHo.empty()) fQCHo.pop();  queue<float>().swap(fQCHo);
	while (!fQPHo.empty()) fQPHo.pop(); queue<float>().swap(fQPHo);
	while (!lQRem.empty()) lQRem.pop(); queue<long>().swap(lQRem);
	while (!lQvol1.empty()) lQvol1.pop(); queue<long>().swap(lQvol1);
	while (!lQvol2.empty()) lQvol2.pop(); queue<long>().swap(lQvol2);
	while (!strQtime1.empty()) strQtime1.pop(); queue<CString>().swap(strQtime1);
	while (!strQtime2.empty()) strQtime2.pop(); queue<CString>().swap(strQtime2);
	while (!fQprc.empty()) fQprc.pop(); queue<float>().swap(fQprc);
	while (!CmpQtime1.empty()) CmpQtime1.pop(); queue<int>().swap(CmpQtime1);
	while (!CmpQtime2.empty()) CmpQtime2.pop(); queue<int>().swap(CmpQtime2);
	while (!CmpQvol1.empty()) CmpQvol1.pop(); queue<int>().swap(CmpQvol1);
	while (!CmpQvol2.empty()) CmpQvol2.pop(); queue<int>().swap(CmpQvol2);
	while (!nQSellQty.empty()) nQSellQty.pop(); queue<int>().swap(nQSellQty);
	while (!fQSellPrc.empty()) fQSellPrc.pop(); queue<float>().swap(fQSellPrc);

	return CDialog::DestroyWindow();
}

//--------------------------------------------------------------------------------------
// 컨트롤 초기화
//--------------------------------------------------------------------------------------
void CDlg_JEKYLL::InitCtrls()
{
	m_lst2105.InsertColumn(0, "필드명", LVCFMT_LEFT, 150);
	m_lst2105.InsertColumn(1, "데이터", LVCFMT_LEFT, 200);

	// Call List Control에 OutBlock 필드명을 넣어준다.
	m_lst2105.InsertItem(0, "종목명            ");
	m_lst2105.InsertItem(1, "현재가");
	m_lst2105.InsertItem(2, "전일대비구분      ");
	m_lst2105.InsertItem(3, "전일대비          ");
	m_lst2105.InsertItem(4, "등락율            ");
	m_lst2105.InsertItem(5, "거래량        ");
	m_lst2105.InsertItem(6, "거래량동시간비 ");
	m_lst2105.InsertItem(7, "전일종가          ");
	m_lst2105.InsertItem(8, "매도호가1         ");
	m_lst2105.InsertItem(9, "매수호가1         ");
	m_lst2105.InsertItem(10, "매도호가수량1");
	m_lst2105.InsertItem(11, "매수호가수량1");
	m_lst2105.InsertItem(12, "매도호가건수1 ");
	m_lst2105.InsertItem(13, "매수호가건수1 ");
	m_lst2105.InsertItem(14, "매도호가2         ");
	m_lst2105.InsertItem(15, "매수호가2         ");
	m_lst2105.InsertItem(16, "매도호가수량2     ");
	m_lst2105.InsertItem(17, "매수호가수량2     ");
	m_lst2105.InsertItem(18, "매도호가건수2 ");
	m_lst2105.InsertItem(19, "매수호가건수2 ");
	m_lst2105.InsertItem(20, "매도호가총수량    ");
	m_lst2105.InsertItem(21, "매수호가총수량    ");
	m_lst2105.InsertItem(22, "총매도호가건수");
	m_lst2105.InsertItem(23, "총매수호가건수");
	m_lst2105.InsertItem(24, "수신시간          ");
	m_lst2105.InsertItem(25, "단축코드          ");

	m_lst2105_.InsertColumn(0, "필드명", LVCFMT_LEFT, 150);
	m_lst2105_.InsertColumn(1, "데이터", LVCFMT_LEFT, 200);

	// Put List Control에 OutBlock 필드명을 넣어준다.
	m_lst2105_.InsertItem(0, "종목명            ");
	m_lst2105_.InsertItem(1, "현재가");
	m_lst2105_.InsertItem(2, "전일대비구분      ");
	m_lst2105_.InsertItem(3, "전일대비          ");
	m_lst2105_.InsertItem(4, "등락율            ");
	m_lst2105_.InsertItem(5, "거래량        ");
	m_lst2105_.InsertItem(6, "거래량동시간비 ");
	m_lst2105_.InsertItem(7, "전일종가          ");
	m_lst2105_.InsertItem(8, "매도호가1         ");
	m_lst2105_.InsertItem(9, "매수호가1         ");
	m_lst2105_.InsertItem(10, "매도호가수량1");
	m_lst2105_.InsertItem(11, "매수호가수량1");
	m_lst2105_.InsertItem(12, "매도호가건수1 ");
	m_lst2105_.InsertItem(13, "매수호가건수1 ");
	m_lst2105_.InsertItem(14, "매도호가2         ");
	m_lst2105_.InsertItem(15, "매수호가2         ");
	m_lst2105_.InsertItem(16, "매도호가수량2     ");
	m_lst2105_.InsertItem(17, "매수호가수량2     ");
	m_lst2105_.InsertItem(18, "매도호가건수2 ");
	m_lst2105_.InsertItem(19, "매수호가건수2 ");
	m_lst2105_.InsertItem(20, "매도호가총수량    ");
	m_lst2105_.InsertItem(21, "매수호가총수량    ");
	m_lst2105_.InsertItem(22, "총매도호가건수");
	m_lst2105_.InsertItem(23, "총매수호가건수");
	m_lst2105_.InsertItem(24, "수신시간          ");
	m_lst2105_.InsertItem(25, "단축코드          ");


	m_lst2105__.InsertColumn(0, "필드명", LVCFMT_LEFT, 150);
	m_lst2105__.InsertColumn(1, "데이터", LVCFMT_LEFT, 200);

	// Put List Control에 OutBlock 필드명을 넣어준다.
	m_lst2105__.InsertItem(0, "종목명            ");
	m_lst2105__.InsertItem(1, "현재가");
	m_lst2105__.InsertItem(2, "전일대비구분      ");
	m_lst2105__.InsertItem(3, "전일대비          ");
	m_lst2105__.InsertItem(4, "등락율            ");
	m_lst2105__.InsertItem(5, "거래량        ");
	m_lst2105__.InsertItem(6, "거래량동시간비 ");
	m_lst2105__.InsertItem(7, "전일종가          ");
	m_lst2105__.InsertItem(8, "매도호가1         ");
	m_lst2105__.InsertItem(9, "매수호가1         ");
	m_lst2105__.InsertItem(10, "매도호가수량1");
	m_lst2105__.InsertItem(11, "매수호가수량1");
	m_lst2105__.InsertItem(12, "매도호가건수1 ");
	m_lst2105__.InsertItem(13, "매수호가건수1 ");
	m_lst2105__.InsertItem(14, "매도호가2         ");
	m_lst2105__.InsertItem(15, "매수호가2         ");
	m_lst2105__.InsertItem(16, "매도호가수량2     ");
	m_lst2105__.InsertItem(17, "매수호가수량2     ");
	m_lst2105__.InsertItem(18, "매도호가건수2 ");
	m_lst2105__.InsertItem(19, "매수호가건수2 ");
	m_lst2105__.InsertItem(20, "매도호가총수량    ");
	m_lst2105__.InsertItem(21, "매수호가총수량    ");
	m_lst2105__.InsertItem(22, "총매도호가건수");
	m_lst2105__.InsertItem(23, "총매수호가건수");
	m_lst2105__.InsertItem(24, "수신시간          ");
	m_lst2105__.InsertItem(25, "단축코드          ");

	m_lst1601.InsertColumn(0, "   ", LVCFMT_LEFT, 80);
	m_lst1601.InsertColumn(1, "개인", LVCFMT_LEFT, 80);
	m_lst1601.InsertColumn(2, "외인", LVCFMT_LEFT, 80);
	m_lst1601.InsertColumn(3, "기관", LVCFMT_LEFT, 80);

	m_lst1601.InsertItem(0, "코스피");
	m_lst1601.InsertItem(1, "   ");
	m_lst1601.InsertItem(2, "(현)");
	m_lst1601.InsertItem(3, "선물");
	m_lst1601.InsertItem(4, "   ");
	m_lst1601.InsertItem(5, "(순)");
	m_lst1601.InsertItem(6, "콜");
	m_lst1601.InsertItem(7, "   ");
	m_lst1601.InsertItem(8, "(순)");
	m_lst1601.InsertItem(9, "풋");
	m_lst1601.InsertItem(10, "   ");
	m_lst1601.InsertItem(11, "(순)");

	int nCol = 0;
	//InsertColumn4List(this, IDC_600, nCol++, "주문번호    ", FALSE, 12);   // [long  ,   10] 주문번호   
	//InsertColumn4List(this, IDC_600, nCol++, "종목번호    ", TRUE, 12);    // [string,   12] 선물옵션종목번호  
	//InsertColumn4List(this, IDC_600, nCol++, "매매구분    ", TRUE, 12);    // [string,   10] 매매구분            
	//InsertColumn4List(this, IDC_600, nCol++, "정정취소    ", TRUE, 12);    // [string,   10] 정정취소구분명      
	//InsertColumn4List(this, IDC_600, nCol++, "주문가      ", FALSE, 13.2); // [double, 13.2] 주문가              
	//InsertColumn4List(this, IDC_600, nCol++, "주문수량    ", FALSE, 12);   // [long  ,   16] 주문수량      
	//InsertColumn4List(this, IDC_600, nCol++, "체결가      ", FALSE, 13.2); // [double, 13.2] 체결가              
	//InsertColumn4List(this, IDC_600, nCol++, "체결수량    ", FALSE, 12);   // [long  ,   16] 체결수량       
	//InsertColumn4List(this, IDC_600, nCol++, "매매손익    ", FALSE, 16);   // [long  ,   16] 매매손익금액        
	//InsertColumn4List(this, IDC_600, nCol++, "미체결수량  ", FALSE, 12);   // [long  ,   16] 미체결수량        

	ZeroMemory(m_szContKey, sizeof(m_szContKey));
	//GetDlgItem(IDC_BUTTON_REQUEST3)->EnableWindow(FALSE);

}

//--------------------------------------------------------------------------------------
// 데이터 조회
//--------------------------------------------------------------------------------------
//void CDlg_JEKYLL::Request0441(BOOL bNext)
//{
//	//-----------------------------------------------------------
//	//약정현황(보유 옵션 평가금액) - 200건/10분(1건/3초)
//	t0441InBlock	pckInBlock;
//
//	TCHAR			szTrNo[] = "t0441";
//	char			szNextKey[] = "";
//
//	//-----------------------------------------------------------
//	// 데이터 초기화
//	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
//
//
//	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
//	//-----------------------------------------------------------
//	// 데이터 입력
//	SetPacketData(pckInBlock.accno, sizeof(pckInBlock.accno), strAccntNo, DATA_TYPE_STRING);
//	SetPacketData(pckInBlock.passwd, sizeof(pckInBlock.passwd), strPwdNo, DATA_TYPE_STRING);
//	SetPacketData(pckInBlock.cts_expcode, sizeof(pckInBlock.cts_expcode), bOption ? PutCode : CallCode, DATA_TYPE_STRING); //
//	SetPacketData(pckInBlock.cts_medocd, sizeof(pckInBlock.cts_medocd), "2", DATA_TYPE_STRING);		//매수
//
//	int nRqID = g_iXingAPI.Request(
//		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
//		szTrNo,						// TR 번호
//		&pckInBlock,				// InBlock 데이터
//		sizeof(pckInBlock),		// InBlock 데이터 크기
//		bNext,						// 다음조회 여부 : 다음조회일 경우에 세팅한다.
//		"",	// 다음조회 Key : Header Type이 B 일 경우엔 이전 조회때 받은 Next Key를 넣어준다.
//		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
//	);
//
//	//-----------------------------------------------------------
//	// Request ID가 0보다 작을 경우에는 에러이다.
//	if (nRqID < 0)
//	{
//		CString strMsg;
//		strMsg.Format("[%d] %s", nRqID, g_iXingAPI.GetErrorMessage(nRqID));
//		MessageBox(strMsg, "조회실패0441", MB_ICONSTOP);
//	}
//	ID0441 = nRqID;
//}

//--------------------------------------------------------------------------------------
// 데이터 조회
//--------------------------------------------------------------------------------------
void CDlg_JEKYLL::Request2400(BOOL bNext)
{
	//-----------------------------------------------------------
	//약정현황(보유 옵션 평가금액) - 200건/10분(1건/3초)
	CFOFQ02400InBlock1	pckInBlock;

	TCHAR			szTrNo[] = "CFOFQ02400";
	char			szNextKey[] = "";

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.RegMktCode, sizeof(pckInBlock.RegMktCode), "99", DATA_TYPE_STRING); //99:전체
	SetPacketData(pckInBlock.BuyDt, sizeof(pckInBlock.BuyDt), strDate, DATA_TYPE_STRING);		//매수일

	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부 : 다음조회일 경우에 세팅한다.
		"",	// 다음조회 Key : Header Type이 B 일 경우엔 이전 조회때 받은 Next Key를 넣어준다.
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		CString strMsg;
		strMsg.Format("[%d] %s", nRqID, g_iXingAPI.GetErrorMessage(nRqID));
		MessageBox(strMsg, "조회실패2400", MB_ICONSTOP);
	}
	ID2400 = nRqID;
}

void CDlg_JEKYLL::Request2400_(BOOL bNext)
{
	//-----------------------------------------------------------
	//약정현황(보유 옵션 평가금액) - 200건/10분(1건/3초)
	CFOFQ02400InBlock1	pckInBlock;

	TCHAR			szTrNo[] = "CFOFQ02400";
	char			szNextKey[] = "";

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.RegMktCode, sizeof(pckInBlock.RegMktCode), "99", DATA_TYPE_STRING); //99:전체
	SetPacketData(pckInBlock.BuyDt, sizeof(pckInBlock.BuyDt), strDate, DATA_TYPE_STRING);		//매수일

	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부 : 다음조회일 경우에 세팅한다.
		"",	// 다음조회 Key : Header Type이 B 일 경우엔 이전 조회때 받은 Next Key를 넣어준다.
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		CString strMsg;
		strMsg.Format("[%d] %s", nRqID, g_iXingAPI.GetErrorMessage(nRqID));
		MessageBox(strMsg, "조회실패", MB_ICONSTOP);
	}
	ID2400_ = nRqID;
}

void CDlg_JEKYLL::Request10100(CString code, BOOL bNext)
{
	//-----------------------------------------------------------
	// 주문가능수량조회(B type)
	CFOAQ10100InBlock1	pckInBlock;

	TCHAR	szTrNo[] = "CFOAQ10100";

	//GetDlgItemTextA(CODE, CallCode[0]);
	CString strPrc = m_lst2105.GetItemText(1, 1);

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);	//   
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.QryTp, sizeof(pckInBlock.QryTp), "1", DATA_TYPE_STRING);	// 1:일반,2:금액 
	SetPacketData(pckInBlock.OrdAmt, sizeof(pckInBlock.OrdAmt), "0", DATA_TYPE_LONG);	//        
	SetPacketData(pckInBlock.RatVal, sizeof(pckInBlock.RatVal), "0", DATA_TYPE_DOT, 8);	//     
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);	//
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), "1", DATA_TYPE_STRING);	// 1:매도,2:매수
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), strPrc, DATA_TYPE_DOT, 8);	//    
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), "00", DATA_TYPE_STRING);	// 00:지정가, 03:시장가  

	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부
		"",							// 다음조회 Key
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	//if (nRqID < 0)		MessageBox("조회실패10100", "에러", MB_ICONSTOP);
	ID10100 = nRqID;
}

void CDlg_JEKYLL::Request10100_(CString code, BOOL bNext)
{
	//-----------------------------------------------------------
	// 주문가능수량조회(B type)
	CFOAQ10100InBlock1	pckInBlock;

	TCHAR	szTrNo[] = "CFOAQ10100";

	//GetDlgItemTextA(IDC_CALLCODE, CallCode[0]);
	CString strPrc = m_lst2105.GetItemText(1, 1);

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);	//   
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.QryTp, sizeof(pckInBlock.QryTp), "1", DATA_TYPE_STRING);	// 1:일반,2:금액 
	SetPacketData(pckInBlock.OrdAmt, sizeof(pckInBlock.OrdAmt), "0", DATA_TYPE_LONG);	//        
	SetPacketData(pckInBlock.RatVal, sizeof(pckInBlock.RatVal), "0", DATA_TYPE_DOT, 8);	//     
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);	//
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), "2", DATA_TYPE_STRING);	// 1:매도,2:매수
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), strPrc, DATA_TYPE_DOT, 8);	//    
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), "00", DATA_TYPE_STRING);	// 00:지정가, 03:시장가  

	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부
		"",							// 다음조회 Key
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패10100", "에러", MB_ICONSTOP);
	ID10100_ = nRqID;
}

void CDlg_JEKYLL::Request2105(BOOL bNext)
{
	// 선옵 현재가 조회
	t2105InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t2105";
	char			szNextKey[] = "";

	// 데이터 취득
	CString Code;
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	bOption ? Code = PutCode[0] : Code = CallCode[0];
	
	//GetDlgItemTextA(IDC_CALLCODE, Code);
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), Code, DATA_TYPE_STRING);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, szNextKey, 30);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패(콜)", "에러", MB_ICONSTOP);
	ID2105 = nRqID;
}

void CDlg_JEKYLL::Request2105_(BOOL bNext)
{
	t2105InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t2105";
	char			szNextKey[] = "";

	// 데이터 취득
	CString Code;
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	bOption ? Code = PutCode[1] : Code = CallCode[1];

	//GetDlgItemTextA(IDC_PUTCODE, PutCode[0]);
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), Code, DATA_TYPE_STRING);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, szNextKey, 30);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패(풋)", "에러", MB_ICONSTOP);
	ID2105_ = nRqID;
}


void CDlg_JEKYLL::Request21052(BOOL bNext)
{
	t2105InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t2105";
	char			szNextKey[] = "";

	// 데이터 취득
	CString Code;
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	bOption ? Code = PutCode[2] : Code = CallCode[2];

	//GetDlgItemTextA(IDC_PUTCODE, PutCode[0]);
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), Code, DATA_TYPE_STRING);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, szNextKey, 30);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패(풋)", "에러", MB_ICONSTOP);
	ID21052 = nRqID;
}


void CDlg_JEKYLL::Request1601(BOOL bNext)
{
	//투자자종합
	t1601InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t1601";

	// 데이터 취득
	CString str_gubun1 = "2";	// 주식금액수량구분1(1:수량, 2:금액)
	CString str_gubun2 = "2";	// 옵션금액수량구분2(1:수량, 2:금액)
	CString str_gubun3 = "";	// 사용안함(금액)
	CString str_gubun4 = "1";	// 선물금액수량구분3(1:수량, 2:금액)

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.gubun1, sizeof(pckInBlock.gubun1), str_gubun1, DATA_TYPE_STRING);		// 주식금액수량구분1
	SetPacketData(pckInBlock.gubun2, sizeof(pckInBlock.gubun2), str_gubun2, DATA_TYPE_STRING);		// 옵션금액수량구분2
	SetPacketData(pckInBlock.gubun3, sizeof(pckInBlock.gubun3), str_gubun3, DATA_TYPE_STRING);		// 사용안함: 금액단위3   
	SetPacketData(pckInBlock.gubun4, sizeof(pckInBlock.gubun4), str_gubun4, DATA_TYPE_STRING);		// 선물금액수량구분4    

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	//((CListCtrl*)GetDlgItem(IDC_1601))->DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패1601", "에러", MB_ICONSTOP);
	ID1601 = nRqID;
}

void CDlg_JEKYLL::Request2301(CString date, BOOL bNext)
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
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID2301 = nRqID;
}

void CDlg_JEKYLL::Request2421(CString focode, BOOL bNext)
{
	//투자자종합
	t2421InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t2421";

	// 데이터 취득
	CString bdgubun = "1", nmin = "1", tcgubun = "1", cnt = "411";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.focode, sizeof(pckInBlock.focode), focode, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.bdgubun, sizeof(pckInBlock.bdgubun), bdgubun, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.nmin, sizeof(pckInBlock.nmin), nmin, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.tcgubun, sizeof(pckInBlock.tcgubun), tcgubun, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.cnt, sizeof(pckInBlock.cnt), cnt, DATA_TYPE_STRING);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	//((CListCtrl*)GetDlgItem(IDC_1601))->DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID2421 = nRqID;
}

void CDlg_JEKYLL::Request1662(BOOL bNext)
{
	//투자자종합
	t1662InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t1662";

	// 데이터 취득

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.gubun, sizeof(pckInBlock.gubun), "0", DATA_TYPE_STRING);
	SetPacketData(pckInBlock.gubun1, sizeof(pckInBlock.gubun1), "0", DATA_TYPE_STRING);
	SetPacketData(pckInBlock.gubun3, sizeof(pckInBlock.gubun3), "0", DATA_TYPE_STRING);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	//((CListCtrl*)GetDlgItem(IDC_1601))->DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID1662 = nRqID;
}

void CDlg_JEKYLL::Request1602(CString str_market, CString str_upcode, CString str_gubun1, CString cts_time, BOOL bNext)
{
	// 시간대별 투자자 매매추이 - 코스피/선물 외인/기관 거래량 30초마다-----------------------------------------------------------
	t1602InBlock	pckInBlock;

	TCHAR			szTrNo[] = "t1602";
	char			szNextKey[] = "";

	CString str_cnt;
	CString str_cts_time;
	int cnt = nCurSec / 30 + 1;
	if (cnt < 822) {
		str_cnt.Format("%d", cnt);
		str_cts_time = " ";		// [string,    8] CTSTIME   
	}
	else
	{
		cnt = 821; //최대900, (410 * 2 + 1=821 30초마다)
		str_cnt.Format("%d", cnt);
		str_cts_time = "15350000";		// [string,    8] CTSTIME   
		bNext = TRUE;
	}
	//-----------------------------------------------------------
	// 데이터 취득
	//CString str_market = "4";		// [string,    1] 시장구분  1.코스피 2.KP200 4.선물 5.콜 6.풋
	//CString str_upcode = "900";	// [string,    3] 업종코드  001.코스피 101:DP200 900.선물 700.콜 810.풋 
	//CString str_gubun1 = "1";		// [string,    1] 수량구분  1.수량 2.금액
	CString str_gubun2 = "0";		// [string,    1] 전일분구분 0.금일 1.전일
	//CString str_cts_idx;			// [long  ,    4] CTSIDX    사용안함
	//CString str_cnt = "791";		// [string,    4] 조회건수791 /최대900
	CString str_gubun3 = "C";		// [string,    1] 직전대비구분(C:직전대비)  

									//-----------------------------------------------------------
									// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.market, sizeof(pckInBlock.market), str_market, DATA_TYPE_STRING);		// [string,    1] 시장구분  
	SetPacketData(pckInBlock.upcode, sizeof(pckInBlock.upcode), str_upcode, DATA_TYPE_STRING);		// [string,    3] 업종코드  
	SetPacketData(pckInBlock.gubun1, sizeof(pckInBlock.gubun1), str_gubun1, DATA_TYPE_STRING);		// [string,    1] 수량구분  
	SetPacketData(pckInBlock.gubun2, sizeof(pckInBlock.gubun2), str_gubun2, DATA_TYPE_STRING);		// [string,    1] 전일분구분
	SetPacketData(pckInBlock.cts_time, sizeof(pckInBlock.cts_time), str_cts_time, DATA_TYPE_STRING);// [string,    8] CTSTIME   
	//SetPacketData(pckInBlock.cts_idx, sizeof(pckInBlock.cts_idx), str_cts_idx, DATA_TYPE_LONG);   // [long  ,    4] CTSIDX    
	SetPacketData(pckInBlock.gubun3, sizeof(pckInBlock.gubun3), str_gubun3, DATA_TYPE_STRING);		// [string,    1] 직전대비구분(C:직전대비) 
	SetPacketData(pckInBlock.cnt, sizeof(pckInBlock.cnt), str_cnt, DATA_TYPE_STRING);

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패1602", "에러", MB_ICONSTOP);
		//Receive1602();
		//Receive1602_();
	}
	if (str_market == "1") ID1602_ = nRqID;
	else ID1602 = nRqID;
}

void CDlg_JEKYLL::Request0167(BOOL bNext)
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

void CDlg_JEKYLL::Request600(BOOL bNext)
{
	//주문체결내역 조회
	CFOAQ00600InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAQ00600";
	char				szNextKey[] = "";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);					// [long  ,    5] 레코드갯수      
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);			// [string,   20] 계좌번호        
	SetPacketData(pckInBlock.InptPwd, sizeof(pckInBlock.InptPwd), strPwdNo, DATA_TYPE_STRING);			// [string,    8] 입력비밀번호    
	SetPacketData(pckInBlock.QrySrtDt, sizeof(pckInBlock.QrySrtDt), strDate, DATA_TYPE_STRING);			// [string,    8] 조회시작일      
	SetPacketData(pckInBlock.QryEndDt, sizeof(pckInBlock.QryEndDt), strDate, DATA_TYPE_STRING);			// [string,    8] 조회종료일      
	SetPacketData(pckInBlock.FnoClssCode, sizeof(pckInBlock.FnoClssCode), "00", DATA_TYPE_STRING);		// [string,    2] 선물옵션분류코드
	SetPacketData(pckInBlock.PrdgrpCode, sizeof(pckInBlock.PrdgrpCode), "00", DATA_TYPE_STRING);		// [string,    2] 상품군코드      00:전체
	SetPacketData(pckInBlock.PrdtExecTpCode, sizeof(pckInBlock.PrdtExecTpCode), "2", DATA_TYPE_STRING);	// [string,    1] 체결구분   0:전체,1:체결,2:미체결     
	SetPacketData(pckInBlock.StnlnSeqTp, sizeof(pckInBlock.StnlnSeqTp), "3", DATA_TYPE_STRING);			// [string,    1] 정렬순서구분    3:역순,4:정순
	SetPacketData(pckInBlock.CommdaCode, sizeof(pckInBlock.CommdaCode), "99", DATA_TYPE_STRING);		// [string,    2] 통신매체코드 

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, bNext ? m_szContKey : "", 30);

	//if (bNext == FALSE)		m_lst600.DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0) MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID600 = nRqID;
}

void CDlg_JEKYLL::Request600C(BOOL bNext)
{
	//주문체결내역 조회
	CFOAQ00600InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAQ00600";
	char				szNextKey[] = "";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);					// [long  ,    5] 레코드갯수      
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);			// [string,   20] 계좌번호        
	SetPacketData(pckInBlock.InptPwd, sizeof(pckInBlock.InptPwd), strPwdNo, DATA_TYPE_STRING);			// [string,    8] 입력비밀번호    
	SetPacketData(pckInBlock.QrySrtDt, sizeof(pckInBlock.QrySrtDt), strDate, DATA_TYPE_STRING);			// [string,    8] 조회시작일      
	SetPacketData(pckInBlock.QryEndDt, sizeof(pckInBlock.QryEndDt), strDate, DATA_TYPE_STRING);			// [string,    8] 조회종료일      
	SetPacketData(pckInBlock.FnoClssCode, sizeof(pckInBlock.FnoClssCode), "00", DATA_TYPE_STRING);		// [string,    2] 선물옵션분류코드
	SetPacketData(pckInBlock.PrdgrpCode, sizeof(pckInBlock.PrdgrpCode), "00", DATA_TYPE_STRING);		// [string,    2] 상품군코드      00:전체
	SetPacketData(pckInBlock.PrdtExecTpCode, sizeof(pckInBlock.PrdtExecTpCode), "2", DATA_TYPE_STRING);	// [string,    1] 체결구분   0:전체,1:체결,2:미체결     
	SetPacketData(pckInBlock.StnlnSeqTp, sizeof(pckInBlock.StnlnSeqTp), "3", DATA_TYPE_STRING);			// [string,    1] 정렬순서구분    3:역순,4:정순
	SetPacketData(pckInBlock.CommdaCode, sizeof(pckInBlock.CommdaCode), "99", DATA_TYPE_STRING);		// [string,    2] 통신매체코드 

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, bNext ? m_szContKey : "", 30);

	//if (bNext == FALSE)		m_lst600.DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0) MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID600C = nRqID;
}

void CDlg_JEKYLL::Request600P(BOOL bNext)
{
	//주문체결내역 조회
	CFOAQ00600InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAQ00600";
	char				szNextKey[] = "";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);					// [long  ,    5] 레코드갯수      
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);			// [string,   20] 계좌번호        
	SetPacketData(pckInBlock.InptPwd, sizeof(pckInBlock.InptPwd), strPwdNo, DATA_TYPE_STRING);			// [string,    8] 입력비밀번호    
	SetPacketData(pckInBlock.QrySrtDt, sizeof(pckInBlock.QrySrtDt), strDate, DATA_TYPE_STRING);			// [string,    8] 조회시작일      
	SetPacketData(pckInBlock.QryEndDt, sizeof(pckInBlock.QryEndDt), strDate, DATA_TYPE_STRING);			// [string,    8] 조회종료일      
	SetPacketData(pckInBlock.FnoClssCode, sizeof(pckInBlock.FnoClssCode), "00", DATA_TYPE_STRING);		// [string,    2] 선물옵션분류코드
	SetPacketData(pckInBlock.PrdgrpCode, sizeof(pckInBlock.PrdgrpCode), "00", DATA_TYPE_STRING);		// [string,    2] 상품군코드      00:전체
	SetPacketData(pckInBlock.PrdtExecTpCode, sizeof(pckInBlock.PrdtExecTpCode), "2", DATA_TYPE_STRING);	// [string,    1] 체결구분   0:전체,1:체결,2:미체결     
	SetPacketData(pckInBlock.StnlnSeqTp, sizeof(pckInBlock.StnlnSeqTp), "3", DATA_TYPE_STRING);			// [string,    1] 정렬순서구분    3:역순,4:정순
	SetPacketData(pckInBlock.CommdaCode, sizeof(pckInBlock.CommdaCode), "99", DATA_TYPE_STRING);		// [string,    2] 통신매체코드 

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, bNext ? m_szContKey : "", 30);

	//if (bNext == FALSE)		m_lst600.DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0) MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID600P = nRqID;
}

void CDlg_JEKYLL::Request600_(BOOL bNext)
{
	//주문체결내역 조회
	CFOAQ00600InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAQ00600";
	char				szNextKey[] = "";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.RecCnt, sizeof(pckInBlock.RecCnt), "1", DATA_TYPE_LONG);					// [long  ,    5] 레코드갯수      
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);			// [string,   20] 계좌번호        
	SetPacketData(pckInBlock.InptPwd, sizeof(pckInBlock.InptPwd), strPwdNo, DATA_TYPE_STRING);			// [string,    8] 입력비밀번호    
	SetPacketData(pckInBlock.QrySrtDt, sizeof(pckInBlock.QrySrtDt), strDate, DATA_TYPE_STRING);			// [string,    8] 조회시작일      
	SetPacketData(pckInBlock.QryEndDt, sizeof(pckInBlock.QryEndDt), strDate, DATA_TYPE_STRING);			// [string,    8] 조회종료일      
	SetPacketData(pckInBlock.FnoClssCode, sizeof(pckInBlock.FnoClssCode), "00", DATA_TYPE_STRING);		// [string,    2] 선물옵션분류코드
	SetPacketData(pckInBlock.PrdgrpCode, sizeof(pckInBlock.PrdgrpCode), "00", DATA_TYPE_STRING);		// [string,    2] 상품군코드      00:전체
	SetPacketData(pckInBlock.PrdtExecTpCode, sizeof(pckInBlock.PrdtExecTpCode), "2", DATA_TYPE_STRING);	// [string,    1] 체결구분   0:전체,1:체결,2:미체결     
	SetPacketData(pckInBlock.StnlnSeqTp, sizeof(pckInBlock.StnlnSeqTp), "3", DATA_TYPE_STRING);			// [string,    1] 정렬순서구분    3:역순,4:정순
	SetPacketData(pckInBlock.CommdaCode, sizeof(pckInBlock.CommdaCode), "99", DATA_TYPE_STRING);		// [string,    2] 통신매체코드 

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, bNext ? m_szContKey : "", 30);

	//if (bNext == FALSE)		m_lst600.DeleteAllItems();

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0) MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID600_ = nRqID;
}

void CDlg_JEKYLL::Request100(CString code, CString bns, CString prc, BOOL bNext)
{
	//매수매도 주문
	CFOAT00100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAT00100";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	// 데이터 입력
	CString strQty;
	if (bns == "2") //매수
	{
		//GetDlgItemTextA(IDC_NEWORD, strUsableMoney); //주문가능금액
		//lBalance = atol(strUsableMoney); // 주문가능금액을 text로 받아서 long 으로 강제변환

		float f1 = (float)atof(prc);
		if (f1 > 0)
		{
			long l1 = lBalance / ((long)f1 * 250000);
			if (l1 == 0) return;
			strQty.Format("%d", l1);
			if (code == CallCode[0])
			{
				lCallQty[0] += l1;
			}
			if (code == PutCode[0])
			{
				lPutQty[0] += l1;
			}
		}
	}
	if (bns == "1") //매도
	{
		//m_lqdt.GetWindowTextA(strQty);//청산가능수if (code == CallCode[0])
		//long l1 = atol(strQty);
		//if (l1 == 0) return;

		if (code == CallCode[0] && lLqdt == lCallQty[0])
		{
			strQty.Format("%d", lCallQty[0]);
			/*long l1 = lCallQty[0];
			lCallQty[0] -= l1;*/
			lCallQty[0] = 0;
		}
		if (code == PutCode[0] && lLqdt == lPutQty[0])
		{
			strQty.Format("%d", lPutQty[0]);
			/*long l1 = lPutQty[0];
			lPutQty[0] -= l1;*/
			lPutQty[0] = 0;
		}
		//SetTimer(7, 5000, NULL);
	}

	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), bns, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), "00", DATA_TYPE_STRING); //00:지정가 03:시장가(주문가 0)
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), prc, DATA_TYPE_DOT, 8);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), strQty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	/*if (bNext == FALSE)
	{
		m_lst100.DeleteAllItems();
	}*/

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID100 = nRqID;
}

void CDlg_JEKYLL::Request100(CString code, CString bns, float prc, BOOL bNext)
{
	//매수매도 주문
	CFOAT00100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAT00100";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	// 데이터 입력
	CString strQty;
	if (bns == "2") //매수
	{
		//GetDlgItemTextA(IDC_NEWORD, strUsableMoney); //주문가능금액
		//lBalance = atol(strUsableMoney); // 주문가능금액을 text로 받아서 long 으로 강제변환

		if (prc > 0)
		{
			long l1 = lBalance / ((long)prc * 250000);
			if (l1 == 0) return;
			strQty.Format("%d", l1);
			if (code == CallCode[0])
			{
				lCallQty[0] += l1;
			}
			if (code == PutCode[0])
			{
				lPutQty[0] += l1;
			}
		}
	}
	if (bns == "1") //매도
	{
		//m_lqdt.GetWindowTextA(strQty);//청산가능수if (code == CallCode[0])
		//long l1 = atol(strQty);
		//if (l1 == 0) return;

		if (code == CallCode[0] && lLqdt == lCallQty[0])
		{
			strQty.Format("%d", lCallQty[0]);
			/*long l1 = lCallQty[0];
			lCallQty[0] -= l1;*/
			lCallQty[0] = 0;
		}
		if (code == PutCode[0] && lLqdt == lPutQty[0])
		{
			strQty.Format("%d", lPutQty[0]);
			/*long l1 = lPutQty[0];
			lPutQty[0] -= l1;*/
			lPutQty[0] = 0;
		}
		//SetTimer(7, 5000, NULL);
	}

	CString strPrc; strPrc.Format("%.2f", prc);

	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), bns, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), "00", DATA_TYPE_STRING); //00:지정가 03:시장가(주문가 0)
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), strPrc, DATA_TYPE_DOT, 8);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), strQty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	/*if (bNext == FALSE)
	{
		m_lst100.DeleteAllItems();
	}*/

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID100 = nRqID;
}

void CDlg_JEKYLL::Request100_(CString code, CString bns, float prc, int qty, BOOL bNext)
{
	//매수매도 주문
	CFOAT00100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAT00100";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	CString strQty;
	strQty.Format("%d", qty);
	CString strPrc; strPrc.Format("%.2f", prc);

	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), bns, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), "00", DATA_TYPE_STRING); //00:지정가 03:시장가(주문가 0)
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), strPrc, DATA_TYPE_DOT, 8);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), strQty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	for (int i = 0; i < 3; i++)
	{
		if (bns == "2")
		{
			if (code == CallCode[i])	lCallQty[i] += (long)qty;
			if (code == PutCode[i])		lPutQty[i] += (long)qty;
		}
		if (bns == "1")
		{
			if (code == CallCode[i])	lCallQty[i] -= (long)qty;
			if (code == PutCode[i])		lPutQty[i] -= (long)qty;
		}
	}
	/*if (bNext == FALSE)
	{
	m_lst100.DeleteAllItems();
	}*/

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID100 = nRqID;
}

void CDlg_JEKYLL::Request100_(CString code, CString bns, CString prc, int qty, BOOL bNext)
{
	//매수매도 주문
	CFOAT00100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAT00100";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	CString strQty;
	strQty.Format("%d", qty);

	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), bns, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), "00", DATA_TYPE_STRING); //00:지정가 03:시장가(주문가 0)
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), prc, DATA_TYPE_DOT, 8);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), strQty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	if (bns == "2")
	{
		if (code == CallCode[0])	lCallQty[0] += (long)qty;
		if (code == PutCode[0])	lPutQty[0] += (long)qty;
	}
	if (bns == "1")
	{
		if (code == CallCode[0])	lCallQty[0] -= (long)qty;
		if (code == PutCode[0])	lPutQty[0] -= (long)qty;
	}

	/*if (bNext == FALSE)
	{
	m_lst100.DeleteAllItems();
	}*/

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID100 = nRqID;
}

void CDlg_JEKYLL::Request100_(CString code, CString bns, CString prc, CString qty, BOOL bNext)
{
	//매수매도 주문
	CFOAT00100InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAT00100";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.BnsTpCode, sizeof(pckInBlock.BnsTpCode), bns, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), "00", DATA_TYPE_STRING); //00:지정가 03:시장가(주문가 0)
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), prc, DATA_TYPE_DOT, 8);
	SetPacketData(pckInBlock.OrdQty, sizeof(pckInBlock.OrdQty), qty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	if (bns == "2") //매수
	{
		if (code == CallCode[0])	lCallQty[0] += atol(qty);
		if (code == PutCode[0])	lPutQty[0] += atol(qty);
	}

	if (bns == "1") //매도
	{
		if (code == CallCode[0])	lCallQty[0] -= atol(qty);
		if (code == PutCode[0])	lPutQty[0] -= atol(qty);
	}
	/*if (bNext == FALSE)
	{
	m_lst100.DeleteAllItems();
	}*/

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID100 = nRqID;
}

void CDlg_JEKYLL::Request200(CString code, CString orgordno, CString prc, CString qty, BOOL bNext)
{
	//정정주문
	CFOAT00200InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAT00200";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	// 데이터 입력
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);				// [string,   20] 계좌번호            
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);							// [string,    8] 비밀번호            
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);					// [string,   12] 선물옵션종목번호    
	SetPacketData(pckInBlock.OrgOrdNo, sizeof(pckInBlock.OrgOrdNo), orgordno, DATA_TYPE_LONG);					// [long  ,   10] 원주문번호          
	SetPacketData(pckInBlock.FnoOrdprcPtnCode, sizeof(pckInBlock.FnoOrdprcPtnCode), "00", DATA_TYPE_STRING);    // [string,    2] 선물옵션호가유형코드 00:지정가 03:시장가
	SetPacketData(pckInBlock.FnoOrdPrc, sizeof(pckInBlock.FnoOrdPrc), prc, DATA_TYPE_DOT, 8);							// [double, 15.2] 주문가격            
	SetPacketData(pckInBlock.MdfyQty, sizeof(pckInBlock.MdfyQty), qty, DATA_TYPE_LONG);							// [long  ,   16] 정정수량

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID200 = nRqID;
}

void CDlg_JEKYLL::Request300(CString code, CString orgordno, CString qty, BOOL bNext)
{
	//취소주문
	CFOAT00300InBlock1	pckInBlock;
	TCHAR				szTrNo[] = "CFOAT00300";

	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	// 데이터 입력
	SetPacketData(pckInBlock.AcntNo, sizeof(pckInBlock.AcntNo), strAccntNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.Pwd, sizeof(pckInBlock.Pwd), strPwdNo, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.FnoIsuNo, sizeof(pckInBlock.FnoIsuNo), code, DATA_TYPE_STRING);
	SetPacketData(pckInBlock.OrgOrdNo, sizeof(pckInBlock.OrgOrdNo), orgordno, DATA_TYPE_LONG);
	SetPacketData(pckInBlock.CancQty, sizeof(pckInBlock.CancQty), qty, DATA_TYPE_LONG);

	// 데이터 전송
	int nRqID = g_iXingAPI.Request(GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);

	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패", "에러", MB_ICONSTOP);
	ID300 = nRqID;
}

void CDlg_JEKYLL::Request8415(CString str_code, BOOL bNext)
{
	//-----------------------------------------------------------
	// 선물옵션차트(n분) 기간별주가(t8415) ( attr,block,headtype=A )
	t8415InBlock	pckInBlock;

	TCHAR			szTrNo[] = "t8415";

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	//CString code; GetDlgItemTextA(IDC_CALLCODE, code);
	//CString strDate = "20190101";
	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), str_code, DATA_TYPE_STRING);	// 단축코드(선물/옵션코드)
	SetPacketData(pckInBlock.ncnt, sizeof(pckInBlock.ncnt), "1", DATA_TYPE_LONG);	//1분
	SetPacketData(pckInBlock.qrycnt, sizeof(pckInBlock.qrycnt), "411", DATA_TYPE_LONG);	//요청건수 411건
	SetPacketData(pckInBlock.nday, sizeof(pckInBlock.nday), "0", DATA_TYPE_STRING);	// 조회영업일수(0:미사용)
	SetPacketData(pckInBlock.sdate, sizeof(pckInBlock.sdate), strDate, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.edate, sizeof(pckInBlock.edate), strDate, DATA_TYPE_STRING);	//  
	SetPacketData(pckInBlock.comp_yn, sizeof(pckInBlock.comp_yn), "N", DATA_TYPE_STRING);	// 압축여부 

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부
		"",							// 다음조회 Key
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패8415", "에러", MB_ICONSTOP);
	ID8415 = nRqID;
}


void CDlg_JEKYLL::Request84152(CString str_code, BOOL bNext)
{
	//-----------------------------------------------------------
	// 선물옵션차트(n분) 기간별주가(t8415) ( attr,block,headtype=A )
	t8415InBlock	pckInBlock;

	TCHAR			szTrNo[] = "t8415";

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	//CString code; GetDlgItemTextA(IDC_CALLCODE, code);
	//CString strDate = "20190101";
	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), str_code, DATA_TYPE_STRING);	// 단축코드(선물/옵션코드)
	SetPacketData(pckInBlock.ncnt, sizeof(pckInBlock.ncnt), "1", DATA_TYPE_LONG);	//1분
	SetPacketData(pckInBlock.qrycnt, sizeof(pckInBlock.qrycnt), "411", DATA_TYPE_LONG);	//요청건수 411건
	SetPacketData(pckInBlock.nday, sizeof(pckInBlock.nday), "0", DATA_TYPE_STRING);	// 조회영업일수(0:미사용)
	SetPacketData(pckInBlock.sdate, sizeof(pckInBlock.sdate), strDate, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.edate, sizeof(pckInBlock.edate), strDate, DATA_TYPE_STRING);	//  
	SetPacketData(pckInBlock.comp_yn, sizeof(pckInBlock.comp_yn), "N", DATA_TYPE_STRING);	// 압축여부 

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부
		"",							// 다음조회 Key
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패8415", "에러", MB_ICONSTOP);
	ID84152 = nRqID;
}


void CDlg_JEKYLL::Request84153(CString str_code, BOOL bNext)
{
	//-----------------------------------------------------------
	// 선물옵션차트(n분) 기간별주가(t8415) ( attr,block,headtype=A )
	t8415InBlock	pckInBlock;

	TCHAR			szTrNo[] = "t8415";

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	//CString code; GetDlgItemTextA(IDC_CALLCODE, code);
	//CString strDate = "20190101";
	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), str_code, DATA_TYPE_STRING);	// 단축코드(선물/옵션코드)
	SetPacketData(pckInBlock.ncnt, sizeof(pckInBlock.ncnt), "1", DATA_TYPE_LONG);	//1분
	SetPacketData(pckInBlock.qrycnt, sizeof(pckInBlock.qrycnt), "411", DATA_TYPE_LONG);	//요청건수 411건
	SetPacketData(pckInBlock.nday, sizeof(pckInBlock.nday), "0", DATA_TYPE_STRING);	// 조회영업일수(0:미사용)
	SetPacketData(pckInBlock.sdate, sizeof(pckInBlock.sdate), strDate, DATA_TYPE_STRING);	// 
	SetPacketData(pckInBlock.edate, sizeof(pckInBlock.edate), strDate, DATA_TYPE_STRING);	//  
	SetPacketData(pckInBlock.comp_yn, sizeof(pckInBlock.comp_yn), "N", DATA_TYPE_STRING);	// 압축여부 

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부
		"",							// 다음조회 Key
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패8415", "에러", MB_ICONSTOP);
	ID84153 = nRqID;
}


void CDlg_JEKYLL::Request3103(BOOL bNext)
{
	//-----------------------------------------------------------
	// 해외선물차트(n분) 기간별주가(o3103) ( attr,block,headtype=A )
	o3103InBlock	pckInBlock;

	TCHAR			szTrNo[] = "o3103";

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	CString str_code = "ESH19   ";
	CString str_cnt;
	if (nCurMin < 411)
		str_cnt.Format("%d", nCurMin / 10 + 21);
	else
		str_cnt.Format("%d", 60);
	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), str_code, DATA_TYPE_STRING);	// 단축코드(선물/옵션코드)
	SetPacketData(pckInBlock.ncnt, sizeof(pckInBlock.ncnt), "10", DATA_TYPE_LONG);	//10분
	SetPacketData(pckInBlock.readcnt, sizeof(pckInBlock.readcnt), str_cnt, DATA_TYPE_LONG);	// 조회건수
	//SetPacketData(pckInBlock.cts_date, sizeof(pckInBlock.cts_date), strDate, DATA_TYPE_STRING);	// 연속일자
	//SetPacketData(pckInBlock.cts_time, sizeof(pckInBlock.cts_time), strDate, DATA_TYPE_STRING);	// 연속시간

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_DATA 으로 온다.
		szTrNo,						// TR 번호
		&pckInBlock,				// InBlock 데이터
		sizeof(pckInBlock),		// InBlock 데이터 크기
		bNext,						// 다음조회 여부
		"",							// 다음조회 Key
		30							// Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
	);

	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)		MessageBox("조회실패3103", "에러", MB_ICONSTOP);
	ID3103 = nRqID;
}

void CDlg_JEKYLL::AdviseFC0()
{
	//선물 실시간
	TCHAR	szTrCode[] = "FC0";

	//-----------------------------------------------------------
	// 데이터 취득

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		FutureCode,					// 종목코드
		sizeof(FC0_InBlock)		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "FCO에러", MB_ICONSTOP);
}

void CDlg_JEKYLL::AdviseOVC()
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

void CDlg_JEKYLL::AdviseOVC2()
{
	//선물 실시간
	TCHAR	szTrCode[] = "OVC";

	//-----------------------------------------------------------
	// 데이터 취득
	CString sym = "FESXH19 ";
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

void CDlg_JEKYLL::AdviseFH0()
{
	//선물 실시간
	TCHAR	szTrCode[] = "FH0";

	//-----------------------------------------------------------
	// 데이터 취득

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		FutureCode,					// 종목코드
		sizeof(FC0_InBlock)		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "FHO에러", MB_ICONSTOP);
}

void CDlg_JEKYLL::AdviseBMT()
{
	//선물 실시간
	TCHAR	szTrCode[] = "BMT";

	//-----------------------------------------------------------
	// 데이터 취득
	CString upcode = "001";//001:코스피 101:코스피200 900:선물 700:콜 800:풋
	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		upcode,					// 업종코드
		sizeof(BMT_InBlock)		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "FCO에러", MB_ICONSTOP);
}

void CDlg_JEKYLL::AdviseBMT2()
{
	//선물 실시간
	TCHAR	szTrCode[] = "BMT";

	//-----------------------------------------------------------
	// 데이터 취득
	CString upcode = "900";//001:코스피 101:코스피200 900:선물 700:콜 800:풋
	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		upcode,					// 업종코드
		sizeof(BMT_InBlock)		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "FCO에러", MB_ICONSTOP);
}

void CDlg_JEKYLL::UnadviseFC0()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	TCHAR	szTrCode[] = "FC0";

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		FutureCode,					// 종목코드
		sizeof(FC0_InBlock)		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "에러", MB_ICONSTOP);
}

void CDlg_JEKYLL::UnadviseOVC()
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

void CDlg_JEKYLL::UnadviseOVC2()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	TCHAR	szTrCode[] = "OVC";

	CString sym = "FESXH19 ";
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

void CDlg_JEKYLL::UnadviseFH0()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	TCHAR	szTrCode[] = "FH0";

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		FutureCode,					// 종목코드
		sizeof(FC0_InBlock)		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "에러", MB_ICONSTOP);
}

void CDlg_JEKYLL::UnadviseBMT()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	TCHAR	szTrCode[] = "BMT";

	CString upcode = "001";//001:코스피 101:코스피200 900:선물 700:콜 800:풋
	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		upcode,					// 종목코드
		sizeof(BMT_InBlock)		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "에러", MB_ICONSTOP);
}

void CDlg_JEKYLL::UnadviseBMT2()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	TCHAR	szTrCode[] = "BMT";

	CString upcode = "900";//001:코스피 101:코스피200 900:선물 700:콜 800:풋
	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		upcode,					// 종목코드
		sizeof(BMT_InBlock)		// 종목코드 길이
	);

	//-----------------------------------------------------------
	// 에러체크
	if (bSuccess == FALSE)		MessageBox("조회실패", "에러", MB_ICONSTOP);
}

LRESULT CDlg_JEKYLL::OnXMReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;
	if (strcmp(pRealPacket->szTrCode, "FC0") == 0)
	{
		CString str;
		LPFC0_OutBlock pOutBlock = (LPFC0_OutBlock)pRealPacket->pszData;
		m_future.SetWindowTextA(GetDispData(pOutBlock->price, sizeof(pOutBlock->price), DATA_TYPE_FLOAT, 2));    // 현재가    
		m_futurechange2.SetWindowTextA(GetDispData(pOutBlock->drate, sizeof(pOutBlock->drate), DATA_TYPE_FLOAT, 2) + "%"); //전일대비등락율
		if (atof(GetDispData(pOutBlock->drate, sizeof(pOutBlock->drate), DATA_TYPE_FLOAT, 2)) >= 0)
			m_futurechange.SetWindowTextA("+" + GetDispData(pOutBlock->change, sizeof(pOutBlock->change), DATA_TYPE_FLOAT, 2)); //전일대비
		else
			m_futurechange.SetWindowTextA("-" + GetDispData(pOutBlock->change, sizeof(pOutBlock->change), DATA_TYPE_FLOAT, 2)); //전일대비
		m_k200.SetWindowTextA(GetDispData(pOutBlock->k200jisu, sizeof(pOutBlock->k200jisu), DATA_TYPE_FLOAT, 2));    // KOSPI200지수
		m_fvol.SetWindowTextA(GetDispData(pOutBlock->volume, sizeof(pOutBlock->volume), DATA_TYPE_LONG));    // 누적거래량
		m_cpower.SetWindowTextA(GetDispData(pOutBlock->cpower, sizeof(pOutBlock->cpower), DATA_TYPE_FLOAT, 2));    // 체결강도

		//gubun 체결구분 +:매수체결(매도1호가체결8) -:매도체결(매수1호가체결9)
		//cvolume 체결량
		//cpowere 체결강도 100기준 상하방 판단
		//chetime 체결시간 mdvolume 매도누적체결량 msvolume 매수누적체결량 (실시간 데이터이므로 뭘기준으로 바뀌었는지 확인 or 실시간 함수(여기)에다 구현

		if (strcmp(GetDispData(pOutBlock->cgubun, sizeof(pOutBlock->cgubun), DATA_TYPE_STRING), "+") == 0)
		{
			lQvol1.push(atol(GetDispData(pOutBlock->cvolume, sizeof(pOutBlock->cvolume), DATA_TYPE_LONG)));
			strQtime1.push(GetDispData(pOutBlock->chetime, sizeof(pOutBlock->chetime), DATA_TYPE_STRING));
		}

		else
		{
			lQvol2.push(atol(GetDispData(pOutBlock->cvolume, sizeof(pOutBlock->cvolume), DATA_TYPE_LONG)));
			strQtime2.push(GetDispData(pOutBlock->chetime, sizeof(pOutBlock->chetime), DATA_TYPE_STRING));
		}

		if (lQvol1.size() > 30) //매수
		{
			lQvol1.pop();
			strQtime1.pop();
		}
		if (lQvol2.size() > 30) //매도
		{
			lQvol2.pop();
			strQtime2.pop();
		}

		// ******************************************************************************************************************* 매수/매도체결량/시간(30초간 총체결량,걸린시간)
		


		if (bFC0)
		{
			OnBnClickedButtonRequest7();
			Request2301(strMonth);
			bFC0 = 0;
		}
	}

	if (strcmp(pRealPacket->szTrCode, "FH0") == 0) //호가잔량 실시간
	{
		CString str1, str2, str3;
		LPFH0_OutBlock pOutBlock = (LPFH0_OutBlock)pRealPacket->pszData;
		str1 = GetDispData(pOutBlock->totbidrem, sizeof(pOutBlock->totbidrem), DATA_TYPE_LONG); str1 = "+" + str1;	 // 매수호가총수량
		str2 = GetDispData(pOutBlock->totofferrem, sizeof(pOutBlock->totofferrem), DATA_TYPE_LONG); str2 = "-" + str2;  // 매도호가총수량
		long l1 = atol(str1) + atol(str2); str3.Format("%d", l1);
		m_lrem.SetWindowTextA(str3); //호가잔량
		m_lrem2.SetWindowTextA(GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));   // 매도호가1수량
		m_lrem3.SetWindowTextA(GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));  // 매수호가1수량
		m_lrem5.SetWindowTextA(GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_FLOAT, 2));//매도호가1
		m_lrem6.SetWindowTextA(GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_FLOAT, 2));//매수호가1
	}

	//if (strcmp(pRealPacket->szTrCode, "BMT") == 0)
	//{
	//	LPBMT_OutBlock pOutBlock = (LPBMT_OutBlock)pRealPacket->pszData;
	//	if (strcmp(GetDispData(pOutBlock->upcode, sizeof(pOutBlock->upcode), DATA_TYPE_STRING), "001") == 0)//코스피
	//	{
	//		m_pension.SetWindowTextA(GetDispData(pOutBlock->msval9, sizeof(pOutBlock->msval9), DATA_TYPE_LONG));  // 연금 순매수대금
	//	}

	//	if (strcmp(GetDispData(pOutBlock->upcode, sizeof(pOutBlock->upcode), DATA_TYPE_STRING), "900") == 0)//선물
	//	{
	//		m_etc.SetWindowTextA(GetDispData(pOutBlock->msvol11, sizeof(pOutBlock->msvol11), DATA_TYPE_LONG));  // 기타 순매수량
	//	}
	//	
	//}

	if (strcmp(pRealPacket->szTrCode, "OVC") == 0) // SNP 지수 실시간
	{
		LPOVC_OutBlock pOutBlock = (LPOVC_OutBlock)pRealPacket->pszData;
		if (strcmp(GetDispData(pOutBlock->symbol, sizeof(pOutBlock->symbol), DATA_TYPE_STRING), "ESH19") == 0)//SNP
			m_futuresnp.SetWindowTextA(GetDispData(pOutBlock->chgrate, sizeof(pOutBlock->chgrate), DATA_TYPE_DOT, 2) + "%"); //전일대비등락율

		//if (strcmp(GetDispData(pOutBlock->symbol, sizeof(pOutBlock->symbol), DATA_TYPE_STRING), "FESXH19") == 0)//EURO
		//	m_futureeuro.SetWindowTextA(GetDispData(pOutBlock->chgrate, sizeof(pOutBlock->chgrate), DATA_TYPE_DOT, 2) + "%"); //전일대비등락율

	}

	return 0L;
}

//--------------------------------------------------------------------------------------
// 데이터를 받음
//--------------------------------------------------------------------------------------
LRESULT CDlg_JEKYLL::OnXMReceiveData(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data를 받음
	if (wParam == REQUEST_DATA)
	{
		LPRECV_PACKET pRpData = (LPRECV_PACKET)lParam;
		if (pRpData->nRqID == ID2105)//선옵현재가
			Receive2105(pRpData);
		if (pRpData->nRqID == ID2105_)
			Receive2105_(pRpData);
		if (pRpData->nRqID == ID21052)
			Receive21052(pRpData);
		if (pRpData->nRqID == ID1601)//투자자종합
			Receive1601(pRpData);
		if (pRpData->nRqID == ID1602)
			Receive1602(pRpData);
		if (pRpData->nRqID == ID1602_)
			Receive1602_(pRpData);
		if (pRpData->nRqID == ID600)//체결내역조회
			Receive600(pRpData);
		if (pRpData->nRqID == ID600C)//체결내역조회
			Receive600C(pRpData);
		if (pRpData->nRqID == ID600P)//체결내역조회
			Receive600P(pRpData);
		if (pRpData->nRqID == ID600_)//체결내역조회
			Receive600_(pRpData);
		if (pRpData->nRqID == ID100)//매수매도
			Receive100(pRpData);
		if (pRpData->nRqID == ID8415)//차트(n분)
			Receive8415(pRpData);
		if (pRpData->nRqID == ID84152)//차트(n분)
			Receive84152(pRpData);
		if (pRpData->nRqID == ID84153)//차트(n분)
			Receive84153(pRpData);
		if (pRpData->nRqID == ID3103)//해외선물차트(n분)
			Receive3103(pRpData);
		if (pRpData->nRqID == ID0167)//서버시간
			Receive0167(pRpData);
		if (pRpData->nRqID == ID10100)//주문가능수량
			Receive10100(pRpData);
		if (pRpData->nRqID == ID10100_)//주문가능수량
			Receive10100_(pRpData);
		if (pRpData->nRqID == ID2400)//평가액
			Receive2400(pRpData);
		if (pRpData->nRqID == ID2400_)//평가액
			Receive2400_(pRpData);
		if (pRpData->nRqID == ID2301)//옵션전광판
			Receive2301(pRpData);
		if (pRpData->nRqID == ID2421)//미결제약정추이
			Receive2421(pRpData);
		if (pRpData->nRqID == ID1662)//프로그램매매차트(베이시스)
			Receive1662(pRpData);
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

//
//void CDlg_JEKYLL::Receive0441(LPRECV_PACKET pRpData)// header D type
//{
//	//-------------------------------------------------------------------------------------
//	// 보유옵션 평가액
//	LPBYTE			lpData = pRpData->lpData;
//	int				nDataLength = pRpData->nDataLength;
//	int				nOffset = 0;
//	int				nBlockSize = 0;
//	int				nCol = 0;
//	int				nRow = 0;
//	int				nCount = 0;
//	char			szCount[6] = { 0 };
//
//	// 연속키를 저장한다.
//	strcpy_s(m_szContKey, pRpData->szContKey);
//	//GetDlgItem(IDC_BUTTON_REQUEST_NEXT)->EnableWindow(pRpData->cCont[0] == 'Y');
//
//
//	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
//
//	//------------------------------------------------
//	// OutBlock
//	nBlockSize = sizeof(t0441OutBlock);
//	nDataLength -= nBlockSize;
//	// 받은 데이터 크기가 Block 크기보다 작다면 처리하지 않는다.
//	if (nDataLength < 0)		return;
//
//	LPt0441OutBlock pOutBlock = (LPt0441OutBlock)(lpData + nOffset);
//	nOffset += nBlockSize;
//
//	nCol = 0;
//	CString str1;
//	str1 = GetDispData(pOutBlock->tappamt, sizeof(pOutBlock->tappamt), DATA_TYPE_LONG);//평가금액
//	bOption ? m_curvaluef.SetWindowTextA(str1) : m_curvalue.SetWindowTextA(str1);					// 보유한 옵션 현재 평가금액
//
//	// OutBlock1
//	// Count 계산
//	nBlockSize = 5;
//	nDataLength -= nBlockSize;
//	if (nDataLength < 0)		return;
//
//	CopyMemory(szCount, lpData + nOffset, 5);
//	nCount = atoi(szCount);
//	nOffset += nBlockSize;
//
//	// Data
//	nBlockSize = sizeof(t0441OutBlock1) * nCount;
//	nDataLength -= nBlockSize;
//	if (nDataLength < 0)		return;
//
//	LPt0441OutBlock1 pOutBlock1 = (LPt0441OutBlock1)(lpData + nOffset);
//	nOffset += nBlockSize;
//
//	CString str4;
//	if (bOption)
//	{
//		//str2 = GetDispData(pAllOutBlock10100->outBlock2.jqty, sizeof(pAllOutBlock10100->outBlock2.jqty), DATA_TYPE_LONG);//잔고수량
//		m_avrprc2f.SetWindowTextA(GetDispData(pOutBlock1->jqty, sizeof(pOutBlock1->jqty), DATA_TYPE_LONG));		// 콜매입수량
//		//str3 = GetDispData(pAllOutBlock10100->outBlock2.mamt, sizeof(pAllOutBlock10100->outBlock2.mamt), DATA_TYPE_LONG);//매입금액
//		m_avrprcf.SetWindowTextA(GetDispData(pOutBlock1->mamt, sizeof(pOutBlock1->mamt), DATA_TYPE_LONG));		// 콜매입금액 
//		str4 = GetDispData(pOutBlock1->pamt, sizeof(pOutBlock1->pamt), DATA_TYPE_FLOAT, 2);//평균단가
//		m_avrprc3f.SetWindowTextA(str4);
//
//	}
//	else
//	{
//		//str2 = GetDispData(pAllOutBlock10100->outBlock2.jqty, sizeof(pAllOutBlock10100->outBlock2.jqty), DATA_TYPE_LONG);//잔고수량
//		m_avrprc2.SetWindowTextA(GetDispData(pOutBlock1->jqty, sizeof(pOutBlock1->jqty), DATA_TYPE_LONG));		// 콜매입수량
//		//str3 = GetDispData(pAllOutBlock10100->outBlock2.mamt, sizeof(pAllOutBlock10100->outBlock2.mamt), DATA_TYPE_LONG);//매입금액
//		m_avrprc.SetWindowTextA(GetDispData(pOutBlock1->mamt, sizeof(pOutBlock1->mamt), DATA_TYPE_LONG));		// 콜매입금액 
//		str4 = GetDispData(pOutBlock1->pamt, sizeof(pOutBlock1->pamt), DATA_TYPE_FLOAT, 2);//평균단가
//		m_avrprc3.SetWindowTextA(str4);
//	}
//
//
//	return;
//}


void CDlg_JEKYLL::Receive2400(LPRECV_PACKET pRpData)// header B type
{
	//------------------------------------------------------------------------------------- 10분당 200건 제한, 200/600초 = 1건 가능/3초
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
	nBlockSize = sizeof(CFOFQ02400OutBlock1);
	nDataLength -= nBlockSize;
	// 받은 데이터 크기가 Block 크기보다 작다면 처리하지 않는다.
	if (nDataLength < 0)		return;

	LPCFOFQ02400OutBlock1 pOutBlock24001 = (LPCFOFQ02400OutBlock1)(lpData + nOffset);
	nOffset += nBlockSize;

	nCol = 0;
	//------------------------------------------------
	// OutBlock2

	// 받은 데이터 크기가 Block 크기보다 작다면 처리하지 않는다.
	nBlockSize = sizeof(CFOFQ02400OutBlock2);
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	LPCFOFQ02400OutBlock2 pOutBlock24002 = (LPCFOFQ02400OutBlock2)(lpData + nOffset);
	nOffset += nBlockSize;

	CString str1, str2, str3, str4;
	str1 = GetDispData(pOutBlock24002->CalloptCtrctAmt, sizeof(pOutBlock24002->CalloptCtrctAmt), DATA_TYPE_LONG);		// 콜계약금액
	str2 = GetDispData(pOutBlock24002->PutoptCtrctAmt, sizeof(pOutBlock24002->PutoptCtrctAmt), DATA_TYPE_LONG);			// 풋계약금액
	//str1 = GetDispData(pOutBlock24002->CallBuyAmt, sizeof(pOutBlock24002->CallBuyAmt), DATA_TYPE_LONG);	// 콜매수금액 
	//str2 = GetDispData(pOutBlock24002->CallSellAmt, sizeof(pOutBlock24002->CallSellAmt), DATA_TYPE_LONG);	// 콜매도금액 
	//str3 = GetDispData(pOutBlock24002->PutBuyAmt, sizeof(pOutBlock24002->PutBuyAmt), DATA_TYPE_LONG);		// 풋매수금액 
	//str4 = GetDispData(pOutBlock24002->PutSellAmt, sizeof(pOutBlock24002->PutSellAmt), DATA_TYPE_LONG);	// 풋매도금액 
	str3 = GetDispData(pOutBlock24002->OptPnlSum, sizeof(pOutBlock24002->OptPnlSum), DATA_TYPE_LONG);					// 현재 순이익
		
	//lCallAvrPrc = atol(str1) + atol(str2);
	//lPutAvrPrc = atol(str3) + atol(str4);

	lCallAvrPrc = atol(str1);							// 콜계약금액
	lPutAvrPrc = atol(str2);							// 풋계약금액

	m_curvalue.SetWindowTextA(str1);					// 콜계약금액 표시
	m_curvaluef.SetWindowTextA(str2);					// 풋계약금액 표시
	//m_curvalue4.SetWindowTextA(str3);					// 순이익 표시


	// OutBlock3
	// Count 계산
	nBlockSize = 5;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	CopyMemory(szCount, lpData + nOffset, 5);
	nCount = atoi(szCount);
	nOffset += nBlockSize;

	// Data
	nBlockSize = sizeof(CFOFQ02400OutBlock3) * nCount;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	LPCFOFQ02400OutBlock3 pOutBlock24003 = (LPCFOFQ02400OutBlock3)(lpData + nOffset);
	nOffset += nBlockSize;

	CString str5, str6, str7, str8;
	//str5 = GetDispData(pOutBlock24003[0].CallBuyQty, sizeof(pOutBlock24003[0].CallBuyQty), DATA_TYPE_LONG); // 콜매수수량
	//str6 = GetDispData(pOutBlock24003[0].CallSellQty, sizeof(pOutBlock24003[0].CallSellQty), DATA_TYPE_LONG);  // 콜매도수량
	//str7 = GetDispData(pOutBlock24003[0].PutBuyQty, sizeof(pOutBlock24003[0].PutBuyQty), DATA_TYPE_LONG);  // 풋매수수량
	//str8 = GetDispData(pOutBlock24003[0].PutSellQty, sizeof(pOutBlock24003[0].PutSellQty), DATA_TYPE_LONG);  // 풋매도수량

	//long sellCnum = atol(str6), sellPnum = atol(str8);
	//if (sellCnum > 0)
	//{
	//	lCallQty[0] = -1 * sellCnum;
	//	lCallAvrPrc -= atol(str1);
	//}
	//else
	//	lCallQty[0] = atol(str5);

	//if (sellPnum > 0)
	//{
	//	lPutQty[0] = -1 * sellPnum;
	//	lPutAvrPrc -= atol(str3);
	//}
	//else
	//	lPutQty[0] = atol(str7);


	// ******************************************** OutBlock4

	// Count 계산
	nBlockSize = 5;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)
	{
		return;
	}

	CopyMemory(szCount, lpData + nOffset, 5);
	nCount = atoi(szCount);
	nOffset += nBlockSize;

	// Data
	nBlockSize = sizeof(CFOFQ02400OutBlock4) * nCount;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)
	{
		return;
	}

	LPCFOFQ02400OutBlock4 pOutBlock4 = (LPCFOFQ02400OutBlock4)(lpData + nOffset);
	nOffset += nBlockSize;

	//int numc = 0, nump = 0; // 콜코드 풋코드 저장 변수
	if (lCallQty[0] == 0 && lPutQty[0] == 0)
	Request10100(CallCode[0]);
	//else
	
	long ltemp = 0; // lLqdt 계산 위한 임시변수
	for (int i = 0; i < nCount; i++)
	{
		str5 = GetDispData(pOutBlock4[i].IsuNo, sizeof(pOutBlock4[i].IsuNo), DATA_TYPE_STRING);
		str6 = GetDispData(pOutBlock4[i].BalQty, sizeof(pOutBlock4[i].BalQty), DATA_TYPE_LONG);
		str7 = GetDispData(pOutBlock4[i].FnoAvrPrc, sizeof(pOutBlock4[i].FnoAvrPrc), DATA_TYPE_DOT, 8);		// [double, 19.8] 
		str8 = GetDispData(pOutBlock4[i].BnsTpCode, sizeof(pOutBlock4[i].BnsTpCode), DATA_TYPE_STRING);     // 매수/매도 구분 +/-

		if (str5.Left(1) == "2")								//콜인 경우
		{
			for (int i = 0; i < 3; i++)
			{
				long lqty = 0;
				if (CallCode[i] == str5)
				{
					lqty += (long)atol(str6);
					lCallQty[i] = lqty;
					if (str8 == "1")
					{
						lCallQty[i] = -1 * lqty;
					}
					fCallAvrPrc[i] = (float)atof(str7);
				}
				ltemp += lqty;
			}

		}
		else													//풋인 경우
		{
			for (int i = 0; i < 3; i++)
			{
				long lqty = 0;
				if (PutCode[i] == str5)
				{
					lqty += (long)atol(str6);
					lPutQty[i] = lqty;
					if (str8 == "1")
					{
						lPutQty[i] = -1 * lqty;
					}
					fPutAvrPrc[i] = (float)atof(str7);
				}
				ltemp += lqty;
			}
		}
	}
	lLqdt = ltemp;
	//numc = 0, nump = 0;
	//str2.Format("%s, %d", CallCode[0], lCallQty[0]);
	//str3.Format("%s, %d", CallCode[1], lCallQty[1]);
	//str4.Format("%s, %d", CallCode[2], lCallQty[2]);	

	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	if (!bOption)
	{
		str2.Format("%d", lCallQty[0]);
		str3.Format("%d", lCallQty[1]);
		str4.Format("%d", lCallQty[2]);
		str5.Format("%.2f", fPutAvrPrc[0]);	m_orgordno2.SetWindowTextA(str5);
		str6.Format("%.2f", fPutAvrPrc[1]);	m_qty2.SetWindowTextA(str6);
		str7.Format("%.2f", fPutAvrPrc[2]);	m_prc2.SetWindowTextA(str7);

		/*m_tst2.SetWindowTextA(CallCode[0]);
		m_tst3.SetWindowTextA(CallCode[1]);
		m_tst4.SetWindowTextA(CallCode[2]);*/
		Request10100(CallCode[0]);
	}
	else
	{ 
		
		str2.Format("%d", lPutQty[0]);
		str3.Format("%d", lPutQty[1]);
		str4.Format("%d", lPutQty[2]);
		str5.Format("%.2f", fCallAvrPrc[0]);	m_orgordno.SetWindowTextA(str5);
		str6.Format("%.2f", fCallAvrPrc[1]);	m_qty.SetWindowTextA(str6);
		str7.Format("%.2f", fCallAvrPrc[2]);	m_prc.SetWindowTextA(str7);

		/*m_tst2.SetWindowTextA(PutCode[0]);
		m_tst3.SetWindowTextA(PutCode[1]);
		m_tst4.SetWindowTextA(PutCode[2]);*/
		Request10100(PutCode[0]);
	}
	m_tst5.SetWindowTextA(str2);
	m_tst6.SetWindowTextA(str3);
	m_tst7.SetWindowTextA(str4);

	return;
}

void CDlg_JEKYLL::Receive2400_(LPRECV_PACKET pRpData)// header B type
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
	nBlockSize = sizeof(CFOFQ02400OutBlock1);
	nDataLength -= nBlockSize;
	// 받은 데이터 크기가 Block 크기보다 작다면 처리하지 않는다.
	if (nDataLength < 0)		return;

	LPCFOFQ02400OutBlock1 pOutBlock24001 = (LPCFOFQ02400OutBlock1)(lpData + nOffset);
	nOffset += nBlockSize;

	nCol = 0;
	//------------------------------------------------
	// OutBlock2

	// 받은 데이터 크기가 Block 크기보다 작다면 처리하지 않는다.
	nBlockSize = sizeof(CFOFQ02400OutBlock2);
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	LPCFOFQ02400OutBlock2 pOutBlock24002 = (LPCFOFQ02400OutBlock2)(lpData + nOffset);
	nOffset += nBlockSize;

	CString str1, str2, str3, str4;
	str1 = GetDispData(pOutBlock24002->CallBuyAmt, sizeof(pOutBlock24002->CallBuyAmt), DATA_TYPE_LONG);		// 콜매수금액 
	str2 = GetDispData(pOutBlock24002->CallSellAmt, sizeof(pOutBlock24002->CallSellAmt), DATA_TYPE_LONG);	// 콜매도금액 
	str3 = GetDispData(pOutBlock24002->PutBuyAmt, sizeof(pOutBlock24002->PutBuyAmt), DATA_TYPE_LONG);		// 풋매수금액 
	str4 = GetDispData(pOutBlock24002->PutSellAmt, sizeof(pOutBlock24002->PutSellAmt), DATA_TYPE_LONG);		// 풋매도금액 
	lCallAvrPrc = atol(str1) + atol(str2);
	lPutAvrPrc = atol(str3) + atol(str4);

	// OutBlock3
	// Count 계산
	nBlockSize = 5;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	CopyMemory(szCount, lpData + nOffset, 5);
	nCount = atoi(szCount);
	nOffset += nBlockSize;

	// Data
	nBlockSize = sizeof(CFOFQ02400OutBlock3) * nCount;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)		return;

	LPCFOFQ02400OutBlock3 pOutBlock24003 = (LPCFOFQ02400OutBlock3)(lpData + nOffset);
	nOffset += nBlockSize;

	CString str5, str6, str7, str8;
	//str5 = GetDispData(pOutBlock24003[0].CallBuyQty, sizeof(pOutBlock24003[0].CallBuyQty), DATA_TYPE_LONG); // 콜매수수량
	//str6 = GetDispData(pOutBlock24003[0].CallSellQty, sizeof(pOutBlock24003[0].CallSellQty), DATA_TYPE_LONG);  // 콜매도수량
	//str7 = GetDispData(pOutBlock24003[0].PutBuyQty, sizeof(pOutBlock24003[0].PutBuyQty), DATA_TYPE_LONG);  // 풋매수수량
	//str8 = GetDispData(pOutBlock24003[0].PutSellQty, sizeof(pOutBlock24003[0].PutSellQty), DATA_TYPE_LONG);  // 풋매도수량

	//long sellCnum = atol(str6), sellPnum = atol(str8);
	//if (sellCnum > 0)
	//{
	//	lCallQty[0] = -1 * sellCnum;
	//	lCallAvrPrc -= atol(str1);
	//}
	//else
	//	lCallQty[0] = atol(str5);

	//if (sellPnum > 0)
	//{
	//	lPutQty[0] = -1 * sellPnum;
	//	lPutAvrPrc -= atol(str3);
	//}
	//else
	//	lPutQty[0] = atol(str7);


	// ******************************************** OutBlock4

	// Count 계산
	nBlockSize = 5;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)
	{
		return;
	}

	CopyMemory(szCount, lpData + nOffset, 5);
	nCount = atoi(szCount);
	nOffset += nBlockSize;

	// Data
	nBlockSize = sizeof(CFOFQ02400OutBlock4) * nCount;
	nDataLength -= nBlockSize;
	if (nDataLength < 0)
	{
		return;
	}

	LPCFOFQ02400OutBlock4 pOutBlock4 = (LPCFOFQ02400OutBlock4)(lpData + nOffset);
	nOffset += nBlockSize;

	//int numc = 0, nump = 0; // 콜코드 풋코드 저장 변수
	/*if (lCallQty[0] == 0 && lPutQty[0] == 0)
	Request10100(CallCode[0]);*/
	//else

	for (int i = 0; i < nCount; i++)
	{
		str5 = GetDispData(pOutBlock4[i].IsuNo, sizeof(pOutBlock4[i].IsuNo), DATA_TYPE_STRING);
		str6 = GetDispData(pOutBlock4[i].BalQty, sizeof(pOutBlock4[i].BalQty), DATA_TYPE_LONG);
		str7 = GetDispData(pOutBlock4[i].FnoAvrPrc, sizeof(pOutBlock4[i].FnoAvrPrc), DATA_TYPE_DOT, 8);		// [double, 19.8] 
		str8 = GetDispData(pOutBlock4[i].BnsTpCode, sizeof(pOutBlock4[i].BnsTpCode), DATA_TYPE_STRING);     // 매수/매도 구분 +/-
		if (str5.Left(1) == "2")
		{
			for (int i = 0; i < 3; i++)
			{
				long lqty = 0;
				if (CallCode[i] == str5)
				{
					if (str8 == "2")
					{
						lqty += (long)atol(str6);
						lCallQty[i] = lqty;
					}
					
					if (str8 == "1")
					{
						lqty -= (long)atol(str6);
						lCallQty[i] = lqty;
					}
					fCallAvrPrc[i] = (float)atof(str7);
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				long lqty = 0;
				if (PutCode[i] == str5)
				{
					if (str8 == "2")
					{
						lqty += (long)atol(str6);
						lPutQty[i] = lqty;
					}
					
					if (str8 == "1")
					{
						lqty -= (long)atol(str6);
						lPutQty[i] = lqty;
					}
					fPutAvrPrc[i] = (float)atof(str7);
				}
			}
		}
	}
	//numc = 0, nump = 0;
	//str2.Format("%s, %d", CallCode[0], lCallQty[0]);
	//str3.Format("%s, %d", CallCode[1], lCallQty[1]);
	//str4.Format("%s, %d", CallCode[2], lCallQty[2]);

	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	if (!bOption)
	{
		str2.Format("%d", lCallQty[0]);
		str3.Format("%d", lCallQty[1]);
		str4.Format("%d", lCallQty[2]);

		/*m_tst2.SetWindowTextA(CallCode[0]);
		m_tst3.SetWindowTextA(CallCode[1]);
		m_tst4.SetWindowTextA(CallCode[2]);*/
		Request10100(CallCode[0]);
	}
	else
	{

		str2.Format("%d", lPutQty[0]);
		str3.Format("%d", lPutQty[1]);
		str4.Format("%d", lPutQty[2]);

		/*m_tst2.SetWindowTextA(PutCode[0]);
		m_tst3.SetWindowTextA(PutCode[1]);
		m_tst4.SetWindowTextA(PutCode[2]);*/
		Request10100(PutCode[0]);
	}
	m_tst5.SetWindowTextA(str2);
	m_tst6.SetWindowTextA(str3);
	m_tst7.SetWindowTextA(str4);

	return;
}

void CDlg_JEKYLL::Receive2105(LPRECV_PACKET pRpData)// header A type
{
	LPt2105OutBlock pOutBlock = (LPt2105OutBlock)pRpData->lpData;
	m_lst2105.SetItemText(0, 1, GetDispData(pOutBlock->hname, sizeof(pOutBlock->hname), DATA_TYPE_STRING));
	m_lst2105.SetItemText(1, 1, GetDispData(pOutBlock->price, sizeof(pOutBlock->price), DATA_TYPE_DOT, 2));
	m_lst2105.SetItemText(2, 1, GetDispData(pOutBlock->sign, sizeof(pOutBlock->sign), DATA_TYPE_STRING));
	m_lst2105.SetItemText(3, 1, GetDispData(pOutBlock->change, sizeof(pOutBlock->change), DATA_TYPE_DOT, 2));
	m_lst2105.SetItemText(4, 1, GetDispData(pOutBlock->diff, sizeof(pOutBlock->diff), DATA_TYPE_DOT, 2));
	m_lst2105.SetItemText(5, 1, GetDispData(pOutBlock->volume, sizeof(pOutBlock->volume), DATA_TYPE_LONG));
	m_lst2105.SetItemText(6, 1, GetDispData(pOutBlock->stimeqrt, sizeof(pOutBlock->stimeqrt), DATA_TYPE_FLOAT, 2));
	m_lst2105.SetItemText(7, 1, GetDispData(pOutBlock->jnilclose, sizeof(pOutBlock->jnilclose), DATA_TYPE_DOT, 2));
	m_lst2105.SetItemText(8, 1, GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_DOT, 2));
	m_lst2105.SetItemText(9, 1, GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_DOT, 2));
	m_lst2105.SetItemText(10, 1, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));
	m_lst2105.SetItemText(11, 1, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));
	m_lst2105.SetItemText(12, 1, GetDispData(pOutBlock->dcnt1, sizeof(pOutBlock->dcnt1), DATA_TYPE_LONG));
	m_lst2105.SetItemText(13, 1, GetDispData(pOutBlock->scnt1, sizeof(pOutBlock->scnt1), DATA_TYPE_LONG));
	m_lst2105.SetItemText(14, 1, GetDispData(pOutBlock->offerho2, sizeof(pOutBlock->offerho2), DATA_TYPE_DOT, 2));
	m_lst2105.SetItemText(15, 1, GetDispData(pOutBlock->bidho2, sizeof(pOutBlock->bidho2), DATA_TYPE_DOT, 2));
	m_lst2105.SetItemText(16, 1, GetDispData(pOutBlock->offerrem2, sizeof(pOutBlock->offerrem2), DATA_TYPE_LONG));
	m_lst2105.SetItemText(17, 1, GetDispData(pOutBlock->bidrem2, sizeof(pOutBlock->bidrem2), DATA_TYPE_LONG));
	m_lst2105.SetItemText(18, 1, GetDispData(pOutBlock->dcnt2, sizeof(pOutBlock->dcnt2), DATA_TYPE_LONG));
	m_lst2105.SetItemText(19, 1, GetDispData(pOutBlock->scnt2, sizeof(pOutBlock->scnt2), DATA_TYPE_LONG));
	m_lst2105.SetItemText(20, 1, GetDispData(pOutBlock->dvol, sizeof(pOutBlock->dvol), DATA_TYPE_LONG));
	m_lst2105.SetItemText(21, 1, GetDispData(pOutBlock->svol, sizeof(pOutBlock->svol), DATA_TYPE_LONG));
	m_lst2105.SetItemText(22, 1, GetDispData(pOutBlock->toffernum, sizeof(pOutBlock->toffernum), DATA_TYPE_LONG));
	m_lst2105.SetItemText(23, 1, GetDispData(pOutBlock->tbidnum, sizeof(pOutBlock->tbidnum), DATA_TYPE_LONG));
	m_lst2105.SetItemText(24, 1, GetDispData(pOutBlock->time, sizeof(pOutBlock->time), DATA_TYPE_STRING));
	m_lst2105.SetItemText(25, 1, GetDispData(pOutBlock->shcode, sizeof(pOutBlock->shcode), DATA_TYPE_STRING));

}

void CDlg_JEKYLL::Receive2105_(LPRECV_PACKET pRpData)
{
	LPt2105OutBlock pOutBlock = (LPt2105OutBlock)pRpData->lpData;
	m_lst2105_.SetItemText(0, 1, GetDispData(pOutBlock->hname, sizeof(pOutBlock->hname), DATA_TYPE_STRING));
	m_lst2105_.SetItemText(1, 1, GetDispData(pOutBlock->price, sizeof(pOutBlock->price), DATA_TYPE_DOT, 2));
	m_lst2105_.SetItemText(2, 1, GetDispData(pOutBlock->sign, sizeof(pOutBlock->sign), DATA_TYPE_STRING));
	m_lst2105_.SetItemText(3, 1, GetDispData(pOutBlock->change, sizeof(pOutBlock->change), DATA_TYPE_DOT, 2));
	m_lst2105_.SetItemText(4, 1, GetDispData(pOutBlock->diff, sizeof(pOutBlock->diff), DATA_TYPE_DOT, 2));
	m_lst2105_.SetItemText(5, 1, GetDispData(pOutBlock->volume, sizeof(pOutBlock->volume), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(6, 1, GetDispData(pOutBlock->stimeqrt, sizeof(pOutBlock->stimeqrt), DATA_TYPE_FLOAT, 2));
	m_lst2105_.SetItemText(7, 1, GetDispData(pOutBlock->jnilclose, sizeof(pOutBlock->jnilclose), DATA_TYPE_DOT, 2));
	m_lst2105_.SetItemText(8, 1, GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_DOT, 2));
	m_lst2105_.SetItemText(9, 1, GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_DOT, 2));
	m_lst2105_.SetItemText(10, 1, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(11, 1, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(12, 1, GetDispData(pOutBlock->dcnt1, sizeof(pOutBlock->dcnt1), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(13, 1, GetDispData(pOutBlock->scnt1, sizeof(pOutBlock->scnt1), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(14, 1, GetDispData(pOutBlock->offerho2, sizeof(pOutBlock->offerho2), DATA_TYPE_DOT, 2));
	m_lst2105_.SetItemText(15, 1, GetDispData(pOutBlock->bidho2, sizeof(pOutBlock->bidho2), DATA_TYPE_DOT, 2));
	m_lst2105_.SetItemText(16, 1, GetDispData(pOutBlock->offerrem2, sizeof(pOutBlock->offerrem2), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(17, 1, GetDispData(pOutBlock->bidrem2, sizeof(pOutBlock->bidrem2), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(18, 1, GetDispData(pOutBlock->dcnt2, sizeof(pOutBlock->dcnt2), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(19, 1, GetDispData(pOutBlock->scnt2, sizeof(pOutBlock->scnt2), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(20, 1, GetDispData(pOutBlock->dvol, sizeof(pOutBlock->dvol), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(21, 1, GetDispData(pOutBlock->svol, sizeof(pOutBlock->svol), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(22, 1, GetDispData(pOutBlock->toffernum, sizeof(pOutBlock->toffernum), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(23, 1, GetDispData(pOutBlock->tbidnum, sizeof(pOutBlock->tbidnum), DATA_TYPE_LONG));
	m_lst2105_.SetItemText(24, 1, GetDispData(pOutBlock->time, sizeof(pOutBlock->time), DATA_TYPE_STRING));
	m_lst2105_.SetItemText(25, 1, GetDispData(pOutBlock->shcode, sizeof(pOutBlock->shcode), DATA_TYPE_STRING));

}


void CDlg_JEKYLL::Receive21052(LPRECV_PACKET pRpData)
{
	LPt2105OutBlock pOutBlock = (LPt2105OutBlock)pRpData->lpData;
	m_lst2105__.SetItemText(0, 1, GetDispData(pOutBlock->hname, sizeof(pOutBlock->hname), DATA_TYPE_STRING));
	m_lst2105__.SetItemText(1, 1, GetDispData(pOutBlock->price, sizeof(pOutBlock->price), DATA_TYPE_DOT, 2));
	m_lst2105__.SetItemText(2, 1, GetDispData(pOutBlock->sign, sizeof(pOutBlock->sign), DATA_TYPE_STRING));
	m_lst2105__.SetItemText(3, 1, GetDispData(pOutBlock->change, sizeof(pOutBlock->change), DATA_TYPE_DOT, 2));
	m_lst2105__.SetItemText(4, 1, GetDispData(pOutBlock->diff, sizeof(pOutBlock->diff), DATA_TYPE_DOT, 2));
	m_lst2105__.SetItemText(5, 1, GetDispData(pOutBlock->volume, sizeof(pOutBlock->volume), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(6, 1, GetDispData(pOutBlock->stimeqrt, sizeof(pOutBlock->stimeqrt), DATA_TYPE_FLOAT, 2));
	m_lst2105__.SetItemText(7, 1, GetDispData(pOutBlock->jnilclose, sizeof(pOutBlock->jnilclose), DATA_TYPE_DOT, 2));
	m_lst2105__.SetItemText(8, 1, GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_DOT, 2));
	m_lst2105__.SetItemText(9, 1, GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_DOT, 2));
	m_lst2105__.SetItemText(10, 1, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(11, 1, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(12, 1, GetDispData(pOutBlock->dcnt1, sizeof(pOutBlock->dcnt1), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(13, 1, GetDispData(pOutBlock->scnt1, sizeof(pOutBlock->scnt1), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(14, 1, GetDispData(pOutBlock->offerho2, sizeof(pOutBlock->offerho2), DATA_TYPE_DOT, 2));
	m_lst2105__.SetItemText(15, 1, GetDispData(pOutBlock->bidho2, sizeof(pOutBlock->bidho2), DATA_TYPE_DOT, 2));
	m_lst2105__.SetItemText(16, 1, GetDispData(pOutBlock->offerrem2, sizeof(pOutBlock->offerrem2), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(17, 1, GetDispData(pOutBlock->bidrem2, sizeof(pOutBlock->bidrem2), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(18, 1, GetDispData(pOutBlock->dcnt2, sizeof(pOutBlock->dcnt2), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(19, 1, GetDispData(pOutBlock->scnt2, sizeof(pOutBlock->scnt2), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(20, 1, GetDispData(pOutBlock->dvol, sizeof(pOutBlock->dvol), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(21, 1, GetDispData(pOutBlock->svol, sizeof(pOutBlock->svol), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(22, 1, GetDispData(pOutBlock->toffernum, sizeof(pOutBlock->toffernum), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(23, 1, GetDispData(pOutBlock->tbidnum, sizeof(pOutBlock->tbidnum), DATA_TYPE_LONG));
	m_lst2105__.SetItemText(24, 1, GetDispData(pOutBlock->time, sizeof(pOutBlock->time), DATA_TYPE_STRING));
	m_lst2105__.SetItemText(25, 1, GetDispData(pOutBlock->shcode, sizeof(pOutBlock->shcode), DATA_TYPE_STRING));

}


void CDlg_JEKYLL::Receive0167(LPRECV_PACKET pRpData)
{
	if (strcmp(pRpData->szBlockName, NAME_t0167OutBlock) == 0)
	{
		LPt0167OutBlock pOutBlock = (LPt0167OutBlock)pRpData->lpData;
		CString str = pOutBlock->time;
		strTime = str.Left(6);

		int sec = atoi(str.Mid(4, 2));
		int min = atoi(str.Mid(2, 2));
		int hour = atoi(str.Left(2));
		nCorrectTime = hour * 3600 + min * 60 + sec;
		nCurSec = nCorrectTime - 3600 * 9;
		CTime t = CTime::GetCurrentTime();
		int sec2 = t.GetSecond();
		int min2 = t.GetMinute();
		int hour2 = t.GetHour();
		int time = hour2 * 3600 + min2 * 60 + sec2;
		nCorrectTime -= time; //서버시간-컴퓨터시간
		m_time.SetWindowText(strTime);
	}
}

void CDlg_JEKYLL::Receive10100(LPRECV_PACKET pRpData) //header B type 매수물량 조회
{

	typedef struct
	{
		CFOAQ10100OutBlock1	outBlock1;
		CFOAQ10100OutBlock2	outBlock2;
	} CFOAQ10100AllOutBlock, *LPCFOAQ10100AllOutBlock;

	//LPRECV_PACKET			pRpData = (LPRECV_PACKET)lParam;
	LPCFOAQ10100AllOutBlock pAllOutBlock10100 = (LPCFOAQ10100AllOutBlock)pRpData->lpData;
	int						nDataLength = pRpData->nDataLength;
	//int						nCol;

	//------------------------------------------------
	// OutBlock1
	nDataLength -= sizeof(CFOAQ10100OutBlock1);
	if (nDataLength < 0)
	{
		return;
	}
	// OutBlock2
	nDataLength -= sizeof(CFOAQ10100OutBlock2);
	if (nDataLength < 0)
	{
		return;
	}

	CString str1, str2;
	str1 = GetDispData(pAllOutBlock10100->outBlock2.LqdtOrdAbleQty, sizeof(pAllOutBlock10100->outBlock2.LqdtOrdAbleQty), DATA_TYPE_LONG);//청산가능
	str2 = GetDispData(pAllOutBlock10100->outBlock2.OrdAbleAmt, sizeof(pAllOutBlock10100->outBlock2.OrdAbleAmt), DATA_TYPE_LONG);//주문가능금액

	//lLqdt = atol(str1);
	long ltemp = atol(str2);
	if (ltemp != 0) 	lBalance = ltemp;	// *************************************************************************************** 3개의 콜/풋코드로 나눠서 구매
	//if (lMaxBalance < lBalance)
	//	lMaxBalance = lBalance;
	/*if (lBalance < 300000)
	{
		bCall = FALSE;
		bPut = FALSE;
	}*/

	if (lLqdt == 0 && lLqdt == lCallQty[0] + lPutQty[0] + lCallQty[1] + lPutQty[1] + lCallQty[2] + lPutQty[2])
	{
		bCall = TRUE;
		bPut = TRUE;
	}
	return;
}

void CDlg_JEKYLL::Receive10100_(LPRECV_PACKET pRpData) //header B type
{

	typedef struct
	{
		CFOAQ10100OutBlock1	outBlock1;
		CFOAQ10100OutBlock2	outBlock2;
	} CFOAQ10100AllOutBlock, *LPCFOAQ10100AllOutBlock;

	//LPRECV_PACKET			pRpData = (LPRECV_PACKET)lParam;
	LPCFOAQ10100AllOutBlock pAllOutBlock10100 = (LPCFOAQ10100AllOutBlock)pRpData->lpData;
	int						nDataLength = pRpData->nDataLength;
	//int						nCol;

	//------------------------------------------------
	// OutBlock1
	nDataLength -= sizeof(CFOAQ10100OutBlock1);
	if (nDataLength < 0)
	{
		return;
	}
	// OutBlock2
	nDataLength -= sizeof(CFOAQ10100OutBlock2);
	if (nDataLength < 0)
	{
		return;
	}

	CString str3, str4, str5;
	str3 = GetDispData(pAllOutBlock10100->outBlock2.NewOrdAbleQty, sizeof(pAllOutBlock10100->outBlock2.NewOrdAbleQty), DATA_TYPE_LONG);//신규가능
	str4 = GetDispData(pAllOutBlock10100->outBlock2.LqdtOrdAbleQty, sizeof(pAllOutBlock10100->outBlock2.LqdtOrdAbleQty), DATA_TYPE_LONG);//청산가능
	str5 = GetDispData(pAllOutBlock10100->outBlock2.OrdAbleAmt, sizeof(pAllOutBlock10100->outBlock2.OrdAbleAmt), DATA_TYPE_LONG);//주문가능금액

	lNewSell = atol(str3);
	lLqdt = atol(str4);
	lBalance = atol(str5);
	/*if (lMaxBalance < lBalance)
		lMaxBalance = lBalance;*/
	/*if (lBalance < 300000)
	{
		bCall = FALSE;
		bPut = FALSE;
	}*/
	return;
}

void CDlg_JEKYLL::Receive1601(LPRECV_PACKET pRpData)//header A type
{
	if (strcmp(pRpData->szBlockName, NAME_t1601OutBlock1) == 0)
	{
		LPt1601OutBlock1 pOutBlock1 = (LPt1601OutBlock1)pRpData->lpData;

		m_lst1601.SetItemText(0, 1, GetDispData(pOutBlock1->ms_08, sizeof(pOutBlock1->ms_08), DATA_TYPE_LONG));				// [long  ,   12] 개인매수       
		m_lst1601.SetItemText(1, 1, GetDispData(pOutBlock1->md_08, sizeof(pOutBlock1->md_08), DATA_TYPE_LONG));				// [long  ,   12] 개인매도               
		m_lst1601.SetItemText(2, 1, GetDispData(pOutBlock1->svolume_08, sizeof(pOutBlock1->svolume_08), DATA_TYPE_LONG));   // [long  ,   12] 개인순매수

		m_lst1601.SetItemText(0, 2, GetDispData(pOutBlock1->ms_17, sizeof(pOutBlock1->ms_17), DATA_TYPE_LONG));				// [long  ,   12] 외국인매수        
		m_lst1601.SetItemText(1, 2, GetDispData(pOutBlock1->md_17, sizeof(pOutBlock1->md_17), DATA_TYPE_LONG));				// [long  ,   12] 외국인매도        
		m_lst1601.SetItemText(2, 2, GetDispData(pOutBlock1->svolume_17, sizeof(pOutBlock1->svolume_17), DATA_TYPE_LONG));   // [long  ,   12] 외국인순매수      

		m_lst1601.SetItemText(0, 3, GetDispData(pOutBlock1->ms_18, sizeof(pOutBlock1->ms_18), DATA_TYPE_LONG));				// [long  ,   12] 기관계매수        
		m_lst1601.SetItemText(1, 3, GetDispData(pOutBlock1->md_18, sizeof(pOutBlock1->md_18), DATA_TYPE_LONG));				// [long  ,   12] 기관계매도        
		m_lst1601.SetItemText(2, 3, GetDispData(pOutBlock1->svolume_18, sizeof(pOutBlock1->svolume_18), DATA_TYPE_LONG));   // [long  ,   12] 기관계순매수
	}

	else if (strcmp(pRpData->szBlockName, NAME_t1601OutBlock2) == 0)
	{
		LPt1601OutBlock2 pOutBlock2 = (LPt1601OutBlock2)pRpData->lpData;
	}

	else if (strcmp(pRpData->szBlockName, NAME_t1601OutBlock3) == 0)
	{
		LPt1601OutBlock3 pOutBlock3 = (LPt1601OutBlock3)pRpData->lpData;

		m_lst1601.SetItemText(3, 1, GetDispData(pOutBlock3->ms_08, sizeof(pOutBlock3->ms_08), DATA_TYPE_LONG));				// [long  ,   12] 개인매수          
		m_lst1601.SetItemText(4, 1, GetDispData(pOutBlock3->md_08, sizeof(pOutBlock3->md_08), DATA_TYPE_LONG));				// [long  ,   12] 개인매도          
		m_lst1601.SetItemText(5, 1, GetDispData(pOutBlock3->svolume_08, sizeof(pOutBlock3->svolume_08), DATA_TYPE_LONG));   // [long  ,   12] 개인순매수        

		m_lst1601.SetItemText(3, 2, GetDispData(pOutBlock3->ms_17, sizeof(pOutBlock3->ms_17), DATA_TYPE_LONG));				// [long  ,   12] 외국인매수        
		m_lst1601.SetItemText(4, 2, GetDispData(pOutBlock3->md_17, sizeof(pOutBlock3->md_17), DATA_TYPE_LONG));				// [long  ,   12] 외국인매도        
		m_lst1601.SetItemText(5, 2, GetDispData(pOutBlock3->svolume_17, sizeof(pOutBlock3->svolume_17), DATA_TYPE_LONG));   // [long  ,   12] 외국인순매수      

		m_lst1601.SetItemText(3, 3, GetDispData(pOutBlock3->ms_18, sizeof(pOutBlock3->ms_18), DATA_TYPE_LONG));				// [long  ,   12] 기관계매수        
		m_lst1601.SetItemText(4, 3, GetDispData(pOutBlock3->md_18, sizeof(pOutBlock3->md_18), DATA_TYPE_LONG));				// [long  ,   12] 기관계매도        
		m_lst1601.SetItemText(5, 3, GetDispData(pOutBlock3->svolume_18, sizeof(pOutBlock3->svolume_18), DATA_TYPE_LONG));   // [long  ,   12] 기관계순매수   
	}

	else if (strcmp(pRpData->szBlockName, NAME_t1601OutBlock4) == 0)
	{
		LPt1601OutBlock4 pOutBlock4 = (LPt1601OutBlock4)pRpData->lpData;

		m_lst1601.SetItemText(6, 1, GetDispData(pOutBlock4->ms_08, sizeof(pOutBlock4->ms_08), DATA_TYPE_LONG));				// [long  ,   12] 개인매수          
		m_lst1601.SetItemText(7, 1, GetDispData(pOutBlock4->md_08, sizeof(pOutBlock4->md_08), DATA_TYPE_LONG));				// [long  ,   12] 개인매도          
		m_lst1601.SetItemText(8, 1, GetDispData(pOutBlock4->svolume_08, sizeof(pOutBlock4->svolume_08), DATA_TYPE_LONG));   // [long  ,   12] 개인순매수        

		m_lst1601.SetItemText(6, 2, GetDispData(pOutBlock4->ms_17, sizeof(pOutBlock4->ms_17), DATA_TYPE_LONG));				// [long  ,   12] 외국인매수        
		m_lst1601.SetItemText(7, 2, GetDispData(pOutBlock4->md_17, sizeof(pOutBlock4->md_17), DATA_TYPE_LONG));				// [long  ,   12] 외국인매도        
		m_lst1601.SetItemText(8, 2, GetDispData(pOutBlock4->svolume_17, sizeof(pOutBlock4->svolume_17), DATA_TYPE_LONG));   // [long  ,   12] 외국인순매수      

		m_lst1601.SetItemText(6, 3, GetDispData(pOutBlock4->ms_18, sizeof(pOutBlock4->ms_18), DATA_TYPE_LONG));				// [long  ,   12] 기관계매수        
		m_lst1601.SetItemText(7, 3, GetDispData(pOutBlock4->md_18, sizeof(pOutBlock4->md_18), DATA_TYPE_LONG));				// [long  ,   12] 기관계매도        
		m_lst1601.SetItemText(8, 3, GetDispData(pOutBlock4->svolume_18, sizeof(pOutBlock4->svolume_18), DATA_TYPE_LONG));   // [long  ,   12] 기관계순매수 
	}

	else if (strcmp(pRpData->szBlockName, NAME_t1601OutBlock5) == 0)
	{
		LPt1601OutBlock5 pOutBlock5 = (LPt1601OutBlock5)pRpData->lpData;

		m_lst1601.SetItemText(9, 1, GetDispData(pOutBlock5->ms_08, sizeof(pOutBlock5->ms_08), DATA_TYPE_LONG));				// [long  ,   12] 개인매수          
		m_lst1601.SetItemText(10, 1, GetDispData(pOutBlock5->md_08, sizeof(pOutBlock5->md_08), DATA_TYPE_LONG));			// [long  ,   12] 개인매도          
		m_lst1601.SetItemText(11, 1, GetDispData(pOutBlock5->svolume_08, sizeof(pOutBlock5->svolume_08), DATA_TYPE_LONG));  // [long  ,   12] 개인순매수        

		m_lst1601.SetItemText(9, 2, GetDispData(pOutBlock5->ms_17, sizeof(pOutBlock5->ms_17), DATA_TYPE_LONG));				// [long  ,   12] 외국인매수        
		m_lst1601.SetItemText(10, 2, GetDispData(pOutBlock5->md_17, sizeof(pOutBlock5->md_17), DATA_TYPE_LONG));			// [long  ,   12] 외국인매도        
		m_lst1601.SetItemText(11, 2, GetDispData(pOutBlock5->svolume_17, sizeof(pOutBlock5->svolume_17), DATA_TYPE_LONG));  // [long  ,   12] 외국인순매수      

		m_lst1601.SetItemText(9, 3, GetDispData(pOutBlock5->ms_18, sizeof(pOutBlock5->ms_18), DATA_TYPE_LONG));				// [long  ,   12] 기관계매수        
		m_lst1601.SetItemText(10, 3, GetDispData(pOutBlock5->md_18, sizeof(pOutBlock5->md_18), DATA_TYPE_LONG));			// [long  ,   12] 기관계매도        
		m_lst1601.SetItemText(11, 3, GetDispData(pOutBlock5->svolume_18, sizeof(pOutBlock5->svolume_18), DATA_TYPE_LONG));  // [long  ,   12] 기관계순매수    
	}

}

void CDlg_JEKYLL::Receive2301(LPRECV_PACKET pRpData)//옵션전광판 header A type
{
	CString strRef;
	GetDlgItemTextA(IDC_REF, strRef);
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
			if (s2 == CallCode[0])
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
			s3 = GetDispData(pOutBlock1[i].iv, sizeof(pOutBlock1[i].iv), DATA_TYPE_FLOAT, 2); //f3 = (float)atof(s3);
			s4 = GetDispData(pOutBlock1[i].delt, sizeof(pOutBlock1[i].delt), DATA_TYPE_FLOAT, 2); //f4 = (float)atof(s4);
			s5 = GetDispData(pOutBlock1[i].gama, sizeof(pOutBlock1[i].gama), DATA_TYPE_FLOAT, 2); //f5 = (float)atof(s5);
			s6 = GetDispData(pOutBlock1[i].ceta, sizeof(pOutBlock1[i].ceta), DATA_TYPE_FLOAT, 2); //f6 = (float)atof(s6);
			s7 = GetDispData(pOutBlock1[i].vega, sizeof(pOutBlock1[i].vega), DATA_TYPE_FLOAT, 2); //f7 = (float)atof(s7);
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
		CallCode[0] = strVecOptcode.at(distance(begin(fVecPrice), it));								// 그 위치의 옵션코드를 저장함
		CallCode[1] = strVecOptcode.at(distance(begin(fVecPrice), it) - 1);
		CallCode[2] = strVecOptcode.at(distance(begin(fVecPrice), it) - 2);
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
			s3 = GetDispData(pOutBlock2[i].iv, sizeof(pOutBlock2[i].iv), DATA_TYPE_FLOAT, 2); //f3 = (float)atof(s3);
			s4 = GetDispData(pOutBlock2[i].delt, sizeof(pOutBlock2[i].delt), DATA_TYPE_FLOAT, 2); //f4 = (float)atof(s4);
			s5 = GetDispData(pOutBlock2[i].gama, sizeof(pOutBlock2[i].gama), DATA_TYPE_FLOAT, 2); //f5 = (float)atof(s5);
			s6 = GetDispData(pOutBlock2[i].ceta, sizeof(pOutBlock2[i].ceta), DATA_TYPE_FLOAT, 2); //f6 = (float)atof(s6);
			s7 = GetDispData(pOutBlock2[i].vega, sizeof(pOutBlock2[i].vega), DATA_TYPE_FLOAT, 2); //f7 = (float)atof(s7);
			s8 = GetDispData(pOutBlock2[i].open, sizeof(pOutBlock2[i].open), DATA_TYPE_FLOAT, 2);
			if (s2 == PutCode[0])
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
			s3 = GetDispData(pOutBlock2[i].iv, sizeof(pOutBlock2[i].iv), DATA_TYPE_FLOAT, 2); //f3 = (float)atof(s3);
			s4 = GetDispData(pOutBlock2[i].delt, sizeof(pOutBlock2[i].delt), DATA_TYPE_FLOAT, 2); //f4 = (float)atof(s4);
			s5 = GetDispData(pOutBlock2[i].gama, sizeof(pOutBlock2[i].gama), DATA_TYPE_FLOAT, 2); //f5 = (float)atof(s5);
			s6 = GetDispData(pOutBlock2[i].ceta, sizeof(pOutBlock2[i].ceta), DATA_TYPE_FLOAT, 2); //f6 = (float)atof(s6);
			s7 = GetDispData(pOutBlock2[i].vega, sizeof(pOutBlock2[i].vega), DATA_TYPE_FLOAT, 2); //f7 = (float)atof(s7);
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
		PutCode[0] = strVecOptcode.at(distance(begin(fVecPrice), it));							// 그 위치의 옵션코드를 저장함
		PutCode[1] = strVecOptcode.at(distance(begin(fVecPrice), it) + 1);
		PutCode[2] = strVecOptcode.at(distance(begin(fVecPrice), it) + 2);
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

	//CallCode[0].Replace("205", "201");
	//PutCode[0].Replace("305", "301");
	m_callcode.SetWindowTextA(CallCode[0]);
	m_putcode.SetWindowTextA(PutCode[0]);
	//m_callcode2.SetWindowTextA(CallCode[1]);
	//m_putcode2.SetWindowTextA(PutCode[1]);
	//m_callcode3.SetWindowTextA(CallCode[2]);
	//m_putcode3.SetWindowTextA(PutCode[2]);
}

void CDlg_JEKYLL::Receive2421(LPRECV_PACKET pRpData)//미결제약정추이 header A type
{
	if (strcmp(pRpData->szBlockName, NAME_t2421OutBlock) == 0)
	{
		LPt2421OutBlock pOutBlock = (LPt2421OutBlock)pRpData->lpData;
	}

	else if (strcmp(pRpData->szBlockName, NAME_t2421OutBlock1) == 0)
	{
		LPt2421OutBlock1 pOutBlock1 = (LPt2421OutBlock1)pRpData->lpData;
		int	nCount = pRpData->nDataLength / sizeof(t2421OutBlock1);
		CString s1, s2;
		for (int i = 0; i < nCount; i++)
		{
			s1 = GetDispData(pOutBlock1[i].closeopenyak, sizeof(pOutBlock1[i].closeopenyak), DATA_TYPE_LONG);
			s2 = GetDispData(pOutBlock1[i].openupdn, sizeof(pOutBlock1[i].openupdn), DATA_TYPE_LONG);
		}
	}
}

void CDlg_JEKYLL::Receive1662(LPRECV_PACKET pRpData)//프로그램매매차트,베이시스 header A type
{
	if (strcmp(pRpData->szBlockName, NAME_t1662OutBlock) == 0)
	{
		LPt1662OutBlock pOutBlock = (LPt1662OutBlock)pRpData->lpData;
		int	nCount = pRpData->nDataLength / sizeof(t1662OutBlock);
		CString str;
		if (nCount > 411) return;
		for (int i = 0; i < nCount - 1; i++)
		{
			str = GetDispData(pOutBlock[i].k200basis, sizeof(pOutBlock[i].k200basis), DATA_TYPE_DOT, 2);
		}

	}
}

void CDlg_JEKYLL::Receive1602(LPRECV_PACKET pRpData) //거래량 header A type
{
	CString cts_time;
	if (strcmp(pRpData->szBlockName, NAME_t1602OutBlock) == 0)
	{
		LPt1602OutBlock pOutBlock = (LPt1602OutBlock)pRpData->lpData;
		cts_time = GetDispData(pOutBlock->cts_time, sizeof(pOutBlock->cts_time), DATA_TYPE_STRING);			//
	}

	if (strcmp(pRpData->szBlockName, NAME_t1602OutBlock1) == 0)
	{
		LPt1602OutBlock1 pOutBlock = (LPt1602OutBlock1)pRpData->lpData;
		int				 nCount = pRpData->nDataLength / sizeof(t1602OutBlock1);		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.

		for (int i = 0; i < nCount; i++) // 데이터가 역순으로 들어옴(30초)
		{
			CString s1, s2, s3;
			s1 = GetDispData(pOutBlock[i].time, sizeof(pOutBlock[i].time), DATA_TYPE_STRING); strArTime1602[nCount - i - 1] = s1;
			s2 = GetDispData(pOutBlock[i].sv_17, sizeof(pOutBlock[i].sv_17), DATA_TYPE_LONG); lArForVol[nCount - i - 1] = atol(s2); // 외인
			s3 = GetDispData(pOutBlock[i].sv_18, sizeof(pOutBlock[i].sv_18), DATA_TYPE_LONG); lArSecVol[nCount - i - 1] = atol(s3); // 기관
		}
		
		for (int i = 1; i < nCount; i++)
		{
			lArForVol[i] = lArForVol[i] + lArForVol[i - 1];//i_max=790
			lArSecVol[i] = lArSecVol[i] + lArSecVol[i - 1];
		}

		//strArTime8415[0] = strArTime1602[2];
		lArForVol2[0] = lArForVol[2];//09:00:00[0] + 09:00:30[1] + 09:01:00[2] - 0분=nCurMin(표시는 09:01)
		lArSecVol2[0] = lArSecVol[2];

		if (nCount > 3)
		{
			if (nCount % 2 == 1)//홀수
			{
				nCount = (nCount - 1) / 2;
				for (int i = 1; i < nCount; i++)
				{
					//strArTime8415[i] = strArTime1602[2 * i + 2];
					lArForVol2[i] = lArForVol[2 * i + 2];  // max 2*409+2=790
					lArSecVol2[i] = lArSecVol[2 * i + 2];
				}
			}
			else //짝수
			{
				nCount /= 2;
				for (int i = 1; i < nCount - 1; i++)
				{
					//strArTime8415[i] = strArTime1602[2 * i + 2];
					lArForVol2[i] = lArForVol[2 * i + 2];  // max 2*409+2=790
					lArSecVol2[i] = lArSecVol[2 * i + 2];
				}
				lArForVol2[nCount - 1] = lArForVol[2 * (nCount)-1];  // max 2*409+2=790
				lArSecVol2[nCount - 1] = lArSecVol[2 * (nCount)-1];
			}

			if (nCount > 5) {
				for (int i = 5; i < nCount; i++)
				{
					long l1 = 0, l2 = 0;
					for (int k = 0; k < 5; k++)										// 5분 SMA
					{
						l1 += (lArForVol2[i - k] - lArForVol2[i - k - 1]);
						l2 += (lArSecVol2[i - k] - lArSecVol2[i - k - 1]);
					}
					l1 = (long)(l1 / 5);
					l2 = (long)(l2 / 5);
					lArForVol5m[i] = l1;
					lArSecVol5m[i] = l2;
				}
			}

		}

		//lArForVol5m[0] = lArForVol2[0];									// 10분 EMA (alpha=2/(N+1), 2/11)
		//lArSecVol5m[0] = lArSecVol2[0];
		//for (int i = 1; i < nCount; i++)
		//{
		//	lArForVol5m[i] = lArForVol2[i] * 2 / 11 + lArForVol5m[i - 1] * 9 / 11;
		//	lArSecVol5m[i] = lArSecVol2[i] * 2 / 11 + lArSecVol5m[i - 1] * 9 / 11;
		//}
		//	

	// 출력 ***************************************************************************************************************************

		ofstream myfile1602("test1602.csv"); // 외인,기관 거래량(30초->1분)
		if (myfile1602.is_open())
		{
			myfile1602 << "시간, 종가, 콜, 풋, 외인, 기관, 외인(10분), 기관(10분)\n";
			for (int i = 0; i < nCount; i++)
			{
				myfile1602 << strArTime8415[i] << ", " << fArClose[i] << ", " << fArCClose[i] << ", " << fArPClose[i] << ", " << lArForVol2[i] << ", " << lArSecVol2[i] << ", "
					<< lArForVol5m[i] << ", " << lArSecVol5m[i] << "\n";
			}
		}
		myfile1602.close();
		/*CString str;
		str.Format("%d", lArForVol5m[nCount - 1]);	m_v51.SetWindowText(str);
		str.Format("%d", lArSecVol5m[nCount - 1]);	m_v61.SetWindowText(str);*/
	}
	return;
}

void CDlg_JEKYLL::Receive1602_(LPRECV_PACKET pRpData) //거래량 header A type
{
	CString cts_time;
	if (strcmp(pRpData->szBlockName, NAME_t1602OutBlock) == 0)
	{
		LPt1602OutBlock pOutBlock = (LPt1602OutBlock)pRpData->lpData;
		cts_time = GetDispData(pOutBlock->cts_time, sizeof(pOutBlock->cts_time), DATA_TYPE_STRING);			//
	}

	if (strcmp(pRpData->szBlockName, NAME_t1602OutBlock1) == 0)
	{
		LPt1602OutBlock1 pOutBlock = (LPt1602OutBlock1)pRpData->lpData;
		int				 nCount = pRpData->nDataLength / sizeof(t1602OutBlock1);		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.

		for (int i = 0; i < nCount; i++) // 데이터가 역순으로 들어옴(30초)
		{
			CString s1, s2, s3;
			s1 = GetDispData(pOutBlock[i].time, sizeof(pOutBlock[i].time), DATA_TYPE_STRING); strArTime1602[nCount - i - 1] = s1;
			s2 = GetDispData(pOutBlock[i].sv_17, sizeof(pOutBlock[i].sv_17), DATA_TYPE_LONG); lArKoForVol[nCount - i - 1] = atol(s2); // 외인
			s3 = GetDispData(pOutBlock[i].sv_18, sizeof(pOutBlock[i].sv_18), DATA_TYPE_LONG); lArKoSecVol[nCount - i - 1] = atol(s3); // 기관
		}

		for (int i = 1; i < nCount; i++)
		{
			lArKoForVol[i] = lArKoForVol[i] + lArKoForVol[i - 1];//i_max=790
			lArKoSecVol[i] = lArKoSecVol[i] + lArKoSecVol[i - 1];
		}

		//strArTime8415[0] = strArTime1602[2];
		lArKoForVol2[0] = lArKoForVol[2];//09:00:00[0] + 09:00:30[1] + 09:01:00[2] - 0분=nCurMin(표시는 09:01)
		lArKoSecVol2[0] = lArKoSecVol[2];

		if (nCount > 3)
		{
			if (nCount % 2 == 1)//홀수
			{
				nCount = (nCount - 1) / 2;
				for (int i = 1; i < nCount; i++)
				{
					//strArTime8415[i] = strArTime1602[2 * i + 2];
					lArKoForVol2[i] = lArKoForVol[2 * i + 2];  // max 2*409+2=790
					lArKoSecVol2[i] = lArKoSecVol[2 * i + 2];
				}
			}
			else //짝수
			{
				nCount /= 2;
				for (int i = 1; i < nCount - 1; i++)
				{
					//strArTime8415[i] = strArTime1602[2 * i + 2];
					lArKoForVol2[i] = lArKoForVol[2 * i + 2];  // max 2*409+2=790
					lArKoSecVol2[i] = lArKoSecVol[2 * i + 2];
				}
				lArKoForVol2[nCount - 1] = lArKoForVol[2 * (nCount)-1];  // max 2*409+2=790
				lArKoSecVol2[nCount - 1] = lArKoSecVol[2 * (nCount)-1];
			}

			if (nCount > 5) {
				for (int i = 5; i < nCount; i++)
				{
					long l1 = 0, l2 = 0;
					for (int k = 0; k < 5; k++)										// 5분 SMA
					{
						l1 += (lArKoForVol2[i - k] - lArKoForVol2[i - k - 1]);
						l2 += (lArKoSecVol2[i - k] - lArKoSecVol2[i - k - 1]);
					}
					l1 = (long)(l1 / 5);
					l2 = (long)(l2 / 5);
					lArKoForVol5m[i] = l1;
					lArKoSecVol5m[i] = l2;
				}
			}

		}

		//lArKoForVol5m[0] = lArKoForVol2[0];									// 10분 EMA (alpha=2/(N+1), 2/11)
		//lArKoSecVol5m[0] = lArKoSecVol2[0];
		//for (int i = 1; i < nCount; i++)
		//{
		//	lArKoForVol5m[i] = lArKoForVol2[i] * 2 / 11 + lArKoForVol5m[i - 1] * 9 / 11;
		//	lArKoSecVol5m[i] = lArKoSecVol2[i] * 2 / 11 + lArKoSecVol5m[i - 1] * 9 / 11;
		//}
		//	

	// 출력 ***************************************************************************************************************************

		ofstream myfile1602_("test1602_.csv"); // 외인,기관 거래량(30초->1분)
		if (myfile1602_.is_open())
		{
			myfile1602_ << "시간, 종가, 콜, 풋, 외인, 기관, 외인(10분), 기관(10분)\n";
			for (int i = 0; i < nCount; i++)
			{
				myfile1602_ << strArTime8415[i] << ", " << fArClose[i] << ", " << fArCClose[i] << ", " << fArPClose[i] << ", " << lArKoForVol2[i] << ", " << lArKoSecVol2[i] << ", "
					<< lArKoForVol5m[i] << ", " << lArKoSecVol5m[i] << "\n";
			}
		}
		myfile1602_.close();
		/*CString str;
		str.Format("%d", lArForVol5m[nCount - 1]);	m_v51.SetWindowText(str);
		str.Format("%d", lArSecVol5m[nCount - 1]);	m_v61.SetWindowText(str);*/
		//CString str;/*
		//str.Format("%d", lArKoForVol5m[nCount - 1]);	m_v51.SetWindowText(str);
		//str.Format("%d", lArKoSecVol5m[nCount - 1]);	m_v61.SetWindowText(str);*/
	}
	return;
}

void CDlg_JEKYLL::Receive1602() //거래량 header A type 선물 거래량
{
	CString str;
	str = m_lst1601.GetItemText(5, 2);	lArForVol2[nCurMin - 1] = atol(str);	// 외인 선물	
	str = m_lst1601.GetItemText(5, 3);	lArSecVol2[nCurMin - 1] = atol(str);	// 기관 선물	

	long l1 = 0, l2 = 0, l3 = 0, l4 = 0;
	if (nCurMin > 5) {
		for (int k = 0; k < 5; k++)										// 5분 SMA
		{
			l1 += (lArForVol2[nCurMin - 1 - k] - lArForVol2[nCurMin - 1 - k - 1]);
			l2 += (lArSecVol2[nCurMin - 1 - k] - lArSecVol2[nCurMin - 1 - k - 1]);
		}
		l1 = (long)(l1 / 5);
		l2 = (long)(l2 / 5);
		lArForVol5m[nCurMin - 1] = l1;
		lArSecVol5m[nCurMin - 1] = l2;
	}

	ofstream myfile1602("test1602.csv", ios::app); // 외인,기관 거래량(30초->1분)
	if (myfile1602.is_open())
	{
		int i = nCurMin - 1;
		myfile1602 << strArTime8415[i] << ", " << fArClose[i] << ", " << fArCClose[i] << ", " << fArPClose[i] << ", " << lArForVol2[i] << ", " << lArSecVol2[i] << ", "
			<< lArForVol5m[i] << ", " << lArSecVol5m[i] << "\n";
	}
	myfile1602.close();

	return;
}


void CDlg_JEKYLL::Receive1602_() //거래량 header A type 코스피 거래량
{
	CString str;
	str = m_lst1601.GetItemText(2, 2);	lArKoForVol2[nCurMin - 1] = atol(str);	// 외인 코스피
	str = m_lst1601.GetItemText(2, 3);	lArKoSecVol2[nCurMin - 1] = atol(str);	// 기관 코스피

	long l1 = 0, l2 = 0, l3 = 0, l4 = 0;
	if (nCurMin > 5) {
		for (int k = 0; k < 5; k++)										// 5분 SMA
		{
			l1 += (lArKoForVol2[nCurMin - 1 - k] - lArKoForVol2[nCurMin - 1 - k - 1]);
			l2 += (lArKoSecVol2[nCurMin - 1 - k] - lArKoSecVol2[nCurMin - 1 - k - 1]);
		}
		l1 = (long)(l1 / 5);
		l2 = (long)(l2 / 5);
		lArForVol5m[nCurMin - 1] = l1;
		lArSecVol5m[nCurMin - 1] = l2;
	}

	// 출력 ***************************************************************************************************************************

	ofstream myfile1602_("test1602_.csv", ios::app); // 외인,기관 거래량(30초->1분)
	if (myfile1602_.is_open())
	{
		int i = nCurMin - 1;
		myfile1602_ << strArTime8415[i] << ", " << fArClose[i] << ", " << fArCClose[i] << ", " << fArPClose[i] << ", " << lArKoForVol2[i] << ", " << lArKoSecVol2[i] << ", "
			<< lArKoForVol5m[i] << ", " << lArKoSecVol5m[i] << "\n";

	}
	myfile1602_.close();

	return;
}

void CDlg_JEKYLL::Receive600(LPRECV_PACKET pRpData)
{
	typedef struct
	{
		CFOAQ00600OutBlock1	outBlock1;
		CFOAQ00600OutBlock2	outBlock2;
		char				sCountOutBlock3[5];
		CFOAQ00600OutBlock3	outBlock3[1];
	} CFOAQ00600AllOutBlock, *LPCFOAQ00600AllOutBlock;

	LPCFOAQ00600AllOutBlock pAllOutBlock = (LPCFOAQ00600AllOutBlock)pRpData->lpData;

	int						nDataLength = pRpData->nDataLength;
	//int						nCol;
	//int						nRow;
	int						nCount;
	char					szCount[6] = { 0 };

	strcpy_s(m_szContKey, pRpData->szContKey);
	//GetDlgItem(IDC_BUTTON_REQUEST3)->EnableWindow(pRpData->cCont[0] == 'Y');

	// OutBlock2
	nDataLength -= sizeof(CFOAQ00600OutBlock2);
	if (nDataLength < 0)
	{
		return;
	}
	//CEdit *pEdit1, *pEdit2;
	//pEdit1 = (CEdit*)GetDlgItem(IDC_ORDQTY);
	//pEdit2 = (CEdit*)GetDlgItem(IDC_DQTY);
	//pEdit1->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OptOrdQty, sizeof(pAllOutBlock->outBlock2.OptOrdQty), DATA_TYPE_LONG)); //주문수량 m_ordered
	//pEdit2->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OptExecQty, sizeof(pAllOutBlock->outBlock2.OptExecQty), DATA_TYPE_LONG)); //체결수량 m_done

	// OutBlock3

	// Count 계산
	nDataLength -= 5;
	if (nDataLength < 0)		return;

	CopyMemory(szCount, pAllOutBlock->sCountOutBlock3, 5);
	nCount = atoi(szCount);

	// Data
	nDataLength -= sizeof(CFOAQ00600OutBlock3) * nCount;
	if (nDataLength < 0)		return;
	for (int i = 0; i < nCount; i++)
	{
		//nCol = 0; 
		if ((GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING) == CallCode[0]) || (GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING) == PutCode[0]))
		{
			CString str1, str2, str3;
			str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
			str2 = GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING);			// [string,   12] 선물옵션종목번호		    
			str3 = GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG);			// [long  ,   16] 미체결수량 
			Request300(str2, str1, str3);

			//if (str2==CallCode[0])	str4 = m_lst2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//if (str2==PutCode[0])	str4 = m_lst2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//Request200(str2, str1, str4, str3);// 현재가로 전부 매수 정정
		}

		//nRow = m_lst600.InsertItem(m_lst600.GetItemCount(), "");
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG));			// [long  ,   10] 주문번호              
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING));    // [string,   12] 선물옵션종목번호   
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsTpNm, sizeof(pAllOutBlock->outBlock3[i].BnsTpNm), DATA_TYPE_STRING));		// [string,   10] 매매구분                
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].MrcTpNm, sizeof(pAllOutBlock->outBlock3[i].MrcTpNm), DATA_TYPE_STRING));		// [string,   10] 정정취소구분명          
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoOrdPrc, sizeof(pAllOutBlock->outBlock3[i].FnoOrdPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 주문가                  
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdQty, sizeof(pAllOutBlock->outBlock3[i].OrdQty), DATA_TYPE_LONG));			// [long  ,   16] 주문수량              
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecPrc, sizeof(pAllOutBlock->outBlock3[i].ExecPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 체결가                  
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecQty, sizeof(pAllOutBlock->outBlock3[i].ExecQty), DATA_TYPE_LONG));		// [long  ,   16] 체결수량      
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsplAmt, sizeof(pAllOutBlock->outBlock3[i].BnsplAmt), DATA_TYPE_LONG));		// [long  ,   16] 매매손익금액            
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG));		// [long  ,   16] 미체결수량  


	}
	bCall = TRUE, bPut = TRUE;
	Request2400(); // lCallQty[0], lPutQty[0]
}

void CDlg_JEKYLL::Receive600C(LPRECV_PACKET pRpData)
{
	typedef struct
	{
		CFOAQ00600OutBlock1	outBlock1;
		CFOAQ00600OutBlock2	outBlock2;
		char				sCountOutBlock3[5];
		CFOAQ00600OutBlock3	outBlock3[1];
	} CFOAQ00600AllOutBlock, *LPCFOAQ00600AllOutBlock;

	LPCFOAQ00600AllOutBlock pAllOutBlock = (LPCFOAQ00600AllOutBlock)pRpData->lpData;

	int						nDataLength = pRpData->nDataLength;
	//int						nCol;
	//int						nRow;
	int						nCount;
	char					szCount[6] = { 0 };

	strcpy_s(m_szContKey, pRpData->szContKey);
	//GetDlgItem(IDC_BUTTON_REQUEST3)->EnableWindow(pRpData->cCont[0] == 'Y');

	// OutBlock2
	nDataLength -= sizeof(CFOAQ00600OutBlock2);
	if (nDataLength < 0)
	{
		return;
	}
	//CEdit *pEdit1, *pEdit2;
	//pEdit1 = (CEdit*)GetDlgItem(IDC_ORDQTY);
	//pEdit2 = (CEdit*)GetDlgItem(IDC_DQTY);
	//pEdit1->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OptOrdQty, sizeof(pAllOutBlock->outBlock2.OptOrdQty), DATA_TYPE_LONG)); //주문수량 m_ordered
	//pEdit2->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OptExecQty, sizeof(pAllOutBlock->outBlock2.OptExecQty), DATA_TYPE_LONG)); //체결수량 m_done

	// OutBlock3

	// Count 계산
	nDataLength -= 5;
	if (nDataLength < 0)		return;

	CopyMemory(szCount, pAllOutBlock->sCountOutBlock3, 5);
	nCount = atoi(szCount);

	// Data
	nDataLength -= sizeof(CFOAQ00600OutBlock3) * nCount;
	if (nDataLength < 0)		return;
	for (int i = 0; i < nCount; i++)
	{
		//nCol = 0; 
		CString str1, str2, str3;
		str2 = GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING);			// [string,   12] 선물옵션종목번호	

		if (str2 == CallCode[0])
		{
			
			str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
			str3 = GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG);			// [long  ,   16] 미체결수량 
			Request300(str2, str1, str3);
			lCallQty[0] -= atol(str3);
			//if (str2==CallCode[0])	str4 = m_lst2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//if (str2==PutCode[0])	str4 = m_lst2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//Request200(str2, str1, str4, str3);// 현재가로 전부 매수 정정
		}
		if (str2 == CallCode[1])
		{

			str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
			str3 = GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG);			// [long  ,   16] 미체결수량 
			Request300(str2, str1, str3);
			lCallQty[1] -= atol(str3);

			//if (str2==CallCode[0])	str4 = m_lst2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//if (str2==PutCode[0])	str4 = m_lst2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//Request200(str2, str1, str4, str3);// 현재가로 전부 매수 정정
		}
		if (str2 == CallCode[2])
		{

			str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
			str3 = GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG);			// [long  ,   16] 미체결수량 
			Request300(str2, str1, str3);
			lCallQty[2] -= atol(str3);

			//if (str2==CallCode[0])	str4 = m_lst2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//if (str2==PutCode[0])	str4 = m_lst2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//Request200(str2, str1, str4, str3);// 현재가로 전부 매수 정정
		}
		
		//nRow = m_lst600.InsertItem(m_lst600.GetItemCount(), "");
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG));			// [long  ,   10] 주문번호              
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING));    // [string,   12] 선물옵션종목번호   
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsTpNm, sizeof(pAllOutBlock->outBlock3[i].BnsTpNm), DATA_TYPE_STRING));		// [string,   10] 매매구분                
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].MrcTpNm, sizeof(pAllOutBlock->outBlock3[i].MrcTpNm), DATA_TYPE_STRING));		// [string,   10] 정정취소구분명          
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoOrdPrc, sizeof(pAllOutBlock->outBlock3[i].FnoOrdPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 주문가                  
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdQty, sizeof(pAllOutBlock->outBlock3[i].OrdQty), DATA_TYPE_LONG));			// [long  ,   16] 주문수량              
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecPrc, sizeof(pAllOutBlock->outBlock3[i].ExecPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 체결가                  
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecQty, sizeof(pAllOutBlock->outBlock3[i].ExecQty), DATA_TYPE_LONG));		// [long  ,   16] 체결수량      
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsplAmt, sizeof(pAllOutBlock->outBlock3[i].BnsplAmt), DATA_TYPE_LONG));		// [long  ,   16] 매매손익금액            
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG));		// [long  ,   16] 미체결수량  

		
	}
	bCall = TRUE;
	//Request2400(); // lCallQty[0], lPutQty[0]
}


void CDlg_JEKYLL::Receive600P(LPRECV_PACKET pRpData)
{
	typedef struct
	{
		CFOAQ00600OutBlock1	outBlock1;
		CFOAQ00600OutBlock2	outBlock2;
		char				sCountOutBlock3[5];
		CFOAQ00600OutBlock3	outBlock3[1];
	} CFOAQ00600AllOutBlock, *LPCFOAQ00600AllOutBlock;

	LPCFOAQ00600AllOutBlock pAllOutBlock = (LPCFOAQ00600AllOutBlock)pRpData->lpData;

	int						nDataLength = pRpData->nDataLength;
	//int						nCol;
	//int						nRow;
	int						nCount;
	char					szCount[6] = { 0 };

	strcpy_s(m_szContKey, pRpData->szContKey);
	//GetDlgItem(IDC_BUTTON_REQUEST3)->EnableWindow(pRpData->cCont[0] == 'Y');

	// OutBlock2
	nDataLength -= sizeof(CFOAQ00600OutBlock2);
	if (nDataLength < 0)
	{
		return;
	}
	//CEdit *pEdit1, *pEdit2;
	//pEdit1 = (CEdit*)GetDlgItem(IDC_ORDQTY);
	//pEdit2 = (CEdit*)GetDlgItem(IDC_DQTY);
	//pEdit1->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OptOrdQty, sizeof(pAllOutBlock->outBlock2.OptOrdQty), DATA_TYPE_LONG)); //주문수량 m_ordered
	//pEdit2->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OptExecQty, sizeof(pAllOutBlock->outBlock2.OptExecQty), DATA_TYPE_LONG)); //체결수량 m_done

	// OutBlock3

	// Count 계산
	nDataLength -= 5;
	if (nDataLength < 0)		return;

	CopyMemory(szCount, pAllOutBlock->sCountOutBlock3, 5);
	nCount = atoi(szCount);

	// Data
	nDataLength -= sizeof(CFOAQ00600OutBlock3) * nCount;
	if (nDataLength < 0)		return;

	
	for (int i = 0; i < nCount; i++)
	{
		//nCol = 0; 
		CString str1, str2, str3;
		str2 = GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING);			// [string,   12] 선물옵션종목번호		    

		if (str2 == PutCode[0])
		{
			
			str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
			str3 = GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG);			// [long  ,   16] 미체결수량 
			Request300(str2, str1, str3);
			lPutQty[0] -= atol(str3);

			//if (str2==CallCode[0])	str4 = m_lst2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//if (str2==PutCode[0])	str4 = m_lst2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//Request200(str2, str1, str4, str3);// 현재가로 전부 매수 정정
		}
		if (str2 == PutCode[1])
		{

			str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
			str3 = GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG);			// [long  ,   16] 미체결수량 
			Request300(str2, str1, str3);
			lPutQty[1] -= atol(str3);

			//if (str2==CallCode[0])	str4 = m_lst2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//if (str2==PutCode[0])	str4 = m_lst2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//Request200(str2, str1, str4, str3);// 현재가로 전부 매수 정정
		}
		if (str2 == PutCode[2])
		{

			str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
			str3 = GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG);			// [long  ,   16] 미체결수량 
			Request300(str2, str1, str3);
			lPutQty[2] -= atol(str3);

			//if (str2==CallCode[0])	str4 = m_lst2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//if (str2==PutCode[0])	str4 = m_lst2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			//Request200(str2, str1, str4, str3);// 현재가로 전부 매수 정정
		}

		//nRow = m_lst600.InsertItem(m_lst600.GetItemCount(), "");
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG));			// [long  ,   10] 주문번호              
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING));    // [string,   12] 선물옵션종목번호   
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsTpNm, sizeof(pAllOutBlock->outBlock3[i].BnsTpNm), DATA_TYPE_STRING));		// [string,   10] 매매구분                
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].MrcTpNm, sizeof(pAllOutBlock->outBlock3[i].MrcTpNm), DATA_TYPE_STRING));		// [string,   10] 정정취소구분명          
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoOrdPrc, sizeof(pAllOutBlock->outBlock3[i].FnoOrdPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 주문가                  
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdQty, sizeof(pAllOutBlock->outBlock3[i].OrdQty), DATA_TYPE_LONG));			// [long  ,   16] 주문수량              
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecPrc, sizeof(pAllOutBlock->outBlock3[i].ExecPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 체결가                  
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecQty, sizeof(pAllOutBlock->outBlock3[i].ExecQty), DATA_TYPE_LONG));		// [long  ,   16] 체결수량      
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsplAmt, sizeof(pAllOutBlock->outBlock3[i].BnsplAmt), DATA_TYPE_LONG));		// [long  ,   16] 매매손익금액            
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG));		// [long  ,   16] 미체결수량 
	}
	bPut = TRUE;
	//Request2400(); // lCallQty[0], lPutQty[0]
}

void CDlg_JEKYLL::Receive600_(LPRECV_PACKET pRpData)
{
	typedef struct
	{
		CFOAQ00600OutBlock1	outBlock1;
		CFOAQ00600OutBlock2	outBlock2;
		char				sCountOutBlock3[5];
		CFOAQ00600OutBlock3	outBlock3[1];
	} CFOAQ00600AllOutBlock, *LPCFOAQ00600AllOutBlock;

	LPCFOAQ00600AllOutBlock pAllOutBlock = (LPCFOAQ00600AllOutBlock)pRpData->lpData;

	int						nDataLength = pRpData->nDataLength;
	//int						nCol;
	//int						nRow;
	int						nCount;
	char					szCount[6] = { 0 };

	strcpy_s(m_szContKey, pRpData->szContKey);
	//GetDlgItem(IDC_BUTTON_REQUEST3)->EnableWindow(pRpData->cCont[0] == 'Y');

	// OutBlock2
	nDataLength -= sizeof(CFOAQ00600OutBlock2);
	if (nDataLength < 0)
	{
		return;
	}
	//CEdit *pEdit1, *pEdit2;
	//pEdit1 = (CEdit*)GetDlgItem(IDC_ORDQTY);
	//pEdit2 = (CEdit*)GetDlgItem(IDC_DQTY);
	//pEdit1->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OptOrdQty, sizeof(pAllOutBlock->outBlock2.OptOrdQty), DATA_TYPE_LONG)); //주문수량 m_ordered
	//pEdit2->SetWindowText(GetDispData(pAllOutBlock->outBlock2.OptExecQty, sizeof(pAllOutBlock->outBlock2.OptExecQty), DATA_TYPE_LONG)); //체결수량 m_done

	// OutBlock3

	// Count 계산
	nDataLength -= 5;
	if (nDataLength < 0)		return;

	CopyMemory(szCount, pAllOutBlock->sCountOutBlock3, 5);
	nCount = atoi(szCount);

	// Data
	nDataLength -= sizeof(CFOAQ00600OutBlock3) * nCount;
	if (nDataLength < 0)		return;
	for (int i = 0; i < nCount; i++)
	{
		//nCol = 0; 
		if (GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING) == CallCode[0] || (GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING) == PutCode[0]))
		{
			CString str1, str2, str3, str4;
			str1 = GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG);					// [long  ,   10] 주문번호              
			str2 = GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING);			// [string,   12] 선물옵션종목번호		    
			str3 = GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG);			// [long  ,   16] 미체결수량 
			//Request300(str2, str1, str3);

			if (str2==CallCode[0])	str4 = m_lst2105.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			if (str2==PutCode[0])	str4 = m_lst2105_.GetItemText(8, 1); //매도호가1(매수가능 현재가)
			Request200(str2, str1, str4, str3);// 현재가로 전부 매수 정정(종목번호, 주문번호, 매도호가, 미체결수량)
		}

		//nRow = m_lst600.InsertItem(m_lst600.GetItemCount(), "");
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdNo, sizeof(pAllOutBlock->outBlock3[i].OrdNo), DATA_TYPE_LONG));			// [long  ,   10] 주문번호              
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoIsuNo, sizeof(pAllOutBlock->outBlock3[i].FnoIsuNo), DATA_TYPE_STRING));    // [string,   12] 선물옵션종목번호   
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsTpNm, sizeof(pAllOutBlock->outBlock3[i].BnsTpNm), DATA_TYPE_STRING));		// [string,   10] 매매구분                
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].MrcTpNm, sizeof(pAllOutBlock->outBlock3[i].MrcTpNm), DATA_TYPE_STRING));		// [string,   10] 정정취소구분명          
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].FnoOrdPrc, sizeof(pAllOutBlock->outBlock3[i].FnoOrdPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 주문가                  
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].OrdQty, sizeof(pAllOutBlock->outBlock3[i].OrdQty), DATA_TYPE_LONG));			// [long  ,   16] 주문수량              
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecPrc, sizeof(pAllOutBlock->outBlock3[i].ExecPrc), DATA_TYPE_DOT, 2));		// [double, 13.2] 체결가                  
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].ExecQty, sizeof(pAllOutBlock->outBlock3[i].ExecQty), DATA_TYPE_LONG));		// [long  ,   16] 체결수량      
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].BnsplAmt, sizeof(pAllOutBlock->outBlock3[i].BnsplAmt), DATA_TYPE_LONG));		// [long  ,   16] 매매손익금액            
		//m_lst600.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock3[i].UnercQty, sizeof(pAllOutBlock->outBlock3[i].UnercQty), DATA_TYPE_LONG));		// [long  ,   16] 미체결수량  


	}
	bCall = TRUE; bPut = TRUE;
	Request2400(); // lCallQty[0], lPutQty[0]
}

void CDlg_JEKYLL::Receive100(LPRECV_PACKET pRpData)
{
	typedef struct
	{
		CFOAT00100OutBlock1	outBlock1;
		CFOAT00100OutBlock2	outBlock2;
	} CFOAT00100AllOutBlock, *LPCFOAT00100AllOutBlock;

	LPCFOAT00100AllOutBlock pAllOutBlock = (LPCFOAT00100AllOutBlock)pRpData->lpData;
	int						nDataLength = pRpData->nDataLength;
	//int						nCol;

	//------------------------------------------------
	// OutBlock1
	nDataLength -= sizeof(CFOAT00100OutBlock1);
	if (nDataLength < 0)		return;

	//nCol = 0;
	//int nRow = m_lst100.InsertItem(m_lst100.GetItemCount(), "");
	//m_lst100.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoIsuNo, sizeof(pAllOutBlock->outBlock1.FnoIsuNo), DATA_TYPE_STRING));		// 옵션종목번호      
	//m_lst100.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock1.FnoOrdPrc, sizeof(pAllOutBlock->outBlock1.FnoOrdPrc), DATA_TYPE_DOT, 2));			// 주문가격            
	//m_lst100.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock1.OrdQty, sizeof(pAllOutBlock->outBlock1.OrdQty), DATA_TYPE_LONG));			// 주문수량     

	//// OutBlock2
	//nDataLength -= sizeof(CFOAT00100OutBlock2);
	//if (nDataLength < 0)		return;
	//m_lst100.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdNo, sizeof(pAllOutBlock->outBlock2.OrdNo), DATA_TYPE_LONG));				// 주문번호     
	//m_lst100.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleAmt, sizeof(pAllOutBlock->outBlock2.OrdAbleAmt), DATA_TYPE_LONG));    // 주문가능금액    
	//m_lst100.SetItemText(nRow, nCol++, GetDispData(pAllOutBlock->outBlock2.OrdAbleQty, sizeof(pAllOutBlock->outBlock2.OrdAbleQty), DATA_TYPE_LONG));    // 주문가능수량    
}

void CDlg_JEKYLL::Receive8415(LPRECV_PACKET pRpData) //선물옵션차트(n분) header A type
{
	CString shcode;
	if (strcmp(pRpData->szBlockName, NAME_t8415OutBlock) == 0)
	{
		LPt8415OutBlock pOutBlock = (LPt8415OutBlock)pRpData->lpData;

		shcode = GetDispData(pOutBlock->shcode, sizeof(pOutBlock->shcode), DATA_TYPE_STRING);			//
	}

	else if (strcmp(pRpData->szBlockName, NAME_t8415OutBlock1) == 0)
	{
		LPt8415OutBlock1 pOutBlock = (LPt8415OutBlock1)pRpData->lpData;
		int				 nCount = pRpData->nDataLength / sizeof(t8415OutBlock1);		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
		float fHigh = fArClose[0], fLow = fArClose[0], fRef = 0.5;
		int nUpdateHigh = 0, nUpdateLow = 0;
		fHighest = 500, fLowest = 0;

		for (int i = 0; i < nCount; i++)
		{
			CString s1, s2, s3, s4, s5, s6;

			s1 = GetDispData(pOutBlock[i].time, sizeof(pOutBlock[i].time), DATA_TYPE_STRING); strArTime8415[i] = s1;			//시간
			s2 = GetDispData(pOutBlock[i].close, sizeof(pOutBlock[i].close), DATA_TYPE_FLOAT, 2); fArClose[i] = (float)atof(s2);		//종가
			s3 = GetDispData(pOutBlock[i].high, sizeof(pOutBlock[i].high), DATA_TYPE_FLOAT, 2); fArHigh[i] = (float)atof(s3);			//고가
			s4 = GetDispData(pOutBlock[i].low, sizeof(pOutBlock[i].low), DATA_TYPE_FLOAT, 2); fArLow[i] = (float)atof(s4);				//저가
			s5 = GetDispData(pOutBlock[i].jdiff_vol, sizeof(pOutBlock[i].jdiff_vol), DATA_TYPE_LONG); lArVol[i] = atol(s5);		//거래량
			s6 = GetDispData(pOutBlock[i].open, sizeof(pOutBlock[i].open), DATA_TYPE_FLOAT, 2); fArOpen[i] = (float)atof(s6);			//시가

			fArWidth[i] = fArClose[i] - fArOpen[i];							//Width price(close-open)

			if (fHighest == 500 || fLowest == 0)
			{
				if (fArClose[i] > fHigh) fHigh = fArClose[i];
				if (fArClose[i] < fLow) fLow = fArClose[i];
				if (fHigh - fLow > fRef)
				{
					fHighest = fHigh;
					fLowest = fLow;
				}
			}
			else
			{
				if (fArClose[i] > fHighest)
				{
					fHighest = fArClose[i];
					nUpdateHigh++;
				}
				if (fArClose[i] < fLowest)
				{
					fLowest = fArClose[i];
					nUpdateLow++;
				}
			}
			nArUpdateHigh[i] = nUpdateHigh;
			nArUpdateLow[i] = nUpdateLow;

			lArVol2[i] = lArVol[i];
			if ((fArWidth[i] < 0) || (fArWidth[i] == 0 && fArHigh[i] - fArClose[i] > fArClose[i] - fArLow[i])) lArVol2[i] *= -1;
			if (fArWidth[i] == 0 && fArHigh[i] - fArClose[i] == fArClose[i] - fArLow[i]) lArVol2[i] *= 0;
		}

		// ************************************************************************************************* 10분봉 High/Low/Open/Close
		int quo = nCount / 10, rem = nCount % 10; //현재시간 위치를 결정
		if (nCount < 410)
		{
			if (nCount > 9) //10분봉 계산
			{
				for (int i = 0; i < quo; ++i) //
				{
					float f1 = 0.0, f2 = 500;//close max,min(50분동안)
					int kn = 10;
					if (quo == 40) kn = 6;
					for (int k = 0; k < kn; k++) //0~9까지 계산
					{
						if (fArHigh[10 * i + k] > f1)	f1 = fArHigh[10 * i + k];			//max
						if (fArLow[10 * i + k] < f2)	f2 = fArLow[10 * i + k];			//min
					}
					fAr10mHigh[i] = f1;
					fAr10mLow[i] = f2;
					fAr10mOpen[i] = fArOpen[10 * i + 0];
					fAr10mClose[i] = fArClose[10 * i + kn - 1];
				}
				if (rem > 0) // 현재시간까지의 10분봉 계산
				{
					float f1 = fArHigh[10 * quo - 1], f2 = fArLow[10 * quo - 1];		//
					for (int k = 0; k < rem; ++k)
					{
						if (fArHigh[10 * quo + k] > f1)	f1 = fArHigh[10 * quo + k];			//max
						if (fArLow[10 * quo + k] < f2)	f2 = fArLow[10 * quo + k];			//min				
					}
					fAr10mHigh[quo] = f1;
					fAr10mLow[quo] = f2;
					fAr10mOpen[quo] = fArOpen[10 * quo + 0];
					fAr10mClose[quo] = fArClose[10 * quo + rem - 1];
				}
			}
			else // nCount <= 9
			{
				if (rem > 1)
				{
					float f1 = fArHigh[nCount - 1], f2 = fArLow[nCount - 1];		//
					for (int k = 0; k < rem; ++k)
					{
						if (fArHigh[k] > f1)	f1 = fArHigh[k];			//max
						if (fArLow[k] < f2)		f2 = fArLow[k];				//min				
					}
					fAr10mHigh[0] = f1;
					fAr10mLow[0] = f2;
					fAr10mOpen[0] = fArOpen[0];
					fAr10mClose[0] = fArClose[rem - 1];
				}
			}
		}
		else // nCount==411
		{
			if (nCount > 9) //10분봉 계산
			{
				for (int i = 0; i < quo; ++i) //
				{
					float f1 = 0.0, f2 = 500;//close max,min(50분동안)
					int kn = 10;
					if (quo == 40) kn = 6;
					for (int k = 0; k < kn; k++) //0~9까지 계산
					{
						if (fArHigh[10 * i + k] > f1)	f1 = fArHigh[10 * i + k];			//max
						if (fArLow[10 * i + k] < f2)	f2 = fArLow[10 * i + k];			//min
					}
					fAr10mHigh[i] = f1;
					fAr10mLow[i] = f2;
					fAr10mOpen[i] = fArOpen[10 * i + 0];
					fAr10mClose[i] = fArClose[10 * i + kn - 1];
				}
				if (rem > 0) // 현재시간까지의 10분봉 계산
				{
					float f1 = fArHigh[10 * quo - 1], f2 = fArLow[10 * quo - 1];		//
					for (int k = 0; k < rem; ++k)
					{
						if (fArHigh[10 * quo + k] > f1)	f1 = fArHigh[10 * quo + k];			//max
						if (fArLow[10 * quo + k] < f2)	f2 = fArLow[10 * quo + k];			//min				
					}
					fAr10mHigh[quo] = f1;
					fAr10mLow[quo] = f2;
					fAr10mOpen[quo] = fArOpen[10 * quo + 0];
					fAr10mClose[quo] = fArClose[10 * quo + rem - 1];
				}
			}
			else // nCount <= 9
			{
				if (rem > 1)
				{
					float f1 = fArHigh[nCount - 1], f2 = fArLow[nCount - 1];		//
					for (int k = 0; k < rem; ++k)
					{
						if (fArHigh[k] > f1)	f1 = fArHigh[k];			//max
						if (fArLow[k] < f2)		f2 = fArLow[k];				//min				
					}
					fAr10mHigh[0] = f1;
					fAr10mLow[0] = f2;
					fAr10mOpen[0] = fArOpen[0];
					fAr10mClose[0] = fArClose[rem - 1];
				}
			}

			float f1 = fArHigh[389], f2 = fArLow[389];		//
			for (int k = 0; k < 6; ++k)
			{
				if (fArHigh[405 + k] > f1)	f1 = fArHigh[405 + k];			//max
				if (fArLow[405 + k] < f2)	f2 = fArLow[405 + k];			//min				
			}
			fAr10mHigh[41] = f1;
			fAr10mLow[41] = f2;
			fAr10mOpen[41] = fArOpen[405];
			fAr10mClose[41] = fArClose[410];
		}

		if (quo >= 4)//10분봉(5,3,3), 10mK 계산
		{
			for (int i = 0; i <= quo; i++)
			{
				float f3 = fAr10mHigh[i], f4 = fAr10mLow[i];//close max,min(50분동안)
				if (i < 4)
				{
					int temp = i;
					while (temp > 0)
					{
						if (fAr10mHigh[temp - 1] > f3)	f3 = fAr10mHigh[temp - 1];			//max
						if (fAr10mLow[temp - 1] < f4)	f4 = fAr10mLow[temp - 1];			//min
						temp -= 1;
					}
					for (int k = 0; k < (4 - i); k++)
					{
						if (fAr10mHighY[41 - k] > f3)	f3 = fAr10mHighY[k];			//max
						if (fAr10mLowY[41 - k] < f4)	f4 = fAr10mLowY[k];				//min					
					}
				}
				else
				{
					for (int k = 0; k < 5; k++)
					{

						if (fAr10mHigh[i - k] > f3)	f3 = fAr10mHigh[i - k];			//max
						if (fAr10mLow[i - k] < f4)	f4 = fAr10mLow[i - k];			//min
					}
					if (f3 == f4)
						fAr10mK[i] = 100;											//fArPerK : %K(분모가 0인경우)
					else
						fAr10mK[i] = (fAr10mClose[i] - f4) / (f3 - f4) * 100;		//%K(5) = (Current Close - Lowest Low)/(Highest High - Lowest Low) - Basic calculation	
				}

				if (f3 == f4)
					fAr10mK[i] = 100;											//fArPerK : %K(분모가 0인경우)
				else
					fAr10mK[i] = (fAr10mClose[i] - f4) / (f3 - f4) * 100;		//%K(5) = (Current Close - Lowest Low)/(Highest High - Lowest Low) - Basic calculation		
			}

		}
		else // quo < 4 (ex quo=3)
		{
			for (int i = 0; i <= quo; i++)
			{
				float f3 = fAr10mHigh[i], f4 = fAr10mLow[i];//close max,min(50분동안)
				int temp = i;
				while (temp > 0)
				{
					if (fAr10mHigh[temp - 1] > f3)	f3 = fAr10mHigh[temp - 1];			//max
					if (fAr10mLow[temp - 1] < f4)	f4 = fAr10mLow[temp - 1];			//min
					temp -= 1;
				}
				for (int k = 0; k < (4 - i); k++)
				{
					if (fAr10mHighY[41 - k] > f3)	f3 = fAr10mHighY[k];			//max
					if (fAr10mLowY[41 - k] < f4)	f4 = fAr10mLowY[k];				//min					
				}
				if (f3 == f4)
					fAr10mK[i] = 100;											//fArPerK : %K(분모가 0인경우)
				else
					fAr10mK[i] = (fAr10mClose[i] - f4) / (f3 - f4) * 100;		//%K(5) = (Current Close - Lowest Low)/(Highest High - Lowest Low) - Basic calculation		
			}
		}

		if (quo >= 3)//10분봉, 10mD 계산
		{
			for (int i = 0; i <= quo; i++)
			{
				if (i < 3)
				{
					float f5 = fAr10mK[i];
					int temp = i;
					while (temp > 0)
					{
						f5 += fAr10mK[temp - 1];
						temp -= 1;
					}
					for (int k = 0; k < (2 - i); k++)
					{
						f5 += fAr10mKY[41 - k];
					}
					fAr10mD[i] = f5 / 3.0f;
				}
				else
				{
					float f5 = 0.0;
					for (int k = 0; k < 3; k++)
						f5 += fAr10mK[i - k];
					fAr10mD[i] = f5 / 3.0f;											//%D(3)= slow %K(3) ; 30분 SMA of %K
				}
			}
		}
		else
		{
			for (int i = 0; i <= quo; i++)
			{
				float f5 = fAr10mK[i];
				int temp = i;
				while (temp > 0)
				{
					f5 += fAr10mK[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (2 - i); k++)
				{
					f5 += fAr10mKY[41 - k];
				}
				fAr10mD[i] = f5 / 3.0f;
			}
		}

		if (quo >= 3) //10분봉, 10mSlowD
		{
			for (int i = 0; i <= quo; i++)
			{
				if (i < 3)
				{
					float f5 = fAr10mD[i];
					int temp = i;
					while (temp > 0)
					{
						f5 += fAr10mD[temp - 1];
						temp -= 1;
					}
					for (int k = 0; k < (2 - i); k++)
						f5 += fAr10mDY[41 - k];
					fAr10mSlowD[i] = f5 / 3.0f;
				}
				else
				{
					float f5 = 0.0;
					for (int k = 0; k < 3; k++)
						f5 += fAr10mD[i - k];
					fAr10mSlowD[i] = f5 / 3.0f;
				}
			}
			
		}
		else
		{
			for (int i = 0; i <= quo; i++)
			{
				float f5 = fAr10mD[i];
				int temp = i;
				while (temp > 0)
				{
					f5 += fAr10mD[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (2 - i); k++)
					f5 += fAr10mDY[41 - k];
				fAr10mSlowD[i] = f5 / 3.0f;
			}
		}

		// ******************************************************************************************** 10분봉의 Bolinger band(20sma)
		if (quo < 20)
		{
			for (int i = 0; i < quo; i++)
			{
				float f1 = fAr10mClose[i];
				int temp = i;
				while (temp > 0)
				{
					f1 += fAr10mClose[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (19 - i); k++)									// 20분 SMA 초기화
				{
					f1 += fAr10mCloseY[41 - k];
				}
				f1 = f1 / 20;
				fAr10m20mSMA[i] = f1;

				f1 = 0.0;
				float f2 = 0.0;
				temp = i;
				while (temp >= 0)
				{
					f1 = (fAr10mClose[temp] + fAr10mLow[temp] + fAr10mHigh[temp]) / 3 - fAr10m20mSMA[i];
					f2 += abs(f1 * f1);
					temp -= 1;
				}
				for (int k = 0; k < (19 - i); k++)									// 20분 SD (Bolinger bandwidth)
				{
					f1 = (fAr10mCloseY[41 - k] + fAr10mLowY[41 - k] + fAr10mHighY[41 - k]) / 3 - fAr10m20mSMA[i];
					f2 += abs(f1 * f1);
				}
				f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
				fAr10m20mSD[i] = f2;
			}

		}
		else // quo >= 20
		{
			for (int i = 0; i <= quo; i++)
			{
				if (i < 19)
				{
					float f1 = fAr10mClose[i];
					int temp = i;
					while (temp > 0)
					{
						f1 += fAr10mClose[temp - 1];
						temp -= 1;
					}
					for (int k = 0; k < (19 - i); k++)									// 20분 SMA 초기화
					{
						f1 += fAr10mCloseY[41 - k];
					}
					f1 = f1 / 20;
					fAr10m20mSMA[i] = f1;

					f1 = 0.0;
					float f2 = 0.0;
					temp = i;
					while (temp >= 0)
					{
						f1 = (fAr10mClose[temp] + fAr10mLow[temp] + fAr10mHigh[temp]) / 3 - fAr10m20mSMA[i];
						f2 += abs(f1 * f1);
						temp -= 1;
					}
					for (int k = 0; k < (19 - i); k++)									// 20분 SD (Bolinger bandwidth)
					{
						f1 = (fAr10mCloseY[41 - k] + fAr10mLowY[41 - k] + fAr10mHighY[41 - k]) / 3 - fAr10m20mSMA[i];
						f2 += abs(f1 * f1);
					}
					f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
					fAr10m20mSD[i] = f2;
				}
				else
				{
					float f1 = 0.0;
					for (int k = 0; k < 20; k++)										// 20분 SMA = Bolinger mid-band
					{
						f1 += fAr10mClose[i - k];
					}
					f1 = f1 / 20;
					fAr10m20mSMA[i] = f1;

					f1 = 0.0;
					float f2 = 0.0;
					for (int k = 0; k < 20; k++)										// 20분 SD (Bolinger bandwidth)
					{
						f1 = (fAr10mClose[i - k] + fAr10mLow[i - k] + fAr10mHigh[i - k]) / 3 - fAr10m20mSMA[i];
						f2 += abs(f1 * f1);
					}
					f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
					fAr10m20mSD[i] = f2;
				}

			}
		}

		// ****************************************************************************************************** 1분봉 Bolinger Band(20m)
		if (nCount < 20)
		{
			for (int i = 0; i < nCount; i++)
			{
				float f1 = fArClose[i];
				int temp = i;
				while (temp > 0)
				{
					f1 += fArClose[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (19 - i); k++)								// 20분 SMA 초기화
				{
					f1 += fArCloseY[410 - k];
				}
				f1 = f1 / 20;
				fAr20mSMA[i] = f1;

				f1 = 0.0;
				float f2 = 0.0;
				temp = i;
				while (temp >= 0)
				{
					f1 = fArClose[temp] - fAr20mSMA[i];
					f2 += abs(f1 * f1);
					temp -= 1;
				}
				for (int k = 0; k < (19 - i); k++)									// 20분 SD (Bolinger bandwidth)
				{
					f1 = fArCloseY[410 - k] - fAr20mSMA[i];
					f2 += abs(f1 * f1);
				}
				f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
				fAr20mSD[i] = f2;
			}


		}
		else
		{
			for (int i = 0; i < nCount; i++)
			{
				if (i < 19)
				{
					float f1 = fArClose[i];
					int temp = i;
					while (temp > 0)
					{
						f1 += fArClose[temp - 1];
						temp -= 1;
					}
					for (int k = 0; k < (19 - i); k++)								// 20분 SMA 초기화
					{
						f1 += fArCloseY[410 - k];
					}
					f1 = f1 / 20;
					fAr20mSMA[i] = f1;

					f1 = 0.0;
					float f2 = 0.0;
					temp = i;
					while (temp >= 0)
					{
						f1 = fArClose[temp] - fAr20mSMA[i];
						f2 += abs(f1 * f1);
						temp -= 1;
					}
					for (int k = 0; k < (19 - i); k++)									// 20분 SD (Bolinger bandwidth)
					{
						f1 = fArCloseY[410 - k] - fAr20mSMA[i];
						f2 += abs(f1 * f1);
					}
					f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
					fAr20mSD[i] = f2;
				}
				else
				{
					float f1 = 0.0;
					for (int k = 0; k < 20; k++)									// 20분 SMA = Bolinger mid-band
					{
						f1 += fArClose[i - k];
					}
					f1 = f1 / 20;
					fAr20mSMA[i] = f1;

					f1 = 0.0;
					float f2 = 0.0;
					for (int k = 0; k < 20; k++)									// 20분 SD (Bolinger bandwidth)
					{
						f1 = fArClose[i - k] - fAr20mSMA[i];
						f2 += abs(f1 * f1);
					}
					f2 = sqrt(f2 / 20.0f) * 2.0f;										// upper band = 20 SMA + SD*2
					fAr20mSD[i] = f2;
				}
			}

		}

		if (nCount > 28)
		{
			for (int i = 29; i < nCount; i++)
			{
				float f1 = 500.0, f2 = 100.0;
				int n1 = 0, n2 = 0;
				for (int k = 0; k < 30; k++)									// fArMax30m, fArMin30m PointA
				{
					if (fArClose[i - k] < f1)
					{
						f1 = fArClose[i - k];
						n1 = i - k + 1;
					}
					if (fArClose[i - k] > f2)
					{
						f2 = fArClose[i - k];
						n2 = i - k + 1;
					}
				}
				fArMin30m[i] = f1; nArMin30m[i] = n1;
				fArMax30m[i] = f2; nArMax30m[i] = n2;
			}
		}

		if (nCount > 58)
		{

			for (int i = 59; i < nCount; i++)
			{
				float f2 = 500.0, f3 = 100.0;
				for (int k = 0; k < 60; k++)									// fArMax60m, fArMin60m
				{
					if (fArLow[i - k] < f2)
						f2 = fArLow[i - k];
					if (fArHigh[i - k] > f3)
						f3 = fArHigh[i - k];
				}
				fArMin60m[i] = f2;
				fArMax60m[i] = f3;
			}
		}

		if (nCount < 60)
		{
			for (int i = 0; i < nCount; i++)
			{
				float f1 = fArClose[i];
				int temp = i;
				while (temp > 0)
				{
					f1 += fArClose[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (59 - i); k++)									// 60분 SMA 초기화
				{
					f1 += fArCloseY[410 - k];
				}
				f1 = f1 / 60;
				fAr60mSMA[i] = f1;
			}
		}
		else
		{
			for (int i = 0; i < nCount; i++)
			{
				if (i < 59)
				{
					float f1 = fArClose[i];
					int temp = i;
					while (temp > 0)
					{
						f1 += fArClose[temp - 1];
						temp -= 1;
					}
					for (int k = 0; k < (59 - i); k++)									// 60분 SMA 초기화
					{
						f1 += fArCloseY[410 - k];
					}
					f1 = f1 / 60;
					fAr60mSMA[i] = f1;
				}
				else
				{
					float f1 = 0.0;
					for (int k = 0; k < 60; k++)									// 60분 SMA = Bolinger mid-band
					{
						f1 += fArClose[i - k];
					}
					f1 = f1 / 60;
					fAr60mSMA[i] = f1;
				}

			}

		}

		if (shcode == FutureCode)
		{
			ofstream myfile8415("test8415.csv");								// 선물,옵션차트 저장(1분봉)
			if (myfile8415.is_open())
			{

				myfile8415 << "시간, 시가, 종가, 거래량, Width, 20mSMA, 20mSD, 60mSMA\n";
				for (int i = 0; i < nCount; i++)
				{

					myfile8415 << strArTime8415[i] << ", " << fArOpen[i] << ", " << fArClose[i] << ", " << lArVol[i] << ", "
						<< fArWidth[i] << ", " << fAr20mSMA[i] << ", " << fAr20mSD[i] << ", " << fAr60mSMA[i] << "\n";
				}

			}
			myfile8415.close();
		}
		else if (shcode == CallCode[0])
		{
			ofstream myfile8415("test8415_call.csv");								// 선물,옵션차트 저장(1분봉)
			if (myfile8415.is_open())
			{

				myfile8415 << "시간, 시가, 종가, 거래량, Width, 20mSMA, 20mSD, 60mSMA\n";
				for (int i = 0; i < nCount; i++)
				{

					myfile8415 << strArTime8415[i] << ", " << fArOpen[i] << ", " << fArClose[i] << ", " << lArVol[i] << ", "
						<< fArWidth[i] << ", " << fAr20mSMA[i] << ", " << fAr20mSD[i] << ", " << fAr60mSMA[i] << "\n";
				}

			}
			myfile8415.close();
		}
		else if (shcode == PutCode[0])
		{
			ofstream myfile8415("test8415_put.csv");								// 선물,옵션차트 저장(1분봉)
			if (myfile8415.is_open())
			{

				myfile8415 << "시간, 시가, 종가, 거래량, Width, 20mSMA, 20mSD, 60mSMA\n";
				for (int i = 0; i < nCount; i++)
				{

					myfile8415 << strArTime8415[i] << ", " << fArOpen[i] << ", " << fArClose[i] << ", " << lArVol[i] << ", "
						<< fArWidth[i] << ", " << fAr20mSMA[i] << ", " << fAr20mSD[i] << ", " << fAr60mSMA[i] << "\n";
				}

			}
			myfile8415.close();
		}
	}

	return;
}


void CDlg_JEKYLL::Receive84152(LPRECV_PACKET pRpData) //옵션차트(n분) header A type (콜)
{
	if (strcmp(pRpData->szBlockName, NAME_t8415OutBlock1) == 0)
	{
		LPt8415OutBlock1 pOutBlock1 = (LPt8415OutBlock1)pRpData->lpData;
		int				 nCount = pRpData->nDataLength / sizeof(t8415OutBlock1);		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.


		for (int i = 0; i < nCount; i++)
		{
			CString s1, s2;
			s1 = GetDispData(pOutBlock1[i].time, sizeof(pOutBlock1[i].time), DATA_TYPE_STRING); strArTime8415[i] = s1;			//시간
			s2 = GetDispData(pOutBlock1[i].close, sizeof(pOutBlock1[i].close), DATA_TYPE_FLOAT, 2); fArCClose[i] = (float)atof(s2);		//종가
		}
	}

	return;
}


void CDlg_JEKYLL::Receive84153(LPRECV_PACKET pRpData) //옵션차트(n분) header A type (풋)
{
	if (strcmp(pRpData->szBlockName, NAME_t8415OutBlock1) == 0)
	{
		LPt8415OutBlock1 pOutBlock1 = (LPt8415OutBlock1)pRpData->lpData;
		int				 nCount = pRpData->nDataLength / sizeof(t8415OutBlock1);		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.


		for (int i = 0; i < nCount; i++)
		{
			CString s1, s2;
			s1 = GetDispData(pOutBlock1[i].time, sizeof(pOutBlock1[i].time), DATA_TYPE_STRING); strArTime8415[i] = s1;			//시간
			s2 = GetDispData(pOutBlock1[i].close, sizeof(pOutBlock1[i].close), DATA_TYPE_FLOAT, 2); fArPClose[i] = (float)atof(s2);		//종가
		}
	}

	return;
}

void CDlg_JEKYLL::Receive8415(int nCount) //선물옵션차트(n분) header A type : 조회에러시
{
	if (nCount > 410 && nCount < 415) return;
	if (nCount >= 415) nCount = 411;
	fArWidth[nCount - 1] = fArClose[nCount - 1] - fArOpen[nCount - 1];							//Width price(close-open)

	float fHigh = fArClose[0], fLow = fArClose[0], fRef = 0.5; //Reference(0.5) 이상 벌어진 경우, 최고,최저 경신 기록
	int nUpdateHigh = 0, nUpdateLow = 0;
	fHighest = 500, fLowest = 0;
	for (int i = 0; i < nCount; i++)
	{
		if (fHighest == 500 || fLowest == 0)
		{
			if (fArClose[i] > fHigh) fHigh = fArClose[i];
			if (fArClose[i] < fLow) fLow = fArClose[i];
			if (fHigh - fLow > fRef)
			{
				fHighest = fHigh;
				fLowest = fLow;
			}
		}
		else
		{
			if (fArClose[i] > fHighest)
			{
				fHighest = fArClose[i];
				nUpdateHigh++;
			}
			if (fArClose[i] < fLowest)
			{
				fLowest = fArClose[i];
				nUpdateLow++;
			}
		}
		nArUpdateHigh[i] = nUpdateHigh;
		nArUpdateLow[i] = nUpdateLow;

		lArVol2[i] = lArVol[i];
		if ((fArWidth[i] < 0) || (fArWidth[i] == 0 && fArHigh[i] - fArClose[i] > fArClose[i] - fArLow[i])) lArVol2[i] *= -1;
		if (fArWidth[i] == 0 && fArHigh[i] - fArClose[i] == fArClose[i] - fArLow[i]) lArVol2[i] *= 0;

	}

	// ************************************************************************************************* 10분봉 High/Low/Open/Close
	int quo = nCount / 10, rem = nCount % 10; //현재시간 위치를 결정
	if (nCount < 410)
	{
		if (nCount > 9) //10분봉 계산
		{
			for (int i = 0; i < quo; ++i) //
			{
				float f1 = 0.0, f2 = 500;//close max,min(50분동안)
				int kn = 10;
				if (quo == 40) kn = 6;
				for (int k = 0; k < kn; k++) //0~9까지 계산
				{
					if (fArHigh[10 * i + k] > f1)	f1 = fArHigh[10 * i + k];			//max
					if (fArLow[10 * i + k] < f2)	f2 = fArLow[10 * i + k];			//min
				}
				fAr10mHigh[i] = f1;
				fAr10mLow[i] = f2;
				fAr10mOpen[i] = fArOpen[10 * i + 0];
				fAr10mClose[i] = fArClose[10 * i + kn - 1];
			}
			if (rem > 0) // 현재시간까지의 10분봉 계산
			{
				float f1 = fArHigh[10 * quo - 1], f2 = fArLow[10 * quo - 1];		//
				for (int k = 0; k < rem; ++k)
				{
					if (fArHigh[10 * quo + k] > f1)	f1 = fArHigh[10 * quo + k];			//max
					if (fArLow[10 * quo + k] < f2)	f2 = fArLow[10 * quo + k];			//min				
				}
				fAr10mHigh[quo] = f1;
				fAr10mLow[quo] = f2;
				fAr10mOpen[quo] = fArOpen[10 * quo + 0];
				fAr10mClose[quo] = fArClose[10 * quo + rem - 1];
			}
		}
		else // nCount <= 9
		{
			if (rem > 1)
			{
				float f1 = fArHigh[nCount - 1], f2 = fArLow[nCount - 1];		//
				for (int k = 0; k < rem; ++k)
				{
					if (fArHigh[k] > f1)	f1 = fArHigh[k];			//max
					if (fArLow[k] < f2)		f2 = fArLow[k];				//min				
				}
				fAr10mHigh[0] = f1;
				fAr10mLow[0] = f2;
				fAr10mOpen[0] = fArOpen[0];
				fAr10mClose[0] = fArClose[rem - 1];
			}
		}
	}
	else // nCount==411
	{
		if (nCount > 9) //10분봉 계산
		{
			for (int i = 0; i < quo; ++i) //
			{
				float f1 = 0.0, f2 = 500;//close max,min(50분동안)
				int kn = 10;
				if (quo == 40) kn = 6;
				for (int k = 0; k < kn; k++) //0~9까지 계산
				{
					if (fArHigh[10 * i + k] > f1)	f1 = fArHigh[10 * i + k];			//max
					if (fArLow[10 * i + k] < f2)	f2 = fArLow[10 * i + k];			//min
				}
				fAr10mHigh[i] = f1;
				fAr10mLow[i] = f2;
				fAr10mOpen[i] = fArOpen[10 * i + 0];
				fAr10mClose[i] = fArClose[10 * i + kn - 1];
			}
			if (rem > 0) // 현재시간까지의 10분봉 계산
			{
				float f1 = fArHigh[10 * quo - 1], f2 = fArLow[10 * quo - 1];		//
				for (int k = 0; k < rem; ++k)
				{
					if (fArHigh[10 * quo + k] > f1)	f1 = fArHigh[10 * quo + k];			//max
					if (fArLow[10 * quo + k] < f2)	f2 = fArLow[10 * quo + k];			//min				
				}
				fAr10mHigh[quo] = f1;
				fAr10mLow[quo] = f2;
				fAr10mOpen[quo] = fArOpen[10 * quo + 0];
				fAr10mClose[quo] = fArClose[10 * quo + rem - 1];
			}
		}
		else // nCount <= 9
		{
			if (rem > 1)
			{
				float f1 = fArHigh[nCount - 1], f2 = fArLow[nCount - 1];		//
				for (int k = 0; k < rem; ++k)
				{
					if (fArHigh[k] > f1)	f1 = fArHigh[k];			//max
					if (fArLow[k] < f2)		f2 = fArLow[k];				//min				
				}
				fAr10mHigh[0] = f1;
				fAr10mLow[0] = f2;
				fAr10mOpen[0] = fArOpen[0];
				fAr10mClose[0] = fArClose[rem - 1];
			}
		}

		float f1 = fArHigh[389], f2 = fArLow[389];		//
		for (int k = 0; k < 6; ++k)
		{
			if (fArHigh[405 + k] > f1)	f1 = fArHigh[405 + k];			//max
			if (fArLow[405 + k] < f2)	f2 = fArLow[405 + k];			//min				
		}
		fAr10mHigh[41] = f1;
		fAr10mLow[41] = f2;
		fAr10mOpen[41] = fArOpen[405];
		fAr10mClose[41] = fArClose[410];
	}

	if (quo >= 4)//10분봉(5,3,3), 10mK 계산
	{
		for (int i = 0; i <= quo; i++)
		{
			float f3 = fAr10mHigh[i], f4 = fAr10mLow[i];//close max,min(50분동안)
			if (i < 4)
			{
				int temp = i;
				while (temp > 0)
				{
					if (fAr10mHigh[temp - 1] > f3)	f3 = fAr10mHigh[temp - 1];			//max
					if (fAr10mLow[temp - 1] < f4)	f4 = fAr10mLow[temp - 1];			//min
					temp -= 1;
				}
				for (int k = 0; k < (4 - i); k++)
				{
					if (fAr10mHighY[41 - k] > f3)	f3 = fAr10mHighY[k];			//max
					if (fAr10mLowY[41 - k] < f4)	f4 = fAr10mLowY[k];				//min					
				}
			}
			else
			{
				for (int k = 0; k < 5; k++)
				{

					if (fAr10mHigh[i - k] > f3)	f3 = fAr10mHigh[i - k];			//max
					if (fAr10mLow[i - k] < f4)	f4 = fAr10mLow[i - k];			//min
				}
				if (f3 == f4)
					fAr10mK[i] = 100;											//fArPerK : %K(분모가 0인경우)
				else
					fAr10mK[i] = (fAr10mClose[i] - f4) / (f3 - f4) * 100;		//%K(5) = (Current Close - Lowest Low)/(Highest High - Lowest Low) - Basic calculation	
			}

			if (f3 == f4)
				fAr10mK[i] = 100;											//fArPerK : %K(분모가 0인경우)
			else
				fAr10mK[i] = (fAr10mClose[i] - f4) / (f3 - f4) * 100;		//%K(5) = (Current Close - Lowest Low)/(Highest High - Lowest Low) - Basic calculation		
		}

	}
	else // quo < 4 (ex quo=3)
	{
		for (int i = 0; i <= quo; i++)
		{
			float f3 = fAr10mHigh[i], f4 = fAr10mLow[i];//close max,min(50분동안)
			int temp = i;
			while (temp > 0)
			{
				if (fAr10mHigh[temp - 1] > f3)	f3 = fAr10mHigh[temp - 1];			//max
				if (fAr10mLow[temp - 1] < f4)	f4 = fAr10mLow[temp - 1];			//min
				temp -= 1;
			}
			for (int k = 0; k < (4 - i); k++)
			{
				if (fAr10mHighY[41 - k] > f3)	f3 = fAr10mHighY[k];			//max
				if (fAr10mLowY[41 - k] < f4)	f4 = fAr10mLowY[k];				//min					
			}
			if (f3 == f4)
				fAr10mK[i] = 100;											//fArPerK : %K(분모가 0인경우)
			else
				fAr10mK[i] = (fAr10mClose[i] - f4) / (f3 - f4) * 100;		//%K(5) = (Current Close - Lowest Low)/(Highest High - Lowest Low) - Basic calculation		
		}
	}

	if (quo >= 3)//10분봉, 10mD 계산
	{
		for (int i = 0; i <= quo; i++)
		{
			if (i < 3)
			{
				float f5 = fAr10mK[i];
				int temp = i;
				while (temp > 0)
				{
					f5 += fAr10mK[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (2 - i); k++)
				{
					f5 += fAr10mKY[41 - k];
				}
				fAr10mD[i] = f5 / 3.0f;
			}
			else
			{
				float f5 = 0.0;
				for (int k = 0; k < 3; k++)
					f5 += fAr10mK[i - k];
				fAr10mD[i] = f5 / 3.0f;											//%D(3)= slow %K(3) ; 30분 SMA of %K ------------------------- SMA:단순이동평균 or EMA(지수이동평균)
			}
		}
	}
	else
	{
		for (int i = 0; i <= quo; i++)
		{
			float f5 = fAr10mK[i];
			int temp = i;
			while (temp > 0)
			{
				f5 += fAr10mK[temp - 1];
				temp -= 1;
			}
			for (int k = 0; k < (2 - i); k++)
			{
				f5 += fAr10mKY[41 - k];
			}
			fAr10mD[i] = f5 / 3.0f;
		}
	}

	if (quo >= 3) //10분봉, 10mSlowD
	{
		for (int i = 0; i <= quo; i++)
		{
			if (i < 3)
			{
				float f5 = fAr10mD[i];
				int temp = i;
				while (temp > 0)
				{
					f5 += fAr10mD[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (2 - i); k++)
					f5 += fAr10mDY[41 - k];
				fAr10mSlowD[i] = f5 / 3.0f;
			}
			else
			{
				float f5 = 0.0;
				for (int k = 0; k < 3; k++)
					f5 += fAr10mD[i - k];
				fAr10mSlowD[i] = f5 / 3.0f;
			}
		}		
	}
	else
	{
		for (int i = 0; i <= quo; i++)
		{
			float f5 = fAr10mD[i];
			int temp = i;
			while (temp > 0)
			{
				f5 += fAr10mD[temp - 1];
				temp -= 1;
			}
			for (int k = 0; k < (2 - i); k++)
				f5 += fAr10mDY[41 - k];
			fAr10mSlowD[i] = f5 / 3.0f;
		}
	}

	// ******************************************************************************************** 10분봉의 Bolinger band(20sma)
	if (quo < 20)
	{
		for (int i = 0; i < quo; i++)
		{
			float f1 = fAr10mClose[i];
			int temp = i;
			while (temp > 0)
			{
				f1 += fAr10mClose[temp - 1];
				temp -= 1;
			}
			for (int k = 0; k < (19 - i); k++)									// 20분 SMA 초기화
			{
				f1 += fAr10mCloseY[41 - k];
			}
			f1 = f1 / 20;
			fAr10m20mSMA[i] = f1;

			f1 = 0.0;
			float f2 = 0.0;
			temp = i;
			while (temp >= 0)
			{
				f1 = (fAr10mClose[temp] + fAr10mLow[temp] + fAr10mHigh[temp]) / 3 - fAr10m20mSMA[i];
				f2 += abs(f1 * f1);
				temp -= 1;
			}
			for (int k = 0; k < (19 - i); k++)									// 20분 SD (Bolinger bandwidth)
			{
				f1 = (fAr10mCloseY[41 - k] + fAr10mLowY[41 - k] + fAr10mHighY[41 - k]) / 3 - fAr10m20mSMA[i];
				f2 += abs(f1 * f1);
			}
			f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
			fAr10m20mSD[i] = f2;
		}

	}
	else
	{
		for (int i = 0; i <= quo; i++)
		{
			if (i < 19)
			{
				float f1 = fAr10mClose[i];
				int temp = i;
				while (temp > 0)
				{
					f1 += fAr10mClose[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (19 - i); k++)									// 20분 SMA 초기화
				{
					f1 += fAr10mCloseY[41 - k];
				}
				f1 = f1 / 20;
				fAr10m20mSMA[i] = f1;

				f1 = 0.0;
				float f2 = 0.0;
				temp = i;
				while (temp >= 0)
				{
					f1 = (fAr10mClose[temp] + fAr10mLow[temp] + fAr10mHigh[temp]) / 3 - fAr10m20mSMA[i];
					f2 += abs(f1 * f1);
					temp -= 1;
				}
				for (int k = 0; k < (19 - i); k++)									// 20분 SD (Bolinger bandwidth)
				{
					f1 = (fAr10mCloseY[41 - k] + fAr10mLowY[41 - k] + fAr10mHighY[41 - k]) / 3 - fAr10m20mSMA[i];
					f2 += abs(f1 * f1);
				}
				f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
				fAr10m20mSD[i] = f2;
			}
			else
			{
				float f1 = 0.0;
				for (int k = 0; k < 20; k++)									// 20분 SMA = Bolinger mid-band
				{
					f1 += fAr10mClose[i - k];
				}
				f1 = f1 / 20;
				fAr10m20mSMA[i] = f1;

				f1 = 0.0;
				float f2 = 0.0;
				for (int k = 0; k < 20; k++)									// 20분 SD (Bolinger bandwidth)
				{
					f1 = (fAr10mClose[i - k] + fAr10mLow[i - k] + fAr10mHigh[i - k]) / 3 - fAr10m20mSMA[i];
					f2 += abs(f1 * f1);
				}
				f2 = sqrt(f2 / 20.0f) * 2.0f;										// upper band = 20 SMA + SD*2
				fAr10m20mSD[i] = f2;
			}

		}
	}


	// ****************************************************************************************************** 1분봉 Bolinger Band(20m)
	if (nCount < 20)
	{
		for (int i = 0; i < nCount; i++)
		{
			float f1 = fArClose[i];
			int temp = i;
			while (temp > 0)
			{
				f1 += fArClose[temp - 1];
				temp -= 1;
			}
			for (int k = 0; k < (19 - i); k++)								// 20분 SMA 초기화
			{
				f1 += fArCloseY[410 - k];
			}
			f1 = f1 / 20;
			fAr20mSMA[i] = f1;

			f1 = 0.0;
			float f2 = 0.0;
			temp = i;
			while (temp >= 0)
			{
				f1 = fArClose[temp] - fAr20mSMA[i];
				f2 += abs(f1 * f1);
				temp -= 1;
			}
			for (int k = 0; k < (19 - i); k++)									// 20분 SD (Bolinger bandwidth)
			{
				f1 = fArCloseY[410 - k] - fAr20mSMA[i];
				f2 += abs(f1 * f1);
			}
			f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
			fAr20mSD[i] = f2;
		}


	}
	else
	{
		for (int i = 0; i < nCount; i++)
		{
			if (i < 19)
			{
				float f1 = fArClose[i];
				int temp = i;
				while (temp > 0)
				{
					f1 += fArClose[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (19 - i); k++)								// 20분 SMA 초기화
				{
					f1 += fArCloseY[410 - k];
				}
				f1 = f1 / 20;
				fAr20mSMA[i] = f1;

				f1 = 0.0;
				float f2 = 0.0;
				temp = i;
				while (temp >= 0)
				{
					f1 = fArClose[temp] - fAr20mSMA[i];
					f2 += abs(f1 * f1);
					temp -= 1;
				}
				for (int k = 0; k < (19 - i); k++)									// 20분 SD (Bolinger bandwidth)
				{
					f1 = fArCloseY[410 - k] - fAr20mSMA[i];
					f2 += abs(f1 * f1);
				}
				f2 = sqrt(f2 / 20.0f) * 2.0f;											// upper band = 20 SMA + SD*2
				fAr20mSD[i] = f2;
			}
			else
			{
				float f1 = 0.0;
				for (int k = 0; k < 20; k++)									// 20분 SMA = Bolinger mid-band
				{
					f1 += fArClose[i - k];
				}
				f1 = f1 / 20;
				fAr20mSMA[i] = f1;

				f1 = 0.0;
				float f2 = 0.0;
				for (int k = 0; k < 20; k++)									// 20분 SD (Bolinger bandwidth)
				{
					f1 = fArClose[i - k] - fAr20mSMA[i];
					f2 += abs(f1 * f1);
				}
				f2 = sqrt(f2 / 20.0f) * 2.0f;										// upper band = 20 SMA + SD*2
				fAr20mSD[i] = f2;
			}
		}

	}

	if (nCount > 28)
	{
		for (int i = 29; i < nCount; i++)
		{
			float f1 = 500.0, f2 = 100.0;
			int n1 = 0, n2 = 0;
			for (int k = 0; k < 30; k++)									// fArMax30m, fArMin30m PointA
			{
				if (fArClose[i - k] < f1)
				{
					f1 = fArClose[i - k];
					n1 = i - k + 1;
				}
				if (fArClose[i - k] > f2)
				{
					f2 = fArClose[i - k];
					n2 = i - k + 1;
				}
			}
			fArMin30m[i] = f1; nArMin30m[i] = n1;
			fArMax30m[i] = f2; nArMax30m[i] = n2;
		}
	}

	if (nCount > 58)
	{

		for (int i = 59; i < nCount; i++)
		{
			float f2 = 500.0, f3 = 100.0;
			for (int k = 0; k < 60; k++)									// 60분 max, min
			{
				if (fArLow[i - k] < f2)
					f2 = fArLow[i - k];
				if (fArHigh[i - k] > f3)
					f3 = fArHigh[i - k];
			}
			fArMin60m[i] = f2;
			fArMax60m[i] = f3;
		}
	}

	if (nCount < 60)
	{
		for (int i = 0; i < nCount; i++)
		{
			float f1 = fArClose[i];
			int temp = i;
			while (temp > 0)
			{
				f1 += fArClose[temp - 1];
				temp -= 1;
			}
			for (int k = 0; k < (59 - i); k++)									// 60분 SMA 초기화
			{
				f1 += fArCloseY[410 - k];
			}
			f1 = f1 / 60;
			fAr60mSMA[i] = f1;
		}
	}
	else
	{
		for (int i = 0; i < nCount; i++)
		{
			if (i < 59)
			{
				float f1 = fArClose[i];
				int temp = i;
				while (temp > 0)
				{
					f1 += fArClose[temp - 1];
					temp -= 1;
				}
				for (int k = 0; k < (59 - i); k++)									// 60분 SMA 초기화
				{
					f1 += fArCloseY[410 - k];
				}
				f1 = f1 / 60;
				fAr60mSMA[i] = f1;
			}
			else
			{
				float f1 = 0.0;
				for (int k = 0; k < 60; k++)									// 60분 SMA = Bolinger mid-band
				{
					f1 += fArClose[i - k];
				}
				f1 = f1 / 60;
				fAr60mSMA[i] = f1;
			}

		}

	}

	ofstream myfile8415("test8415.csv");								// 선물,옵션차트 저장(1분봉)
	if (myfile8415.is_open())
	{

		myfile8415 << "시간, 시가, 종가, 거래량, Width, 20mSMA, 20mSD, 60mSMA\n";
		for (int i = 0; i < nCount; i++)
		{

			myfile8415 << strArTime8415[i] << ", " << fArOpen[i] << ", " << fArClose[i] << ", " << lArVol[i] << ", "
				<< fArWidth[i] << ", " << fAr20mSMA[i] << ", " << fAr20mSD[i] << ", " << fAr60mSMA[i] << "\n";
		}
	}
	myfile8415.close();

	return;
}

void CDlg_JEKYLL::Receive3103(LPRECV_PACKET pRpData) //해외선물(S&P)차트(n분) header A type : 현재외 20개 추가 요청(거꾸로 들어옴)
{
	if (strcmp(pRpData->szBlockName, NAME_o3103OutBlock1) == 0)
	{
		LPo3103OutBlock1 pOutBlock = (LPo3103OutBlock1)pRpData->lpData;
		int				 nCount = pRpData->nDataLength / sizeof(o3103OutBlock1);		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.

		for (int i = 0; i < nCount; i++)
		{
			fArSNPClose[nCount - 1 - i] = (float)atof(GetDispData(pOutBlock[i].close, sizeof(pOutBlock[i].close), DATA_TYPE_DOT, 9));		//종가
			fArSNPHigh[nCount - 1 - i] = (float)atof(GetDispData(pOutBlock[i].high, sizeof(pOutBlock[i].high), DATA_TYPE_DOT, 9));			//고가
			fArSNPLow[nCount - 1 - i] = (float)atof(GetDispData(pOutBlock[i].low, sizeof(pOutBlock[i].low), DATA_TYPE_DOT, 9));			//저가
		}

		// ************************************************************************************************* %K, %D, %slowD		
		int quo = nCurMin / 10;
		for (int i = 0; i < quo + 7; i++) //%K[19] 9시 이전, %K[20] : 9:00:00~9:09:59
		{
			float f3 = fArSNPHigh[i + 13], f4 = fArSNPLow[i + 13];//close max,min(50분동안)
			for (int k = 0; k < 5; k++)
			{
				if (fArSNPHigh[i + 13 - k] > f3)	f3 = fArSNPHigh[i + 13 - k];		//max
				if (fArSNPLow[i + 13 - k] < f4)	f4 = fArSNPLow[i + 13 - k];				//min
			}
			if (f3 == f4)
				fArSNPK[i + 13] = 100;													//fArPerK : %K(분모가 0인경우)
			else
				fArSNPK[i + 13] = (fArSNPClose[i + 13] - f4) / (f3 - f4) * 100;			//%K(5) = (Current Close - Lowest Low)/(Highest High - Lowest Low) - Basic calculation	
		}

		for (int i = 2; i < quo + 7; i++)
		{

			float f5 = 0.0;
			for (int k = 0; k < 3; k++)
				f5 += fArSNPK[i + 13 - k];
			fArSNPD[i + 13] = f5 / 3.0f;													//%D(3)= slow %K(3) ; 30분 SMA of %K

			if (i > 3)
			{
				f5 = 0.0;
				for (int k = 0; k < 3; k++)
					f5 += fArSNPD[i + 13 - k];
				fArSNPSlowD[i + 13] = f5 / 3.0f;
			}
		}

		// ****************************************************************************************************** Bolinger Band(20m)

		for (int i = 0; i < quo + 1; i++)
		{
			float f1 = 0.0;;
			for (int k = 0; k < 20; k++)									// 20분 SMA 초기화
			{
				f1 += fArSNPClose[i + 19 - k];
			}
			f1 = f1 / 20;
			fArSNP20mSMA[i + 19] = f1;

			float f2 = 0.0;
			for (int k = 0; k < 20; k++)									// 20분 SD (Bolinger bandwidth)
			{
				f1 = fArSNPClose[i + 19 - k] - fArSNP20mSMA[i + 19];
				f2 += abs(f1 * f1);
			}
			f2 = sqrt(f2 / 20.0f) * 2.0f;										// upper band = 20 SMA + SD*2
			fArSNP20mSD[i + 19] = f2;
		}

		ofstream myfile3103("test3103.csv");								// 선물,옵션차트 저장(1분봉)
		if (myfile3103.is_open())
		{

			myfile3103 << "시간, 고가, 저가, 종가, %K, %D, %slowD, 20mSMA, width\n";
			for (int i = 0; i < quo; i++)
			{

				myfile3103 << strArTime8415[(i + 1) * 10 - 1] << ", " << fArSNPHigh[i + 19] << ", " << fArSNPLow[i + 19] << ", " << fArSNPClose[i + 19] << ", "
					<< fArSNPK[i + 19] << ", " << fArSNPD[i + 19] << ", " << fArSNPSlowD[i + 19] << ", " << fArSNP20mSMA[i + 19] << ", " << fArSNP20mSD[i + 19] << "\n";
			}

		}
		myfile3103.close();
	}

	return;
}

//--------------------------------------------------------------------------------------
// Timeout 발생
//--------------------------------------------------------------------------------------
LRESULT CDlg_JEKYLL::OnXMTimeoutData(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);
	return 0L;
}

void CDlg_JEKYLL::Combine_8415_1602()
{
	// TODO: Add your control notification handler code here

	//str = m_lst2105.GetItemText(1, 1);		m_callprc.SetWindowText(str);	float fCallPrice = (float)atof(str);			// 현재가(콜)	
	//str = m_lst2105_.GetItemText(1, 1);		m_putprc.SetWindowText(str);	float fPutPrice = (float)atof(str);			// 현재가(풋)	

	if (nCurMin >= 411) nCurMin = 411; //
	//----------------------------------------------------------------------------------------------------------------------- 전고점, 전저점 설정하기, 저항선(ResistanceLine, SupportLine)
	float fHigh = fArClose[0], fLow = fArClose[0], fHighest = 500, fLowest = 0, fRef = 0.5, ratio = 0.5;// 0.5 이상 벌어질때부터 하이 로를 계산함, 매수포인트 35% 설정
	int nUpdateLow = 0, nUpdateHigh = 0;
	CString strFilePath = strDate + ".csv";

	ofstream myfileCombine(strFilePath);
	if (myfileCombine.is_open())
	{
		myfileCombine << "시간, 시가, 종가, 고가, 저가,  Width, 20mSMA, 20mSD, 60mSMA, "
			<< "UpdateHigh, UpdateLow, Min30m, Time, Max30m, Time, 외인, 기관, 외인5m, 기관5m, 거래량, 거래량(부호),ResQty, 콜(종가), 풋(종가) ,외인(ko), 기관(ko), 외인(ko)5m, 기관(ko)5m\n";
		for (int i = 0; i < nCurMin; i++)
		{
			if (fHighest == 500 || fLowest == 0)
			{
				if (fArClose[i] > fHigh) fHigh = fArClose[i];
				if (fArClose[i] < fLow) fLow = fArClose[i];
				if (fHigh - fLow > fRef)
				{
					fHighest = fHigh;
					fLowest = fLow;
				}
			}
			else
			{
				if (fArClose[i] > fHighest)
				{
					fHighest = fArClose[i];
					nUpdateHigh++;
				}
				if (fArClose[i] < fLowest)
				{
					fLowest = fArClose[i];
					nUpdateLow++;
				}
				nArUpdateHigh[i] = nUpdateHigh;
				nArUpdateLow[i] = nUpdateLow;

				lArVol2[i] = lArVol[i];
				if ((fArWidth[i] < 0) || (fArWidth[i] == 0 && fArHigh[i] - fArClose[i] > fArClose[i] - fArLow[i])) lArVol2[i] *= -1;
				if (fArWidth[i] == 0 && fArHigh[i] - fArClose[i] == fArClose[i] - fArLow[i]) lArVol2[i] *= 0;

			}

			myfileCombine << strArTime8415[i] << ", " << fArOpen[i] << ", " << fArClose[i] << ", " << fArHigh[i] << ", " << fArLow[i] << ", "
				<< fArWidth[i] << ", " << fAr20mSMA[i] << ", " << fAr20mSD[i] << ", " << fAr60mSMA[i] << ", "
				<< nArUpdateHigh[i] << ", " << nArUpdateLow[i] << ", "
				<< fArMin30m[i] << ", " << nArMin30m[i] << ", " << fArMax30m[i] << ", " << nArMax30m[i] << ", "
				<< lArForVol2[i] << ", " << lArSecVol2[i] << ", " << lArForVol5m[i] << ", " << lArSecVol5m[i] << ", " << lArVol[i] << ", " << lArVol2[i] << ", " << lArRemClose[i] << ", "
				<< fArCClose[i] << ", " << fArPClose[i] << ", " <<  lArKoForVol2[i] << ", " << lArKoSecVol2[i] << ", " << lArKoForVol5m[i] << ", " << lArKoSecVol5m[i];


			myfileCombine << "\n";
		}
	}
	myfileCombine.close();

	CString name = strDate + "_10m.csv";

	ofstream myfileCombine2(name); //시간, High, Low, Close, %K, %D, %slowD, 20mSMA, 20mSD
	if (myfileCombine2.is_open())
	{
		int quo = nCurMin / 10;
		if (nCurMin > 410) quo = 40;
		for (int i = 0; i < quo; i++)
		{
			if (i < 41)
			{
				myfileCombine2 << strArTime8415[(i + 1) * 10 - 1] << ", " << fAr10mHigh[i] << ", " << fAr10mLow[i] << ", " << fAr10mClose[i] << ", "
					<< fAr10mK[i] << ", " << fAr10mD[i] << ", " << fAr10mSlowD[i] << ", "
					<< fAr10m20mSMA[i] << ", " << fAr10m20mSD[i] << "\n";
			}
			else
			{
				myfileCombine2 << strArTime8415[410] << ", " << fAr10mHigh[i] << ", " << fAr10mLow[i] << ", " << fAr10mClose[i] << ", "
					<< fAr10mK[i] << ", " << fAr10mD[i] << ", " << fAr10mSlowD[i] << ", "
					<< fAr10m20mSMA[i] << ", " << fAr10m20mSD[i] << "\n";
			}

		}
	}
	myfileCombine2.close();
}

void CDlg_JEKYLL::GetData()
{
	// 시간 처리 ******************************************************************
	Request0167();
	Sleep(50);

	CTime t = CTime::GetCurrentTime();
	t += CTimeSpan(0, 0, 0, nCorrectTime);
	int sec = t.GetSecond();
	int min = t.GetMinute();
	int hour = t.GetHour();
	nCurMin = (hour - 9) * 60 + min + 15;

	CString strMinute; strMinute.Format("%d", nCurMin);	m_curmin.SetWindowText(strMinute); // nCurMin 표출

	// 데이터 수집 m_lst2105(선옵현재가)에서 수집 ************************************
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();

	CString str, strCHo9, strPHo9, strCHo8, strPHo8, strRem, strV1, strV2, strV3, strV4;

	float fCallPrice = 0.0, fPutPrice = 0.0;
	if (!bOption)
	{
		if (fQCHo.size() > 10) fQCHo.pop();// 호가8 10개(10초) 저장
		str = m_lst2105.GetItemText(1, 1);			m_callprc.SetWindowText(str);	fCallPrice = (float)atof(str);			// 현재가(콜)			
		strCHo8 = m_lst2105.GetItemText(8, 1);		fCho8 = (float)atof(strCHo8);	fQCHo.push(fCho8);						// 매도호가1(콜)	
		lCho8 = atol(m_lst2105.GetItemText(10, 1));																	// 매도호가1수량(콜)	

		strCHo9 = m_lst2105.GetItemText(9, 1);			fCho9 = (float)atof(strCHo9);										// 매수호가1(콜)	
		strCHo9 = m_lst2105_.GetItemText(9, 1);			fC2ho9 = (float)atof(strCHo9);										// 매수호가1(콜2)	
		strCHo9 = m_lst2105__.GetItemText(9, 1);		fC3ho9 = (float)atof(strCHo9);										// 매수호가1(콜3)	

		lCho9 = atol(m_lst2105.GetItemText(11, 1));																	// 매수호가1수량(콜)	
		lC2ho9 = atol(m_lst2105_.GetItemText(11, 1));																// 매수호가1수량(콜2)	
		lC3ho9 = atol(m_lst2105__.GetItemText(11, 1));																// 매수호가1수량(콜3)	

		m_tst2.SetWindowTextA(CallCode[0]);
		m_tst3.SetWindowTextA(CallCode[1]);
		m_tst4.SetWindowTextA(CallCode[2]);
	}
	else
	{
		if (fQPHo.size() > 10) fQPHo.pop();
		str = m_lst2105.GetItemText(1, 1);			m_putprc.SetWindowText(str);	fPutPrice = (float)atof(str);			// 현재가(풋)
		strPHo8 = m_lst2105.GetItemText(8, 1);		fPho8 = (float)atof(strPHo8);	fQPHo.push(fPho8);						// 매도호가1(풋)
		lPho8 = atol(m_lst2105.GetItemText(10, 1));																	// 매도호가1수량(풋)

		strPHo9 = m_lst2105.GetItemText(9, 1);			fPho9 = (float)atof(strPHo9);										// 매수호가1(풋)	
		strPHo9 = m_lst2105_.GetItemText(9, 1);			fP2ho9 = (float)atof(strPHo9);										// 매수호가1(풋2)	
		strPHo9 = m_lst2105__.GetItemText(9, 1);		fP3ho9 = (float)atof(strPHo9);										// 매수호가1(풋3)	

		lPho9 = atol(m_lst2105.GetItemText(11, 1));																	// 매수호가1수량(풋)	
		lP2ho9 = atol(m_lst2105_.GetItemText(11, 1));																// 매수호가1수량(풋2)	
		lP3ho9 = atol(m_lst2105__.GetItemText(11, 1));																// 매수호가1수량(풋3)	

		m_tst2.SetWindowTextA(PutCode[0]);
		m_tst3.SetWindowTextA(PutCode[1]);
		m_tst4.SetWindowTextA(PutCode[2]);
	}
	str = m_lst1601.GetItemText(2, 2);		long lKoFVol = (long)atol(str); 									// 외인 KO		*********************************************
	str = m_lst1601.GetItemText(2, 3);		long lKoSVol = (long)atol(str);										// 기관 KO		*********************************************
	str = m_lst1601.GetItemText(5, 2);		long lFutFVol = (long)atol(str); 									// 외인 선물	*********************************************
	str = m_lst1601.GetItemText(5, 3);		long lFutSVol = (long)atol(str);									// 기관 선물	*********************************************
	GetDlgItemText(IDC_FUTURE, str);		fFutPrc = (float)atof(str);												// 선물가격
	GetDlgItemText(IDC_FVOL, str);			long lFvol = atol(str);												// 선물누적거래량
	GetDlgItemText(IDC_FVOL2, str);			long lFvol2 = atol(str);											// 1분전 선물누적거래량
	GetDlgItemText(IDC_LREM, strRem);		lRemQty = atol(strRem);												// 매수잔량
	
	// 콜옵션 매수중일때 외국 코스피 순매도량이 -1000 이 넘으면 자동매수주문 모두 취소 ************************************************************************** (자동매입취소)
	// 풋옵션 매수중일때 외국 && 기관 코스피 순매수량이 각각 500 이 넘으면 자동매수주문 모두 취소

	BOOL bCheckOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	if ((lKoFVol < -1000 && !bCheckOption) || (lKoFVol > 500 && lKoSVol > 500 && bCheckOption))
	{
		KillTimer(4);//BuyOption2();
		KillTimer(8);//BuyOption();
		KillTimer(10);//BuyOption4();
		KillTimer(12);//BuyOption3();
		KillTimer(13);//BuyOption5();
		KillTimer(17);//BuyOption1();
	}

	if (bCheckOption)	// **************************************************************************************************************************************** 풋	
	{
		int isun = (int)(250000.0f*(fPho9*lPutQty[0] + fP2ho9 * lPutQty[1] + fP3ho9 * lPutQty[2]));
		str.Format("%d", isun);
		m_curvaluef4.SetWindowTextA(str);					// 현재보유옵션평가금액 표시
		//if (isun > 210000000 && isun < 400000000) OnBnClickedButtonprofit4();
	}
	else				// **************************************************************************************************************************************** 콜
	{
		int isun = (int)(250000.0f*(fCho9*lCallQty[0] + fC2ho9 * lCallQty[1] + fC3ho9 * lCallQty[2]));
		str.Format("%d", isun);
		m_curvalue4.SetWindowTextA(str);					// 현재보유옵션평가금액 표시
		if (isun > 210000000 && isun < 400000000) OnBnClickedButtonprofit4();
	}


	// 현재가가 시초가의 40% 미만일때 (기존 물량 청산) 및 매수(이익은 시초가의 20%로 한정) *********************************************************************** (자동 매입)
	//if (fCallPrice < 0.4*fCallOpen && lCallQty[0] == 0 && nIndex > 120) //콜매수
	//{
	//	((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);
	//	CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
	//	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(strCHo9);//시작 매수 가격
	//	pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", 0.2*fCallOpen); pEdit2->SetWindowText(str);//원하는 이익
	//	pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 10); pEdit3->SetWindowText(str);//매수량 %
	//	pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격
	//	OnBnClickedButtonprofit2();
	//	pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;

	//}
	//if (fPutPrice < 0.4*fPutOpen && lPutQty[0] == 0 && nIndex > 120) // 풋매수
	//{
	//	((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(1);
	//	CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
	//	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(strPHo9);//시작 매수 가격
	//	pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", 0.2*fPutOpen); pEdit2->SetWindowText(str);//원하는 이익
	//	pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 10); pEdit3->SetWindowText(str);//매수량 %
	//	pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격
	//	OnBnClickedButtonprofit2();
	//	pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
	//}

	// 매수 잔량의 최대값-lRemHighest과 최소값-lRemLowest을 갱신 및 카운트 기록 (카운트 현재 미사용) **********************************
	// 30초내 500개이상 증감 감시후, 매수매도체결량 및 속도 고려해 매수주문(50초내 수량 50개 이상)
	if (lRemQty > lRemHighest)
	{
		lRemHighest = lRemQty;
		lRemHtime = nIndex;
	}
	if (lRemQty < lRemLowest)
	{
		lRemLowest = lRemQty;
		lRemLtime = nIndex;
	} 

	lQRem.push(lRemQty);
	if (lQRem.size() > 30)	lQRem.pop(); // 호가잔량 30초 저장

	// 오류 처리 *****************************************************************************************************(미사용)
	GetDlgItemTextA(IDC_FUTURE60MA, str);	float f60ma = (float)atof(str);			//1분 60 이평선
	GetDlgItemTextA(IDC_BOLGR10M, str);		float f10ma = (float)atof(str);			//10분 20 이평선
	//if (abs(f60ma) > 5 || abs(f10ma) > 5) OnBnClickedButtonRequest7();

	GetDlgItemTextA(IDC_SD2, str); float fsd2 = (float)atof(str);						//10분 20 이평선 Width(볼린저밴드 폭)
	if (fsd2 > 5) // 오류 가정 (못읽어오면)
	{
		str.Format("%.2f", fAr10m20mSD[(int)(nCurMin/10) - 1]);			
		m_sd2.SetWindowText(str);
		fsd2 = (float)atof(str);
	}

	// 계좌관련 업데이트 지속 ********************************************************************************
	DispAccnt();

	// BOOL, int 변수 표시 bCall, bPut, bCancel, nProfit ************************************************************
	CString str1, str2, str3, str4;
	(bCall) ? str1 = "True" : str1 = "False"; m_bcall.SetWindowTextA(str1);
	(bPut) ? str2 = "True" : str2 = "False"; m_bput.SetWindowTextA(str2);
	(bCancel) ? str3 = "True" : str3 = "False"; m_bcancel.SetWindowTextA(str3);
	str4.Format("%d", nProfit); m_nprofit.SetWindowTextA(str4);

	// 매수취소 구현 (1분내 미체결 매수건수 자동 취소)
	if (bCancel && nCurMin == nCancelTime + 1)
	{
		Request600();
		bCancel = FALSE;
	}

	// 09:00~15:35분에만 처리하고 45분에 Request8415()로 데이터 정리 **************************************************************************************************************
	if (nCurMin < 411 && nCurMin > 0)
	{
		// 청산처리 ********************************************************************************************************************************************************* (청산처리)
		//if ((lLqdt > 0) && (!bCancel) && (nSellOption == 0)) //청산가능물량이 있고, 매수주문이 완료된 경우에 매도 (nSellOption == 0)
		//{
		//	if (lCallQty[0] > 0)		//콜옵션보유수가 있을경우
		//	{
		//		BOOL bCheckTrail = ((CButton*)GetDlgItem(IDC_CHECKTRAIL))->GetCheck(); // 트래킹모드인지 확인
		//		if (bCheckTrail)		SellCall2(nProfit); // trackingSell
		//		else					SellCall(nProfit); // set profit
		//	}
		//	

		//	if (lPutQty[0] > 0)		//풋옵션보유수가 있을경우
		//	{
		//		BOOL bCheckTrail = ((CButton*)GetDlgItem(IDC_CHECKTRAIL))->GetCheck();
		//		if (bCheckTrail)		SellPut2(nProfit);
		//		else					SellPut(nProfit);
		//	}
		//	

		//}

		if ((lLqdt != 0) && (nSellOption == 1)) //청산가능물량이 있고,  오버된 수량 청산 (nSellOption == 1)
		{
			if (lCallQty[0] < 0)		//nSellOption == 1 에서 오버된 수량 청산
			{
				Request100_(CallCode[0], "2", fCho8, (int)(-1 * lCallQty[0]));
			}
			if (lCallQty[1] < 0)		//nSellOption == 1 에서 오버된 수량 청산
			{
				Request100_(CallCode[1], "2", fC2ho8, (int)(-1 * lCallQty[1]));
			}
			if (lCallQty[2] < 0)		//nSellOption == 1 에서 오버된 수량 청산
			{
				Request100_(CallCode[2], "2", fC3ho8, (int)(-1 * lCallQty[2]));
			}

			if (lPutQty[0] < 0)		//nSellOption == 1 에서 오버된 수량 청산
			{
				Request100_(PutCode[0], "2", fPho8, (int)(-1 * lPutQty[0]));
			}
			if (lPutQty[1] < 0)		//nSellOption == 1 에서 오버된 수량 청산
			{
				Request100_(PutCode[1], "2", fP2ho8, (int)(-1 * lPutQty[1]));
			}
			if (lPutQty[2] < 0)		//nSellOption == 1 에서 오버된 수량 청산
			{
				Request100_(PutCode[2], "2", fP3ho8, (int)(-1 * lPutQty[2]));
			}
		}

		//if ((lLqdt > 0) && (lLqdt == lCallQty[0] + lPutQty[0]) && (nSellOption == 2))		// 속도관련 청산 (nSellOption == 2)
		//{
		//	float profit = 0.02;
		//	if (nIndex - nSaveTime > 60) profit = 0.01;
		//	SellOption(profit);
		//}

		// 0초 *************************************************************************************************************************************************
		if (sec == 0)
		{
			strArTime8415[nCurMin - 1] = strTime;
			GetDlgItemText(IDC_FVOL3, str);			m_fvol4.SetWindowTextA(str);	//1분전 거래량을 m_fvol4에 저장
			GetDlgItemText(IDC_FVOL2, str);			lFvol2 = atol(str);				//1분전 거래량을 lFvol2에 저장
			lArVol[nCurMin - 1] += (lFvol - lFvol2);
			str.Format("%d", lFvol);				m_fvol2.SetWindowText(str);		//1분전 선물누적거래량을 m_fvol2에 저장

			GetDlgItemText(IDC_LREM, str);											//1분전 매수잔량을 IDC_LREM4 에 표출
			CEdit *pEdit1;
			pEdit1 = (CEdit*)GetDlgItem(IDC_LREM4);
			pEdit1->SetWindowText(str);

			// 1분간 call/put high,low 기록 ********************************************************************************
			GetDlgItemText(IDC_CALLHIGH, str); m_callhigh2.SetWindowTextA(str);
			GetDlgItemText(IDC_CALLLOW, str); m_calllow2.SetWindowTextA(str);
			GetDlgItemText(IDC_PUTHIGH, str); m_puthigh2.SetWindowTextA(str);
			GetDlgItemText(IDC_PUTLOW, str); m_putlow2.SetWindowTextA(str);

			str.Format("%.2f", fCallHigh);	m_callhigh.SetWindowTextA(str);
			str.Format("%.2f", fCallLow);	m_calllow.SetWindowTextA(str);
			str.Format("%.2f", fPutHigh);	m_puthigh.SetWindowTextA(str);
			str.Format("%.2f", fPutLow);	m_putlow.SetWindowTextA(str);

			fArOpen[nCurMin] = fFutPrc; //1분0초부터 [1]에 저장되기 시작(시가,고가,저가)	
			fArHigh[nCurMin] = fFutPrc;
			fArLow[nCurMin] = fFutPrc;

			lArRemHigh[nCurMin] = lRemQty; // 잔량 최대,최소값 기록 시작
			lArRemLow[nCurMin] = lRemQty;

			Receive1602_(); // ***************************************************************************************************** 코스피 수급
			Receive1602(); //******************************************************************************************************* 선물 수급
			Receive8415(nCurMin);// ************************************************************************************************ 선물가격 8415 (84152 84153 콜풋 매분 필요없음)

			// ******************************************************************************************** 구매함수 관련(CC)
			//bCC = 1; //CheckCondtion 감시 시작
			//bCCact = 0; // 구매함수 비활성화

			// 외인 기관 추세 ***************************************************************************** 1분전 데이터 표출
			
			pEdit1 = NULL;
		}

		// 선물 최근 1분간 거래량
		str.Format("%d", lFvol - lFvol2);		m_fvol3.SetWindowTextA(str);

		// 1초 *********************************************************************************************************************************************
		if (sec == 1)
		{
			if (lArVol[nCurMin - 1] == 0)
			{
				strArTime8415[nCurMin - 1] = strTime;
				GetDlgItemText(IDC_FVOL2, str);			long lFvol2 = atol(str);		//1분전 거래량을 lFvol2에 저장
				lArVol[nCurMin - 1] += (lFvol - lFvol2);
				str.Format("%d", lFvol);				m_fvol2.SetWindowText(str);		//1분전 선물누적거래량을 m_fvol2에 저장
				// 외인 기관 추세 ********************************************************************	
				str.Format("%d", lFvol);	m_fvol2.SetWindowText(str);					// 1분전 선물누적거래량	을 표시	
			}

			if (fArOpen[nCurMin] == 0) fArOpen[nCurMin] = fFutPrc;					//1분0초부터 [1]에 저장되기 시작(시가,고가,저가)	
			if (fArHigh[nCurMin] == 0) fArHigh[nCurMin] = fFutPrc;
			if (fArLow[nCurMin] == 0) fArLow[nCurMin] = fFutPrc;

			if (lArRemHigh[nCurMin] == 0) lArRemHigh[nCurMin] = lRemQty;				// 잔량 최대,최소값 기록 시작
			if (lArRemLow[nCurMin] == 0) lArRemLow[nCurMin] = lRemQty;

			if (lArForVol2[nCurMin - 1] == 0) // 0초에 저장 안되었을 경우
			{
				Receive1602(); //******************************************************************************************************* 선물 수급
				Receive1602_(); // ***************************************************************************************************** 코스피 수급
				Receive8415(nCurMin); //************************************************************************************************ 선물가격 8415

			}
			// 콜,풋 가격 초기화
			fCallHigh = fCallPrice;
			fCallLow = fCallPrice;
			fPutHigh = fPutPrice;
			fPutLow = fPutPrice;
		}

		// 2초 *********************************************************************************************************************************************
		if (sec == 2 && lArForVol2[nCurMin - 1] == 0)
		{
			if (fArOpen[nCurMin] == 0) fArOpen[nCurMin] = fFutPrc; //1분0초부터 [1]에 저장되기 시작		
			if (fArHigh[nCurMin] == 0) fArHigh[nCurMin] = fFutPrc;
			if (fArLow[nCurMin] == 0) fArLow[nCurMin] = fFutPrc;
		}

		// 3초 ********************************************************************************************************************** (수급 고려해 매입 또는 청산)
		// 5분 평균 매수량이 100개 이상일때 콜매수 5%, -100개 이하일때 풋매수 (; 코스피 순매수량 고려), 콜+풋 시초가 대비 10틱보다 커지면 매입량 늘리기, 콜풋 개별 가격변동차이에 따른 콜/풋 선정 고려
		// 40분 이후 외인, 기관 코스피 순매수량이 합계 250 기준으로 첫 방향 고려 결정
		// 10시30분 이후 두번째 방향 고려
		// 12-13시 ....
		// 13시 이후 세번째 방향 고려

		//if (nIndex > 60 && sec == 3 && bCC == 1) //손절 및 구매조건 검색
		//{
		//	CheckCondition0(nCurMin - 1);
		//}

		//if (bCCact == 1 && nCCmin == nCurMin) //매입 함수
		//{
		//	CheckCondition();
		//}

		//str.Format("%.2f", fArCClose[nCurMin - 1]);
		//m_tst.SetWindowTextA(str);


		// 3초 **********************************************************************************************************************
		//if (nCurMin == 0 && sec == 3) OnBnClickedButtonprofit2();

		// 5초 *****************************************************************************
		if (nCurMin % 10 == 0 && sec == 5)
		{
			//Request3103(); //SNP %D, SNP 해외선물 지수 볼린저 계산
		}

		// 6초 *****************************************************************************
		if (nIndex < 60 && sec == 6)
		{
			Request84152(CallCode[0]); //**************************************************************************************************************** 콜 가격 8415
		}

		// 9초 *****************************************************************************
		if (nIndex < 60 && sec == 9)
		{
			Request84153(PutCode[0]); //**************************************************************************************************************** 풋 가격 8415
		}

		// 5분부터 실행 ***************************************************************************** (자동 옵션매수 : 볼린저밴드 상하단을 1포인트 이상 벗어날경우) 초기 급변동시
		if (nCurMin > 4) 
		{
			//if (bAutoToken && abs(f10ma) < 5 && fsd2 < 3)
			//{
			//	if ((f10ma < fsd2*-1.0 - 1.0) || (f10ma > fsd2 + 1.0))
			//	{
			//		OnBnClickedButtonprofit3(); //기존 BuyOption 모두 kill
			//		SetTimer(12, 1000, NULL);//BuyOption3 실행(볼린저밴드 상하단 터치)
			//		m_tauto.SetWindowTextA("12 Running");
			//		bAutoToken = FALSE; //1번만 실행하기 위함
			//	}
			//}
		}

		// 10분부터 실행 *****************************************************************************
		if (nCurMin > 9)
		{
			if (sec == 3 || sec == 8)
			{
				// 20mSMA, 20mSD **************************************************************** 1분전 데이터 표출	
				float f1 = fAr20mSD[nCurMin - 1], f2 = fAr20mSMA[nCurMin - 1];
				str.Format("%.2f", f1);		m_sd.SetWindowText(str);
				str.Format("%.2f", f2);	m_20msma.SetWindowText(str);

				// ****************************************************************************************************************************************** 10분봉 기준 %K %D
				int tempMin = nCurMin / 10;
				if (nCurMin < 20)
				{
					if (nCurMin < 10)
					{
						str.Format("%.2f", fAr10mSlowDY[41]);			m_percentd5.SetWindowText(str); //%D -10m
						str.Format("%.2f", fAr10mSlowD[38]);			m_percentd9.SetWindowText(str); //%D -20m
						str.Format("%.2f", fAr10mDY[41]);				m_percentd10.SetWindowText(str);//%K -10m
						str.Format("%.2f", fAr10m20mSDY[41]);			m_sd2.SetWindowText(str);		//sd(width) - 10m
					}
					else
					{
						str.Format("%.2f", fAr10mSlowDY[0]);			m_percentd5.SetWindowText(str); //%D -10m
						str.Format("%.2f", fAr10mSlowD[41]);			m_percentd9.SetWindowText(str); //%D -20m
						str.Format("%.2f", fAr10mDY[0]);				m_percentd10.SetWindowText(str);//%K
						str.Format("%.2f", fAr10m20mSD[0]);				m_sd2.SetWindowText(str);		// sd(width)
					}
				}
				else
				{
					str.Format("%.2f", fAr10mSlowD[tempMin - 1]);		m_percentd5.SetWindowText(str);
					str.Format("%.2f", fAr10mSlowD[tempMin - 2]);		m_percentd9.SetWindowText(str);
					str.Format("%.2f", fAr10mD[tempMin - 1]);			m_percentd10.SetWindowText(str);
				}

				str.Format("%.2f", fAr10mD[tempMin]);				m_percentd3.SetWindowText(str);
				str.Format("%.2f", fAr10mSlowD[tempMin]);			m_percentd4.SetWindowText(str);

				if (nCurMin < 10)
				{
					str.Format("%.2f", fAr10m20mSDY[41]);			m_sd2.SetWindowText(str);		// 10분봉 20분 Width
					str.Format("%.2f", fAr10m20mSMAY[41]);			m_20msma2.SetWindowText(str);	// 10분봉 20분 중심선
				}
				else
				{
					str.Format("%.2f", fAr10m20mSD[tempMin - 1]);			m_sd2.SetWindowText(str);		// 10분봉 20분 Width
					str.Format("%.2f", fAr10m20mSMA[tempMin - 1]);			m_20msma2.SetWindowText(str);	// 10분봉 20분 중심선
				}				
			}
		}

		// 고가 저가 상시 갱신 **************************************************************************
		if (fFutPrc > fArHigh[nCurMin])	fArHigh[nCurMin] = fFutPrc;
		if (fFutPrc < fArLow[nCurMin])	fArLow[nCurMin] = fFutPrc;

		if (sec > 55)  // ******************************************************************************************** 종가 (선물, 콜, 풋) 저장 84152 84153
		{
			fArClose[nCurMin] = fFutPrc;
			fArCClose[nCurMin] = fCallPrice;
			fArPClose[nCurMin] = fPutPrice;
		}

		if (fCallPrice > fCallHigh) fCallHigh = fCallPrice;
		if (fCallPrice < fCallLow) fCallLow = fCallPrice;

		if (fPutPrice > fPutHigh) fPutHigh = fPutPrice;
		if (fPutPrice < fPutLow) fPutLow = fPutPrice;

		// 매수잔량 최대/최저값 갱신 ********************************************************************
		if (fFutPrc > lArRemHigh[nCurMin])	lArRemHigh[nCurMin] = lRemQty;
		if (fFutPrc < lArRemLow[nCurMin])	lArRemLow[nCurMin] = lRemQty;
		lArRemClose[nCurMin] = lRemQty;

		// 1분마다 데이터 저장 및 표출 갱신 *****************************************************************************          ******************************************
		if (sec % 10 == 11) Request2400();//callqty, putqty...	10초마다 수량 확인
		if (sec == 41)									
		{
			if (lCallQty[0] < 0) Request10100_(CallCode[0]);	//  20초마다 주문가능금액,청산가능수량 확인
            else Request10100(CallCode[0]);		//  20초마다 주문가능금액,청산가능수량 확인
		}
		if (sec == 42)
		{
			if (lPutQty[0] < 0) Request10100_(PutCode[0]);	//  20초마다 주문가능금액,청산가능수량 확인
            else Request10100(PutCode[0]);	//  20초마다 주문가능금액,청산가능수량 확인
		}
		if (sec == 58 && nCurMin % 30 == 0)
		{
			Combine_8415_1602();
			Request2301(strMonth);
		}

		// ***************************************************************************************************************** 선물 60분, 볼린저밴드 20분(Center)******
		if (nCurMin > 1)
		{
			str.Format("%.2f", fFutPrc - fAr60mSMA[nCurMin - 1]);		m_future60ma.SetWindowText(str);//60분선 Center (1분봉)******
			str.Format("%.2f", fFutPrc - fAr20mSMA[nCurMin - 1]);		m_bolgr20.SetWindowText(str);	//20분선 Center (1분봉)******
		}

		if (nCurMin > 9)		str.Format("%.2f", fFutPrc - fAr10m20mSMA[nCurMin / 10 - 1]);
		else					str.Format("%.2f", fFutPrc - fAr10m20mSMAY[41]);
		m_bolgr10m.SetWindowText(str);	//20분선 Center (10분봉)******
	}
	

	if (nCurMin == 409 && (sec > 0 || sec < 5))
	{
		OnBnClickedButtonprofit3();		//자동매수 킬 BuyOption0 kill
	}

	if (nCurMin >= 410) // 15:35 실행
	{
		if (sec == 1 || sec == 11)
		{
			/*fArClose[410] = fFutPrc;
			fArOpen[410] = fFutPrc;
			fArHigh[410] = fFutPrc;
			fArLow[410] = fFutPrc;

			nCurMin = 411;*/
			UnadviseFC0();
			UnadviseFH0();
			UnadviseOVC();
			UnadviseOVC2();
			KillTimer(1); // 2105 선옵현재가
			KillTimer(2); // 2105_ 선옵현재가
			KillTimer(3); // 1601 투자자종합
			KillTimer(7); // SellFast
			KillTimer(8); // BuyOption() 자동매수매도
		}

		if (nCurMin >= 411) // 15:45 이후 실행
		{
			//Request8415(FutureCode);
			int temp = nCurMin;
			nCurMin = 411;
			Combine_8415_1602();
			KillTimer(1); // 2105 선옵현재가
			KillTimer(2); // 2105_ 선옵현재가
			KillTimer(3); // 1601 투자자종합
			KillTimer(7); // SellFast
			KillTimer(8); // BuyOption() 자동매수매도
			KillTimer(6); // GetData() 중지

			nCurMin = temp;
			OnBnClickedButtonStop();
		}
	}

	ofstream myfileGetdata("FindMoment.csv", ios::app);								// 속도 감시 이어쓰기
	if (myfileGetdata.is_open())
	{
		myfileGetdata << strTime << ", " << strVelocity7 << ", " << strVelocity8 << ", " << strVelocity9 << ", " << strVelocity10 << ", " << strRem << ", "
			<< strCHo8 << ", " << m_lst2105.GetItemText(10, 1) << ", " << strPHo8 << ", " << m_lst2105_.GetItemText(10, 1) << ", "
			<< strV1 << ", " << strV3 << ", " << strV2 << ", " << strV4 << "\n";
	}
	myfileGetdata.close();

	str.Format("%d", nIndex); 	m_idx.SetWindowText(str);
	nIndex++;
}


void CDlg_JEKYLL::BuyCall()
{
	if (lBalance == 0) return;

	(lCho9 < 100) ? Request100(CallCode[0], "2", fCho9) : Request100(CallCode[0], "2", fCho8);
	nCancelTime = nCurMin;
	CString cancel;
	cancel.Format("%d", nCancelTime); m_ncanceltime.SetWindowTextA(cancel);
	bCancel = TRUE;
	//bCall = FALSE;
	return;
}

void CDlg_JEKYLL::BuyCall(int amnt, int per)
{
	if (lBalance == 0) return;

	long l0 = (long)(lBalance / (fCho8 * 250000));
	long l1 = (long)(lBalance / (fCho9 * 250000));

	//strQty.Format("%d", l1);
	if (l0 == 0 || l1 == 0)
		return;

	int n0 = (int)l0;
	int n1 = (int)l1;

	n0 = (n0*per) / 100;
	n1 = (n1*per) / 100;

	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	//(lQty > lQty1)?Request100(CallCode[0], "2", strPrc1):Request100(CallCode[0], "2", strPrc);
	if (lCho9 > lCho8) //매도호가1 수량이 77 미만일때는 매도호가로 주문개시
	{
		if (n0 > amnt)
		{
			for (int i = 0; i < quota; ++i)
			{
				Request100_(CallCode[0], "2", fCho8, amnt);
				Sleep(80);
			}
			Request100_(CallCode[0], "2", fCho8, remainder);
		}
		else
		{
			Request100_(CallCode[0], "2", fCho8, n0);
		}
		//nCall = l0;
	}
	else //그 외일때는 매수호가로 주문개시
	{
		Request100_(CallCode[0], "2", fCho9, n1);
		//nCall = l1;
	}

	nCancelTime = nCurMin;
	CString cancel;
	cancel.Format("%d", nCancelTime); m_ncanceltime.SetWindowTextA(cancel);
	bCancel = TRUE;
	return;
}

void CDlg_JEKYLL::BuyCall(CString strPrc, int amnt, int per)
{
	if (lBalance == 0) return;

	float f0 = (float)atof(strPrc);
	long l0 = (long)(lBalance / (f0 * 250000));
	if (l0 == 0)
		return;

	int n0 = (int)l0;
	n0 = (n0*per) / 100;

	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (n0 > amnt)
	{
		for (int i = 0; i < quota; ++i)
		{
			Request100_(CallCode[0], "2", strPrc, amnt);
			Sleep(80);
		}
		Request100_(CallCode[0], "2", strPrc, remainder);
	}
	else
	{
		Request100_(CallCode[0], "2", strPrc, n0);
	}

	nCancelTime = nCurMin;
	CString cancel;
	cancel.Format("%d", nCancelTime); m_ncanceltime.SetWindowTextA(cancel);
	bCancel = TRUE;
	//bCall = FALSE;
	return;
}

void CDlg_JEKYLL::BuyCall(float fprc, int amnt, int per)
{
	if (lBalance == 0) return;

	long l0 = (long)((lBalance / (fprc * 250000)));
	int n0 = (int)l0;
	if (n0 == 0)
		return;

	n0 = (n0*per) / 100;

	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (n0 > amnt)
	{

		if (quota > 0)
		{
			for (int i = 0; i < quota; ++i)
			{
				Request100_(CallCode[0], "2", fprc, amnt);
				Sleep(80);
			}
		}
		if (remainder > 0)
		Request100_(CallCode[0], "2", fprc, remainder);
	}
	else
	{
		Request100_(CallCode[0], "2", fprc, n0);
	}


	return;
}


void CDlg_JEKYLL::BuyCall(CString code, float fprc, int amnt, int per)
{
	if (lBalance == 0) return;

	long l0 = (long)(lBalance / (fprc * 250000));
	int n0 = (int)l0;
	if (n0 == 0)
		return;

	n0 = (n0*per) / 100;

	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (amnt == 1)
	{
		for (int i = 0; i < n0; ++i)
		{
			Request100_(code, "2", fprc, amnt);
			Sleep(80);
		}
		return;
	}

	if (n0 > amnt)
	{

		if (quota > 0)
		{
			for (int i = 0; i < quota; ++i)
			{
				Request100_(code, "2", fprc, amnt);
				Sleep(80);
			}
		}
		if (remainder > 0)
			Request100_(code, "2", fprc, remainder);
	}
	else
	{
		Request100_(code, "2", fprc, n0);
	}


	return;
}

void CDlg_JEKYLL::BuyCallR(CString code, float fprc, int per)
{
	if (lBalance == 0 || fprc < 0.01f) return;

	long l0 = static_cast<long>((lBalance / (fprc * 250000)));
	int n0 = (int)l0;
	if (n0 == 0)
		return;

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

		Request100_(code, "2", fprc, orderQty);
		totalOrders += orderQty;

		if (totalOrders < n0) // No need to sleep if we've reached the total quantity
		{
			double sleepTime = timeDist(gen);
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime * 1000)));
		}
	}

	return;

	//int quota = n0 / amnt;
	//int remainder = n0 % amnt;

	//if (n0 > amnt)
	//{

	//	if (quota > 0)
	//	{
	//		for (int i = 0; i < quota; ++i)
	//		{
	//			Request100(CallCode, "2", fprc, amnt);
	//			Sleep(80);
	//		}
	//	}
	//	if (remainder > 0)
	//	Request100(CallCode, "2", fprc, remainder);
	//}
	//else
	//{
	//	Request100(CallCode, "2", fprc, n0);
	//}


	//return;
}


void CDlg_JEKYLL::SellCall(float fprc, int amnt, int per)
{
	int n0 = (int)lCallQty[0];
	if (n0 == 0) return;

	n0 = (n0*per) / 100;
	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (n0 > amnt)
	{
		for (int i = 0; i < quota; ++i)
		{
			Request100_(CallCode[0], "1", fprc, amnt);
			Sleep(80);
		}
		Request100_(CallCode[0], "1", fprc, remainder);
	}
	else
	{
		Request100_(CallCode[0], "1", fprc, n0);
	}

	return;
}

void CDlg_JEKYLL::BuyPut()
{
	if (lBalance == 0) return;

	(lPho9 < 100) ? Request100(PutCode[0], "2", fPho9) : Request100(PutCode[0], "2", fPho8);
	nCancelTime = nCurMin;
	CString cancel;
	cancel.Format("%d", nCancelTime); m_ncanceltime.SetWindowTextA(cancel);
	bCancel = TRUE;

	//bPut = FALSE;
	return;
}

void CDlg_JEKYLL::BuyPut(int amnt, int per)
{
	if (lBalance == 0) return;

	long l0 = (long)(lBalance / (fPho8 * 250000));
	long l1 = (long)(lBalance / (fPho9 * 250000));

	//strQty.Format("%d", l1);
	if (l0 == 0 || l1 == 0)
		return;

	int n0 = (int)l0;
	int n1 = (int)l1;

	n0 = (n0*per) / 100;
	n1 = (n1*per) / 100;
	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (lPho9 > lPho8) //매도호가1 수량이 77 미만일때는 매도호가로 주문개시
	{
		if (n0 > amnt)
		{
			for (int i = 0; i < quota; ++i)
			{
				Request100_(PutCode[0], "2", fPho8, amnt);
				Sleep(80);
			}
			Request100_(PutCode[0], "2", fPho8, remainder);
		}
		else
		{
			Request100_(PutCode[0], "2", fPho8, n0);
		}
		//nCall = l0;
	}
	else //그 외일때는 매수호가로 주문개시
	{
		Request100_(PutCode[0], "2", fPho9, n1);
		//nCall = l1;
	}

	nCancelTime = nCurMin;
	CString cancel;
	cancel.Format("%d", nCancelTime); m_ncanceltime.SetWindowTextA(cancel);
	bCancel = TRUE;

	//bPut = FALSE;
	return;
}

void CDlg_JEKYLL::BuyPut(CString strPrc, int amnt, int per)
{
	if (lBalance == 0) return;

	float f0 = (float)atof(strPrc);
	long l0 = (long)(lBalance / (f0 * 250000));
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
			Request100_(PutCode[0], "2", strPrc, amnt);
			Sleep(80);
		}
		Request100_(PutCode[0], "2", strPrc, remainder);
	}
	else
	{
		Request100_(PutCode[0], "2", strPrc, n0);
	}
	nCancelTime = nCurMin;
	CString cancel;
	cancel.Format("%d", nCancelTime); m_ncanceltime.SetWindowTextA(cancel);
	bCancel = TRUE;

	//bPut = FALSE;
	return;
}

void CDlg_JEKYLL::BuyPut(float fprc, int amnt, int per)
{
	if (lBalance == 0) return;

	long l0 = (long)(lBalance / (fprc * 250000));
	int n0 = (int)l0;
	if (n0 == 0)
		return;

	n0 = (n0 * per) / 100;
	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (n0 > amnt)
	{
		if (quota > 0)
		{
			for (int i = 0; i < quota; ++i)
			{
				Request100_(PutCode[0], "2", fprc, amnt);
				Sleep(80);
			}
		}
		if (remainder > 0)
		Request100_(PutCode[0], "2", fprc, remainder);
	}
	else
	{
		Request100_(PutCode[0], "2", fprc, n0);
	}

	return;
}


void CDlg_JEKYLL::BuyPut(CString code, float fprc, int amnt, int per)
{
	if (lBalance == 0) return;

	long l0 = (long)(lBalance / (fprc * 250000));
	int n0 = (int)l0;
	if (n0 == 0)
		return;

	n0 = (n0 * per) / 100;
	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (amnt == 1)
	{
		for (int i = 0; i < n0; ++i)
		{
			Request100_(code, "2", fprc, amnt);
			Sleep(80);
		}
		return;
	}

	if (n0 > amnt)
	{
		if (quota > 0)
		{
			for (int i = 0; i < quota; ++i)
			{
				Request100_(code, "2", fprc, amnt);
				Sleep(80);
			}
		}
		if (remainder > 0)
			Request100_(code, "2", fprc, remainder);
	}
	else
	{
		Request100_(code, "2", fprc, n0);
	}

	return;
}

void CDlg_JEKYLL::BuyPutR(CString code, float fprc, int per) // 랜덤한 수량(1~2)으로 랜덤한 시간간격(100~300ms) 을 가지고 주문-> Request100() (가격, 수량n)
{
	if (lBalance == 0 || fprc < 0.01f) return;

	long l0 = static_cast<long>((lBalance / (fprc * 250000))); // 옵션가격 250000
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

		Request100_(code, "2", fprc, orderQty);
		totalOrders += orderQty;

		if (totalOrders < n0) // No need to sleep if we've reached the total quantity
		{
			double sleepTime = timeDist(gen);
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime * 1000)));
		}
	}

	return;

	//int quota = n0 / amnt;
	//int remainder = n0 % amnt;

	//if (n0 > amnt)
	//{
	//	if (quota > 0)
	//	{
	//		for (int i = 0; i < quota; ++i)
	//		{
	//			Request100_(code, "2", fprc, amnt); // 구매 주문함수 (상품코드, 매수구분, 매입가격, 매입수량)
	//			Sleep(80);
	//		}
	//	}
	//	if (remainder > 0)
	//	Request100_(code, "2", fprc, remainder);
	//}
	//else
	//{
	//	Request100(PutCode, "2", fprc, n0);
	//}

	//return;
}

void CDlg_JEKYLL::SellPut(float fprc, int amnt, int per)
{
	int n0 = (int)lPutQty[0];
	if (n0 == 0) return;

	n0 = (n0 * per) / 100;
	int quota = n0 / amnt;
	int remainder = n0 % amnt;

	if (n0 > amnt)
	{
		for (int i = 0; i < quota; ++i)
		{
			Request100_(PutCode[0], "1", fprc, amnt);
			Sleep(80);
		}
		Request100_(PutCode[0], "1", fprc, remainder);
	}
	else
	{
		Request100_(PutCode[0], "1", fprc, n0);
	}

	return;
}


void CDlg_JEKYLL::MonOrder()//매도주문 완료 감시
{
	if (lLqdt == (lCallQty[0] + lPutQty[0]))
	{
		KillTimer(7);
	}
	return;
}

void CDlg_JEKYLL::DispAccnt()//계좌디스플레이
{
	// 청산가능수, 콜보유수량, 풋보유수량 표시
	CString str1, str2, str3, str4, str5, str6, str7, str8;

    str1.Format("%d", lLqdt);           m_lqdt.SetWindowTextA(str1);

    str2.Format("%d", lCallQty[0]);     m_avrprc2.SetWindowTextA(str2);
    str2.Format("%d", lCallQty[1]);     m_avrprc21.SetWindowTextA(str2);
    str2.Format("%d", lCallQty[2]);     m_avrprc22.SetWindowTextA(str2);

    str3.Format("%d", lPutQty[0]);      m_avrprc2f.SetWindowTextA(str3);
    str3.Format("%d", lPutQty[1]);      m_avrprc21f.SetWindowTextA(str3);
    str3.Format("%d", lPutQty[2]);      m_avrprc22f.SetWindowTextA(str3);

	str4.Format("%d", lBalance / 10000);	m_neword.SetWindowTextA(str4);

	// 콜 계좌	
	/*if (lCallQty[0] != 0) fCallAvrPrc[0] = (float)lCallAvrPrc / 250000 / abs(lCallQty[0]);
	else fCallAvrPrc[0] = 0.0;			*/					//평단가 계산	
	str5.Format("%.3f", fCallAvrPrc[0]);
    (fCallAvrPrc[0] > 0) ? m_avrprc3.SetWindowTextA(str5) : m_avrprc3.SetWindowTextA("-");
    str5.Format("%.3f", fCallAvrPrc[1]);
    (fCallAvrPrc[1] > 0) ? m_avrprc31.SetWindowTextA(str5) : m_avrprc31.SetWindowTextA("-");
    str5.Format("%.3f", fCallAvrPrc[2]);
    (fCallAvrPrc[2] > 0) ? m_avrprc32.SetWindowTextA(str5) : m_avrprc32.SetWindowTextA("-");

	//풋 계좌	
	/*if (lPutQty[0] != 0) fPutAvrPrc[0] = (float)lPutAvrPrc / 250000 / abs(lPutQty[0]);
	else fPutAvrPrc[0] = 0.0;	*/							//평단가 계산
	str6.Format("%.3f", fPutAvrPrc[0]);
    (fPutAvrPrc[0] > 0) ? m_avrprc3f.SetWindowTextA(str6) : m_avrprc3f.SetWindowTextA("-");
    str6.Format("%.3f", fPutAvrPrc[1]);
    (fPutAvrPrc[1] > 0) ? m_avrprc31f.SetWindowTextA(str6) : m_avrprc31f.SetWindowTextA("-");
    str6.Format("%.3f", fPutAvrPrc[2]);
    (fPutAvrPrc[2] > 0) ? m_avrprc32f.SetWindowTextA(str6) : m_avrprc32f.SetWindowTextA("-");

	//구입금액(콜/풋)
	str7.Format("%d", lCallAvrPrc); str8.Format("%d", lPutAvrPrc);
	m_avrprc.SetWindowTextA(str7);
	m_avrprcf.SetWindowTextA(str8);
	
	CString str9, str10;
	long lCurValue1 = (lCallQty[0] * (long)(250000 * fCho9));
	lCurValue1 += (lCallQty[1] * (long)(250000 * fC2ho9));
	lCurValue1 += (lCallQty[2] * (long)(250000 * fC3ho9));
	//str9.Format("%d", lCurValue1);
	//m_curvalue.SetWindowTextA(str9);					// 보유한 콜옵션 현재 평가금액
	long lCurValue2 = (lPutQty[0] * (long)(250000 * fPho9));
	lCurValue2 += (lPutQty[1] * (long)(250000 * fP2ho9));
	lCurValue2 += (lPutQty[2] * (long)(250000 * fP3ho9));
	//str10.Format("%d", lCurValue2);
	//m_curvaluef.SetWindowTextA(str10);					// 보유한 풋옵션 현재 평가금액

	CString disp, disp2;								// 보유한 각 옵션 순이익 및 손실
	if (lCallQty[0] > 0)		disp.Format("%d", lCurValue1 - lCallAvrPrc);
	else		disp.Format("%d", lCallAvrPrc + lCurValue1);

	if (lPutQty[0] > 0)			disp2.Format("%d", lCurValue2 - lPutAvrPrc);
	else		disp2.Format("%d", lPutAvrPrc + lCurValue2);

	//m_curvalue4.SetWindowTextA(disp);
	//m_curvaluef4.SetWindowTextA(disp2);

	return;
}

void CDlg_JEKYLL::SellCall()//손절
{
	Request100(CallCode[0], "1", fCho9);
	//bSearch = TRUE;
	bCall = TRUE;
	nSelltime = nCurMin;
	nCase = 0, nBuytime = 0;//케이스 및 해당시간 초기화
	return;
}

void CDlg_JEKYLL::SellCall(int profit)// 설정된 이익에 무조건 청산
{
	if (fCallAvrPrc[0] == 0)
		return;

	if ((fCho9 >= (ceilf(fCallAvrPrc[0] * (100 + profit)) / 100)) || (fCho9 <= (roundf(fCallAvrPrc[0] * (100 - profit)) / 100))) //roundf,ceilf,floorf(반올림,올림,내림)
	{
		SellOption1();
	}

	CString str;
	CEdit *pEdit2, *pEdit3;
	pEdit2 = (CEdit*)GetDlgItem(IDC_FTRAIL2); str.Format("%.3f", roundf(fCallAvrPrc[0] * (100 - profit)) / 100); pEdit2->SetWindowText(str);
	pEdit3 = (CEdit*)GetDlgItem(IDC_FTRAIL3); str.Format("%.3f", roundf(fCallAvrPrc[0] * (100 + profit)) / 100); pEdit3->SetWindowText(str);
	pEdit2 = NULL, pEdit3 = NULL;

	return;
}

void CDlg_JEKYLL::SellCall(float profit)
{
	if (fCallAvrPrc[0] == 0)
		return;

	if ((fCho9 >= fCallAvrPrc[0] + profit) || (fCho9 <= fCallAvrPrc[0] - profit)) //roundf,ceilf,floorf
	{
		SellOption1();
	}

	CString str;
	CEdit *pEdit2, *pEdit3;
	pEdit2 = (CEdit*)GetDlgItem(IDC_FTRAIL2); str.Format("%.3f", fCallAvrPrc[0] - profit); pEdit2->SetWindowText(str);
	pEdit3 = (CEdit*)GetDlgItem(IDC_FTRAIL3); str.Format("%.3f", fCallAvrPrc[0] + profit); pEdit3->SetWindowText(str);

	pEdit2 = NULL, pEdit3 = NULL;
	return;
}

void CDlg_JEKYLL::SellCall2(int profit, int percent) //trailing stop
{
    if (fCallAvrPrc[0] == 0) return;

    const float profitFactor = (100 + profit) / 100.0f;
    const float lossFactor = (100 - profit) / 100.0f;
    const float trailingStopHighFactor = 3.5f; //350% (최대 2.5배 수익)
    const float trailingStopLowFactor = 0.1f; // 최고가에서 10% 하락시 익절

    float goal = roundf(fCallAvrPrc[0] * profitFactor); // 목표가 130%
    float giveup = roundf(fCallAvrPrc[0] * lossFactor); // 손절가 70%

    fTrailingHigh = max(goal, fTrailingHigh); // 목표가 or 현재 fTrailingHigh 중 큰 값

    if (fCho9 > fTrailingHigh) { // trailing 기준값 업데이트
        fTrailingHigh = fCho9;
    }

    if (fTrailingHigh > 0 && fCho9 > 0 && fCallAvrPrc[0] > 0 && goal > 0)
    {
        if ((fTrailingHigh == goal) && (fCho9 <= giveup)) { // 고점을 갱신 못한 상태에 손절가에 도달 시
            Request100(CallCode[0], "1", fCho9, lCallQty[0]);
            bCall = TRUE;
            nSellOption = 0;
            return; // Early exit to avoid checking the next condition unnecessarily
        }

        if (fTrailingHigh > goal) {
            float highStop = fCallAvrPrc[0] * trailingStopHighFactor;
            float lowStop = roundf(fTrailingHigh * trailingStopLowFactor);
            if ((fCho9 >= highStop) || (fCho9 <= lowStop)) { // goal 갱신 후 trailing stop 250%~90%
                SellOption1();
            }
        }
    }
    CString ctrail; ctrail.Format("%.3f", fTrailingHigh); m_ftrail.SetWindowTextA(ctrail);
    CString str;
    CEdit* pEdit2, * pEdit3, * pEdit4, * pEdit5;
    pEdit2 = (CEdit*)GetDlgItem(IDC_FTRAIL2); str.Format("%.3f", giveup); pEdit2->SetWindowText(str); //손절가
    pEdit3 = (CEdit*)GetDlgItem(IDC_FTRAIL3); str.Format("%.3f", goal); pEdit3->SetWindowText(str); // 목표가
    pEdit4 = (CEdit*)GetDlgItem(IDC_FTRAIL4); str.Format("%.3f", roundf(fTrailingHigh * 90) / 100); pEdit4->SetWindowText(str); //trailing stop 90%
    pEdit5 = (CEdit*)GetDlgItem(IDC_FTRAIL5); str.Format("%.3f", fCallAvrPrc[0] * 3.5); pEdit5->SetWindowText(str); //trailing stop 250%
    pEdit5 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
    return;
}

void CDlg_JEKYLL::SellCall2(float profit, int percent) //trailing stop
{
	if (fCallAvrPrc[0] == 0)
		return;

	float goal = fCallAvrPrc[0] + profit; //목표가+
	float giveup = fCallAvrPrc[0] - profit; //목표가-
	if (fTrailingHigh == 0) fTrailingHigh = goal;

	if (fCho9 > fTrailingHigh) //trailing 기준값 업데이트
		fTrailingHigh = fCho9;

	if ((fTrailingHigh == goal) && (fCho9 <= giveup)) //고점을 갱신못한 상태에 손절가에 도달시
	{
		Request100(CallCode[0], "1", fCho9);
		bCall = TRUE;
	}

	if ((fTrailingHigh > goal) && ((fCho9 >= (goal + profit * 6)) || fCho9 <= (fTrailingHigh - profit + 0.05)))//trailing stop 200%~90%
	{
		SellOption1();
	}
	CString ctrail; ctrail.Format("%.3f", fTrailingHigh); m_ftrail.SetWindowTextA(ctrail);
	CString str;
	CEdit *pEdit2, *pEdit3, *pEdit4, *pEdit5;
	pEdit2 = (CEdit*)GetDlgItem(IDC_FTRAIL2); str.Format("%.3f", giveup); pEdit2->SetWindowText(str);
	pEdit3 = (CEdit*)GetDlgItem(IDC_FTRAIL3); str.Format("%.3f", goal); pEdit3->SetWindowText(str);
	pEdit4 = (CEdit*)GetDlgItem(IDC_FTRAIL4); str.Format("%.3f", fTrailingHigh - profit + 0.05); pEdit4->SetWindowText(str);
	pEdit5 = (CEdit*)GetDlgItem(IDC_FTRAIL5); str.Format("%.3f", goal + profit * 6); pEdit5->SetWindowText(str);
	pEdit5 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
	return;
}

void CDlg_JEKYLL::SellPut()//손절
{
	Request100(PutCode[0], "1", fPho9);
	bPut = TRUE;
	nSelltime = nCurMin;
	nCase = 0, nBuytime = 0;//케이스 및 해당시간 초기화
	return;
}

void CDlg_JEKYLL::SellPut(int profit)// 설정된 이익에 무조건 청산
{
	if (fPutAvrPrc[0] == 0)
		return;

	if ((fPho9 >= (roundf(fPutAvrPrc[0] * (100 + profit)) / 100)) || (fPho9 <= (roundf(fPutAvrPrc[0] * (100 - profit)) / 100))) //목표가 15% or 손절가 15% 설정
	{
		SellOption2();
	}

	CString str;
	CEdit *pEdit2, *pEdit3;
	pEdit2 = (CEdit*)GetDlgItem(IDC_FTRAIL2); str.Format("%.3f", roundf(fPutAvrPrc[0] * (100 - profit)) / 100); pEdit2->SetWindowText(str);
	pEdit3 = (CEdit*)GetDlgItem(IDC_FTRAIL3); str.Format("%.3f", roundf(fPutAvrPrc[0] * (100 + profit)) / 100); pEdit3->SetWindowText(str);

	pEdit2 = NULL, pEdit3 = NULL;
	return;
}

void CDlg_JEKYLL::SellPut(float profit)
{
	if (fPutAvrPrc[0] == 0)
		return;

	if ((fPho9 >= fPutAvrPrc[0] + profit) || (fPho9 <= fPutAvrPrc[0] - profit)) //roundf,ceilf,floorf
	{
		SellOption2();
	}

	CString str;
	CEdit *pEdit2, *pEdit3;
	pEdit2 = (CEdit*)GetDlgItem(IDC_FTRAIL2); str.Format("%.3f", fPutAvrPrc[0] - profit); pEdit2->SetWindowText(str);
	pEdit3 = (CEdit*)GetDlgItem(IDC_FTRAIL3); str.Format("%.3f", fPutAvrPrc[0] + profit); pEdit3->SetWindowText(str);

	pEdit2 = NULL, pEdit3 = NULL;
	return;
}

void CDlg_JEKYLL::SellPut2(int profit, int percent) //trailing stop
{
	float goal = roundf(fPutAvrPrc[0] * (100 + profit)) / 100; //목표가 130%
	float giveup = roundf(fPutAvrPrc[0] * (100 - profit)) / 100; //목표가 70%
	fTrailingHigh = goal;

	if (fPho9 > fTrailingHigh) //trailing 기준값 업데이트
		fTrailingHigh = fPho9;

	if ((fTrailingHigh == goal) && (fPho9 <= giveup)) //고점을 갱신못한 상태에 손절가에 도달시
	{
		SellOption2();
	}

	if ((fTrailingHigh > goal) && ((fPho9 >= (fPutAvrPrc[0] * 3.5)) || (fPho9 <= (roundf(fTrailingHigh * 90) / 100))))//trailing stop 200%~90%
	{
		SellOption2();
	}
	CString ctrail; ctrail.Format("%.3f", fTrailingHigh); m_ftrail.SetWindowTextA(ctrail);
	CString str;
	CEdit *pEdit2, *pEdit3, *pEdit4, *pEdit5;
	pEdit2 = (CEdit*)GetDlgItem(IDC_FTRAIL2); str.Format("%.3f", giveup); pEdit2->SetWindowText(str);
	pEdit3 = (CEdit*)GetDlgItem(IDC_FTRAIL3); str.Format("%.3f", goal); pEdit3->SetWindowText(str);
	pEdit4 = (CEdit*)GetDlgItem(IDC_FTRAIL4); str.Format("%.3f", roundf(fTrailingHigh * 90) / 100); pEdit4->SetWindowText(str);
	pEdit5 = (CEdit*)GetDlgItem(IDC_FTRAIL5); str.Format("%.3f", fPutAvrPrc[0] * 3.5); pEdit5->SetWindowText(str);
	pEdit5 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
	return;
}

void CDlg_JEKYLL::SellPut2(float profit, int percent) //trailing stop
{
	if (fPutAvrPrc[0] == 0)
		return;

	float goal = fPutAvrPrc[0] + profit; //목표가+
	float giveup = fPutAvrPrc[0] - profit; //목표가-
	if (fTrailingHigh == 0) fTrailingHigh = goal;

	if (fPho9 > fTrailingHigh) //trailing 기준값 업데이트
		fTrailingHigh = fPho9;

	if ((fTrailingHigh == goal) && (fPho9 <= giveup)) //고점을 갱신못한 상태에 손절가에 도달시
	{
		Request100(PutCode[0], "1", fPho9);
		bPut = TRUE;
	}

	if ((fTrailingHigh > goal) && ((fPho9 >= (goal + profit * 6)) || fPho9 <= (fTrailingHigh - profit + 0.05)))//trailing stop 200%~90%
	{
		SellOption2();
	}
	CString ctrail; ctrail.Format("%.3f", fTrailingHigh); m_ftrail.SetWindowTextA(ctrail);
	CString str;
	CEdit *pEdit2, *pEdit3, *pEdit4, *pEdit5;
	pEdit2 = (CEdit*)GetDlgItem(IDC_FTRAIL2); str.Format("%.3f", giveup); pEdit2->SetWindowText(str);
	pEdit3 = (CEdit*)GetDlgItem(IDC_FTRAIL3); str.Format("%.3f", goal); pEdit3->SetWindowText(str);
	pEdit4 = (CEdit*)GetDlgItem(IDC_FTRAIL4); str.Format("%.3f", fTrailingHigh - profit + 0.05); pEdit4->SetWindowText(str);
	pEdit5 = (CEdit*)GetDlgItem(IDC_FTRAIL5); str.Format("%.3f", goal + profit * 6); pEdit5->SetWindowText(str);
	pEdit5 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
	return;
}

void CDlg_JEKYLL::StandbyNine()
{
	// 시간 처리 ******************************************************************
	Request0167();
	Sleep(50);

	CTime t = CTime::GetCurrentTime();
	t += CTimeSpan(0, 0, 0, nCorrectTime);
	int sec = t.GetSecond();
	int min = t.GetMinute();
	int hour = t.GetHour();
	nCurMin = (hour - 9) * 60 + min + 15; // 8시45분 적용 (9시0분 -15분)
	CString strMinute; strMinute.Format("%d", nCurMin);	m_curmin.SetWindowText(strMinute); // nCurMin 표출
	//OnBnClickedButtonRequest22(); // Write csv(yesterday data)
	//OnBnClickedButtonRequest23(); // Read csv

	if (nCurMin < 0) // 0시~ 장전 실행
	{
		return;
	}
	else if (nCurMin >= 0 && nCurMin <= (7 * 60)) { // 장중 실행
		// Routine A: Perform this routine until 15:45 (7 * 60 minutes)
		// ... Your code for routine A here ...
		KillTimer(16); // kill StandbyNine() 

		/*Request2105();
		Sleep(50);
		Request2105_();
		Sleep(50);
		Request1601();
		Sleep(50);*/

		AdviseFC0();//FC0(bFC0) 데이터 받기 시작하면 CNCT(button7) 눌러 getdata 시작하고 bFC0 = 0 , 장후 실행안함
		Sleep(100);
		AdviseFH0();
		Sleep(100);
		//AdviseOVC();
		//AdviseOVC2();
		/*AdviseBMT();
		AdviseBMT2();*/

		SetTimer(1, 1000, NULL); //2105 
		Sleep(50);
		SetTimer(2, 1000, NULL); //2105_ 
		Sleep(50);
		SetTimer(3, 1000, NULL); //1601 투자자종합		
		Sleep(50);
		SetTimer(9, 1000, NULL); //21052
		Sleep(50);

		// 계좌
		Request2400();//lCallQty, lPutQty(콜,풋 보유수량 확인),fCallAvrPrc, fPutAvrPrc(평단가 계산)
		Sleep(50);

	}
	else if (nCurMin > (7 * 60) && nCurMin < (7 * 60 + 15 + 8 * 60)) { // 장후~ 24시까지 실행
		// Routine B: Perform this routine from 15:46 to 24:00 (16시 + 8시간 = 24시) 
		// ... Your code for routine B here ...
		KillTimer(16); // kill StandbyNine() 

		/*Request2105();
		Sleep(50);
		Request2105_();
		Sleep(50);
		Request1601();
		Sleep(50);*/

		//AdviseFC0();//FC0(bFC0) 데이터 받기 시작하면 CNCT(button7) 눌러 getdata 시작하고 bFC0 = 0 , 장후 실행안함
		Sleep(100);
		AdviseFH0();
		Sleep(100);
		//AdviseOVC();
		//AdviseOVC2();
		/*AdviseBMT();
		AdviseBMT2();*/

		SetTimer(1, 1000, NULL); //2105 
		Sleep(50);
		SetTimer(2, 1000, NULL); //2105_ 
		Sleep(50);
		SetTimer(3, 1000, NULL); //1601 투자자종합
		Sleep(50);
		SetTimer(9, 1000, NULL); //21052	
		Sleep(50);

		// 계좌
		Request2400();//lCallQty, lPutQty(콜,풋 보유수량 확인),fCallAvrPrc, fPutAvrPrc(평단가 계산)
		Sleep(50);

		OnBnClickedButtonRequest7(); //CNCT 버튼 실행


	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- Button
void CDlg_JEKYLL::OnBnClickedButtonRequest()
{
	// TODO: Add your control notification handler code here.
	SetTimer(16, 500, NULL); //StandbyNine() : 9시이전 시작시 대기 루틴
}

void CDlg_JEKYLL::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	KillTimer(5);
	KillTimer(6);
	KillTimer(7);
	KillTimer(8);
	KillTimer(9);
	KillTimer(10);
	KillTimer(11);
	KillTimer(12);
	KillTimer(13);
	KillTimer(14);
	KillTimer(15);
	KillTimer(16);
	KillTimer(17);
	KillTimer(18);

	UnadviseFC0();
	UnadviseFH0();
	UnadviseOVC();
	UnadviseOVC2();
	//UnadviseBMT();
}

void CDlg_JEKYLL::OnBnClickedButtonRequest2()
{
	// TODO: Add your control notification handler code here
	nProfit = nGoalFlat; // nGoalFlat 이익률로 매수매도

	CString str1, str2;
	GetDlgItemTextA(IDC_QTY, str1);
	GetDlgItemTextA(IDC_PRC, str2);
	Request100_(CallCode[0], "2", str2, str1);
}

void CDlg_JEKYLL::OnBnClickedButtonRequest3()
{
	// TODO: Add your control notification handler code here
	//Request100(CallCode[0], "1", fCho9);
	SellCall();//콜 손절

}

void CDlg_JEKYLL::OnBnClickedButtonRequest4()
{
	// TODO: Add your control notification handler code here
	// call 옵션 주문가능수량 조회 및 표출
	//Request10100();//주문가능수량/금액 조회
	//Sleep(150);	
	CString str1, str4;
	str1.Format("%d", lLqdt); str4.Format("%d", lBalance);

	CString strPrc = m_lst2105.GetItemText(1, 1);
	m_prc.SetWindowTextA(strPrc);

	//GetDlgItemTextA(IDC_NEWORD, strUsableMoney);//주문가능금액
	//lBalance = atol(strUsableMoney); //주문가능금액을 text로 받아서 long으로 강제변환

	float fPrc = (float)atof(strPrc);
	if (fPrc > 0)
	{
		fPrc = (float)(lBalance / (fPrc * 250000));
		int b = (int)fPrc;
		strPrc.Format("%d", b);
	}

	m_qty.SetWindowTextA(strPrc);
}

void CDlg_JEKYLL::OnBnClickedButtonRequest5()
{
	// TODO: Add your control notification handler code here
	/*KillTimer(8);
	GetDlgItemTextA(IDC_ORGORDNO, strOrgOrdNo);
	CString strQty;
	GetDlgItemTextA(IDC_QTY, strQty);
	Request300(CallCode[0], strOrgOrdNo, strQty);*/
	Request600();
}

void CDlg_JEKYLL::OnBnClickedButtonRequest6()
{
	// TODO: Add your control notification handler code here
	GetDlgItemTextA(IDC_ORGORDNO, strOrgOrdNo);
	CString strPrc, strQty;
	GetDlgItemTextA(IDC_PRC, strPrc);
	GetDlgItemTextA(IDC_QTY, strQty);
	Request200(CallCode[0], strOrgOrdNo, strPrc, strQty);
}

void CDlg_JEKYLL::OnBnClickedButtonRequest7() //CNCT
{
	// TODO: Add your control notification handler code here

	//Request0167();
	Request8415(FutureCode);
	//Sleep(50);
	//Request1602("4", "900", "1");
	Sleep(1000);
	//Request2421(FutureCode);
	//Request1662();
	DispAccnt();
	/*
	if (lCallQty[0] > 0) bCall = FALSE;
	if (lPutQty[0] > 0) bPut = FALSE;*/
	if (lLqdt != (lCallQty[0] + lPutQty[0]))
	{
		bCancel = TRUE;//구매취소 활성화
		nCancelTime = nCurMin;
	}
	CString strTemp;
	GetDlgItemText(IDC_FVOL, strTemp);
	m_fvol2.SetWindowText(strTemp);			// 현재선물누적거래량표시

	OnBnClickedButtonRequest19(); //getdata 실행

}

void CDlg_JEKYLL::OnBnClickedButtonRequest10()
{
	// TODO: Add your control notification handler code here
	//Request10100();//주문가능수량/금액 조회
	//Sleep(150);
	CString str1, str4;
	str1.Format("%d", lLqdt); str4.Format("%d", lBalance);

	CString strPrc = m_lst2105_.GetItemText(1, 1);
	m_prc2.SetWindowTextA(strPrc);

	float fPrc = (float)atof(strPrc);
	if (fPrc > 0)
	{
		fPrc = (float)(lBalance / (fPrc * 250000));
		int b = (int)fPrc;
		strPrc.Format("%d", b);
	}

	m_qty2.SetWindowTextA(strPrc);
}

void CDlg_JEKYLL::OnBnClickedButtonRequest11()
{
	// TODO: Add your control notification handler code here
	nProfit = nGoalFlat; // nGoalFlat 이익률로 매수매도

	CString str1, str2;
	GetDlgItemTextA(IDC_QTY2, str1);
	GetDlgItemTextA(IDC_PRC2, str2);
	Request100_(PutCode[0], "2", str2, str1);
	//bPut = FALSE;
}

void CDlg_JEKYLL::OnBnClickedButtonRequest12()
{
	// TODO: Add your control notification handler code here
	Request100(PutCode[0], "1", fPho9);
}

void CDlg_JEKYLL::OnBnClickedButtonRequest13()
{
	// TODO: Add your control notification handler code here
	/*GetDlgItemTextA(IDC_ORGORDNO2, strOrgOrdNo);
	CString strQty;
	GetDlgItemTextA(IDC_QTY2, strQty);
	Request300(PutCode[0], strOrgOrdNo, strQty);*/
	Request600();

}

void CDlg_JEKYLL::OnBnClickedButtonRequest14()
{
	// TODO: Add your control notification handler code here
	GetDlgItemTextA(IDC_ORGORDNO2, strOrgOrdNo);
	CString strPrc, strQty;
	GetDlgItemTextA(IDC_PRC2, strPrc);
	GetDlgItemTextA(IDC_QTY2, strQty);
	Request200(PutCode[0], strOrgOrdNo, strPrc, strQty);
}

void CDlg_JEKYLL::OnBnClickedButtonRequest19()
{
	// TODO: Add your control notification handler code here
	//Sleep(3000);
	//Request1602("1", "001", "2");
	SetTimer(6, 1000, NULL); //getdata() 실행
}

void CDlg_JEKYLL::OnBnClickedButtonRequest20()
{
	// TODO: Add your control notification handler code here
	KillTimer(6);

}

void CDlg_JEKYLL::OnBnClickedButtonRequest21()
{
	// TODO: Add your control notification handler code here
	OnBnClickedButtonStop();
	//ExportToCSVFile();
	bToken = FALSE;
	bCall = FALSE, bPut = FALSE;
	Request2301(strMonth);
	Sleep(80);
	OnBnClickedButtonRequest();
}


void CDlg_JEKYLL::ExportToCSVFile()
{
	/*ofstream myfile("trend_call.csv");
	if (myfile.is_open())
	{
	myfile << "시간, 현재가, 매수가격\n";

	for (int i = 0; i < nIndex; i++)
	{
	myfile << strArCurTime[i] << ", " << fArCallPrice[i] << ", " <<  strArTestBuyPrice[i] << "\n";
	}

	myfile.close();
	}

	ofstream myfile2("trend_put.csv");
	if (myfile2.is_open())
	{
	myfile2 << "시간, 현재가, 매수가격\n";

	for (int i = 0; i < nIndex; i++)
	{
	myfile2 << strArCurTime[i] << ", " << fArPutPrice[i] << ", " << strArTestBuyPrice[i] << "\n";
	}
	myfile2.close();
	}
	else cout << "Unable to open file2";
	return;*/
}

void CDlg_JEKYLL::ExportToCSVFile(const CListCtrl *plistctrlContent, BOOL bIncludeHeaderNames, char cDelimiter) // default to ',' and declared in the header file
{
	CFile filePersistent;
	CString strFilter = _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||");

	CTime t = CTime::GetCurrentTime();

	CFileDialog dlgSaveFile(
		FALSE,	     // Save As, not File Open
		_T(".csv"),  // default file name extentsion
		strDate,        // initial file name in the dialog
		0,           // DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		strFilter,   // filter
		this);       // parent window, i.e., Your own window class

	if (dlgSaveFile.DoModal() == IDOK)
	{
		// 1. file
		CString strFileName = dlgSaveFile.GetPathName(); // full path
		filePersistent.Open(strFileName, CFile::modeCreate | CFile::modeWrite); // write and create user rights

																				// 2. archive
																				// Constructs a CArchive object and specifies
																				// whether it will be used for loading or storing objects.
		CArchive archiveContent(&filePersistent, CArchive::store); // just storing obj

																   // 3. optional: header names
		CHeaderCtrl *pheaderctrl = plistctrlContent->GetHeaderCtrl();
		int iHeaderNameCount = pheaderctrl->GetItemCount();
		CString strRightHaffSeparator(_T(""));
		strRightHaffSeparator.Format(_T("%c "), cDelimiter);


		if (TRUE == bIncludeHeaderNames)
		{
			CHeaderCtrl *pheaderctrl = plistctrlContent->GetHeaderCtrl();
			CString strOneRecord(_T(""));
			for (int i = 0; i < iHeaderNameCount - 1; ++i)
			{
				//strOneRecord += _T("\"");
				strOneRecord += this->GetColumnName(plistctrlContent, i);
				strOneRecord += strRightHaffSeparator;
			}
			//strOneRecord += _T("\"");
			strOneRecord += this->GetColumnName(plistctrlContent, iHeaderNameCount - 1);
			strOneRecord += _T("\r\n"); // windows change a line
			archiveContent.Write(strOneRecord, strOneRecord.GetLength() * sizeof(_TCHAR));
		}

		int iItemCount = plistctrlContent->GetItemCount();
		for (int i = 0; i < iItemCount; ++i)
		{
			CString strOneRecord(_T(""));
			for (int j = 0; j < iHeaderNameCount - 1; ++j)
			{
				//strOneRecord += _T("\"");
				strOneRecord += plistctrlContent->GetItemText(i, j);
				strOneRecord += strRightHaffSeparator;
			}
			//strOneRecord += _T("\"");
			strOneRecord += plistctrlContent->GetItemText(i, iHeaderNameCount - 1);
			strOneRecord += _T("\r\n");

			archiveContent.Write(strOneRecord, strOneRecord.GetLength() * sizeof(_TCHAR));
		}

		archiveContent.Close();
		filePersistent.Close();
	}
	return;
}

//void CDlg_JEKYLL::OnNMClick600(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	/*NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
//	int index = pNMView->iItem;
//	CString str = m_lst600.GetItemText(index, 0);
//	m_orgordno.SetWindowTextA(str);
//	m_orgordno2.SetWindowTextA(str);
//	*pResult = 0;*/
//}

CString CDlg_JEKYLL::GetColumnName(const CListCtrl * listctrl, int iCol)
{
	CString strName(_T(""));
	CHeaderCtrl* pHeaderCtrl = listctrl->GetHeaderCtrl();
	if (NULL != pHeaderCtrl && iCol < pHeaderCtrl->GetItemCount())
	{
		HDITEM hditem;
		hditem.mask = HDI_TEXT;
		hditem.pszText = strName.GetBuffer(256);
		hditem.cchTextMax = 256;
		pHeaderCtrl->GetItem(iCol, &hditem);
		strName.ReleaseBuffer();
	}
	return strName;
}

HBRUSH CDlg_JEKYLL::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		if (pWnd->GetDlgCtrlID() == IDC_FCHG
			|| pWnd->GetDlgCtrlID() == IDC_LREM || pWnd->GetDlgCtrlID() == IDC_FUTURE60MA
			|| pWnd->GetDlgCtrlID() == IDC_BOLGR10M )
		{
			pDC->SetTextColor(RGB(255, 0, 0));//red
		}

		if (pWnd->GetDlgCtrlID() == IDC_LREM5)
		{
			CString str;
			GetDlgItemTextA(IDC_LREM5, str);
			float f1 = (float)atof(str);
			if (f1 == fFutPrc)
				pDC->SetTextColor(RGB(255, 0, 0));//red
		}

		if (pWnd->GetDlgCtrlID() == IDC_LREM6)
		{
			CString str;
			GetDlgItemTextA(IDC_LREM6, str);
			float f1 = (float)atof(str);
			if (f1 == fFutPrc)
				pDC->SetTextColor(RGB(255, 0, 0));//red
		}

		if (pWnd->GetDlgCtrlID() == IDC_NEWORD || pWnd->GetDlgCtrlID() == IDC_DDAY)
		{
			pDC->SetTextColor(RGB(255, 0, 255));//magenta
		}

		if (pWnd->GetDlgCtrlID() == IDC_STIME || pWnd->GetDlgCtrlID() == IDC_BCALL || pWnd->GetDlgCtrlID() == IDC_BPUT
			|| pWnd->GetDlgCtrlID() == IDC_PERCENTD3 || pWnd->GetDlgCtrlID() == IDC_PERCENTD4 || pWnd->GetDlgCtrlID() == IDC_PERCENTD5
			|| pWnd->GetDlgCtrlID() == IDC_PERCENTD9 || pWnd->GetDlgCtrlID() == IDC_PERCENTD10 || pWnd->GetDlgCtrlID() == IDC_PERCENTD11
			|| pWnd->GetDlgCtrlID() == IDC_FCHG2 || pWnd->GetDlgCtrlID() == IDC_FUTURE 
			|| pWnd->GetDlgCtrlID() == IDC_CURMIN)
		{
			pDC->SetTextColor(RGB(0, 0, 255));//blue
		}

		if (pWnd->GetDlgCtrlID() == IDC_CALLPRC || pWnd->GetDlgCtrlID() == IDC_PUTPRC || pWnd->GetDlgCtrlID() == IDC_FVOL3
			|| pWnd->GetDlgCtrlID() == IDC_FUTURESNP || pWnd->GetDlgCtrlID() == IDC_CPOWER
			|| pWnd->GetDlgCtrlID() == IDC_FTRAIL2 || pWnd->GetDlgCtrlID() == IDC_FTRAIL3
			|| pWnd->GetDlgCtrlID() == IDC_CURVALUE4 || pWnd->GetDlgCtrlID() == IDC_CURVALUEF4
            || pWnd->GetDlgCtrlID() == IDC_CURVALUE2 || pWnd->GetDlgCtrlID() == IDC_CURVALUE21 || pWnd->GetDlgCtrlID() == IDC_CURVALUE22)
		{
			pDC->SetTextColor(RGB(148, 0, 211));//dark violet
			//pDC->SetBkColor(RGB(171, 130, 255));
		}
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CDlg_JEKYLL::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 1:
		Request2105();//선옵현재가
		//OnBnClickedButtonRequest4();
		break;
	case 2:
		Request2105_();
		//OnBnClickedButtonRequest10();
		break;
	case 3:
		Request1601();//투자자종합
		break;
	case 4:
		BuyOption2();
		break;
	case 5:
		Request8415(FutureCode); //chart
		break;
	case 6:
		GetData();
		break;
	case 7:
		SellFast(); // fast sell
		break;
	case 8://자동 매수매도
		BuyOption();
		break;
	case 9:
		Request21052();
		break;
	case 10:
		BuyOption4();
		break;
	case 11:
		//StrangleBuy();//양매도 청산
		break;
	case 12:
		BuyOption3();
		break;
	case 13:
		BuyOption5(); // 60m line
		break;
	case 14:
		//StrangleSell();//양매도 주문
		break;
	case 15:
		//StrangleBuyStep();//양매도 주문
		break;
	case 16:
		StandbyNine();//9시이전 시작시 대기 루틴
		break;
	case 17:
		BuyOption1();//자동으로 사고 SetSell 에서 정의된 n개씩 팔기
		break;
	case 18:
		BuyOption0();
		//BuyOption7(nCurMin-1);//자동매수매도_매수잔량감추기
		break;
	}

	//CString strQty;
	//m_lqdt.GetWindowTextA(strQty);//청산가능수
	//if (strQty == "0")
	//{
	//	KillTimer(8);
	//}
	//청산가능수량이 0 이면 매도함수(콜/풋) 를 kill한다.
	CDialog::OnTimer(nIDEvent);
}


void CDlg_JEKYLL::OnBnClickedButtonprofit() // Profit editbox
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString temp;
	GetDlgItemTextA(IDC_EDITPROFIT, temp);
	nProfit = atoi(temp);
	if (nProfit > 20) // 20보다 크면 트레일모드
		((CButton*)GetDlgItem(IDC_CHECKTRAIL))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_CHECKTRAIL))->SetCheck(0);
	m_nprofit.SetWindowTextA(temp);
}


void CDlg_JEKYLL::CheckCondition0(int i) // - 매입프로세스 :  손절 및 조건 검색
{
	// 3초 ***************************************************************************** (수급 고려해 매입 또는 청산)
	nCCamnt = 0;
		// ************************************************************************************** 외국인 코스피 순매수량 기준(시간대별)
	long lRefForVol = 200;
	if (i > 40 && i <= 90) lRefForVol = 400;
	else if (i > 90 && i <= 180) lRefForVol = 550;
	else if (i > 180 && i <= 240) lRefForVol = 600;
	else if (i > 240 && i <= 320) lRefForVol = 750;
	else lRefForVol = 800;

	// ************************************************************************************** 시초가 대비 상승 하락할 만큼 매수수량 조절
	int nPerBuy = 100;
	if (fArCClose[i] + fArPClose[i] < fCallOpen + fPutOpen - 0.40) nPerBuy = 10;
	else if (fArCClose[i] + fArPClose[i] < fCallOpen + fPutOpen - 0.30) nPerBuy = 5;
	else if (fArCClose[i] + fArPClose[i] < fCallOpen + fPutOpen - 0.20) nPerBuy = 2;
	else nPerBuy = 1;

	if (lArForVol2[i] > 4000 || lArForVol2[i] < -4000) nPerBuy = 1;

	float fSimCPrc = fCallAvrPrc[0], fSimPPrc = fPutAvrPrc[0];	//지역변수 사용 , 전역변수(시뮬) 과 충돌방지
	int nCqty = (int)lCallQty[0], nPqty = (int)lPutQty[0];		//지역변수 사용 , 전역변수(시뮬) 과 충돌방지

	int nCPch = (int)(lBalance / (250000 * fCho8)); // 매입가능한 콜수량
	int nPPch = (int)(lBalance / (250000 * fPho8)); // 매입가능한 풋수량	

	// ************************************************************************************************************************************************ 청산
	if (fSimCPrc > 0 || fSimPPrc > 0)
	{
		// 손절 ******************************************************************************************************************************* 손절
		if (nCqty > 0)
		{
			if (
				((nCase == 4 && i > 10 + nBuytime) && (fArCClose[i] <= fSimCPrc + 0.05))				// 콜손절4
				|| (nCase == 1 && i > 40 + nBuytime)													//콜손절1
				|| (nCase == 1 && i > 15 + nBuytime && i <= 320 && (fArCClose[i] <= fSimCPrc + 0.05))
				|| (nCase == 1 && i > 15 + nBuytime && i > 320 && (fArCClose[i] <= fSimCPrc + 0.02))
				|| (i == 409)
				)
			{
				SellOption1();
				return;
			}
		}

		if (nPqty > 0)
		{

			if (
				((nCase == 4 && i > 10 + nBuytime) && (fArPClose[i] <= fSimPPrc + 0.05))				//풋손절4
				|| (nCase == 1 && i > 40 + nBuytime)													//풋손절1
				|| (nCase == 1 && i > 15 + nBuytime && i <= 320 && (fArPClose[i] <= fSimPPrc + 0.05))
				|| (nCase == 1 && i > 15 + nBuytime && i > 320 && (fArPClose[i] <= fSimPPrc + 0.02))
				|| (i == 409)
				)
			{
				SellOption2();
				return;
			}
		}

	}

	// 매수 ************************************************************************************************************************************ 매수
	if (i >= 50 && (i > nSelltime + 90 || i <= 90)) // 9:50분 이후 && 청산후 90분이상 지난후 또는 10:30분 이내
	{
		if (nCPch > 0 || nPPch > 0) //매수가능한 수량이 있는지 확인
		{
			if (
				lArKoForVol2[i] > -500														// 외국인 코스피 매도 규모 0억 이하
				&& lArKoSecVol2[i] > -500													// 기관 코스피 매도 규모 0억 이하
				&& (lArKoSecVol2[i] + lArKoForVol2[i]) > (long)((20.5 - i * 7.7 / 405)*i)	// 기관 코스피 매도 규모 5000억/405분 = 12.8억/분
				&& nPqty == 0
				)
			{
					nCCamnt += (nCPch / 5) / nPerBuy;
					nCase = 1, nBuytime = i;//케이스 및 해당시간 저장
					bCC = 0;//검색중지
					bCCact = 1;//CheckCondition() 실행
					bCCoption = 1;//콜옵션매수
					nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

					ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 콜매수1
					if (myfileRecording2.is_open())
					{
						myfileRecording2 << strArTime8415[i] << ", 콜매수1, " << CallCode[0] << ", " << fArCClose[i] << ", " << nCCamnt << "\n";
					}
					myfileRecording2.close();
			}

			//if (
			//	lArForVol5m[i] > 100							// 선물외인5m 100 초과
			//	&& lArForVol2[i] > 2000							// 선물외인 2000 초과
			//	&& lArKoForVol5m[i] + lArKoSecVol5m[i] > 5		// 코스피 외인+기관5m 5억 초과
			//	&& fArCClose[i] < fArCClose[0] * 1.5			// 시가대비 150% 이내일때
			//	&& nPqty == 0
			//	)
			//	 옵션만기일 전날 급변동시 이익 최대, 옵션만기일 다음날 추세장에서도 이익  ***********
			//{
			//	if (!(nCqty > 0 && fArCClose[i] < fpreCCprc - 0.02 && i < 320))
			//	{
			//		Request100_(CallCode[0], "2", fCho8 + 0.01, nCCamnt);
			//		nCCamnt += (nCPch / 7) / nPerBuy;
			//		nCase = 1, nBuytime = i;//케이스 및 해당시간 저장
			//		bCC = 0;//검색중지
			//		bCCact = 1;//CheckCondition() 실행
			//		bCCoption = 1;//콜옵션매수
			//		nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

			//		ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 콜매수1-2
			//		if (myfileRecording2.is_open())
			//		{
			//			myfileRecording2 << strArTime8415[i] << ", 콜매수1-2, " << CallCode[0] << ", " << fArCClose[i] << ", " << nCCamnt << "\n";
			//		}
			//		myfileRecording2.close();
			//	}
			//	else
			//	{
			//		nBuytime -= 40;
			//	}
			//}
			// 1000억, 2500계약, 지속적인 증가 확인 20분 단위
			//if (
			//	i > 60
			//	&& lArKoForVol2[i] > 1000
			//	&& lArForVol2[i] > 2000
			//	&& lArKoForVol2[i-20] > 700 && lArKoForVol2[i - 40] > 500 && lArKoForVol2[i - 60] > 300
			//	&& lArForVol2[i - 20] > 2000 && lArKoForVol2[i - 40] > 1500 && lArKoForVol2[i - 60] > 1000
			//	&& fArCClose[i] > fArCClose[i-35]*1.1
			//	)
			//{
			//	nCCamnt += (nCPch / 7) / nPerBuy;
			//	nCase = 1, nBuytime = i;//케이스 및 해당시간 저장
			//	bCC = 0;//검색중지
			//	bCCact = 1;//CheckCondition() 실행
			//	bCCoption = 1;//콜옵션매수
			//	nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

			//	ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 콜매수1-3
			//	if (myfileRecording2.is_open())
			//	{
			//		myfileRecording2 << strArTime8415[i] << ", 콜매수1-3, " << CallCode[0] << ", " << fArCClose[i] << ", " << nCCamnt << "\n";
			//	}
			//	myfileRecording2.close();
			//}

			else if (
				lArKoForVol2[i] < 500										// 외국인 코스피 매도 규모 0억 이하
				&& lArKoSecVol2[i] < 500										// 기관 코스피 매도 규모 0억 이하
				&& (lArKoSecVol2[i] + lArKoForVol2[i]) < (long)(-(20.5 - i * 7.7 / 405)*i)	// 기관 코스피 매도 규모 5000억/405분 = 12.8억/분
				&& nCqty == 0
				)
			{
					nCCamnt += (nPPch / 5) / nPerBuy;
					nCase = 1, nBuytime = i;//케이스 및 해당시간 저장
					bCC = 0;//검색중지
					bCCact = 1;//CheckCondition() 실행
					bCCoption = 0;//풋옵션매수
					nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

					ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 풋매수1
					if (myfileRecording2.is_open())
					{
						myfileRecording2 << strArTime8415[i] << ", 풋매수1, " << PutCode[0] << ", " << fArPClose[i] << ", " << nCCamnt << "\n";
					}
					myfileRecording2.close();
			}			

			//if (
			//	lArForVol5m[i] < -100
			//	&& lArForVol2[i] < -2000
			//	&& fArPClose[i] < fArPClose[0] * 1.5			// 시가대비 150% 이내일때
			//	&& lArKoForVol5m[i] + lArKoSecVol5m[i] < 5  // 외국인이 선물 대량 매도할경우 현물은 많이 안팔수있음 (-5가 아닌 이유)
			//	&& nCqty == 0
			//	)
			//{
			//	if (!(nPqty > 0 && fArPClose[i] < fpreCCprc - 0.02 && i < 320))
			//	{
			//		nCCamnt += (nPPch / 7) / nPerBuy;
			//		nCase = 1, nBuytime = i;//케이스 및 해당시간 저장
			//		bCC = 0;//검색중지
			//		bCCact = 1;//CheckCondition() 실행
			//		bCCoption = 0;//풋옵션매수
			//		nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

			//		ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 풋매수1-2
			//		if (myfileRecording2.is_open())
			//		{
			//			myfileRecording2 << strArTime8415[i] << ", 풋매수1-2, " << PutCode[0] << ", " << fArPClose[i] << ", " << nCCamnt << "\n";
			//		}
			//		myfileRecording2.close();
			//	}
			//	else
			//	{
			//		nBuytime -= 40;
			//	}
			//}

			//// -1000억, -2500계약, 지속적인 증가 확인 20분 단위
			//if (
			//	i > 60
			//	&& lArKoForVol2[i] < -1000
			//	&& lArForVol2[i] < -2500
			//	&& lArKoForVol2[i - 20] < -700 && lArKoForVol2[i - 40] < -500 && lArKoForVol2[i - 60] < -300
			//	&& lArForVol2[i - 20] < -2000 && lArKoForVol2[i - 40] < -1500 && lArKoForVol2[i - 60] < -1000
			//	&& fArPClose[i] > fArPClose[i - 35] * 1.1
			//	)
			//{
			//	nCCamnt += (nPPch / 7) / nPerBuy;
			//	nCase = 1, nBuytime = i;//케이스 및 해당시간 저장
			//	bCC = 0;//검색중지
			//	bCCact = 1;//CheckCondition() 실행
			//	bCCoption = 0;//풋옵션매수
			//	nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

			//	ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 풋매수1-3
			//	if (myfileRecording2.is_open())
			//	{
			//		myfileRecording2 << strArTime8415[i] << ", 풋매수1-3, " << PutCode[0] << ", " << fArPClose[i] << ", " << nCCamnt << "\n";
			//	}
			//	myfileRecording2.close();
			//}
		}

		// 선물은 매수하지만 현물 외인기관 매도로 가격이 하락할 경우 (선물 순매수량이 3000을 넘지 못하고 하락할경우)
		// 선물은 매도하지만 현물 외인기관 매수로 가격이 상승하는 경우 (선물 순매수량이 -3000을 넘지 못하고 상승할경우)
		if (i >= 70)
		{
			if (
				lArForVol2[i] > -2000							// 선물외인 -2000 미만이지만
				&& lArKoForVol5m[i] + lArKoSecVol5m[i] > 20		// 코스피 외인+기관 5m 20억 초과
				&& nPqty == 0
				)//지속적으로 살때(매수세가 지속 증가)...어떻게 표현???? 매입했는데 지속성이 유지안되면 청산					
			{
				int cnt1 = 0, cnt2 = 0;
				for (int k = 0; k < 30; ++k)
				{
					if (lArKoForVol2[i - k] - lArKoForVol2[i - k - 1] > 0) // 코스피외인 매수가 25회/30 초과 증가할때
						cnt1++;
					if (lArKoSecVol2[i - k] - lArKoSecVol2[i - k - 1] > 0) // 코스피기관 매수가 25회/30 초과 증가할때
						cnt2++;
				}
				if (cnt1 > 24 && cnt2 > 24 && nCase == 0)
				{
					nCCamnt += (nCPch / 50) / nPerBuy;
					bCC = 0;//검색중지
					bCCact = 1;//CheckCondition() 실행
					bCCoption = 1;//콜옵션매수
					nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

					ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 콜매수2
					if (myfileRecording2.is_open())
					{
						myfileRecording2 << strArTime8415[i] << ", 콜매수2, " << CallCode[0] << ", " << fArCClose[i] << ", " << nCCamnt << "\n";
					}
					myfileRecording2.close();
				}
			}
			if (
				lArForVol2[i] < 2000
				&& lArKoForVol5m[i] + lArKoSecVol5m[i] < -20
				&& nCqty == 0
				)
			{
				int cnt1 = 0, cnt2 = 0;
				for (int k = 0; k < 30; ++k)
				{
					if (lArKoForVol2[i - k] - lArKoForVol2[i - k - 1] < 0)
						cnt1++;
					if (lArKoSecVol2[i - k] - lArKoSecVol2[i - k - 1] < 0)
						cnt2++;
				}
				if (cnt1 > 24 && cnt2 > 24 && nCase == 0)
				{
					nCCamnt += (nPPch / 50) / nPerBuy;
					bCC = 0;//검색중지
					bCCact = 1;//CheckCondition() 실행
					bCCoption = 0;//풋옵션매수
					nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

					ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 풋매수2
					if (myfileRecording2.is_open())
					{
						myfileRecording2 << strArTime8415[i] << ", 풋매수2, " << PutCode[0] << ", " << fArPClose[i] << ", " << nCCamnt << "\n";
					}
					myfileRecording2.close();
				}
			}
		}
	}

	if (i >= 90 && i <= 300 && (nCPch > 0 || nPPch > 0)) // 손절하더라도 바로 실행할수 있도록 nSelltime 미적용, 10분후부터 가격감시 제가격으로 돌아오면 손절
	{
		BOOL temp = 1;
		for (int j = 0; j < 30; j++) // 최근 30분동안 30분최고최저차가 0.3 미만일경우(총60분)
		{
			temp = temp & (fArMax30m[i - j - 1] - fArMin30m[i - j - 1] < 0.3);
		}
		if (temp) // 30분최고최저차가 0.3 초과할때
		{
			if (fArMax30m[i] - fArMin30m[i] > 0.3 && nCase == 0)
			{

				if (fArClose[i] - fArClose[i - 1] > 0 && nPqty == 0)
				{
					if (nCqty == 0)	nBuytime = i;//케이스 및 해당시간 저장 처음 구매할때만 저장
					nCCamnt += (nCPch / 3) / nPerBuy;
					nCase = 4;
					bCC = 0;//검색중지
					bCCact = 1;//CheckCondition() 실행
					bCCoption = 1;//콜옵션매수
					nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

					ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 콜매수4
					if (myfileRecording2.is_open())
					{
						myfileRecording2 << strArTime8415[i] << ", 콜매수4, " << CallCode[0] << ", " << fArCClose[i] << ", " << nCCamnt << "\n";
					}
					myfileRecording2.close();

				}

				if (fArClose[i] - fArClose[i - 1] < 0 && nCqty == 0)
				{
					if (nPqty == 0)	nBuytime = i;//케이스 및 해당시간 저장 처음 구매할때만 저장
					nCCamnt += (nPPch / 3) / nPerBuy; //30% 매입
					nCase = 4;
					bCC = 0;//검색중지
					bCCact = 1;//CheckCondition() 실행
					bCCoption = 0;//풋옵션매수
					nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

					ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 풋매수4
					if (myfileRecording2.is_open())
					{
						myfileRecording2 << strArTime8415[i] << ", 풋매수4, " << PutCode[0] << ", " << fArPClose[i] << ", " << nCCamnt << "\n";
					}
					myfileRecording2.close();
				}
			}
		}
	}

	// 14시 20분 이후,, 급격한 가격변화가 생길경우 그 방향으로 매수 진행(반대방향으로 뒤바뀔경우 손절 필요)
	if (i >= 320 && fArCClose[i] + fArPClose[i] > fCallOpen + fPutOpen - 0.2 && i <= 380 && i > nSelltime + 90 && (nCPch > 0 || nPPch > 0))
	{
		int cnt1 = 0, cnt2 = 0;
		for (int k = 0; k < 10; ++k)
		{
			if (lArForVol5m[i - k] > 50)		// 선물 외인5m 7회/10회 초과 50이상
				cnt1++;
			if (lArForVol5m[i - k] < -50)
				cnt2++;
		}
		if (cnt1 > 7
			&& nPqty == 0 && nCase == 0)
		{
			nCCamnt += (nCPch / 20) / nPerBuy;
			nBuytime = i, nCase = 3;
			bCC = 0;//검색중지
			bCCact = 1;//CheckCondition() 실행
			bCCoption = 1;//콜옵션매수
			nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

			ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 콜매수3
			if (myfileRecording2.is_open())
			{
				myfileRecording2 << strArTime8415[i] << ", 콜매수3, " << CallCode[0] << ", " << fArCClose[i] << ", " << nCCamnt << "\n";
			}
			myfileRecording2.close();
		}

		if (cnt2 > 7
			&& nCqty == 0 && nCase == 0)
		{
			nCCamnt += (nPPch / 20) / nPerBuy;
			nBuytime = i, nCase = 3;
			bCC = 0;//검색중지
			bCCact = 1;//CheckCondition() 실행
			bCCoption = 0;//풋옵션매수
			nCCmin = nCurMin;//현재분저장, 현재분에만 매수실행

			ofstream myfileRecording2("RecordOrder2.csv", ios::app);								// 풋매수3
			if (myfileRecording2.is_open())
			{
				myfileRecording2 << strArTime8415[i] << ", 풋매수3, " << PutCode[0] << ", " << fArPClose[i] << ", " << nCCamnt << "\n";
			}
			myfileRecording2.close();
		}
	}

}

void CDlg_JEKYLL::CheckCondition() // - 매입프로세스 :  bCCact == 1 이고 nCCmin==nCurMin 일때 getdata 에서 매초 실행(구매후 bCCact = 0)
{
	if (bCCoption)//콜매입
	{
		if (fCCprc == fCho8)			Request100_(CallCode[0], "2", fCCprc, nCCamnt);
		else if (fCCprc > fCho8) 		Request100_(CallCode[0], "2", fCho8, nCCamnt);// 구매하려고 하는 가격보다 현재가격이 낮으면 현재가격으로 매입
	}
	else if (!bCCoption)//풋매입
	{
		if (fCCprc == fPho8)			Request100_(PutCode[0], "2", fCCprc, nCCamnt);
		else if (fCCprc > fPho8)		Request100_(PutCode[0], "2", fPho8, nCCamnt);
	}
	nBuytime = nCurMin;
	bCancel = TRUE;
	bCCact = 0;
	nCCamnt = 0;
}

void CDlg_JEKYLL::BuyOption() // 정해진 가격에 사고 팔기
{
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	CString temp1, temp2, temp4, temp5;
	GetDlgItemTextA(IDC_EDITPRC1, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITPRC2, temp2); // 얻을 이익
	GetDlgItemTextA(IDC_EDITPRC3, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITPRC4, temp5); // 매수간격 0.02

	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

	// ******************************************************** 매수가격 조정(보유옵션의 평균가로 조정) 소수점 두자리
	CString strPrc; 
	bOption ? GetDlgItemTextA(IDC_AVRPRC3F, strPrc) : GetDlgItemTextA(IDC_AVRPRC3, strPrc); // 콜옵션인지 풋옵션인지에 따라 가격 불러오기
	float fAvrPrc = (float)atof(strPrc);
	//if (fAvrPrc < fPrc && fAvrPrc > fPrc - 0.1) // 매수할 가격이 보유옵션보다 비싸거나 20틱 낮은가격보다 싸면 매수가격을 조정
	//{
	//	fAvrPrc = roundf(fAvrPrc * 100) / 100; // 보유옵션가격을 소수점 두자리 반올림
	//	strPrc.Format("%.2f", fAvrPrc);
	//	CEdit *pEdit1;
	//	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); 		
	//	pEdit1->SetWindowText(strPrc);
	//	pEdit1 = NULL;
	//}	

	int nPer = atoi(temp4);//매수 %
	int iter = 100 / nPer; //

	if (iter > 0)
	{
		// ******************************************************************************************************* 매수
		if (bPut && bOption && (fPho9 < fPrc + 0.03))//buy put **** 매수가격이 호가가격 3틱 근처로 접근했을때
		{
			//for (int i = iter; i > 0; --i)
			for (int i = 0; i < iter; ++i)
			{
				BuyPut(fPrc - ((float)i)*fGap, 10, nPer);
			}
			//BuyPut(fPrc, 10, nPer);
			//BuyPut(fPrc - fGap, 10, nPer);
			//BuyPut(fPrc - (fGap*3.5), 10, nPer);
			//Request100(PutCode[0], "2", temp1);
			bPut = FALSE;
		}
		if (!bPut && bOption && (fPho9 > (fPrc + fProfit)) && lLqdt == 0) //cancel buying put ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
		{
			Request600P();
			bPut = TRUE;
		}

		if (bCall && !bOption && (fCho9 < fPrc + 0.03)) // buy call
		{
			for (int i = 0; i < iter; ++i)
			{
				BuyCall(fPrc - ((float)i)*fGap, 10, nPer);
			}
			//BuyCall(fPrc, 10, nPer);
			//BuyCall(fPrc - fGap, 10, nPer);
			//BuyCall(fPrc - (fGap*3.5), 10, nPer);
			//Request100(CallCode[0], "2", temp1);
			bCall = FALSE;
		}
		if (!bCall && !bOption && (fCho9 > (fPrc + fProfit)) && lLqdt == 0) //cancel buying call
		{
			Request600C(); // 매수매도주문 모두 취소
			bCall = TRUE;
		}
	}

	// ******************************************************************************************************* 청산
	if ((lLqdt > 0) && (nSellOption == 1) ) //청산가능물량이 있고 가격옵션일 경우
	{
		if (lCallQty[0] > 0  && (fCho9 >= (fPrc + fProfit)))				//콜옵션보유수가 있을경우
		{
			if (lCallQty[0] < 10 && lLqdt == lCallQty[0] + lPutQty[0] && lCallQty[0] < lCho9)
			{
				Request100_(CallCode[0], "1", fPrc + fProfit, (int)lCallQty[0]);
				bCall = TRUE;
				OnBnClickedButtonprofit3();//kill
			}
			else if (lCallQty[0] < 50)
			{
				if (lCallQty[0] / 2 < lCho9)
					Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 2));
				if (lCallQty[0] < 20) Request10100(CallCode[0]);
			}
			else if (lCallQty[0] < 100)
			{
				if (lCallQty[0] / 4 < lCho9)
					Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 4));
			}
			else
			{
				if (lCallQty[0] / 6 < lCho9)
					Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 6));
			}
		}

		if (lPutQty[0] > 0 && (fPho9 >= (fPrc + fProfit)))					//풋옵션보유수가 있을경우
		{
			if (lPutQty[0] < 10 && lLqdt == lCallQty[0] + lPutQty[0] && lPutQty[0] < lPho9)
			{
				Request100_(PutCode[0], "1", fPrc + fProfit, (int)lPutQty[0]);
				bPut = TRUE;
				OnBnClickedButtonprofit3();//kill
			}
			else if (lPutQty[0] < 50)
			{
				if (lPutQty[0] / 2 < lPho9)
					Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 2));
				if (lPutQty[0] < 20) Request10100(PutCode[0]);
			}
			else if (lPutQty[0] < 100)
			{
				if (lPutQty[0] / 4 < lPho9)
					Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 4));
			}
			else
			{
				if (lPutQty[0] / 6 < lPho9)
					Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 6));
			}
		}
	}


	//if ((lLqdt > 0) && (nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
	//{
	//	if (lCallQty[0] > 0)		//콜옵션보유수가 있을경우
	//	{
	//		for (int i = 0; i < iter; ++i)
	//		{
	//			SellCall(fPrc + fProfit + ((float)i * 0.01), 10, nPer);
	//		}
	//		bCall = TRUE;
	//	}

	//	if (lPutQty[0] > 0)			//풋옵션보유수가 있을경우
	//	{
	//		for (int i = 0; i < iter; ++i)
	//		{
	//			SellPut(fPrc + fProfit + ((float)i * 0.01), 10, nPer);
	//		}
	//		bPut = TRUE;
	//	}
	//}
}


void CDlg_JEKYLL::BuyOption0() // 정해진 가격에 사고 팔기 + 매수물량 감추기
{
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();

	BOOL bOption1 = ((CButton*)GetDlgItem(IDC_CHECKOPTION1))->GetCheck();
	BOOL bOption2 = ((CButton*)GetDlgItem(IDC_CHECKOPTION2))->GetCheck();
	BOOL bOption3 = ((CButton*)GetDlgItem(IDC_CHECKOPTION3))->GetCheck();
	CString temp1, temp2, temp4, temp5, str;
	GetDlgItemTextA(IDC_EDITPRC1, temp1); // 매수가격 fPrc
	GetDlgItemTextA(IDC_EDITPRC2, temp2); // 얻을 이익 fProfit
	GetDlgItemTextA(IDC_EDITPRC3, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITPRC4, temp5); // 매수간격 0.02 fGap

	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

	GetDlgItemTextA(IDC_EDITPRC6, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITPRC7, temp2); // 얻을 이익
	//GetDlgItemTextA(IDC_EDITPRC8, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITPRC9, temp5); // 매수간격 0.02

	float fPrc2 = (float)atof(temp1), fProfit2 = (float)atof(temp2), fGap2 = (float)atof(temp5);

	GetDlgItemTextA(IDC_EDITPRC10, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITPRC11, temp2); // 얻을 이익
	//GetDlgItemTextA(IDC_EDITPRC12, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITPRC13, temp5); // 매수간격 0.02

	float fPrc3 = (float)atof(temp1), fProfit3 = (float)atof(temp2), fGap3 = (float)atof(temp5);


    // **************************************************************************************************************** 각 옵션의 현재 수익률 표시
    float fTotalProfit = 0.0f, fProfit0 = 0.0f, fProfit01 = 0.0f, fProfit02 = 0.0f;
    if (bOption)
    {
        if (fPutAvrPrc[0] != 0) {
            fProfit0 = (1.0f - (fPutAvrPrc[0] / fPho9)) * 100.0f;
            str.Format("%.1f", fProfit0);   str = str + " %";
            m_curvalue2.SetWindowTextA(str);
        }

        if (fPutAvrPrc[1] != 0) {
            fProfit01 = (1.0f - (fPutAvrPrc[1] / fP2ho9)) * 100.0f;
            str.Format("%.1f", fProfit01);  str = str + " %";
            m_curvalue21.SetWindowTextA(str);
        }

        if (fPutAvrPrc[2] != 0) {
            fProfit02 = (1.0f - (fPutAvrPrc[2] / fP3ho9)) * 100.0f;
            str.Format("%.1f", fProfit02);  str = str + " %";
            m_curvalue22.SetWindowTextA(str);
        }
        if (lPutQty[0] + lPutQty[1] + lPutQty[2] != 0) {
            fTotalProfit = (fProfit0 * lPutQty[0] + fProfit01 * lPutQty[1] + fProfit02 * lPutQty[2]) / (lPutQty[0] + lPutQty[1] + lPutQty[2]);
        }
    }
    else
    {
        if (fCallAvrPrc[0] != 0) {
            fProfit0 = (1.0f - (fCallAvrPrc[0] / fCho9)) * 100.0f;
            str.Format("%.1f", fProfit0);   str = str + " %";
            m_curvalue2.SetWindowTextA(str);
        }

        if (fCallAvrPrc[1] != 0) {
            fProfit01 = (1.0f - (fCallAvrPrc[1] / fC2ho9)) * 100.0f;
            str.Format("%.1f", fProfit01);  str = str + " %";
            m_curvalue21.SetWindowTextA(str);
        }

        if (fCallAvrPrc[2] != 0) {
            fProfit02 = (1.0f - (fCallAvrPrc[2] / fC3ho9)) * 100.0f;
            str.Format("%.1f", fProfit02);  str = str + " %";
            m_curvalue22.SetWindowTextA(str);
        }
        if (lCallQty[0] + lCallQty[1] + lCallQty[2] != 0) {
            fTotalProfit = (fProfit0 * lCallQty[0] + fProfit01 * lCallQty[1] + fProfit02 * lCallQty[2]) / (lCallQty[0] + lCallQty[1] + lCallQty[2]);
        }
    }


	//str.Format("%.2f", fArCClose[nCurMin - 1]);
	//m_tst.SetWindowTextA(CallCode[1]);
	//m_tst.SetWindowTextA(

	// ******************************************************** 매수가격 조정(보유옵션의 평균가로 조정) 소수점 두자리
	//CString strPrc;
	//bOption ? GetDlgItemTextA(IDC_AVRPRC3F, strPrc) : GetDlgItemTextA(IDC_AVRPRC3, strPrc); // 콜옵션인지 풋옵션인지에 따라 가격 불러오기
	//float fAvrPrc = atof(strPrc);
	//if (fAvrPrc < fPrc && fAvrPrc > fPrc - 0.1) // 매수할 가격이 보유옵션보다 비싸거나 20틱 낮은가격보다 싸면 매수가격을 조정
	//{
	//	fAvrPrc = roundf(fAvrPrc * 100) / 100; // 보유옵션가격을 소수점 두자리 반올림
	//	strPrc.Format("%.2f", fAvrPrc);
	//	CEdit *pEdit1;
	//	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); 		
	//	pEdit1->SetWindowText(strPrc);
	//	pEdit1 = NULL;
	//}	

	int nPer = atoi(temp4);//매수 %
	int iter = 100 / nPer; //

	if (iter > 0)
	{
		if (gIter[0] > 0)
		{
			// ******************************************************************************************************* 풋옵션 매수1
			if (bPut && bOption && bOption1 && (fPho9 < fPrc - ((float)iter - (float)gIter[0])*fGap))//buy put
			{
				BuyPutR(PutCode[0], fPrc - ((float)iter - (float)gIter[0])*fGap, (int)(100/gIter[0]));
				gIter[0] -= 1;
			}
			//if (bOption && (fPho9 > (fPrc + fProfit))) //cancel buying put ** 매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600P(); // 풋 매수매도주문 모두 취소
			//	bPut = TRUE;
			//}

			// ******************************************************************************************************* 콜옵션 매수1
			if (bCall && !bOption && bOption1 && (fCho9 < fPrc - ((float)iter - (float)gIter[0])*fGap))// buy call
			{
				BuyCallR(CallCode[0], fPrc - ((float)iter - (float)gIter[0])*fGap, (int)(100 / gIter[0]));
				gIter[0] -= 1;
			}
			//if (!bOption && (fCho9 > (fPrc + fProfit))) //cancel buying call ** 매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600C(); // 콜 매수매도주문 모두 취소
			//	bCall = TRUE;
			//}

			if (bSetPrice && ((iter - gIter[0]) == 1)) // 세개의 구매가격중에 첫번째 높은 가격으로 구매시작 1회 한후 두번째, 세번째 가격도 구매 개시
			{
				CString str1, str2, str3;
				//str1 = m_lst2105.GetItemText(1, 1); //0부터 시작
				str2 = m_lst2105_.GetItemText(1, 1); //0부터 시작
				str3 = m_lst2105__.GetItemText(1, 1); //0부터 시작

				CEdit *pEdit1;
				//pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(str1);
				pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(str2);
				pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(str3);

				//((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);
				pEdit1 = NULL;
				bSetPrice = FALSE;
			}
		}

		if (!bSetPrice && gIter[1] > 0)
		{
			// ******************************************************************************************************* 풋옵션 매수2
			if (bPut && bOption && bOption2 && (fP2ho9 < fPrc2 - ((float)iter - (float)gIter[1])*fGap2))//buy put
			{
				BuyPutR(PutCode[1], fPrc2 - ((float)iter - (float)gIter[1])*fGap2, (int)(100 / gIter[1]));
				gIter[1] -= 1;
			}
			//if (bOption && (fP2ho9 > (fPrc2 + fProfit2)) ) //cancel buying put ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600P(); // 매수매도주문 모두 취소
			//	bPut = TRUE;
			//}

			// ******************************************************************************************************* 콜옵션 매수2
			if (bCall && !bOption && bOption2 && (fC2ho9 < fPrc2 - ((float)iter - (float)gIter[1])*fGap2))// buy call
			{
				BuyCallR(CallCode[1], fPrc2 - ((float)iter - (float)gIter[1])*fGap2, (int)(100 / gIter[1]));
				gIter[1] -= 1;
			}
			//if (!bOption && (fC2ho9 > (fPrc2 + fProfit2)) ) //cancel buying call ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600C(); // 매수매도주문 모두 취소
			//	bCall = TRUE;
			//}			
		}


		if (!bSetPrice && gIter[2] > 0)
		{
			// ******************************************************************************************************* 풋옵션 매수3
			if (bPut && bOption && bOption3 && (fP3ho9 < fPrc3 - ((float)iter - (float)gIter[2])*fGap3))//buy put
			{
				BuyPutR(PutCode[2], fPrc3 - ((float)iter - (float)gIter[2])*fGap3, (int)(100 / gIter[2]));
				gIter[2] -= 1;
			}

			//if (bOption && (fP3ho9 > (fPrc3 + fProfit3)) ) //cancel buying put ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600P(); // 매수매도주문 모두 취소
			//	bPut = TRUE;
			//}

			// ******************************************************************************************************* 콜옵션 매수3
			if (bCall && !bOption && bOption3 && (fC3ho9 < fPrc3 - ((float)iter - (float)gIter[2])*fGap3))// buy call
			{
				BuyCallR(CallCode[2], fPrc3 - ((float)iter - (float)gIter[2])*fGap3, (int)(100 / gIter[2]));
				gIter[2] -= 1;
			}

			//if (!bOption && (fC3ho9 > (fPrc3 + fProfit3)) ) //cancel buying call ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600C(); // 매수매도주문 모두 취소
			//	bCall = TRUE;
			//}
		}

		//if (gIter[0] == 0 && gIter[1] == 0 && gIter[2] == 0) // 구매가 모두 끝남 (추가고려 : 세개 가격으로 분할구매함으로써 남게되는 추가구매 가능금액에 대한 액션 필요)
		//{			
		//	if (lLqdt == 0) // 구매도 다 끝나고 청산물량이 없을때, 다 팔렸을때,,
		//	{
		//		for (int i = 0; i < 3; i++)
		//		{
		//			gIter[i] = iter; //
		//		}
		//		nSellOption = 1;
		//		bSetPrice = TRUE;
		//		bCall = TRUE;
		//		bPut = TRUE;
		//	}
		//}

	}

	str.Format("%d, %d, %d", gIter[0], gIter[1], gIter[2]);
	//m_tst.SetWindowTextA(CallCode[1]);
	m_tst.SetWindowTextA(str);

	// ******************************************************************************************************* 콜청산
    if ((nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
    {
        if (lCallQty[0] > 0 && (fCho9 >= (fPrc + fProfit)))				//콜옵션보유수가 있을경우-1
        {
            if ((lCallQty[0] < 10 && lCallQty[0] < lCho9) || (lCallQty[0] < lCho9)) // 
            {
                Request100_(CallCode[0], "1", fPrc + fProfit, (int)lCallQty[0]);
                if (lCallQty[0] == 0 && lCallQty[1] == 0 && lCallQty[2] == 0)
                {
                    bCall = TRUE;
                    Request2400();
                    for (int i = 0; i < 3; i++)
                    {
                        gIter[i] = iter; //
                    }
                    bSetPrice = TRUE;
                    //OnBnClickedButtonprofit3();//kill
                    SetPrice(); //기본 per = 50 % 적용
                }
            }
            else if (lCallQty[0] < 40)
            {
                if (lCallQty[0] / 2 < lCho9)
                    Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 2));
            }
            else if (lCallQty[0] < 80)
            {
                if (lCallQty[0] / 3 < lCho9)
                    Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 3));
            }
            else if (lCallQty[0] < 120)
            {
                if (lCallQty[0] / 5 < lCho9)
                    Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 5));
            }
            else if (lCallQty[0] < 200)
            {
                if (lCallQty[0] / 8 < lCho9)
                    Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 8));
            }
            else
            {
                if (lCallQty[0] / 12 < lCho9)
                    Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 12));
            }
        }

        if (lCallQty[1] > 0 && (fC2ho9 >= (fPrc2 + fProfit2)))				//콜옵션보유수가 있을경우2
        {
            if ((lCallQty[1] < 10 && lCallQty[1] < lC2ho9) || (lCallQty[1] < lC2ho9))
            {
                Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)lCallQty[1]);
                if (lCallQty[0] == 0 && lCallQty[1] == 0 && lCallQty[2] == 0)
                {
                    bCall = TRUE;
                    Request2400();
                    for (int i = 0; i < 3; i++)
                    {
                        gIter[i] = iter; //
                    }
                    bSetPrice = TRUE;
                    //OnBnClickedButtonprofit3();//kill
                    SetPrice();//기본 per = 15 % 적용
                }
            }
            else if (lCallQty[1] < 40)
            {
                if (lCallQty[1] / 2 < lC2ho9)
                    Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 2));
            }
            else if (lCallQty[1] < 80)
            {
                if (lCallQty[1] / 3 < lC2ho9)
                    Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 3));
            }
            else if (lCallQty[1] < 120)
            {
                if (lCallQty[1] / 5 < lC2ho9)
                    Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 5));
            }
            else if (lCallQty[1] < 200)
            {
                if (lCallQty[1] / 8 < lC2ho9)
                    Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 8));
            }
            else
            {
                if (lCallQty[1] / 12 < lC2ho9)
                    Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 12));
            }
        }

        if (lCallQty[2] > 0 && (fC3ho9 >= (fPrc3 + fProfit3)))				//콜옵션보유수가 있을경우3
        {
            if ((lCallQty[2] < 10 && lCallQty[2] < lC3ho9) || (lCallQty[2] < lC3ho9))
            {
                Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)lCallQty[2]);
                if (lCallQty[0] == 0 && lCallQty[1] == 0 && lCallQty[2] == 0)
                {
                    bCall = TRUE;
                    Request2400();
                    for (int i = 0; i < 3; i++)
                    {
                        gIter[i] = iter; //
                    }
                    bSetPrice = TRUE;
                    //OnBnClickedButtonprofit3();//kill
                    SetPrice();//기본 per = 15 % 적용
                }
            }
            else if (lCallQty[2] < 40)
            {
                if (lCallQty[2] / 2 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 2));
            }
            else if (lCallQty[2] < 80)
            {
                if (lCallQty[2] / 3 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 3));
            }
            else if (lCallQty[2] < 120)
            {
                if (lCallQty[2] / 5 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 5));
            }
            else if (lCallQty[2] < 200)
            {
                if (lCallQty[2] / 8 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 8));
            }
            else
            {
                if (lCallQty[2] / 12 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 12));
            }
        }

        // ******************************************************************************************************* 풋청산

        if (lPutQty[0] > 0 && (fPho9 >= (fPrc + fProfit)))					//풋옵션보유수가 있을경우1
        {
            if ((lPutQty[0] < 10 && lPutQty[0] < lPho9) || (lPutQty[0] < lPho9))
            {
                Request100_(PutCode[0], "1", fPrc + fProfit, (int)lPutQty[0]);
                if (lPutQty[0] == 0 && lPutQty[1] == 0 && lPutQty[2] == 0)
                {
                    bPut = TRUE;
                    Request2400();
                    for (int i = 0; i < 3; i++)
                    {
                        gIter[i] = iter; //
                    }
                    bSetPrice = TRUE;
                    //OnBnClickedButtonprofit3();//kill
                    SetPrice();
                }
            }
            else if (lPutQty[0] < 40)
            {
                if (lPutQty[0] / 2 < lPho9)
                    Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 2));
            }
            else if (lPutQty[0] < 80)
            {
                if (lPutQty[0] / 3 < lPho9)
                    Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 3));
            }
            else if (lPutQty[0] < 120)
            {
                if (lPutQty[0] / 5 < lPho9)
                    Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 5));
            }
            else if (lPutQty[0] < 200)
            {
                if (lPutQty[0] / 8 < lPho9)
                    Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 8));
            }
            else
            {
                if (lPutQty[0] / 12 < lPho9)
                    Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 12));
            }
        }

        if (lPutQty[1] > 0 && (fP2ho9 >= (fPrc2 + fProfit2)))					//풋옵션보유수가 있을경우2
        {
            if ((lPutQty[1] < 10 && lPutQty[1] < lP2ho9) || (lPutQty[1] < lP2ho9))
            {
                Request100_(PutCode[1], "1", fPrc2 + fProfit2, (int)lPutQty[1]);
                if (lPutQty[0] == 0 && lPutQty[1] == 0 && lPutQty[2] == 0)
                {
                    bPut = TRUE;
                    Request2400();
                    for (int i = 0; i < 3; i++)
                    {
                        gIter[i] = iter; //
                    }
                    bSetPrice = TRUE;
                    //OnBnClickedButtonprofit3();//kill
                    SetPrice();
                }
            }
            else if (lPutQty[1] < 40)
            {
                if (lPutQty[1] / 2 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 2));
            }
            else if (lPutQty[1] < 80)
            {
                if (lPutQty[1] / 3 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 3));
            }
            else if (lPutQty[1] < 120)
            {
                if (lPutQty[1] / 5 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 5));
            }
            else if (lPutQty[1] < 200)
            {
                if (lPutQty[1] / 8 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 8));
            }
            else
            {
                if (lPutQty[1] / 12 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 12));
            }
        }

        if (lPutQty[2] > 0 && (fP3ho9 >= (fPrc3 + fProfit3)))					//풋옵션보유수가 있을경우3
        {
            if ((lPutQty[2] < 10 && lPutQty[2] < lP3ho9) || (lPutQty[2] < lP3ho9))
            {
                Request100_(PutCode[2], "1", fPrc3 + fProfit3, (int)lPutQty[2]);
                if (lPutQty[0] == 0 && lPutQty[1] == 0 && lPutQty[2] == 0)
                {
                    bPut = TRUE;
                    Request2400();
                    for (int i = 0; i < 3; i++)
                    {
                        gIter[i] = iter; //
                    }
                    bSetPrice = TRUE;
                    //OnBnClickedButtonprofit3();//kill
                    SetPrice();
                }
            }
            else if (lPutQty[2] < 40)
            {
                if (lPutQty[2] / 2 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 2));
            }
            else if (lPutQty[2] < 80)
            {
                if (lPutQty[2] / 3 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 3));
            }
            else if (lPutQty[2] < 120)
            {
                if (lPutQty[2] / 5 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 5));
            }
            else if (lPutQty[2] < 200)
            {
                if (lPutQty[2] / 8 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 8));
            }
            else
            {
                if (lPutQty[2] / 12 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 12));
            }
        }

    }

	//if ((lLqdt > 0) && (nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
	//{
	//	if (lCallQty[0] > 0)		//콜옵션보유수가 있을경우
	//	{
	//		for (int i = 0; i < iter; ++i)
	//		{
	//			SellCall(fPrc + fProfit + ((float)i * 0.01), 10, nPer);
	//		}
	//		bCall = TRUE;
	//	}

	//	if (lPutQty[0] > 0)			//풋옵션보유수가 있을경우
	//	{
	//		for (int i = 0; i < iter; ++i)
	//		{
	//			SellPut(fPrc + fProfit + ((float)i * 0.01), 10, nPer);
	//		}
	//		bPut = TRUE;
	//	}
	//}
}


void CDlg_JEKYLL::BuyOption7(int i) // 정해진 가격에 사고 팔기 + 매수물량 감추기(적극매수-매수가를 높이면서 매입)
{
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	CString temp1, temp2, temp4, temp5, str;
	GetDlgItemTextA(IDC_EDITPRC1, temp1); // 매수가격 fPrc
	GetDlgItemTextA(IDC_EDITPRC2, temp2); // 얻을 이익 fProfit
	GetDlgItemTextA(IDC_EDITPRC3, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITPRC4, temp5); // 매수간격 0.02 fGap

	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

	GetDlgItemTextA(IDC_EDITPRC6, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITPRC7, temp2); // 얻을 이익
	//GetDlgItemTextA(IDC_EDITPRC8, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITPRC9, temp5); // 매수간격 0.02

	float fPrc2 = (float)atof(temp1), fProfit2 = (float)atof(temp2), fGap2 = (float)atof(temp5);

	GetDlgItemTextA(IDC_EDITPRC10, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITPRC11, temp2); // 얻을 이익
	//GetDlgItemTextA(IDC_EDITPRC12, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITPRC13, temp5); // 매수간격 0.02

	float fPrc3 = (float)atof(temp1), fProfit3 = (float)atof(temp2), fGap3 = (float)atof(temp5);


	//str.Format("%.2f", fArCClose[i]);
	//m_tst.SetWindowTextA(CallCode[1]);
	//m_tst.SetWindowTextA(

	// ******************************************************** 매수가격 조정(보유옵션의 평균가로 조정) 소수점 두자리
	//CString strPrc;
	//bOption ? GetDlgItemTextA(IDC_AVRPRC3F, strPrc) : GetDlgItemTextA(IDC_AVRPRC3, strPrc); // 콜옵션인지 풋옵션인지에 따라 가격 불러오기
	//float fAvrPrc = atof(strPrc);
	//if (fAvrPrc < fPrc && fAvrPrc > fPrc - 0.1) // 매수할 가격이 보유옵션보다 비싸거나 20틱 낮은가격보다 싸면 매수가격을 조정
	//{
	//	fAvrPrc = roundf(fAvrPrc * 100) / 100; // 보유옵션가격을 소수점 두자리 반올림
	//	strPrc.Format("%.2f", fAvrPrc);
	//	CEdit *pEdit1;
	//	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); 		
	//	pEdit1->SetWindowText(strPrc);
	//	pEdit1 = NULL;
	//}	

	int nPer = atoi(temp4);//매수 %
	int iter = 100 / nPer; //

	if (iter > 0)
	{
		if (gIter[0] > 0)
		{
			// ******************************************************************************************************* 매수1(풋/콜)
			if (
				lArKoForVol2[i] < 500										// 외국인 코스피 매도 규모 500억 이하
				&& lArKoSecVol2[i] < 500										// 기관 코스피 매도 규모 500억 이하
				&& (lArKoSecVol2[i] + lArKoForVol2[i]) < (long)(-(20.5 - (i) * 7.7 / 405)*(i))	// 기관 코스피 매도 규모 5000억/405분 = 12.8억/분, 8000억 = 20.5억/분
				&& lCallQty[0] == 0)
			{
				if (bPut && bOption && (fPho9 < fPrc - ((float)iter - (float)gIter[0])*fGap))//buy put
				{
					BuyPut(PutCode[0], fPrc - ((float)iter - (float)gIter[0])*fGap, 1, (int)(100 / gIter[0]));
					//BuyPut(PutCode[0], fPho8, 1, (int)(100 / gIter[0]));
					gIter[0] -= 1;
				}
			}
			//if (bOption && (fPho9 > (fPrc + fProfit))) //cancel buying put ** 매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600P(); // 풋 매수매도주문 모두 취소
			//	bPut = TRUE;
			//}
			if (
				lArKoForVol2[i] > -500										// 외국인 코스피 매도 규모 0억 이하
				&& lArKoSecVol2[i] > -500										// 기관 코스피 매도 규모 0억 이하
				&& (lArKoSecVol2[i] + lArKoForVol2[i]) > (long)((20.5 - (i) * 7.7 / 405)*(i))	// 기관 코스피 매도 규모 5000억/405분 = 12.8억/분, 8000억 = 20.5억/분
				&& lPutQty[0] == 0)
			{
				if (bCall && !bOption && (fCho9 < fPrc - ((float)iter - (float)gIter[0])*fGap))// buy call
				{
					BuyCall(CallCode[0], fPrc - ((float)iter - (float)gIter[0])*fGap, 1, (int)(100 / gIter[0]));
					//BuyCall(CallCode[0], fCho8, 1, (int)(100 / gIter[0]));
					gIter[0] -= 1;
				}
			}
			//if (!bOption && (fCho9 > (fPrc + fProfit))) //cancel buying call ** 매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600C(); // 콜 매수매도주문 모두 취소
			//	bCall = TRUE;
			//}

			if (bSetPrice && ((iter - gIter[0]) == 1)) // 세개의 구매가격중에 첫번째 높은 가격으로 구매시작 1회 한후 두번째, 세번째 가격도 구매 개시
			{
				CString str1, str2, str3;
				//str1 = m_lst2105.GetItemText(1, 1); //0부터 시작
				str2 = m_lst2105_.GetItemText(1, 1); //0부터 시작
				str3 = m_lst2105__.GetItemText(1, 1); //0부터 시작

				CEdit *pEdit1;
				//pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(str1);
				pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(str2);
				pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(str3);

				//((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);
				pEdit1 = NULL;
				bSetPrice = FALSE;
			}
		}

		if (!bSetPrice && gIter[1] > 0)
		{
			// ******************************************************************************************************* 매수2(풋/콜)
			if (bPut && bOption && (fP2ho9 < fPrc2 - ((float)iter - (float)gIter[1])*fGap2))//buy put
			{
				BuyPut(PutCode[1], fPrc2 - ((float)iter - (float)gIter[1])*fGap2, 1, (int)(100 / gIter[1]));
				//BuyPut(PutCode[1], fP2ho8, 1, (int)(100 / gIter[1]));
				gIter[1] -= 1;
			}
			//if (bOption && (fP2ho9 > (fPrc2 + fProfit2)) ) //cancel buying put ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600P(); // 매수매도주문 모두 취소
			//	bPut = TRUE;
			//}

			if (bCall && !bOption && (fC2ho9 < fPrc2 - ((float)iter - (float)gIter[1])*fGap2))// buy call
			{
				BuyCall(CallCode[1], fPrc2 - ((float)iter - (float)gIter[1])*fGap2, 1, (int)(100 / gIter[1]));
				//BuyCall(CallCode[1], fC2ho8, 1, (int)(100 / gIter[1]));
				gIter[1] -= 1;
			}
			//if (!bOption && (fC2ho9 > (fPrc2 + fProfit2)) ) //cancel buying call ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600C(); // 매수매도주문 모두 취소
			//	bCall = TRUE;
			//}			
		}


		if (!bSetPrice && gIter[2] > 0)
		{
			// ******************************************************************************************************* 매수3(풋/콜)
			if (bPut && bOption && (fP3ho9 < fPrc3 - ((float)iter - (float)gIter[2])*fGap3))//buy put
			{
				BuyPut(PutCode[2], fPrc3 - ((float)iter - (float)gIter[2])*fGap3, 1, (int)(100 / gIter[2]));
				//BuyPut(PutCode[2], fP3ho8, 1, (int)(100 / gIter[2]));
				gIter[2] -= 1;
			}

			//if (bOption && (fP3ho9 > (fPrc3 + fProfit3)) ) //cancel buying put ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600P(); // 매수매도주문 모두 취소
			//	bPut = TRUE;
			//}

			if (bCall && !bOption && (fC3ho9 < fPrc3 - ((float)iter - (float)gIter[2])*fGap3))// buy call
			{
				BuyCall(CallCode[2], fPrc3 - ((float)iter - (float)gIter[2])*fGap3, 1, (int)(100 / gIter[2]));
				//BuyCall(CallCode[2], fC3ho8, 1, (int)(100 / gIter[2]));
				gIter[2] -= 1;
			}

			//if (!bOption && (fC3ho9 > (fPrc3 + fProfit3)) ) //cancel buying call ** 청산가능수량이 없을경우/매수가격과 이득합이 호가보다 작을때/
			//{
			//	Request600C(); // 매수매도주문 모두 취소
			//	bCall = TRUE;
			//}
		}

		//if (gIter[0] == 0 && gIter[1] == 0 && gIter[2] == 0) // 구매가 모두 끝남 (추가고려 : 세개 가격으로 분할구매함으로써 남게되는 추가구매 가능금액에 대한 액션 필요)
		//{			
		//	if (lLqdt == 0) // 구매도 다 끝나고 청산물량이 없을때, 다 팔렸을때,,
		//	{
		//		for (int i = 0; i < 3; i++)
		//		{
		//			gIter[i] = iter; //
		//		}
		//		nSellOption = 1;
		//		bSetPrice = TRUE;
		//		bCall = TRUE;
		//		bPut = TRUE;
		//	}
		//}

	}

	str.Format("%d, %d, %d", gIter[0], gIter[1], gIter[2]);
	//m_tst.SetWindowTextA(CallCode[1]);
	m_tst.SetWindowTextA(str);

	// ******************************************************************************************************* 콜청산
	if ((nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
	{
		if (lCallQty[0] > 0 && (fCho9 >= (fPrc + fProfit)))				//콜옵션보유수가 있을경우-1
		{
			if ((lCallQty[0] < 10 && lCallQty[0] < lCho9) || (lCallQty[0] < lCho9 * 0.9)) // 매도호가 1 수량대비 보유수량이 90%이면 전부 매도
			{
				Request100_(CallCode[0], "1", fPrc + fProfit, (int)lCallQty[0]);
				if (lCallQty[0] == 0 && lCallQty[1] == 0 && lCallQty[2] == 0)
				{
					bCall = TRUE;
					Request2400();
					for (int i = 0; i < 3; i++)
					{
						gIter[i] = iter; //
					}
					bSetPrice = TRUE;
					//OnBnClickedButtonprofit3();//kill
					SetPrice(); //기본 per = 50 % 적용
				}
			}
			else if (lCallQty[0] < 40)
			{
                if (lCallQty[0] / 2 < lCho9)
					Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 2));
			}
			else if (lCallQty[0] < 80)
			{
                if (lCallQty[0] / 3 < lCho9)
					Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 3));
			}
			else if (lCallQty[0] < 120)
			{
                if (lCallQty[0] / 5 < lCho9)
					Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 5));
			}
			else if (lCallQty[0] < 200)
			{
                if (lCallQty[0] / 8 < lCho9)
					Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 8));
			}
			else
			{
               if (lCallQty[0] / 12 < lCho9)
					Request100_(CallCode[0], "1", fPrc + fProfit, (int)(lCallQty[0] / 12));
			}
		}

		if (lCallQty[1] > 0 && (fC2ho9 >= (fPrc2 + fProfit2)))				//콜옵션보유수가 있을경우2
		{
			if ((lCallQty[1] < 10 && lCallQty[1] < lC2ho9) || (lCallQty[1] < lC2ho9 * 0.9))
			{
				Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)lCallQty[1]);
				if (lCallQty[0] == 0 && lCallQty[1] == 0 && lCallQty[2] == 0)
				{
					bCall = TRUE;
					Request2400();
					for (int i = 0; i < 3; i++)
					{
						gIter[i] = iter; //
					}
					bSetPrice = TRUE;
					//OnBnClickedButtonprofit3();//kill
					SetPrice();//기본 per = 15 % 적용
				}
			}
			else if (lCallQty[1] < 40)
			{
                if (lCallQty[1] / 2 < lC2ho9)
					Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 2));
			}
			else if (lCallQty[1] < 80)
			{
                if (lCallQty[1] / 3 < lC2ho9)
					Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 3));
			}
			else if (lCallQty[1] < 120)
			{
                if (lCallQty[1] / 5 < lC2ho9)
					Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 5));
			}
			else if (lCallQty[1] < 200)
			{
               if (lCallQty[1] / 8 < lC2ho9)
					Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 8));
			}
			else
			{
                if (lCallQty[1] / 12 < lC2ho9)
					Request100_(CallCode[1], "1", fPrc2 + fProfit2, (int)(lCallQty[1] / 12));
			}
		}

		if (lCallQty[2] > 0 && (fC3ho9 >= (fPrc3 + fProfit3)))				//콜옵션보유수가 있을경우3
		{
			if ((lCallQty[2] < 10 && lCallQty[2] < lC3ho9) || (lCallQty[2] < lC3ho9 * 0.75))
			{
				Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)lCallQty[2]);
				if (lCallQty[0] == 0 && lCallQty[1] == 0 && lCallQty[2] == 0)
				{
					bCall = TRUE;
					Request2400();
					for (int i = 0; i < 3; i++)
					{
						gIter[i] = iter; //
					}
					bSetPrice = TRUE;
					//OnBnClickedButtonprofit3();//kill
					SetPrice();//기본 per = 15 % 적용
				}
			}
            else if (lCallQty[2] < 40)
            {
                if (lCallQty[2] / 2 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 2));
            }
            else if (lCallQty[2] < 80)
            {
                if (lCallQty[2] / 3 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 3));
            }
            else if (lCallQty[2] < 120)
            {
                if (lCallQty[2] / 5 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 5));
            }
            else if (lCallQty[2] < 200)
            {
                if (lCallQty[2] / 8 < lC3ho9)
                    Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 8));
            }
            else
            {
                if (lCallQty[2] / 12 < lC3ho9)
					Request100_(CallCode[2], "1", fPrc3 + fProfit3, (int)(lCallQty[2] / 12));
			}
		}

		// ******************************************************************************************************* 풋청산

		if (lPutQty[0] > 0 && (fPho9 >= (fPrc + fProfit)))					//풋옵션보유수가 있을경우1
		{
			if ((lPutQty[0] < 10 && lPutQty[0] < lPho9) || (lPutQty[0] < lPho9 * 0.9))
			{
				Request100_(PutCode[0], "1", fPrc + fProfit, (int)lPutQty[0]);
				if (lPutQty[0] == 0 && lPutQty[1] == 0 && lPutQty[2] == 0)
				{
					bPut = TRUE;
					Request2400();
					for (int i = 0; i < 3; i++)
					{
						gIter[i] = iter; //
					}
					bSetPrice = TRUE;
					//OnBnClickedButtonprofit3();//kill
					SetPrice();
				}
			}			
			else if (lPutQty[0] < 40)
			{
                if (lPutQty[0] / 2 < lPho9)
					Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 2));
			}
			else if (lPutQty[0] < 80)
			{
               if (lPutQty[0] / 3 < lPho9)
                    Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 3));
            }
            else if (lPutQty[0] < 120)
            {
               if (lPutQty[0] / 5 < lPho9)
                    Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 5));
            }
            else if (lPutQty[0] < 200)
            {
                if (lPutQty[0] / 8 < lPho9)
                    Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 8));
            }
            else
            {
                if (lPutQty[0] / 12 < lPho9)
					Request100_(PutCode[0], "1", fPrc + fProfit, (int)(lPutQty[0] / 12));
			}
		}

		if (lPutQty[1] > 0 && (fP2ho9 >= (fPrc2 + fProfit2)))					//풋옵션보유수가 있을경우2
		{
			if ((lPutQty[1] < 10 && lPutQty[1] < lP2ho9) || (lPutQty[1] < lP2ho9 * 0.9))
			{
				Request100_(PutCode[1], "1", fPrc2 + fProfit2, (int)lPutQty[1]);
				if (lPutQty[0] == 0 && lPutQty[1] == 0 && lPutQty[2] == 0)
				{
					bPut = TRUE;
					Request2400();
					for (int i = 0; i < 3; i++)
					{
						gIter[i] = iter; //
					}
					bSetPrice = TRUE;
					//OnBnClickedButtonprofit3();//kill
					SetPrice();
				}
			}
            else if (lPutQty[1] < 40)
            {
                if (lPutQty[1] / 2 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 2));
            }
            else if (lPutQty[1] < 80)
            {
                if (lPutQty[1] / 3 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 3));
            }
            else if (lPutQty[1] < 120)
            {
                if (lPutQty[1] / 5 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 5));
            }
            else if (lPutQty[1] < 200)
            {
                if (lPutQty[1] / 8 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 8));
            }
            else
            {
                if (lPutQty[1] / 12 < lP2ho9)
                    Request100_(PutCode[1], "1", fPrc + fProfit, (int)(lPutQty[1] / 12));
            }
		}

		if (lPutQty[2] > 0 && (fP3ho9 >= (fPrc3 + fProfit3)))					//풋옵션보유수가 있을경우3
		{
			if ((lPutQty[2] < 10 && lPutQty[2] < lP3ho9) || (lPutQty[2] < lP3ho9 * 0.75))
			{
				Request100_(PutCode[2], "1", fPrc3 + fProfit3, (int)lPutQty[2]);
				if (lPutQty[0] == 0 && lPutQty[1] == 0 && lPutQty[2] == 0)
				{
					bPut = TRUE;
					Request2400();
					for (int i = 0; i < 3; i++)
					{
						gIter[i] = iter; //
					}
					bSetPrice = TRUE;
					//OnBnClickedButtonprofit3();//kill
					SetPrice();
				}
			}
            else if (lPutQty[2] < 40)
            {
               if (lPutQty[2] / 2 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 2));
            }
            else if (lPutQty[2] < 80)
            {
                if (lPutQty[2] / 3 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 3));
            }
            else if (lPutQty[2] < 120)
            {
                if (lPutQty[2] / 5 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 5));
            }
            else if (lPutQty[2] < 200)
            {
                if (lPutQty[2] / 8 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 8));
            }
            else
            {
                if (lPutQty[2] / 12 < lP3ho9)
                    Request100_(PutCode[2], "1", fPrc + fProfit, (int)(lPutQty[2] / 12));
            }
		}

	}

	//if ((lLqdt > 0) && (nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
	//{
	//	if (lCallQty[0] > 0)		//콜옵션보유수가 있을경우
	//	{
	//		for (int i = 0; i < iter; ++i)
	//		{
	//			SellCall(fPrc + fProfit + ((float)i * 0.01), 10, nPer);
	//		}
	//		bCall = TRUE;
	//	}

	//	if (lPutQty[0] > 0)			//풋옵션보유수가 있을경우
	//	{
	//		for (int i = 0; i < iter; ++i)
	//		{
	//			SellPut(fPrc + fProfit + ((float)i * 0.01), 10, nPer);
	//		}
	//		bPut = TRUE;
	//	}
	//}
}

void CDlg_JEKYLL::BuyOption1() //정해진 가격에 사고 팔기 - n개씩 팔기 SetSell 함수 선행
{
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	CString temp1, temp2, temp4, temp5;
	GetDlgItemTextA(IDC_EDITPRC1, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITPRC2, temp2); // 얻을 이익
	GetDlgItemTextA(IDC_EDITPRC3, temp4); // 매수량 기본 100%
	GetDlgItemTextA(IDC_EDITPRC4, temp5); // 매수간격 0.02

	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2), fGap = (float)atof(temp5);

	// ******************************************************** 매수가격 조정(평균가로 조정) 소수점 두자리
	CString strPrc;
	bOption ? GetDlgItemTextA(IDC_AVRPRC3F, strPrc) : GetDlgItemTextA(IDC_AVRPRC3, strPrc);
	float fAvrPrc = (float)atof(strPrc);
	if (fAvrPrc < fPrc && fAvrPrc > fPrc - 0.1) //20틱보다 크면 
	{
		fAvrPrc = roundf(fAvrPrc * 100) / 100; // 소수점 두자리 반올림
		strPrc.Format("%.2f", fAvrPrc);
		CEdit *pEdit1;
		pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1);
		pEdit1->SetWindowText(strPrc);
		pEdit1 = NULL;
	}

	int nPer = atoi(temp4);
	int iter = 100 / nPer;

	// ******************************************************************************************************* 매수
	if (bPut && bOption && (fPho9 < fPrc + 0.03))//buy put
	{
		//for (int i = iter; i > 0; --i)
		for (int i = 0; i < iter; ++i)
		{
			BuyPut(fPrc - ((float)i)*fGap, 10, nPer);
		}
		//BuyPut(fPrc, 10, nPer);
		//BuyPut(fPrc - fGap, 10, nPer);
		//BuyPut(fPrc - (fGap*3.5), 10, nPer);
		//Request100(PutCode[0], "2", temp1);
		bPut = FALSE;
	}
	if (!bPut && bOption && (fPho9 > (fPrc + fProfit)) && lLqdt == 0) //cancel buying put
	{
		Request600P();
		bPut = TRUE;
	}

	if (bCall && !bOption && (fCho9 < fPrc + 0.03)) // buy call
	{
		for (int i = 0; i < iter; ++i)
		{
			BuyCall(fPrc - ((float)i)*fGap, 10, nPer);
		}
		//BuyCall(fPrc, 10, nPer);
		//BuyCall(fPrc - fGap, 10, nPer);
		//BuyCall(fPrc - (fGap*3.5), 10, nPer);
		//Request100(CallCode[0], "2", temp1);
		bCall = FALSE;
	}
	if (!bCall && !bOption && (fCho9 > (fPrc + fProfit)) && lLqdt == 0) //cancel buying call
	{
		Request600C(); // 매수매도주문 모두 취소
		bCall = TRUE;
	}

	// ******************************************************************************************************* 청산
	if ((lLqdt > 0) && (nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
	{
		if (lCallQty[0] > 0 && !bOption && (fCho9 == fQSellPrc.front()) && fQSellPrc.size() > 0 && nQSellQty.size() > 0)				//콜옵션보유수가 있을경우
		{
			Request100_(CallCode[0], "1", fQSellPrc.front(), nQSellQty.front());
			fQSellPrc.pop();
			nQSellQty.pop();
			bCall = TRUE;
			if (nQSellQty.size() == 0)	KillTimer(17);
		}

		if (lPutQty[0] > 0 && bOption && (fPho9 == fQSellPrc.front()) && fQSellPrc.size() > 0 && nQSellQty.size() > 0)				//콜옵션보유수가 있을경우
		{
			Request100_(PutCode[0], "1", fQSellPrc.front(), nQSellQty.front());
			fQSellPrc.pop();
			nQSellQty.pop();
			bPut = TRUE;
			if (nQSellQty.size() == 0)	KillTimer(17);
		}
	}
}

void CDlg_JEKYLL::SetSell(int qty)
{
	// 여러개 가격으로 순차적으로 매도(기본 10개씩)
	CString temp1, temp2;
	GetDlgItemTextA(IDC_EDITPRC1, temp1); // 매수가격
	GetDlgItemTextA(IDC_EDITPRC2, temp2); // 얻을 이익
	float fPrc = (float)atof(temp1), fProfit = (float)atof(temp2);

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
		fQSellPrc.push(fPrc + fProfit + i * 0.01f); //정해진물량의 가격폭으로 1틱씩 가격저장
	}
	SetTimer(17, 777, NULL); //BuyOption1 함수 호출	
}

void CDlg_JEKYLL::SetPrice(int per) // 기본 per=15% 적용
{
	CString str, str1, str2, str3;
	str1 = m_lst2105.GetItemText(9, 1);
	str2 = m_lst2105_.GetItemText(9, 1);
	str3 = m_lst2105__.GetItemText(9, 1);
	float f1 = (float)atof(str1), f2 = (float)atof(str2), f3 = (float)atof(str3); // 현재 매수1호가

	f1 *= (float)(100 - per);
	f1 = roundf(f1) / 100; // 소수점2자리 반올림
	f2 *= (float)(100 - per);
	f2 = roundf(f2) / 100; // 소수점2자리 반올림
	f3 *= (float)(100 - per);
	f3 = roundf(f3) / 100; // 소수점2자리 반올림

	str1.Format("%.2f", f1);
	str2.Format("%.2f", f2);
	str3.Format("%.2f", f3);

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(str1);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(str2);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(str3);
	pEdit1 = NULL;
}

void CDlg_JEKYLL::OnBnClickedButtonprofit2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString temp4;
	GetDlgItemTextA(IDC_EDITPRC3, temp4); // 매수량 기본 % 미리 정해짐

	int nPer = atoi(temp4);//매수 %
	for (int i = 0; i < 3; i++)
	{
		gIter[i] = (int)(100 / nPer); //
	}
	nSellOption = 1;
	bSetPrice = TRUE;
	SetTimer(18, 1000, NULL); //BuyOption0/7 함수호출(매수잔량 감추기)
	//SetSell();
	m_tauto.SetWindowTextA("Running");

}

void CDlg_JEKYLL::OnBnClickedButtonprofit3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(18);
	for (int i = 0; i < 3; i++)
	{
		gIter[i] = 0;
	}

	//KillTimer(17);
	bSetPrice = FALSE;
	m_tauto.SetWindowTextA("Stop");

	CString str;
	str.Format("%d, %d, %d", gIter[0], gIter[1], gIter[2]);
	m_tst.SetWindowTextA(str);

	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	bOption ? Request600P() : Request600C();
	nSellOption = 0;

	//KillTimer(17) BuyOption1() 관련
	//while (!nQSellQty.empty()) nQSellQty.pop(); queue<int>().swap(nQSellQty);
	//while (!fQSellPrc.empty()) fQSellPrc.pop(); queue<float>().swap(fQSellPrc);
}

void CDlg_JEKYLL::OnBnClickedButtonprofit4() // fPrc = fCho9 - fProfit
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, str1, str2, str3, str4, str5, str6;
	str1 = m_lst2105.GetItemText(9, 1);
	str2 = m_lst2105_.GetItemText(9, 1);
	str3 = m_lst2105__.GetItemText(9, 1);
	GetDlgItemTextA(IDC_EDITPRC2, str4);
	GetDlgItemTextA(IDC_EDITPRC7, str5);
	GetDlgItemTextA(IDC_EDITPRC11, str6);
	float f1 = (float)atof(str1), f2 = (float)atof(str2), f3 = (float)atof(str3);
	float f4 = (float)atof(str4), f5 = (float)atof(str5), f6 = (float)atof(str6);

	f1 -= f4;
	f2 -= f5;
	f3 -= f6;

	if (f1 < 0) f1 = 0.0;
	if (f2 < 0) f2 = 0.0;
	if (f3 < 0) f3 = 0.0;

	str1.Format("%.2f", f1);
	str2.Format("%.2f", f2);
	str3.Format("%.2f", f3);

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(str1);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(str2);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(str3);
	pEdit1 = NULL;
}


//void CDlg_JEKYLL::OnNMClick100(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
//	int index = pNMView->iItem;
//	CString str = m_lst100.GetItemText(index, 3);
//	m_orgordno.SetWindowTextA(str);
//	m_orgordno2.SetWindowTextA(str);
//	*pResult = 0;
//}

void CDlg_JEKYLL::SellOptionSimul(float fProfit)
{
	if (fCallSellPrc !=  0 && lCallQty[0] > 0 && lCho9 > lCallQty[0] && (fCho9 >= (fCallSellPrc + fProfit)))		//콜옵션보유수가 있을경우
	{
		Request100(CallCode[0], "1", fCallSellPrc + fProfit);
		bCall = FALSE;
		nSellOption = 0;
		ofstream myfileRecording("RecordOrder.csv", ios::app);								// 주문 기록 이어쓰기
		if (myfileRecording.is_open())
		{
			myfileRecording << strTime << ", 매도, " << CallCode[0] << ", " << fCallSellPrc + fProfit << ", " << lCallQty[0] << "\n";
		}
		myfileRecording.close();
	}

	if (fPutSellPrc != 0 && lPutQty[0] > 0 && lPho9 > lPutQty[0] && (fPho9 >= (fPutSellPrc + fProfit)))			//풋옵션보유수가 있을경우
	{
		Request100(PutCode[0], "1", fPutSellPrc + fProfit);
		bPut = FALSE;
		nSellOption = 0;
		ofstream myfileRecording("RecordOrder.csv", ios::app);								// 주문 기록 이어쓰기
		if (myfileRecording.is_open())
		{
			myfileRecording << strTime << ", 매도, " << PutCode[0] << ", " << fPutSellPrc + fProfit << ", " << lPutQty[0] << "\n";
		}
		myfileRecording.close();
	}
}

void CDlg_JEKYLL::SellOption1() // 콜청산
{
	// ******************************************************************************************************* 콜청산
	if ((lLqdt > 0) && (nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
	{
		if (lCallQty[0] > 0 )				//콜옵션보유수가 있을경우1
		{
			if (lCallQty[0] < 10 && lCallQty[0] < lCho9)
			{
				Request100_(CallCode[0], "1", fCho9, (int)lCallQty[0]);
			}
			else if (lCallQty[0] < 50)
			{
				if (lCallQty[0] / 2 < lCho9)
					Request100_(CallCode[0], "1", fCho9, (int)(lCallQty[0] / 2));
				if (lCallQty[0] < 20) Request10100(CallCode[0]);
			}
			else if (lCallQty[0] < 100)
			{
				if (lCallQty[0] / 4 < lCho9)
					Request100_(CallCode[0], "1", fCho9, (int)(lCallQty[0] / 4));
			}
			else
			{
				if (lCallQty[0] / 6 < lCho9)
					Request100_(CallCode[0], "1", fCho9, (int)(lCallQty[0] / 6));
			}
		}

		if (lCallQty[1] > 0)				//콜옵션보유수가 있을경우2
		{
			if (lCallQty[1] < 10 && lCallQty[1] < lC2ho9)
			{
				Request100_(CallCode[1], "1", fC2ho9, (int)lCallQty[1]);
			}
			else if (lCallQty[1] < 50)
			{
				if (lCallQty[1] / 2 < lC2ho9)
					Request100_(CallCode[1], "1", fC2ho9, (int)(lCallQty[1] / 2));
				if (lCallQty[1] < 20) Request10100(CallCode[1]);
			}
			else if (lCallQty[1] < 100)
			{
				if (lCallQty[1] / 4 < lC2ho9)
					Request100_(CallCode[1], "1", fC2ho9, (int)(lCallQty[1] / 4));
			}
			else
			{
				if (lCallQty[1] / 6 < lC2ho9)
					Request100_(CallCode[1], "1", fC2ho9, (int)(lCallQty[1] / 6));
			}
		}

		if (lCallQty[2] > 0)				//콜옵션보유수가 있을경우3
		{
			if (lCallQty[2] < 10 && lCallQty[2] < lC3ho9)
			{
				Request100_(CallCode[2], "1", fC3ho9, (int)lCallQty[2]);
			}
			else if (lCallQty[2] < 50)
			{
				if (lCallQty[2] / 2 < lC3ho9)
					Request100_(CallCode[2], "1", fC3ho9, (int)(lCallQty[2] / 2));
				if (lCallQty[2] < 20) Request10100(CallCode[2]);
			}
			else if (lCallQty[2] < 100)
			{
				if (lCallQty[2] / 4 < lC3ho9)
					Request100_(CallCode[2], "1", fC3ho9, (int)(lCallQty[2] / 4));
			}
			else
			{
				if (lCallQty[2] / 6 < lC3ho9)
					Request100_(CallCode[2], "1", fC3ho9, (int)(lCallQty[2] / 6));
			}
		}		

	}

	if (lLqdt == 0 && lLqdt == lCallQty[0] + lPutQty[0] + lCallQty[1] + lPutQty[1] + lCallQty[2] + lPutQty[2])
	{
		OnBnClickedButtonprofit3();
	}
}


void CDlg_JEKYLL::SellOption2() // 풋 청산
{
	// ******************************************************************************************************* 콜청산
	if ((lLqdt > 0) && (nSellOption == 1)) //청산가능물량이 있고 가격옵션일 경우
	{
		// ******************************************************************************************************* 풋청산

		if (lPutQty[0] > 0)					//풋옵션보유수가 있을경우1
		{
			if (lPutQty[0] < 10 && lPutQty[0] < lPho9)
			{
				Request100_(PutCode[0], "1", fPho9, (int)lPutQty[0]);
			}
			else if (lPutQty[0] < 50)
			{
				if (lPutQty[0] / 2 < lPho9)
					Request100_(PutCode[0], "1", fPho9, (int)(lPutQty[0] / 2));
				if (lPutQty[0] < 20) Request10100(PutCode[0]);
			}
			else if (lPutQty[0] < 100)
			{
				if (lPutQty[0] / 4 < lPho9)
					Request100_(PutCode[0], "1", fPho9, (int)(lPutQty[0] / 4));
			}
			else
			{
				if (lPutQty[0] / 6 < lPho9)
					Request100_(PutCode[0], "1", fPho9, (int)(lPutQty[0] / 6));
			}
		}

		if (lPutQty[1] > 0)					//풋옵션보유수가 있을경우2
		{
			if (lPutQty[1] < 10 && lPutQty[1] < lP2ho9)
			{
				Request100_(PutCode[1], "1", fP2ho9, (int)lPutQty[1]);
			}
			else if (lPutQty[1] < 50)
			{
				if (lPutQty[1] / 2 < lP2ho9)
					Request100_(PutCode[1], "1", fP2ho9, (int)(lPutQty[1] / 2));
				if (lPutQty[1] < 20) Request10100(PutCode[1]);
			}
			else if (lPutQty[1] < 100)
			{
				if (lPutQty[1] / 4 < lP2ho9)
					Request100_(PutCode[1], "1", fP2ho9, (int)(lPutQty[1] / 4));
			}
			else
			{
				if (lPutQty[1] / 6 < lP2ho9)
					Request100_(PutCode[1], "1", fP2ho9, (int)(lPutQty[1] / 6));
			}
		}

		if (lPutQty[2] > 0)					//풋옵션보유수가 있을경우3
		{
			if (lPutQty[2] < 10 && lPutQty[2] < lP3ho9)
			{
				Request100_(PutCode[2], "1", fP3ho9, (int)lPutQty[2]);
			}
			else if (lPutQty[2] < 50)
			{
				if (lPutQty[2] / 2 < lP3ho9)
					Request100_(PutCode[2], "1", fP3ho9, (int)(lPutQty[2] / 2));
				if (lPutQty[2] < 20) Request10100(PutCode[2]);
			}
			else if (lPutQty[2] < 100)
			{
				if (lPutQty[2] / 4 < lP3ho9)
					Request100_(PutCode[2], "1", fP3ho9, (int)(lPutQty[2] / 4));
			}
			else
			{
				if (lPutQty[2] / 6 < lP3ho9)
					Request100_(PutCode[2], "1", fP3ho9, (int)(lPutQty[2] / 6));
			}
		}

	}

	if (lLqdt == 0 && lLqdt == lCallQty[0] + lPutQty[0] + lCallQty[1] + lPutQty[1] + lCallQty[2] + lPutQty[2])
	{
		OnBnClickedButtonprofit3();
	}
}

void CDlg_JEKYLL::SellOption(float fProfit)
{
	// ******************************************************************************************************* 청산
	if ((lLqdt > 0)) //청산가능물량이 있고 가격옵션일 경우
	{
		if (lCallQty[0] > 0 && fCallAvrPrc[0] > 0 && (fCho9 >= (fCallAvrPrc[0] + fProfit)))				//콜옵션보유수가 있을경우
		{
			if (lCallQty[0] < 10 && lLqdt == lCallQty[0] + lPutQty[0] && lCallQty[0] < lCho9)
			{
				Request100_(CallCode[0], "1", fCho9, (int)lCallQty[0]);
				bCall = TRUE;
				OnBnClickedButtonprofit3();//kill
			}
			else if (lCallQty[0] < 50)
			{
				if (lCallQty[0] / 2 < lCho9)
					Request100_(CallCode[0], "1", fCho9, (int)(lCallQty[0] / 2));
				if (lCallQty[0] < 20) Request10100(CallCode[0]);
			}
			else if (lCallQty[0] < 100)
			{
				if (lCallQty[0] / 4 < lCho9)
					Request100_(CallCode[0], "1", fCho9, (int)(lCallQty[0] / 4));
			}
			else
			{
				if (lCallQty[0] / 6 < lCho9)
					Request100_(CallCode[0], "1", fCho9, (int)(lCallQty[0] / 6));
			}
		}

		if (lPutQty[0] > 0 && fPutAvrPrc[0] > 0 && (fPho9 >= (fPutAvrPrc[0] + fProfit)))					//풋옵션보유수가 있을경우
		{
			if (lPutQty[0] < 10 && lLqdt == lCallQty[0] + lPutQty[0] && lPutQty[0] < lPho9)
			{
				Request100_(PutCode[0], "1", fPho9, (int)lPutQty[0]);
				bPut = TRUE;
				OnBnClickedButtonprofit3();//kill
			}
			else if (lPutQty[0] < 50)
			{
				if (lPutQty[0] / 2 < lPho9)
					Request100_(PutCode[0], "1", fPho9, (int)(lPutQty[0] / 2));
				if (lPutQty[0] < 20) Request10100(PutCode[0]);
			}
			else if (lPutQty[0] < 100)
			{
				if (lPutQty[0] / 4 < lPho9)
					Request100_(PutCode[0], "1", fPho9, (int)(lPutQty[0] / 4));
			}
			else
			{
				if (lPutQty[0] / 6 < lPho9)
					Request100_(PutCode[0], "1", fPho9, (int)(lPutQty[0] / 6));
			}
		}
	}
}



void CDlg_JEKYLL::SellFast() // 100ms 속도로 큐잉하면서 back값이 max에서 3틱빠지면 청산/20개짜리 큐 저장하는데(2초 후에 실행)
{
	CString str;
	if (lCallQty[0] > 0)
	{
		str = m_lst2105.GetItemText(9, 1);		fQprc.push((float)atof(str));												// 매수호가1(콜)	
		if (fQprc.size() > 20)	fQprc.pop();
	}
	else if (lPutQty[0] > 0)
	{
		str = m_lst2105_.GetItemText(9, 1);		fQprc.push((float)atof(str));												// 매수호가1(풋)
		if (fQprc.size() > 20)	fQprc.pop();
	}

	queue<float> temp1 = fQprc;

	float max1 = 0.0;

	// max
	do 
	{
		float f1 = 0.0;
		f1 = temp1.front();
		if (f1 > max1) max1 = f1;
		temp1.pop();
	} while (!temp1.empty());

	if ((fQprc.size() == 20) && (fQprc.back() < max1 - 0.03)) //청산조건 : back(현재값)이 max에서 3틱 빠지면 청산 (1초에 10개 저장, 매우빠르므로, 현재값에서 3틱빠지는것과 같음)
	{
		if (lCallQty[0] > 0)
			Request100_(CallCode[0], "1", str, (int)lCallQty[0]);
		if (lPutQty[0] > 0)
			Request100_(PutCode[0], "1", str, (int)lPutQty[0]);
	}

	// 메모리 삭제
	while (!temp1.empty()) temp1.pop(); queue<float>().swap(temp1);
}


void CDlg_JEKYLL::OnBnClickedButtonRequest8() //Fast Sell
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (lLqdt == (lCallQty[0] + lPutQty[0]))
	{
		SetTimer(7, 100, NULL); //SellFast(); // fast sell
	}
	else
	{
		if (lCallQty[0] >= 0)		Request10100(CallCode[0]);
		if (lCallQty[0] < 0)		Request10100_(CallCode[0]);
		if (lPutQty[0] >= 0)		Request10100(PutCode[0]);
		if (lPutQty[0] < 0)		Request10100_(PutCode[0]);
	}
}


void CDlg_JEKYLL::OnBnClickedButtonRequest9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(7);
}

void CDlg_JEKYLL::BuyOption2()// 원하는 선물가격이 되었을경우 BuyOption0(자동거래) 가동
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str1, str2;
	GetDlgItemText(IDC_FUTURE, str1); //현재 선물가격
	GetDlgItemText(IDC_EDITPRC5, str2);//입력 가격
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();

	float prc1 = (float)atof(str1), prc2 = (float)atof(str2);
	
	if ((!bOption && (prc1 <= prc2)) || (bOption && (prc1 >= prc2))) // 콜매수 || 풋매수
	{
		CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;

		CString sPrc1 = m_lst2105.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
		pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(sPrc1);//시작 매수 가격
		float p1 = ((float)atof(sPrc1)*0.6f);										//이익을 60%로 설정
		p1 = roundf(p1*100) / 100; //소수점2자리 반올림
		pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", p1); pEdit2->SetWindowText(str);//원하는 이익
		pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
		pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격


		CString sPrc2 = m_lst2105_.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
		pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(sPrc2);//시작 매수 가격
		float p2 = ((float)atof(sPrc2)*0.6f);										//이익을 60%로 설정
		p2 = roundf(p2*100) / 100; //소수점2자리 반올림
		pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC7); str.Format("%.2f", p2); pEdit2->SetWindowText(str);//원하는 이익
		pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC9); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격

		CString sPrc3 = m_lst2105__.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
		pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(sPrc3);//시작 매수 가격
		float p3 = ((float)atof(sPrc3)*0.6f);										//이익을 60%로 설정
		p3 = roundf(p3*100) / 100; //소수점2자리 반올림
		pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC11); str.Format("%.2f", p3); pEdit2->SetWindowText(str);//원하는 이익
		pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC13); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격

		KillTimer(4);
		pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;

		Sleep(1000);
		OnBnClickedButtonprofit2();
	}
}

void CDlg_JEKYLL::OnBnClickedButtonprofit9() // 세팅된 선물가격이 되었을경우 콜/풋 선택여부에 따라 매수
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(4, 1000, NULL);//BuyOption2 실행
	m_tauto.SetWindowTextA("4 Running");
}

void CDlg_JEKYLL::BuyOption4()// 원하는 선물가격이 되었을경우 BuyOption4 가동 - 10분 중심선 터치
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str1, str2;
	GetDlgItemText(IDC_FUTURE, str1); //현재 선물가격
	GetDlgItemText(IDC_BOLGR10M, str2);//10분 중심선 대비 내 위치

	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	float prc2 = (float)atof(str2);
	if (abs(prc2) < 0.03)
	{
		if (!bOption) // 콜매수
		{
			CString sPrc1 = m_lst2105.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
			CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
			pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(sPrc1);//시작 매수 가격
			float temp = (float)(atof(sPrc1)*0.05); // 시작 매수 가격의 5% 수익 설정
			pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", temp); pEdit2->SetWindowText(str);//원하는 이익
			pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
			pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격
			pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
		}
		else if (bOption) // 풋매수
		{
			CString sPrc1 = m_lst2105_.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
			CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
			pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(sPrc1);//시작 매수 가격
			float temp = (float)(atof(sPrc1)*0.05); // 시작 매수 가격의 5% 수익 설정
			pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", temp); pEdit2->SetWindowText(str);//원하는 이익
			pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
			pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격
			pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
		}

		KillTimer(10);
		Sleep(1000);
		OnBnClickedButtonprofit2();
	}
}

void CDlg_JEKYLL::OnBnClickedButtonprofit11() //볼린저밴드 중심선 터치
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str2;
	GetDlgItemText(IDC_BOLGR10M, str2);//실행시점 기준 10분 중심선 기준 현재가가 상단에 있을 경우 콜/ 반대의 경우 풋
	float prc2 = (float)atof(str2);
	if (prc2 > 0)
	{
		((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(1);
	}
	SetTimer(10, 1000, NULL);//BuyOption4 실행(중심선 터치)
	m_tauto.SetWindowTextA("10 Running");
}


void CDlg_JEKYLL::BuyOption5()// 원하는 선물가격이 되었을경우 BuyOption5 가동 - 60m 터치
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str1, str2;
	GetDlgItemText(IDC_FUTURE, str1); //현재 선물가격
	GetDlgItemText(IDC_FUTURE60MA, str2);//60분 중심선 대비 내 위치

	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	float prc2 = (float)atof(str2);
	if (abs(prc2) < 0.03)
	{
		if (!bOption) // 콜매수
		{
			CString sPrc1 = m_lst2105.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
			CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
			pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(sPrc1);//시작 매수 가격
			float temp = (float)(atof(sPrc1)*0.05); // 시작 매수 가격의 5% 수익 설정
			pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", temp); pEdit2->SetWindowText(str);//원하는 이익
			pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
			pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격
			pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
		}
		else if (bOption) // 풋매수
		{
			CString sPrc1 = m_lst2105_.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
			CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
			pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(sPrc1);//시작 매수 가격
			float temp = (float)(atof(sPrc1)*0.05); // 시작 매수 가격의 5% 수익 설정
			pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", temp); pEdit2->SetWindowText(str);//원하는 이익
			pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
			pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격
			pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
		}

		KillTimer(13);
		Sleep(1000);
		OnBnClickedButtonprofit2();
	}
}

void CDlg_JEKYLL::OnBnClickedButtonprofit19() // 60m 선 터치할 경우(상단에서는 콜 매수, 하단에서는 풋 매수)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str2;
	GetDlgItemText(IDC_FUTURE60MA, str2);//실행시점 기준 10분 중심선 기준 현재가가 상단에 있을 경우 콜/ 반대의 경우 풋
	float prc2 = (float)atof(str2);
	if (prc2 > 0)
	{
		((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(1);
	}
	SetTimer(13, 1000, NULL);//BuyOption5 실행(60m 터치)
	m_tauto.SetWindowTextA("60m Running");
}

void CDlg_JEKYLL::BuyOption3()// 원하는 선물가격이 되었을경우 BuyOption 가동 - 볼린저 상하단을 터치하는 경우
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str1, str2, str3;
	GetDlgItemText(IDC_FUTURE, str1); //현재 선물가격
	GetDlgItemText(IDC_20MSMA2, str2);//20mSMA
	GetDlgItemText(IDC_SD2, str3);//width
	float prc1 = (float)atof(str1), prc2 = (float)atof(str2), prc3 = (float)atof(str3);
	if (prc1 >= (prc2 + prc3 - 0.1))// 풋매수( 상단 터치 상향돌파시) - 여유 0.1
	{
		((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(1);
		CString sPrc1 = m_lst2105_.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
		CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
		pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(sPrc1);//시작 매수 가격
		float temp = (float)(atof(sPrc1)*0.05); // 시작 매수 가격의 5% 수익 설정
		pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", temp); pEdit2->SetWindowText(str);//원하는 이익
		pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
		pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격
		pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
		KillTimer(12);
		Sleep(1000);
		OnBnClickedButtonprofit2();
	}

	if (prc1 <= (prc2 - prc3 + 0.1))// 콜매수 ( 하단 터치 하향돌파시) - 여유 0.1
	{
		((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);
		CString sPrc1 = m_lst2105.GetItemText(9, 1); //매수호가1(매도가능 현재가 = 매수대기현재가)
		CString str; CEdit *pEdit1, *pEdit2, *pEdit3, *pEdit4;
		pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(sPrc1);//시작 매수 가격
		float temp = (float)(atof(sPrc1)*0.05); // 시작 매수 가격의 5% 수익 설정
		pEdit2 = (CEdit*)GetDlgItem(IDC_EDITPRC2); str.Format("%.2f", temp); pEdit2->SetWindowText(str);//원하는 이익
		pEdit3 = (CEdit*)GetDlgItem(IDC_EDITPRC3); str.Format("%d", 5); pEdit3->SetWindowText(str);//매수량 %
		pEdit4 = (CEdit*)GetDlgItem(IDC_EDITPRC4); str.Format("%.2f", 0.01); pEdit4->SetWindowText(str);//매수간격
		pEdit1 = NULL, pEdit2 = NULL, pEdit3 = NULL, pEdit4 = NULL;
		KillTimer(12);
		Sleep(1000);
		OnBnClickedButtonprofit2();
	}
}

void CDlg_JEKYLL::OnBnClickedButtonprofit16()//BuyOption3 실행(볼린저밴드 상하단 터치)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(12, 1000, NULL);//BuyOption3 실행(볼린저밴드 상하단 터치)
	m_tauto.SetWindowTextA("12 Running");
}


void CDlg_JEKYLL::OnBnClickedButtonprofit17()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(4);
	KillTimer(10);
	KillTimer(12);
	KillTimer(13);
	m_tauto.SetWindowTextA("Stop");
}

void CDlg_JEKYLL::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString strType;
	BOOL bErrorFlag = FALSE;
	BOOL bWarnningFlag = FALSE;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	strType = m_lst1601.GetItemText(pLVCD->nmcd.dwItemSpec, 0);

	if ((strType.Find(_T("(순)")) != -1))
	{
		bErrorFlag = TRUE;
	}

	if ((strType.Find(_T("(현)")) != -1))
	{
		bWarnningFlag = TRUE;
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
		else
		{
			pLVCD->clrText = RGB(0, 0, 0);
		}

		*pResult = CDRF_DODEFAULT;
	}
}

void CDlg_JEKYLL::OnCustomdrawList2105(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString strType;
	BOOL bErrorFlag = FALSE;
	BOOL bWarnningFlag = FALSE;
	BOOL bWarnning2Flag = FALSE;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	strType = m_lst2105.GetItemText(pLVCD->nmcd.dwItemSpec, 0);

	if ((strType.Find(_T("현재가")) != -1))
	{
		bErrorFlag = TRUE;
	}

	if ((strType.Find(_T("매도호가수량1")) != -1))
	{
		bWarnningFlag = TRUE;
	}

	if ((strType.Find(_T("매수호가수량1")) != -1))
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

void CDlg_JEKYLL::OnCustomdrawList2105B(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString strType;
	BOOL bErrorFlag = FALSE;
	BOOL bWarnningFlag = FALSE;
	BOOL bWarnning2Flag = FALSE;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	strType = m_lst2105_.GetItemText(pLVCD->nmcd.dwItemSpec, 0);

	if ((strType.Find(_T("현재가")) != -1))
	{
		bErrorFlag = TRUE;
	}

	if ((strType.Find(_T("매도호가수량1")) != -1))
	{
		bWarnningFlag = TRUE;
	}

	if ((strType.Find(_T("매수호가수량1")) != -1))
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


void CDlg_JEKYLL::OnCustomdrawList2105C(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString strType;
	BOOL bErrorFlag = FALSE;
	BOOL bWarnningFlag = FALSE;
	BOOL bWarnning2Flag = FALSE;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	strType = m_lst2105__.GetItemText(pLVCD->nmcd.dwItemSpec, 0);

	if ((strType.Find(_T("현재가")) != -1))
	{
		bErrorFlag = TRUE;
	}

	if ((strType.Find(_T("매도호가수량1")) != -1))
	{
		bWarnningFlag = TRUE;
	}

	if ((strType.Find(_T("매수호가수량1")) != -1))
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

void CDlg_JEKYLL::OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC2, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC2); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC4, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC4); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC3, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC3); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC1, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_PRC, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_PRC); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_PRC2, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_PRC2); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_QTY, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_QTY); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_QTY2, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_QTY2); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnBnClickedButtonprofit18()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Request2400();
}



//if (fCho8 > fmaxCHo) // 5틱 고가경신 속도
	//{
	//	fQCHo.push(nIndex - nCtime);
	//	fmaxCHo = fCho8;
	//	nCtime = nIndex;
	//	if (fQCHo.size() > 5)	fQCHo.pop();// 5틱 고가경신 속도
	//	if (fQCHo.size() == 5)
	//	{
	//		queue<int> temp3 = fQCHo;
	//		int sum1 = 0;
	//		float avr1 = 0.0;
	//		// 평균
	//		do
	//		{
	//			int n1 = temp3.front();
	//			sum1 += n1;
	//			temp3.pop();
	//		} while (!temp3.empty());
	//		avr1 = (float)sum1 / (float)fQCHo.size();
	//		// 메모리 삭제
	//		queue<int>().swap(temp3);

	//		strV3.Format("%.2f", avr1);	m_velocity3.SetWindowText(strV3); // 콜 고가경신 평균시간(5틱)
	//	}
	//}
	//if (fPho8 > fmaxPHo)// 5틱 고가경신 속도
	//{
	//	fQPHo.push(nIndex - nPtime);
	//	fmaxPHo = fPho8;
	//	nPtime = nIndex;
	//	if (fQPHo.size() > 5)	fQPHo.pop();// 5틱 고가경신 속도
	//	if (fQPHo.size() == 5)
	//	{
	//		queue<int> temp4 = fQPHo;
	//		int sum1 = 0;
	//		float avr1 = 0.0;
	//		// 평균
	//		do
	//		{
	//			int n1 = temp4.front();
	//			sum1 += n1;
	//			temp4.pop();
	//		} while (!temp4.empty());
	//		avr1 = (float)sum1 / (float)fQPHo.size();
	//		// 메모리 삭제
	//		queue<int>().swap(temp4);

	//		strV4.Format("%.2f", avr1);	m_velocity4.SetWindowText(strV4); // 풋 고가경신 평균시간(5틱)
	//	}
	//}
	//strV1.Format("%d", nIndex - nCtime);		m_velocity.SetWindowText(strV1);	// 콜 고가 경신후 경과시간
	//strV2.Format("%d", nIndex - nPtime);		m_velocity2.SetWindowText(strV2); // 풋 고가 경신후 경과시간


void CDlg_JEKYLL::OnDeltaposSpin11(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_AVRPRC2, str);
	int n1 = atoi(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		Request100_(CallCode[0], "2", fCho8, 1);
		n1 += 1;
	}
	else // 하 버튼
	{
		Request100_(CallCode[0], "1", fCho9, 1);
		n1 -= 1;
	}

	str.Format("%d", n1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_AVRPRC2); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin15(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin33(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin12(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_AVRPRC2F, str);
	int n1 = atoi(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		Request100_(PutCode[0], "2", fPho8, 1);
		n1 += 1;
	}
	else // 하 버튼
	{
		Request100_(PutCode[0], "1", fPho9, 1);
		n1 -= 1;
	}

	str.Format("%d", n1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_AVRPRC2F); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}

void CDlg_JEKYLL::OnDeltaposSpin32(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin34(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin16(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, str1, str2, str3;
	nIndex = 0;
	GetDlgItemTextA(IDC_CALLCODE, str);
	int n1 = atoi(str.Right(3)), n2=0, n3=0;

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		n2 = n1 + 5; 
		(n1 % 5) ? n1 += 3 : n1 += 2; // ex)209B2322-> 322 -> 322+3=325	
		n3 = n1 + 5;
	}
	else // 하 버튼
	{
		n2 = n1;
		(n1 % 5) ? n1 -= 2 : n1 -= 3; // ex)209B2322-> 322 -> 322-2=320		
		n3 = n1 + 5;
	}

	str1.Format("%d", n1); str2.Format("%d", n2); str3.Format("%d", n3);
	str1 = str.Left(5) + str1;
	str2 = str.Left(5) + str2;
	str3 = str.Left(5) + str3;
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_CALLCODE); pEdit1->SetWindowText(str1);
	pEdit1 = NULL;
	CallCode[0] = str1;
	CallCode[1] = str2;
	CallCode[2] = str3;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin17(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, str1, str2, str3;
	nIndex = 0;
	GetDlgItemTextA(IDC_PUTCODE, str);
	int n1 = atoi(str.Right(3)), n2=0, n3=0;

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		n2 = n1;
		(n1 % 5) ? n1 += 3 : n1 += 2; // ex)309B2320 -> 320 -> 320+2=322
		n3 = n1 - 5;
	}
	else // 하 버튼
	{
		n2 = n1 - 5;
		(n1 % 5) ? n1 -= 2 : n1 -= 3; // ex)309B2320 -> 320 -> 320-3=317
		n3 = n1 - 5;
	}

	str1.Format("%d", n1); str2.Format("%d", n2); str3.Format("%d", n3);
	str1 = str.Left(5) + str1;
	str2 = str.Left(5) + str2;
	str3 = str.Left(5) + str3;
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_PUTCODE); pEdit1->SetWindowText(str1);
	pEdit1 = NULL;
	PutCode[0] = str1;
	PutCode[1] = str2;
	PutCode[2] = str3;

	*pResult = 0;
}


void CDlg_JEKYLL::OnClick2105(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;
	CString str1, str2, str3;
	str1= m_lst2105.GetItemText(index, 1); //0부터 시작
	str2 = m_lst2105_.GetItemText(index, 1); //0부터 시작
	str3 = m_lst2105__.GetItemText(index, 1); //0부터 시작

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(str1);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(str2);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(str3);

	//((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);

	float f1 = (float)atof(str1), f2 = (float)atof(str2), f3 = (float)atof(str3);
	
	f1 *= 15;
	f1 = roundf(f1) / 100; // 소수점2자리 반올림
	f2 *= 15;
	f2 = roundf(f2) / 100; // 소수점2자리 반올림
	f3 *= 15;
	f3 = roundf(f3) / 100; // 소수점2자리 반올림

	str1.Format("%.2f", f1);
	str2.Format("%.2f", f2);
	str3.Format("%.2f", f3);

	//CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC2); pEdit1->SetWindowText(str1);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC7); pEdit1->SetWindowText(str2);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC11); pEdit1->SetWindowText(str3);

	pEdit1 = NULL;
	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin13(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC6, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin14(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC10, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin9(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC7, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC7); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin24(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC11, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC11); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin10(NMHDR *pNMHDR, LRESULT *pResult) // 현재가를 기준으로 가격 % 상하 조정
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, str1, str2, str3;
	//GetDlgItemTextA(IDC_EDITPRC1, str1);
	//GetDlgItemTextA(IDC_EDITPRC6, str2);
	//GetDlgItemTextA(IDC_EDITPRC10, str3);
	str1 = m_lst2105.GetItemText(9, 1);
	str2 = m_lst2105_.GetItemText(9, 1);
	str3 = m_lst2105__.GetItemText(9, 1);
	float f1 = (float)atof(str1), f2 = (float)atof(str2), f3 = (float)atof(str3); // 현재 매수1호가

	GetDlgItemTextA(IDC_EDITPRC8, str);
	int n1 = atoi(str);


	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		f1 *= (float)(100 + n1);
		f1 = roundf(f1) / 100; // 소수점2자리 반올림
		f2 *= (float)(100 + n1);
		f2 = roundf(f2) / 100; // 소수점2자리 반올림
		f3 *= (float)(100 + n1);
		f3 = roundf(f3) / 100; // 소수점2자리 반올림
	}
	else // 하 버튼
	{
		f1 *= (float)(100 - n1);
		f1 = roundf(f1) / 100; // 소수점2자리 반올림
		f2 *= (float)(100 - n1);
		f2 = roundf(f2) / 100; // 소수점2자리 반올림
		f3 *= (float)(100 - n1);
		f3 = roundf(f3) / 100; // 소수점2자리 반올림
	}
	
	str1.Format("%.2f", f1);
	str2.Format("%.2f", f2);
	str3.Format("%.2f", f3);

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC1); pEdit1->SetWindowText(str1);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(str2);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(str3);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin26(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC12, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC12); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin23(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC9, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC9); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin25(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC13, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC13); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnClick21052(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;
	CString str = m_lst2105_.GetItemText(index, 1); //0부터 시작

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC6); pEdit1->SetWindowText(str);

	//((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnClick21053(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;
	CString str = m_lst2105__.GetItemText(index, 1); //0부터 시작

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC10); pEdit1->SetWindowText(str);

	//((CButton*)GetDlgItem(IDC_CHECKOPTION))->SetCheck(0);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin27(NMHDR *pNMHDR, LRESULT *pResult) // 매수가를 기준으로 이익률을 상하로 조정
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, str1, str2, str3;
	GetDlgItemTextA(IDC_EDITPRC1, str1);
	GetDlgItemTextA(IDC_EDITPRC6, str2);
	GetDlgItemTextA(IDC_EDITPRC10, str3);
	float f1 = (float)atof(str1), f2 = (float)atof(str2), f3 = (float)atof(str3);

	GetDlgItemTextA(IDC_EDITPRC14, str);
	int n1 = atoi(str);


	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		n1 += 1;
	}
	else // 하 버튼
	{
		n1 -= 1;
	}

	f1 *= (float)n1;
	f1 = roundf(f1) / 100; // 소수점2자리 반올림
	f2 *= (float)n1;
	f2 = roundf(f2) / 100; // 소수점2자리 반올림
	f3 *= (float)n1;
	f3 = roundf(f3) / 100; // 소수점2자리 반올림

	str1.Format("%.2f", f1);
	str2.Format("%.2f", f2);
	str3.Format("%.2f", f3);
	str.Format("%d", n1);

	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC2); pEdit1->SetWindowText(str1);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC7); pEdit1->SetWindowText(str2);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC11); pEdit1->SetWindowText(str3);
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC14); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin28(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_TST5, str);
	int n1 = atoi(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		n1 += 1;
	}
	else // 하 버튼
	{
		n1 -= 1;
	}
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	if (bOption)
		lPutQty[0] = (int)n1;
	else
		lCallQty[0] = (int)n1;

	str.Format("%d", n1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_TST5); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin29(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_TST6, str);
	int n1 = atoi(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		n1 += 1;
	}
	else // 하 버튼
	{
		n1 -= 1;
	}
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	if (bOption)
		lPutQty[1] = (int)n1;
	else
		lCallQty[1] = (int)n1;

	str.Format("%d", n1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_TST6); pEdit1->SetWindowText(str);
	pEdit1 = NULL;
	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin30(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_TST7, str);
	int n1 = atoi(str);

	if (pNMUpDown->iDelta < 0) //상 버튼
	{
		n1 += 1;
	}
	else // 하 버튼
	{
		n1 -= 1;
	}
	BOOL bOption = ((CButton*)GetDlgItem(IDC_CHECKOPTION))->GetCheck();
	if (bOption)
		lPutQty[2] = (int)n1;
	else
		lCallQty[2] = (int)n1;

	str.Format("%d", n1);
	CEdit *pEdit1;
	pEdit1 = (CEdit*)GetDlgItem(IDC_TST7); pEdit1->SetWindowText(str);
	pEdit1 = NULL;
	*pResult = 0;
}


void CDlg_JEKYLL::OnDeltaposSpin31(NMHDR *pNMHDR, LRESULT *pResult) // 매수가격을 조정하기 위한 %를 기본 30%에서 1%씩 조정
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemTextA(IDC_EDITPRC8, str);
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
	pEdit1 = (CEdit*)GetDlgItem(IDC_EDITPRC8); pEdit1->SetWindowText(str);
	pEdit1 = NULL;

	*pResult = 0;
}


void CDlg_JEKYLL::OnClickedCheckoption1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateCheckedCount(IDC_CHECKOPTION1);
	if (nCheckedCount > 0)
	{
		lBalance /= nCheckedCount; // 예산 분배
	}
}


void CDlg_JEKYLL::OnClickedCheckoption2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateCheckedCount(IDC_CHECKOPTION2);
    if (nCheckedCount > 0)
    {
        lBalance /= nCheckedCount; // 예산 분배
    }
}


void CDlg_JEKYLL::OnClickedCheckoption3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateCheckedCount(IDC_CHECKOPTION3);
    if (nCheckedCount > 0)
    {
        lBalance /= nCheckedCount; // 예산 분배
    }
}

void CDlg_JEKYLL::UpdateCheckedCount(int nCheckBoxID) {
	CButton* pCheckBox = (CButton*)GetDlgItem(nCheckBoxID);
	if (pCheckBox->GetCheck() == BST_CHECKED)
	{
		if (nCheckedCount != 0) lBalance *= (long)nCheckedCount;
		nCheckedCount++;
	}
	else
	{
		lBalance *= (long)nCheckedCount;
		nCheckedCount--;
	}
	CString str; str.Format("%d", nCheckedCount);
	CEdit* pEdit;
	pEdit = (CEdit*)GetDlgItem(IDC_TST8); pEdit->SetWindowText(str);// nCheckedCount 확인
	pEdit = NULL;

}
