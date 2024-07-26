#include "afxwin.h"
#include "afxcmn.h"

#include <queue>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif

// CDlg_JEKYLL dialog
// 옵션기준일 현재 Request2301 CString str_gubun1="201807"

class CDlg_JEKYLL : public CDialog
{
	DECLARE_DYNCREATE(CDlg_JEKYLL)

public:
	CDlg_JEKYLL(CWnd* pParent = NULL);
	enum { IDD = IDD_JEKYLL };
	BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void				InitCtrls();
	void				Request2105(BOOL bNext = FALSE); // 선옵 현재가 조회
	void				Request2105_(BOOL bNext = FALSE);
	void				Request21052(BOOL bNext = FALSE);
	void				Request1601(BOOL bNext = FALSE); // 투자자종합
	void				Request1602(CString str_market = "1", CString str_upcode = "001", CString str_gubun1 = "2", CString cts_time = " ", BOOL bNext = FALSE);//30초 투자자 매매추이  - 코스피: 1/001/2, 선물:4/900/1(수량), 콜:5/700/2(금액), 풋/6/800/2
	void				Request600(BOOL bNext = FALSE); // 주문내역조회후 모두 취소
	void				Request600C(BOOL bNext = FALSE); // 주문내역조회후 모두 취소
	void				Request600P(BOOL bNext = FALSE); // 주문내역조회후 모두 취소
	void				Request600_(BOOL bNext = FALSE); // 주문내역조회후 모두 현재가로 매수정정
	void				Request100(CString code, CString bns, CString prc, BOOL bNext = FALSE); //1:매도,2:매수
	void				Request100(CString code, CString bns, float prc, BOOL bNext = FALSE); //1:매도,2:매수
	void				Request100_(CString code, CString bns, float prc, int qty, BOOL bNext = FALSE); //bns 1:매도,2:매수
	void				Request100_(CString code, CString bns, CString prc, int qty, BOOL bNext = FALSE); //bns 1:매도,2:매수
	void				Request100_(CString code, CString bns, CString prc, CString qty, BOOL bNext = FALSE); //bns 1:매도,2:매수
	void				Request200(CString code, CString orgordno, CString prc, CString qty, BOOL bNext = FALSE);//정정주문
	void				Request300(CString code, CString orgordno, CString qty, BOOL bNext = FALSE);//취소주문
	void				Request8415(CString str_code, BOOL bNext = FALSE);//선물 n분차트
    void				Request8415Y(CString str_code, BOOL bNext = FALSE);//선물 n분차트
	void				Request84152(CString str_code, BOOL bNext = FALSE);//옵션 n분차트
	void				Request84153(CString str_code, BOOL bNext = FALSE);//옵션 n분차트
	void				Request3103(BOOL bNext = FALSE);//o3103 해외선물 분봉차트
	void				Request0167(BOOL bNext = FALSE);//
	void				Request10100(CString code, BOOL bNext = FALSE);//매수된 물량 조회(청산가능, 신규주문가능금액 : lLqdt, lBalance)
	void				Request10100_(CString code, BOOL bNext = FALSE);//매도된 물량 조회(청산가능, 신규주문가능금액 : lLqdt, lBalance)
//	void				Request0441(BOOL bNext = FALSE);// 옵션잔고평가
	void				Request2400(BOOL bNext = FALSE);// 약정현황(보유 선옵평가조회, lCallQty, lPutQty)
	void				Request2400_(BOOL bNext = FALSE); // 미사용(Vector 사용)
	void				Request2301(CString date, BOOL bNext = FALSE); // 옵션전광판 CallCode, PutCode 조회
	void				Request2421(CString focode, BOOL bNext = FALSE); // 미결제약정추이
	void				Request1662(BOOL bNext = FALSE);//프로그램매매차트(베이시스)
	void				AdviseFC0();//선물가 실시간조회
	void				AdviseFH0();//호가잔량 조회
	void				AdviseBMT();//시간대별투자자추이(코스피)
	void				AdviseBMT2();//시간대별투자자추이(선물)
	void				AdviseOVC();//해외선물 호가(S&P)
	void				AdviseOVC2();//해외선물 호가(Euro)
	void				UnadviseFC0();
	void				UnadviseFH0();
	void				UnadviseBMT();
	void				UnadviseBMT2();
	void				UnadviseOVC();
	void				UnadviseOVC2();
	LRESULT				OnXMReceiveRealData(WPARAM wParam, LPARAM lParam);

