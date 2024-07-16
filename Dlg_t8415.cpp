// Dlg_t8415.cpp : implementation file
//

#include "stdafx.h"
#include "xingapi_sample.h"
#include "Dlg_t8415.h"
#include "./Packet/t8415.h"
#include "./packet/t1602.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_t8415 dialog


IMPLEMENT_DYNCREATE(CDlg_t8415, CDialog)

CDlg_t8415::CDlg_t8415(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_t8415::IDD, pParent)
{
}


void CDlg_t8415::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_t8415, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceiveData)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeoutData)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_t8415 message handlers

BOOL CDlg_t8415::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 30초, 120*6.5+10+1=791
	arrs1 = new CString[40];
	arr1 = new float[40];
	arr2 = new float[40];
	arr3 = new float[40];
	arr4 = new long[40];
	arr6 = new float[40];
	arr7 = new float[40];
	arr8 = new float[40];

	memset(arr1, 0, 40 * sizeof(float));
	memset(arr2, 0, 40 * sizeof(float));
	memset(arr3, 0, 40 * sizeof(float));
	memset(arr4, 0, 40 * sizeof(float));
	memset(arr6, 0, 40 * sizeof(float));
	memset(arr7, 0, 40 * sizeof(float));
	memset(arr8, 0, 40 * sizeof(float));
	return TRUE; 
}

void CDlg_t8415::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	delete[] arrs1;	
	delete[] arr1;	delete[] arr2;	delete[] arr3;	delete[] arr4;	delete[] arr6;
	delete[] arr7;	delete[] arr8;	

	arrs1 = NULL;	
	arr1 = NULL;	arr2 = NULL;	arr3 = NULL;	arr4 = NULL;	arr6 = NULL;
	arr7 = NULL;	arr8 = NULL;	
}


//--------------------------------------------------------------------------------------
// 8415 현재가
//--------------------------------------------------------------------------------------
void CDlg_t8415::Request8415(BOOL bNext)
{
	//-----------------------------------------------------------
	// 시간별 가격 및 거래량(t8415) ( attr,block,headtype=A )
	t8415InBlock	pckInBlock;

	TCHAR			szTrNo[] = "t8415";

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');
	CTime t = CTime::GetCurrentTime();
	int nToday = t.GetDayOfWeek(); //금일 요일(일요일=1)
	if (nToday == 2)
		t -= CTimeSpan(3, 0, 0, 0);
	else
		t -= CTimeSpan(1, 0, 0, 0);
	CString strFilePath = t.Format("%Y%m%d");
	CString strDate = t.Format("%Y%m%d");
	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.shcode, sizeof(pckInBlock.shcode), "101NC000", DATA_TYPE_STRING);  
	SetPacketData(pckInBlock.ncnt, sizeof(pckInBlock.ncnt), "10", DATA_TYPE_STRING);
	SetPacketData(pckInBlock.qrycnt, sizeof(pckInBlock.qrycnt), "40", DATA_TYPE_STRING);
	SetPacketData(pckInBlock.nday, sizeof(pckInBlock.nday), "0", DATA_TYPE_STRING);      
	SetPacketData(pckInBlock.sdate, sizeof(pckInBlock.sdate), strDate, DATA_TYPE_STRING);       
	SetPacketData(pckInBlock.edate, sizeof(pckInBlock.edate), strDate, DATA_TYPE_STRING);   
	SetPacketData(pckInBlock.comp_yn, sizeof(pckInBlock.comp_yn), "N", DATA_TYPE_STRING);  

	//-----------------------------------------------------------
	// 데이터 전송
	int nRqID = g_iXingAPI.Request( GetSafeHwnd(), szTrNo, &pckInBlock, sizeof(pckInBlock), bNext, "", 30);
	
	//-----------------------------------------------------------
	// Request ID가 0보다 작을 경우에는 에러이다.
	if (nRqID < 0)
	{
		MessageBox("조회실패", "에러", MB_ICONSTOP);
	}
	ID8415 = nRqID;
}

