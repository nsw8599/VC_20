#include "afxwin.h"
#include "afxcmn.h"
#include <queue>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif 

// The number of samples per data series used in this demo

class CDlg_night : public CDialog
{
	DECLARE_DYNCREATE(CDlg_night)

public:
	CDlg_night(CWnd* pParent = NULL);
	enum { IDD = IDD_night };
	// The index of the array position to which new data values are added.
	int idx;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	CString acntnum = "00151751313";
	CString pwdnum = "0716";
	CString strDate;

protected:
	virtual BOOL OnInitDialog();
	void			InitCtrls();
	void			Request100(CString code, CString bns, BOOL bNext=FALSE);//매수
	void			Request100_(CString code, CString bns, CString prc, int qty, BOOL bNext = FALSE); //bns 1:매도,2:매수
	void			Request100_(CString code, CString bns, float prc, int qty, BOOL bNext = FALSE); //bns 1:매도,2:매수
	void			Request200(CString code, BOOL bNext = FALSE);//정정
	void			Request300(CString code, CString orgordno, BOOL bNext = FALSE);//취소
	void			Request21200(CString code, BOOL bNext = FALSE);//선옵 주문가능수량/금액 조회(청산가능, 신규주문가능금액 : lLqdt, lBal)
	void			Request21200_(CString code, BOOL bNext = FALSE);//선옵 주문가능수량/금액 조회(청산가능, 신규주문가능금액 : lLqdt, lBal)
	void			Request31200(BOOL bNext = FALSE);//평단가, 수량(lCallQty, lPutQty)
	void			Request600(BOOL bNext = FALSE);//체결내역조회
	void			Request2830(BOOL bNext = FALSE);//야간옵션 콜 Price조회
	void			Request2830_(BOOL bNext = FALSE);//야간옵션 풋 Price조회
    void			Request2831(BOOL bNext = FALSE);//야간옵션 콜 호가 조회
    void			Request2831_(BOOL bNext = FALSE);//야간옵션 풋 호가 조회
	void			Request2813(BOOL bNext = FALSE);//투자자(시간대별)
	void			Request2816(BOOL bNext = FALSE);//투자자종합
	void			Request0167(BOOL bNext = FALSE);
	void			Request2301(CString date, BOOL bNext = FALSE);//옵션전광판
	void			AdviseOVC();//해외선물 호가(S&P)
	void			UnadviseOVC();

	void			Receive2816(LPRECV_PACKET pRpData);
	void			Receive2830(LPRECV_PACKET pRpData);
	void			Receive2830_(LPRECV_PACKET pRpData);
    void			Receive2831(LPRECV_PACKET pRpData);
    void			Receive2831_(LPRECV_PACKET pRpData);
	void			Receive2813(LPRECV_PACKET pRpData);
	void			Receive100(LPRECV_PACKET pRpData);
	void			Receive21200(LPRECV_PACKET pRpData);
	void			Receive31200(LPRECV_PACKET pRpData);
	void			Receive600(LPRECV_PACKET pRpData);
	void			Receive0167(LPRECV_PACKET pRpData);// 시간조회
	void			Receive2301(LPRECV_PACKET pRpData);// 옵션전광판(델타,쎄타)
	void		getData();
	void			ExportToCSVFile();

	void			BuyOption();
    void			BuyOption0();//정해진 가격에 사고 팔기 + 매수잔량숨기기
    void			BuyOption1();
	void			SetBuy(int qty = 10);
	void			SetSell(int qty = 10);
	void			BuyCall(float fprc, int amnt, int per = 100);// n개씩 구매
    void			BuyCallR(float fprc, int per = 100);// 랜덤한 수량(1~3)으로 랜덤한 시간간격(100~300ms) 을 가지고 주문-> Request100() (가격, 수량n)
    void			BuyPut(float fprc, int amnt, int per = 100);// n개씩 구매
    void			BuyPutR(float fprc, int per = 100);// 랜덤한 수량(1~3)으로 랜덤한 시간간격(100~300ms) 을 가지고 주문-> Request100() (가격, 수량n)
    void			SetPrice(int per = 50); // 50% 가격다운후 세팅

	afx_msg void OnBnClickedSaveCsv();
	afx_msg void OnBnClickedButtonRequest();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonRequest2();
	afx_msg void OnBnClickedBttnprofit2();
	afx_msg void OnBnClickedBttnprofit3();
	afx_msg	LRESULT		OnXMReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT		OnXMTimeoutData(WPARAM wParam, LPARAM lParam);
	LRESULT				OnXMReceiveRealData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin19(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin18(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin20(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClick2830outblock(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClick2830outblock2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:

	int ID2816, ID2830, ID2830_, ID2831, ID2831_, ID100, ID200, ID300, ID600, ID21200, ID31200, ID0167, ID2813, ID2301;
	long acnt, lBal, lCallQty, lPutQty, lLqdt, lCmpVol;
	BOOL bCall, bPut;

	//변동성, 델타, 감마, 세타 (2301)
	float fCallIV, fCallDelta, fCallGamma, fCallTheta, fCallVega, fCallHigh, fCallLow, fCallOpen, fPutIV, fPutDelta, fPutGamma, fPutTheta, fPutVega, fPutHigh, fPutLow, fPutOpen;
	BOOL bToken, bAutoToken;// 옵션전광판 콜/풋 코드 유지여부 1:유지(2301), 자동 옵션매수 설정
    float fCallAvrPrc, fPutAvrPrc, fCmpPrc, fCho9, fPho9;
    long lCho9, lPho9;

	int nCurMin, nCorrectTime;// 현재 총시간 분으로 환산
    int gIter; //구매횟수(100/%) 변수

	char m_szContKey[30]; // 연속키 저장

	long *lArFornBuy;// 외인선물거래량 foreingers

	// BuyOption() 매수
	queue<int> nQBuyQty;
	queue<float> fQBuyPrc;
	// BuyOption() 청산
	queue<int> nQSellQty;
	queue<float> fQSellPrc;

	CEdit m_focode, m_focode2;
	CString strTime; // %HHMMSS
	CString strMonth; // %Y%m	
	CString FutureCode, CallCode, PutCode, CallCode2, PutCode2, CallCode3, PutCode3; //다량매매시 여러개 코드를 구입
	CString strCallPrc, strPutPrc, strOrgOrdNo, strUsableMoney, strCallDelta, strPutDelta;


	CListCtrl m_2816listctrl;
	CListCtrl m_2830listctrl;
	CListCtrl m_2830listctrl_;

	CEdit m_qty;
	CEdit m_orgordno;
	CEdit m_ordprc;
	CEdit m_ordno;

	CStatic m_stime;
	CStatic m_index;
	CStatic m_persnp;
	CStatic m_fornbuy;
	CStatic m_fornbuy2;
	CStatic m_fornbuy3;
	CStatic m_fornbuy4;
	CStatic m_fornbuy5;
	CStatic m_fornbuy6;
	CStatic m_fornbuy7;
	CStatic m_fornbuy8;
	CStatic m_fornbuy9;
	CStatic m_fornbuy10;
	CStatic m_ststxt;

	afx_msg void OnDeltaposSpin21(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin22(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBttnprofit5();
	afx_msg void OnBnClickedButtonRequest11();
    afx_msg void OnCustomdraw2830outblock(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnCustomdraw2830outblock2(NMHDR* pNMHDR, LRESULT* pResult);
};
