// Ct2830.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Ct2830.h"
#include "./packet/t2830.h"


// Ct2830

IMPLEMENT_DYNAMIC(Ct2830, CWnd)

Ct2830::Ct2830()
{

}

Ct2830::~Ct2830()
{
}


BEGIN_MESSAGE_MAP(Ct2830, CWnd)
	ON_MESSAGE(WM_USER + XM_RECEIVE_DATA, OnXMReceiveData)
	ON_MESSAGE(WM_USER + XM_TIMEOUT_DATA, OnXMTimeoutData)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// Ct2830 message handlers
void Ct2830::RequestData(BOOL bNext)
{
	//-----------------------------------------------------------
	// Eurex 시세조회
	t2830InBlock	pckInBlock;
	TCHAR			szTrNo[] = "t2830";
	char			szNextKey[] = "";

	//-----------------------------------------------------------
	// 데이터 취득
	CString str_focode = "201M9317";	//SetDlgItemText(IDC_INBLOCK_SHCODE, str_shcode);

	//-----------------------------------------------------------
	// 데이터 초기화
	FillMemory(&pckInBlock, sizeof(pckInBlock), ' ');

	//-----------------------------------------------------------
	// 데이터 입력
	SetPacketData(pckInBlock.focode, sizeof(pckInBlock.focode), str_focode, DATA_TYPE_STRING);

	//블럭 지우기
	//((CListCtrl*)GetDlgItem(IDC_OUTBLOCK))->DeleteAllItems();

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
}

//--------------------------------------------------------------------------------------
// 데이터를 받음
//--------------------------------------------------------------------------------------
LRESULT Ct2830::OnXMReceiveData(WPARAM wParam, LPARAM lParam)
{
	//-------------------------------------------------------------------------------------
	// Data를 받음
	if (wParam == REQUEST_DATA)
	{
		LPRECV_PACKET pRpData = (LPRECV_PACKET)lParam;
		LPt2830OutBlock pOutBlock = (LPt2830OutBlock)pRpData->lpData;

		//m_ctrlOutBlock.SetItemText(0, 1, GetDispData(pOutBlock->hname, sizeof(pOutBlock->hname), DATA_TYPE_STRING));
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
LRESULT Ct2830::OnXMTimeoutData(WPARAM wParam, LPARAM lParam)
{
	g_iXingAPI.ReleaseRequestData((int)lParam);

	return 0L;
}