	void				Receive2105(LPRECV_PACKET pRpData);// 선옵현재가(콜)
	void				Receive2105_(LPRECV_PACKET pRpData);// 선옵현재가(콜2)
	void				Receive21052(LPRECV_PACKET pRpData);// 선옵현재가(콜3)
	void				Receive1601(LPRECV_PACKET pRpData);// 투자자종합
	void				Receive2301(LPRECV_PACKET pRpData);// 옵션전광판(델타,쎄타) // CallCode, PutCode 조회
	void				Receive1602(LPRECV_PACKET pRpData);// 시간대별 투자자 매매추이
	void				Receive1602_(LPRECV_PACKET pRpData);// 시간대별 투자자 매매추이
	void				Receive1602();// 시간대별 투자자 매매추이
	void				Receive1602_();// 시간대별 투자자 매매추이(코스피)
	void				Receive600(LPRECV_PACKET pRpData);// 선옵 주문체결내역조회후 취소
	void				Receive600C(LPRECV_PACKET pRpData);// 선옵 주문체결내역조회후 취소
	void				Receive600P(LPRECV_PACKET pRpData);// 선옵 주문체결내역조회후 취소
	void				Receive600_(LPRECV_PACKET pRpData);// 선옵 주문체결내역조회후 현재가로 매수정정
	void				Receive100(LPRECV_PACKET pRpData);// 선옵 정상주문
	void				Receive8415(LPRECV_PACKET pRpData);// 선물차트(n분)
    void				Receive8415Y(LPRECV_PACKET pRpData);// 선물차트(n분)
	void				Receive84152(LPRECV_PACKET pRpData);// 옵션차트(n분)
	void				Receive84153(LPRECV_PACKET pRpData);// 옵션차트(n분)
	void				Receive3103(LPRECV_PACKET pRpData);// 해외선물차트(n분)
	void				Receive8415(int nCount);// 선물옵션차트(조회에러시)
	void				Receive0167(LPRECV_PACKET pRpData);// 시간조회
	void				Receive10100(LPRECV_PACKET pRpData);// 매수된 물량 조회(매도청산가능, 신규주문가능금액 : lLqdt, lBalance)
	void				Receive10100_(LPRECV_PACKET pRpData);// 매도된 물량 조회(매수청산가능, 신규주문가능금액 : lLqdt, lBalance)
//	void				Receive0441(LPRECV_PACKET pRpData);// 옵션잔고평가
	void				Receive2400(LPRECV_PACKET pRpData);// 약정현황(보유 선옵평가조회, lCallQty, lPutQty, fCallAvrPrc, fPutAvrPrc)
	void				Receive2400_(LPRECV_PACKET pRpData);//
	void				Receive2421(LPRECV_PACKET pRpData);// 미결제약정추이
	void				Receive1662(LPRECV_PACKET pRpData);// 프로그램매매차트(베이시스)

	void				BuyCall();
	void				BuyCall(CString strPrc, int amnt, int per = 100);// n개씩 구매
	void				BuyCall(float fprc, int amnt, int per = 100);// n개씩 구매
	void				BuyCall(CString code, float fprc, int amnt, int per = 100);// n개씩 구매
	void				BuyCallR(CString code, float fprc, int per = 100);// 랜덤한 수량(1~3)으로 랜덤한 시간간격(100~300ms) 을 가지고 주문-> Request100() (가격, 수량n)
	void				BuyCall(int amnt, int per = 100);// n개씩 구매
	void				BuyPut();
	void				BuyPut(CString strPrc, int amnt, int per = 100);// n개씩 구매
	void				BuyPut(float fprc, int amnt, int per = 100);// n개씩 구매
	void				BuyPut(CString code, float fprc, int amnt, int per = 100);// n개씩 구매
	void				BuyPutR(CString code, float fprc, int per = 100);// 랜덤한 수량(1~3)으로 랜덤한 시간간격(100~300ms) 을 가지고 주문-> Request100() (가격, 수량n)
	void				BuyPut(int amnt, int per = 100);// n개씩 구매 - 10개씩 짤라서 구매
	void				BuyOption();//정해진 가격에 사고 팔기
	void				BuyOption0();// 정해진 가격에 사고 팔기 + 매수물량 감추기
	void				BuyOption7(int i);// 정해진 가격에 사고 팔기 + 매수물량 감추기(적극매수-매수가를 높이면서 매입)
	void				BuyOption1();//정해진 가격에 사고 팔기1 - n개씩 팔기 SetSell 함수 선행
	void				BuyOption2();//정해진 가격에 사고 팔기2 - 원하는 선물가격이 되었을경우 옵션 구매
	void				BuyOption3();//정해진 가격에 사고 팔기3 - 10분봉기준 볼린저 상하단을 터치했을때
	void				BuyOption4();//정해진 가격에 사고 팔기4 - 10분봉기준 볼린저 밴드 중심선을 터치했을때
	void				BuyOption5();//정해진 가격에 사고 팔기5 - 1분봉기준 60분선 중심선을 터치했을때
	void				SellOptionSimul(float fProfit);//정해진 가격에 팔기(시뮬)
	void				SellOption(float fProfit);
	void				SellOption1();//콜청산
	void				SellOption2();//풋청산
	void				CheckCondition0(int i);//청산 + 조건 검색 
	void				CheckCondition();//매입
	