//--------------------------------------------------------------------------------------
// 데이터를 받음
//--------------------------------------------------------------------------------------
LRESULT CDlg_t8415::OnXMReceiveData(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data를 받음
	if (wParam == REQUEST_DATA)
	{
		LPRECV_PACKET pRpData = (LPRECV_PACKET)lParam;
		if (pRpData->nRqID == ID8415)
		{
			Receive8415(pRpData);
		}	

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
LRESULT CDlg_t8415::OnXMTimeoutData(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);
	return 0L;
}

void CDlg_t8415::OnButtonRequest()
{
	//Request1602("4","900","1");
	Request8415();
}


void CDlg_t8415::Receive8415(LPRECV_PACKET pRpData)//현재가
{
	if (strcmp(pRpData->szBlockName, NAME_t8415OutBlock1) == 0)
	{
		LPt8415OutBlock1 pOutBlock = (LPt8415OutBlock1)pRpData->lpData;
		int				 nCount = pRpData->nDataLength / sizeof(t8415OutBlock1);		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
		float f1 = 0.0, f2 = 0.0, f3 = 0.0, f4 = 0.0, f5 = 0.0;

		for (int i = 0; i < nCount; i++)
		{
			CString s1, s2, s3, s4, s5;		

			s1 = GetDispData(pOutBlock[i].time, sizeof(pOutBlock[i].time), DATA_TYPE_STRING); arrs1[i] = s1;
			s2 = GetDispData(pOutBlock[i].close, sizeof(pOutBlock[i].close), DATA_TYPE_FLOAT, 2); arr1[i] = atof(s2);
			s3 = GetDispData(pOutBlock[i].high, sizeof(pOutBlock[i].high), DATA_TYPE_FLOAT, 2); arr2[i] = atof(s3);
			s4 = GetDispData(pOutBlock[i].low, sizeof(pOutBlock[i].low), DATA_TYPE_FLOAT, 2); arr3[i] = atof(s4);
			s5 = GetDispData(pOutBlock[i].jdiff_vol, sizeof(pOutBlock[i].jdiff_vol), DATA_TYPE_LONG); arr4[i] = atol(s5);
		}
		if (nCount > 7)
		{

			for (int i = 4; i < nCount; i++)
			{
				float f3 = arr2[i], f4 = arr3[i];		//close max,min(10분동안)
				for (int k = 0; k < 5; k++)
				{
					if (arr2[i - k] > f3)	f3 = arr2[i - k];			//max
					if (arr3[i - k] < f4)		f4 = arr3[i - k];				//min
				}			

				if (f3 == f4)
					arr6[i] = 100;											//arr6 : %K(분모가 0인경우)
				else
					arr6[i] = (arr1[i] - f4) / (f3 - f4) * 100;			//%K(5) = (Current Close - Lowest Low)/(Highest High - Lowest Low) - Basic calculation				
			}

			for (int i = 6; i < nCount; i++)
			{
			
				float f5 = 0.0;
				for (int k = 0; k < 3; k++)
					f5 += arr6[i - k];
				arr7[i] = f5 / 3.0;											//%D(3)= slow %K(3) ; 3분 SMA of %K ------------------------- SMA:단순이동평균
			}

			for (int i = 8; i < nCount; i++)
			{
				
				float f5 = 0.0;
				for (int k = 0; k < 3; k++)
					f5 += arr7[i - k];
				arr8[i] = f5 / 3.0;										//%slow D(3) ; 3분 SMA of slow %K ------------------------- SMA:단순이동평균
			}
		}

		CTime t = CTime::GetCurrentTime();
		int nToday = t.GetDayOfWeek(); //금일 요일(일요일=1)
		if (nToday == 2)
			t -= CTimeSpan(3, 0, 0, 0);
		else
			t -= CTimeSpan(1, 0, 0, 0);
		CString strFilePath = t.Format("%Y%m%d");
		CString strDate = t.Format("%Y%m%d");
		CString temp = strDate + "_10m.csv";
		ofstream myfile2(temp); // 선물,옵션 가격(10분봉)
		if (myfile2.is_open())
		{
			myfile2 << "시간, 고가, 저가, 종가, %K, %D, %SlowD\n";
			for (int i = 0; i < nCount; i++)
			{
				
				myfile2 << arrs1[i] << ", " << arr2[i] << ", " << arr3[i] << ", " << arr1[i] << ", " << arr6[i] << ", " << arr7[i] << ", " << arr8[i]<< "\n";
			}
		}
		myfile2.close();
	}
	return;
}
