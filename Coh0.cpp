// Coh0.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Coh0.h"

#include "./packet/OH0.h"


// Coh0

IMPLEMENT_DYNAMIC(Coh0, CWnd)

Coh0::Coh0()
{

}

Coh0::~Coh0()
{
}


BEGIN_MESSAGE_MAP(Coh0, CWnd)
	ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealOH0)
END_MESSAGE_MAP()



// Coh0 message handlers
void Coh0::AdviseOH0()
{
	TCHAR	szTrCode[] = "OH0";

	//-----------------------------------------------------------
	// 데이터 취득
	CString strCode = "201M9317";
	//GetDlgItemText(IDC_EDIT_CODE, strCode);

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		strCode,					// 종목코드
		strCode.GetLength()
		//sizeof(OH0_InBlock)		// 종목코드 길이
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
void Coh0::UnadviseOH0()
{
	//-----------------------------------------------------------
	// 이전에 등록한 종목이 없다면 Return한다.
	if (m_strCode.IsEmpty())
	{
		return;
	}

	TCHAR	szTrCode[] = "OH0";

	//-----------------------------------------------------------
	// 데이터 전송
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// 데이터를 받을 윈도우, XM_RECEIVE_REAL_DATA 으로 온다.
		szTrCode,					// TR 번호
		m_strCode,					// 종목코드
		m_strCode.GetLength()
		//sizeof(OH0_InBlock)		// 종목코드 길이
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
LRESULT Coh0::OnXMReceiveRealOH0(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;

	if (strcmp(pRealPacket->szTrCode, "OH0") == 0)
	{

		LPOH0_OutBlock pOutBlock = (LPOH0_OutBlock)pRealPacket->pszData;
		//int nRow = 0;
		//m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->hotime, sizeof(pOutBlock->hotime), DATA_TYPE_STRING));    // 호가시간
	}
	return 0L;
}