	void				MonOrder();// 매도주문완료 감시
	void				DispAccnt();// 계좌디스플레이
	void				SellCall();// 손절
	void				SellCall(int profit);// 설정된 이익에 무조건 청산
	void				SellCall(float profit);
	void				SellCall(float fprc, int amnt, int per = 100);//n개씩 매도
	void				SellCall2(int profit, int percent = 100);// trailingstop
	void				SellCall2(float profit, int percent = 100);
	void				SellPut();// 손절
	void				SellPut(int profit);// 설정된 이익에 무조건 청산
	void				SellPut(float profit);
	void				SellPut(float fprc, int amnt, int per = 100);//n개씩 매도
	void				SellPut2(int profit, int percent = 100);// trailingstop
	void				SellPut2(float profit, int percent = 100);
	void				GetData();
	void				Combine_8415_1602();
	void				SetSell(int qty = 10); // 기본 10개로 큐 세팅(청산 준비)
	void				SellFast();//빨리 팔기
	void				StandbyNine();// 9시이전에 동작
	void				SetPrice(int per=50); // 15% 가격다운후 세팅

	CString				GetColumnName(const CListCtrl * listctrl, int iCol);
	void				ExportToCSVFile(const CListCtrl *plistctrlContent, BOOL bIncludeHeaderNames = TRUE, char cDelimiter = ',');
	void				ExportToCSVFile();
	void				UpdateCheckedCount(int nCheckBoxID);

	afx_msg	LRESULT		OnXMReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT		OnXMTimeoutData(WPARAM wParam, LPARAM lParam);
	afx_msg void		OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonRequest();
	afx_msg void OnBnClickedButtonStop();
//	afx_msg void OnBnClickedButtonRequest2();
//	afx_msg void OnBnClickedButtonRequest3();
//	afx_msg void OnBnClickedButtonRequest4();
//	afx_msg void OnBnClickedButtonRequest5();
//	afx_msg void OnBnClickedButtonRequest6();
	afx_msg void OnBnClickedButtonRequest7();
//	afx_msg void OnBnClickedButtonRequest10();
//	afx_msg void OnBnClickedButtonRequest11();
//	afx_msg void OnBnClickedButtonRequest12();
//	afx_msg void OnBnClickedButtonRequest13();
//	afx_msg void OnBnClickedButtonRequest14();
	afx_msg void OnBnClickedButtonRequest19();
	afx_msg void OnBnClickedButtonRequest20();
	afx_msg void OnBnClickedButtonRequest21();
	//afx_msg void OnNMClick600(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonprofit();
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawList2105(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawList2105B(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawList2105C(NMHDR* pNMHDR, LRESULT* pResult);

	BOOL bToken, bAutoToken;// 옵션전광판 콜/풋 코드 유지여부 1:유지(2301), 자동 옵션매수 설정
	BOOL bCall, bPut, bCancel; // 바이콜 바이풋 매수취소 활성화 여부 0:비활성화 1:활성화
	BOOL bFC0;// CNCT7 버튼누르기위함 //FC0에서 거래량 데이터 시작되면 CNCT7 버튼누름
	BOOL bSetPrice; // Code1 첫매수시 Code2, Code3 가격 변경(한번만)

	char m_szContKey[30]; // 연속키 저장

	int ID2105, ID2105_, ID21052, ID1601, ID1602, ID1602_, ID100, ID200, ID300, ID600, ID600C, ID600P, ID600_, ID8415, ID8415Y, ID84152, ID84153, ID3103, ID0167, ID10100, ID10100_, ID2400, ID2400_, ID2301, ID2421, ID1662, ID0441;

	int nIndex;// 데이터저장 카운트(초)
	int nCurMin, nCurSec, nCorrectTime;// 총 분초, 서버조정시간 from 0167

	int nBuyTestCount;// 매수 테스트
	int nProfit, nGoalTrend, nGoalFlat; // 원하는 수익률
	int *gIter; //구매횟수(100/%) 변수

	// 양매도 수량
	int nCall, nPut;
	
	int nCancelTime;// 취소주문변수
	int nSaveTime;// 시간 기록(nSellOption == 2) 속도관련
	int nTrend;// 트렌드감시(0:off, 1:call, 2:put)
	int nSellOption; // 0:nProfit, 1:fProfit, 2:속도관련
	int nCheckedCount; // 구매할 옵션코드 개수(1~3)

	long lBalance, lMaxBalance, lLqdt, lNewSell; //매수가능금액, 청산가능 10100, 신규매도가능수량
	long lCallAvrPrc, lPutAvrPrc, lCho8, lPho8, lCho9, lPho9, lC2ho8, lP2ho8, lC2ho9, lP2ho9, lC3ho8, lP3ho8, lC3ho9, lP3ho9; // 콜,풋 매입금액, 콜금액, 풋금액
	long *lCallQty, *lPutQty; // 콜,풋 매입수량
	float *fCallAvrPrc, *fPutAvrPrc; //콜,풋 평단가
	float fFutPrc, f60mEMAY, fCallSellPrc, fPutSellPrc, fCho8, fCho9, fPho8, fPho9, fC2ho8, fC2ho9, fP2ho8, fP2ho9, fC3ho8, fC3ho9, fP3ho8, fP3ho9;// 선물현재가, 평단가, 팔가격(목표가격), 콜풋 현재가격(ho8,9)

	CString FutureCode; 
	CString *CallCode;
	CString *PutCode;
	CString strCallPrc, strPutPrc, strOrgOrdNo, strUsableMoney, strCallDelta, strPutDelta;

	const CString strAccntNo = "00151751313";
	const CString strPwdNo = "0716";

	//변동성, 델타, 감마, 세타 (2301)
	float fCallIV, fCallDelta, fCallGamma, fCallTheta, fCallVega, fCallHigh, fCallLow, fCallOpen, fPutIV, fPutDelta, fPutGamma, fPutTheta, fPutVega, fPutHigh, fPutLow, fPutOpen;
	float fTrailingHigh, fHighest, fLowest;

	// 시뮬레이션 변수, 조건검색, 손절
	float fSimCPrc, fSimPPrc;
	int nCqty, nPqty;
	int nSelltime, nCase, nBuytime;
	BOOL bTrail, bCC;

	// CheckCondition 변수
	BOOL bCCoption, bCCact; // 콜(1)/풋(0) 여부, 구매실행여부
	float fCCprc, fpreCCprc; //구매가격
	int nCCamnt, nCCmin; //구매수량, 구매시간(해당분에만 구매하려고함)

	// 매도호가 매수호가 5틱 고가경신
	//queue<int> nQCHo, nQPHo;
	queue<float> fQCHo, fQPHo;
	float fmaxCHo, fmaxPHo;
	int nCtime, nPtime;
	// 호가잔량
	queue<long> lQRem;
	long lRemQty, lRemHighest, lRemLowest;
	int lRemHtime, lRemLtime;

	// 매수체결건수, 매도체결건수
	queue<long> lQvol1, lQvol2;
	queue<CString> strQtime1, strQtime2;
	CString strVelocity7, strVelocity8, strVelocity9, strVelocity10;//매수매도 체결량 30건 체결량 총합(7,9)과 걸린시간(8,10)

	queue<int> CmpQtime1, CmpQtime2, CmpQvol1, CmpQvol2;

	// 트래킹 매도 convert
	queue<float> fQprc;

	// BuyOption() 청산
	queue<int> nQSellQty;
	queue<float> fQSellPrc;

	CString strDate; // %Y%m&d
	CString strDateY;
	CString strMonth; // %Y%m	
	CString strTime; // %HHMMSS

	CString *strArTime8415;// 8415 시간
	float *fArOpen;// open
	float *fArClose;// close
	float *fArCloseY;// close
	float *fArHigh;// high
	float *fArLow;// low

	float *fArCClose;// call close
	float *fArPClose;// put close


	//*************************** 10분봉
	float *fAr10mOpen;// open
	float *fAr10mClose;// close
	float *fAr10mHigh;// high
	float *fAr10mLow;// low

    float* fAr10mOpenY;// open
	float *fAr10mCloseY;// Yesterday close
	float *fAr10mHighY;// high
	float *fAr10mLowY;// low

	float *fArWidth;//close-open
	long *lArVol;// volume
	long *lArVol2;// volume(부호적용 - fArWidth를 사용)

	float *fAr10mK;//%K(10분)
	float *fAr10mD;//%D(10분)
	float *fAr10mSlowD;//%D(10분)

	float *fAr10mKY;// %10mK
	float *fAr10mDY;// %10mD
	float *fAr10mSlowDY;// %10mSlowD

	float *fAr20mSMA;// 20분 MA
	float *fAr20mSMAY;// 20분 MA
	float *fAr20mSD;// 20분 SD(표준편차)
	float *fAr60mSMA;// 60분 SMA

	float *fAr10m20mSMA;// 20분 MA(10m)
	float *fAr10m20mSMAY;// 20분 MA(10m)
	float *fAr10m20mSD;// 20분 SD(표준편차)(10m)
	float *fAr10m20mSDY;// 20분 SD(표준편차)(10m)

	float *fArMax60m;// 60분간의 최대값
	float *fArMin60m;// 60분간의 최소값
	float *fArMax30m; //30분간의 최대값
	float *fArMin30m; //30분간의 최소값

	CString *strArTime1602;//1602 시간
	long *lArForVol;// 외인선물거래량 foreingers 30초
	long *lArSecVol;// 기관선물거래량 securities 30초
	long *lArForVol2;// 외인선물거래량 1분
	long *lArSecVol2;// 기관선물거래량 1분
	long *lArForVol5m; //5분평균
	long *lArSecVol5m; //5분평균

	long *lArKoForVol;// 외인거래량 foreingers 30초
	long *lArKoSecVol;// 기관거래량 securities 30초
	long *lArKoForVol2;// 외인거래량 1분
	long *lArKoSecVol2;// 기관거래량 1분
	long *lArKoForVol5m; //5분평균
	long *lArKoSecVol5m; //5분평균

	long *lArRemClose; //순매수잔량 Close
	long *lArRemHigh; //순매수잔량 High
	long *lArRemLow; //순매수잔량 Low

	int *nArUpdateHigh, *nArUpdateLow;// 최고가/최저가 갱신횟수
	int *nArMin30m, *nArMax30m; //30분간의 최대최소값 시간 기록

	// 해외선물 SNP
	float *fArSNPClose;// close
	float *fArSNPHigh;// high
	float *fArSNPLow;// low
	float *fArSNPK;//%K(10분)
	float *fArSNPD;//%D(10분)
	float *fArSNPSlowD;//%D(10분)
	float *fArSNP20mSMA;// 20분 MA(10m)
	float *fArSNP20mSD;// 20분 SD(표준편차)(10m)

	CEdit m_callcode;
	CEdit m_putcode;
	//CStatic m_callcode2;
	//CStatic m_callcode3;
	//CStatic m_putcode2;
	//CStatic m_putcode3;

	CListCtrl m_lst2105;
	CListCtrl m_lst2105_;
	CListCtrl m_lst2105__;
	CListCtrl m_lst1601;

	CStatic m_callprc;//callprc
	CStatic m_callhigh;//callprc
	CStatic m_calllow;//callprc
	CStatic m_callhigh2;//callprc
	CStatic m_calllow2;//callprc
	CStatic m_putprc;//putprc
	CStatic m_puthigh;//putprc
	CStatic m_putlow;//putprc
	CStatic m_puthigh2;//putprc
	CStatic m_putlow2;//putprc

	CStatic m_time;//time

	CStatic m_lqdt;
	CStatic m_neword;

	CStatic m_avrprc;
	CStatic m_avrprc2;
    CStatic m_avrprc21;
    CStatic m_avrprc22;
	CStatic m_avrprc3;
    CStatic m_avrprc31;
    CStatic m_avrprc32;
	CStatic m_curvalue;
    CStatic m_curvalue2;
    CStatic m_curvalue21;
    CStatic m_curvalue22;
	CStatic m_curvalue4;
	CStatic m_avrprcf;
	CStatic m_avrprc2f;
    CStatic m_avrprc21f;
    CStatic m_avrprc22f;
	CStatic m_avrprc3f;
    CStatic m_avrprc31f;
    CStatic m_avrprc32f;
	CStatic m_curvaluef;
	CStatic m_curvaluef4;

	CStatic m_idx;//total seconds

	CStatic m_k200;
	CStatic m_future;
	CStatic m_futurechange;
	CStatic m_futurechange2;
	CStatic m_futuresnp;

	CStatic m_curmin;//nCurMin
	CStatic strDday;

	CStatic m_bcall;
	CStatic m_bput;

	CStatic m_bcancel;
	CStatic m_ncanceltime;

	CStatic m_nprofit;

	CStatic m_ftrail;

	//거래량
	CStatic m_fvol;
	CStatic m_fvol2;
	CStatic m_fvol3;
	CStatic m_fvol4;
	

	//잔량
	CStatic m_lrem;
	CStatic m_lrem2;
	CStatic m_lrem3;
	CStatic m_lrem5;
	CStatic m_lrem6;

	//60분, 20분, 
	CStatic m_future60ma;
	CStatic m_20msma;
	CStatic m_sd;
	CStatic m_20msma2;
	CStatic m_sd2;
	CStatic m_bolgr20;
	CStatic m_bolgr10m;

	//10분봉%D, %SlowD
	CStatic m_percentd3;
	CStatic m_percentd4;
	CStatic m_percentd5;
	CStatic m_percentd9;
	CStatic m_percentd10;
	CStatic m_percentd11;	// snp %slowD
	CStatic m_percentd12;	// snp %slowD

	// 체결강도
	CStatic m_cpower;

	// 텍스트 자동
	CStatic m_tauto;

	// 양매도 관련

	// 테스트 관련 TST
	CStatic m_tst;
	CStatic m_tst2;
	CStatic m_tst3;
	CStatic m_tst4;
	CStatic m_tst5;
	CStatic m_tst6;
	CStatic m_tst7;

	afx_msg void OnBnClickedButtonprofit2();
	afx_msg void OnBnClickedButtonprofit3();
	afx_msg void OnBnClickedButtonprofit9();
	afx_msg void OnBnClickedButtonprofit11();
	afx_msg void OnBnClickedButtonprofit16();
	afx_msg void OnBnClickedButtonprofit17();
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnDeltaposSpin7(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnDeltaposSpin8(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnBnClickedButtonRequest8();
//	afx_msg void OnBnClickedButtonRequest9();
	afx_msg void OnBnClickedButtonprofit18();
	afx_msg void OnBnClickedButtonprofit19();
	afx_msg void OnDeltaposSpin11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin12(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin16(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin17(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonprofit4();
	afx_msg void OnClick2105(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin13(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin14(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin9(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin24(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin10(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin26(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin23(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin25(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClick21052(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClick21053(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin27(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin28(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin29(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin30(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin31(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedCheckoption1();
	afx_msg void OnClickedCheckoption2();
	afx_msg void OnClickedCheckoption3();
    afx_msg void OnDeltaposSpin15(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaposSpin32(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaposSpin33(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaposSpin34(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin36(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin35(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonRequest22();
    afx_msg void OnBnClickedButtonRequest23();
    afx_msg void OnBnClickedButtonRequest15();
    afx_msg void OnBnClickedButtonRequest8();
    afx_msg void OnBnClickedButtonRequest12();
    afx_msg void OnBnClickedButtonRequest9();
    afx_msg void OnBnClickedButtonRequest13();
    afx_msg void OnDeltaposSpin38(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaposSpin37(NMHDR* pNMHDR, LRESULT* pResult);
};
