// Dlg_t1101.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Dlg_t1101.h"

#include "./Packet/t2105.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_t1101 dialog

IMPLEMENT_DYNCREATE(CDlg_t1101, CDialog)

// CDlg_t1101::CDlg_t1101(CWnd* pParent /*=NULL*/)
// : CDialog(CDlg_t1101::IDD, pParent)
CDlg_t1101::CDlg_t1101()
{
	//{{AFX_DATA_INIT(CDlg_t1101)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_t1101::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_t1101)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_OUTBLOCK, m_ctrlOutBlock);
	DDX_Control(pDX, IDC_INBLOCK_SHCODE, m_code);
}


BEGIN_MESSAGE_MAP(CDlg_t1101, CDialog)
	//{{AFX_MSG_MAP(CDlg_t1101)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED( IDC_BUTTON_REQUEST,		  OnButtonRequest	  )
	ON_MESSAGE	 ( WM_USER + XM_RECEIVE_DATA, OnXMReceiveData	  )
	ON_MESSAGE	 ( WM_USER + XM_TIMEOUT_DATA, OnXMTimeoutData	  )
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlg_t1101::OnBnClickedButtonStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_t1101 message handlers

BOOL CDlg_t1101::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitCtrls();
	m_code.SetWindowTextA("201MA322");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_t1101::OnButtonRequest() 
{
	RequestData();
	SetTimer(1, 1000, NULL);
}


//--------------------------------------------------------------------------------------
// ��Ʈ�� �ʱ�ȭ
//--------------------------------------------------------------------------------------
void CDlg_t1101::InitCtrls()
{
	m_ctrlOutBlock.InsertColumn( 0, "�ʵ��", LVCFMT_LEFT, 150 );
	m_ctrlOutBlock.InsertColumn( 1, "������", LVCFMT_LEFT, 200 );

	// List Control�� OutBlock �ʵ���� �־��ش�.
	m_ctrlOutBlock.InsertItem(  0, "�����            " );
	m_ctrlOutBlock.InsertItem(  1, "���簡            " );
	m_ctrlOutBlock.InsertItem(  2, "���ϴ�񱸺�      " );
	m_ctrlOutBlock.InsertItem(  3, "���ϴ��          " );
	m_ctrlOutBlock.InsertItem(  4, "�����            " );
	m_ctrlOutBlock.InsertItem(  5, "�ŷ���        " );
	m_ctrlOutBlock.InsertItem(	6, "�ŷ������ð��� ");
	m_ctrlOutBlock.InsertItem(  7, "��������          " );
	m_ctrlOutBlock.InsertItem(  8, "�ŵ�ȣ��1         " );
	m_ctrlOutBlock.InsertItem(  9, "�ż�ȣ��1         " );
	m_ctrlOutBlock.InsertItem( 10, "�ŵ�ȣ������1     " );
	m_ctrlOutBlock.InsertItem( 11, "�ż�ȣ������1     " );
	m_ctrlOutBlock.InsertItem( 12, "�ŵ�ȣ���Ǽ�1 " );
	m_ctrlOutBlock.InsertItem( 13, "�ż�ȣ���Ǽ�1 " );
	m_ctrlOutBlock.InsertItem( 14, "�ŵ�ȣ��2         " );
	m_ctrlOutBlock.InsertItem( 15, "�ż�ȣ��2         " );
	m_ctrlOutBlock.InsertItem( 16, "�ŵ�ȣ������2     " );
	m_ctrlOutBlock.InsertItem( 17, "�ż�ȣ������2     " );
	m_ctrlOutBlock.InsertItem( 18, "�ŵ�ȣ���Ǽ�2 " );
	m_ctrlOutBlock.InsertItem( 19, "�ż�ȣ���Ǽ�2 " );
	m_ctrlOutBlock.InsertItem( 20, "�ŵ�ȣ��3         " );
	m_ctrlOutBlock.InsertItem( 21, "�ż�ȣ��3         " );
	m_ctrlOutBlock.InsertItem( 22, "�ŵ�ȣ������3     " );
	m_ctrlOutBlock.InsertItem( 23, "�ż�ȣ������3     " );
	m_ctrlOutBlock.InsertItem( 24, "�ŵ�ȣ���Ǽ�3 " );
	m_ctrlOutBlock.InsertItem( 25, "�ż�ȣ���Ǽ�3 " );
	m_ctrlOutBlock.InsertItem( 26, "�ŵ�ȣ��4         " );
	m_ctrlOutBlock.InsertItem( 27, "�ż�ȣ��4         " );
	m_ctrlOutBlock.InsertItem( 28, "�ŵ�ȣ������4     " );
	m_ctrlOutBlock.InsertItem( 29, "�ż�ȣ������4     " );
	m_ctrlOutBlock.InsertItem( 30, "�ŵ�ȣ���Ǽ�4 " );
	m_ctrlOutBlock.InsertItem( 31, "�ż�ȣ���Ǽ�4 " );
	m_ctrlOutBlock.InsertItem( 32, "�ŵ�ȣ��5         " );
	m_ctrlOutBlock.InsertItem( 33, "�ż�ȣ��5         " );
	m_ctrlOutBlock.InsertItem( 34, "�ŵ�ȣ������5     " );
	m_ctrlOutBlock.InsertItem( 35, "�ż�ȣ������5     " );
	m_ctrlOutBlock.InsertItem( 36, "�ŵ�ȣ���Ǽ�5 " );
	m_ctrlOutBlock.InsertItem( 37, "�ż�ȣ���Ǽ�5 " );
	m_ctrlOutBlock.InsertItem( 38, "�ŵ�ȣ���Ѽ���    " );
	m_ctrlOutBlock.InsertItem( 39, "�ż�ȣ���Ѽ���    " );
	m_ctrlOutBlock.InsertItem( 40, "�Ѹŵ�ȣ���Ǽ�" );
	m_ctrlOutBlock.InsertItem( 41, "�Ѹż�ȣ���Ǽ�" );
	m_ctrlOutBlock.InsertItem( 42, "���Žð�          " );
	m_ctrlOutBlock.InsertItem( 43, "�����ڵ�          " );
}

//--------------------------------------------------------------------------------------
// ������ ��ȸ
//--------------------------------------------------------------------------------------
void CDlg_t1101::RequestData( BOOL bNext )
{
	//-----------------------------------------------------------
	// �ֽ����簡ȣ����ȸ(t1101) ( attr,block,headtype=A )
	t2105InBlock	pckInBlock;

	TCHAR			szTrNo[]	= "t2105";
	char			szNextKey[]	= "";

	//-----------------------------------------------------------
	// ������ ���
	CString str_shcode="201M9317";		SetDlgItemText( IDC_INBLOCK_SHCODE, str_shcode );		// �����ڵ�

	//-----------------------------------------------------------
	// ������ �ʱ�ȭ
	FillMemory( &pckInBlock, sizeof( pckInBlock ), ' ' );

	//-----------------------------------------------------------
	// ������ �Է�
	SetPacketData( pckInBlock.shcode, sizeof( pckInBlock.shcode ), str_shcode, DATA_TYPE_STRING );	

	//�� �����
	//((CListCtrl*)GetDlgItem(IDC_OUTBLOCK))->DeleteAllItems();

	//-----------------------------------------------------------
	// ������ ����
	int nRqID = g_iXingAPI.Request( 
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_DATA ���� �´�.
		szTrNo,						// TR ��ȣ
		&pckInBlock,				// InBlock ������
		sizeof( pckInBlock ),		// InBlock ������ ũ��
		bNext,						// ������ȸ ���� : ������ȸ�� ��쿡 �����Ѵ�.
		szNextKey,					// ������ȸ Key : Header Type�� B �� ��쿣 ���� ��ȸ�� ���� Next Key�� �־��ش�.
		30							// Timeout(��) : �ش� �ð�(��)���� �����Ͱ� ���� ������ Timeout�� �߻��Ѵ�. XM_TIMEOUT_DATA �޽����� �߻��Ѵ�.
	);
	
	//-----------------------------------------------------------
	// Request ID�� 0���� ���� ��쿡�� �����̴�.
	if( nRqID < 0 )
	{
		MessageBox( "��ȸ����", "����", MB_ICONSTOP );
	}
}

//--------------------------------------------------------------------------------------
// �����͸� ����
//--------------------------------------------------------------------------------------
LRESULT CDlg_t1101::OnXMReceiveData( WPARAM wParam, LPARAM lParam )
{
	//-------------------------------------------------------------------------------------
	// Data�� ����
	if( wParam == REQUEST_DATA )
	{
		LPRECV_PACKET pRpData = (LPRECV_PACKET)lParam;

		LPt2105OutBlock pOutBlock = (LPt2105OutBlock)pRpData->lpData;

		m_ctrlOutBlock.SetItemText(  0, 1, GetDispData( pOutBlock->hname        , sizeof( pOutBlock->hname         ), DATA_TYPE_STRING ) );
		m_ctrlOutBlock.SetItemText(  1, 1, GetDispData( pOutBlock->price        , sizeof( pOutBlock->price         ), DATA_TYPE_DOT,2  ) );
		m_ctrlOutBlock.SetItemText(  2, 1, GetDispData( pOutBlock->sign         , sizeof( pOutBlock->sign          ), DATA_TYPE_STRING ) );
		m_ctrlOutBlock.SetItemText(  3, 1, GetDispData( pOutBlock->change       , sizeof( pOutBlock->change        ), DATA_TYPE_DOT,2));
		m_ctrlOutBlock.SetItemText(  4, 1, GetDispData( pOutBlock->diff         , sizeof( pOutBlock->diff          ), DATA_TYPE_DOT , 2 ) );
		m_ctrlOutBlock.SetItemText(  5, 1, GetDispData( pOutBlock->volume       , sizeof( pOutBlock->volume        ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText(6, 1, GetDispData(pOutBlock->stimeqrt		, sizeof(pOutBlock->stimeqrt		), DATA_TYPE_FLOAT,2));
		m_ctrlOutBlock.SetItemText(  7, 1, GetDispData( pOutBlock->jnilclose    , sizeof( pOutBlock->jnilclose     ), DATA_TYPE_DOT,2));
		m_ctrlOutBlock.SetItemText(  8, 1, GetDispData( pOutBlock->offerho1     , sizeof( pOutBlock->offerho1      ), DATA_TYPE_DOT,2));
		m_ctrlOutBlock.SetItemText(  9, 1, GetDispData( pOutBlock->bidho1       , sizeof( pOutBlock->bidho1        ), DATA_TYPE_DOT,2));
		m_ctrlOutBlock.SetItemText( 10, 1, GetDispData( pOutBlock->offerrem1    , sizeof( pOutBlock->offerrem1     ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 11, 1, GetDispData( pOutBlock->bidrem1      , sizeof( pOutBlock->bidrem1       ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 12, 1, GetDispData( pOutBlock->dcnt1		, sizeof( pOutBlock->dcnt1			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 13, 1, GetDispData( pOutBlock->scnt1		, sizeof( pOutBlock->scnt1			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 14, 1, GetDispData( pOutBlock->offerho2     , sizeof( pOutBlock->offerho2      ), DATA_TYPE_DOT,2) );
		m_ctrlOutBlock.SetItemText( 15, 1, GetDispData( pOutBlock->bidho2       , sizeof( pOutBlock->bidho2        ), DATA_TYPE_DOT,2) );
		m_ctrlOutBlock.SetItemText( 16, 1, GetDispData( pOutBlock->offerrem2    , sizeof( pOutBlock->offerrem2     ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 17, 1, GetDispData( pOutBlock->bidrem2      , sizeof( pOutBlock->bidrem2       ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 18, 1, GetDispData( pOutBlock->dcnt2		, sizeof( pOutBlock->dcnt2			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 19, 1, GetDispData( pOutBlock->scnt2		, sizeof( pOutBlock->scnt2			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 20, 1, GetDispData( pOutBlock->offerho3     , sizeof( pOutBlock->offerho3      ), DATA_TYPE_DOT,2) );
		m_ctrlOutBlock.SetItemText( 21, 1, GetDispData( pOutBlock->bidho3       , sizeof( pOutBlock->bidho3        ), DATA_TYPE_DOT,2) );
		m_ctrlOutBlock.SetItemText( 22, 1, GetDispData( pOutBlock->offerrem3    , sizeof( pOutBlock->offerrem3     ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 23, 1, GetDispData( pOutBlock->bidrem3      , sizeof( pOutBlock->bidrem3       ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 24, 1, GetDispData( pOutBlock->dcnt3		, sizeof( pOutBlock->dcnt3			 ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 25, 1, GetDispData( pOutBlock->scnt3		, sizeof( pOutBlock->scnt3			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 26, 1, GetDispData( pOutBlock->offerho4     , sizeof( pOutBlock->offerho4      ), DATA_TYPE_DOT,2) );
		m_ctrlOutBlock.SetItemText( 27, 1, GetDispData( pOutBlock->bidho4       , sizeof( pOutBlock->bidho4        ), DATA_TYPE_DOT,2) );
		m_ctrlOutBlock.SetItemText( 28, 1, GetDispData( pOutBlock->offerrem4    , sizeof( pOutBlock->offerrem4     ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 29, 1, GetDispData( pOutBlock->bidrem4      , sizeof( pOutBlock->bidrem4       ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 30, 1, GetDispData( pOutBlock->dcnt4		, sizeof( pOutBlock->dcnt4			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 31, 1, GetDispData( pOutBlock->scnt4		, sizeof( pOutBlock->scnt4			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 32, 1, GetDispData( pOutBlock->offerho5     , sizeof( pOutBlock->offerho5      ), DATA_TYPE_DOT,2) );
		m_ctrlOutBlock.SetItemText( 33, 1, GetDispData( pOutBlock->bidho5       , sizeof( pOutBlock->bidho5        ), DATA_TYPE_DOT,2) );
		m_ctrlOutBlock.SetItemText( 34, 1, GetDispData( pOutBlock->offerrem5    , sizeof( pOutBlock->offerrem5     ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 35, 1, GetDispData( pOutBlock->bidrem5      , sizeof( pOutBlock->bidrem5       ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 36, 1, GetDispData( pOutBlock->dcnt5		, sizeof( pOutBlock->dcnt5			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 37, 1, GetDispData( pOutBlock->scnt5		, sizeof( pOutBlock->scnt5			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 38, 1, GetDispData( pOutBlock->dvol			, sizeof( pOutBlock->dvol			), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 39, 1, GetDispData( pOutBlock->svol         , sizeof( pOutBlock->svol           ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 40, 1, GetDispData( pOutBlock->toffernum    , sizeof( pOutBlock->toffernum       ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText( 41, 1, GetDispData( pOutBlock->tbidnum      , sizeof( pOutBlock->tbidnum         ), DATA_TYPE_LONG   ) );
		m_ctrlOutBlock.SetItemText(42, 1, GetDispData(pOutBlock->time			, sizeof(pOutBlock->time			), DATA_TYPE_STRING));
		m_ctrlOutBlock.SetItemText( 43, 1, GetDispData( pOutBlock->shcode       , sizeof( pOutBlock->shcode        ), DATA_TYPE_STRING ) );
	}
	
	//-------------------------------------------------------------------------------------
	// �޽����� ����
	else if( wParam == MESSAGE_DATA )
	{
		LPMSG_PACKET pMsg = (LPMSG_PACKET)lParam;

		CString strMsg( (char*)pMsg->lpszMessageData, pMsg->nMsgLength );
		GetParent()->SendMessage( WMU_SET_MESSAGE, (WPARAM)pMsg->szMsgCode, (LPARAM)(LPCTSTR)strMsg );		
		
		g_iXingAPI.ReleaseMessageData( lParam );
	}
	
	//-------------------------------------------------------------------------------------
	// System Error�� ����
	else if( wParam == SYSTEM_ERROR_DATA )
	{
		LPMSG_PACKET pMsg = (LPMSG_PACKET)lParam;
		
		CString strMsg( (char*)pMsg->lpszMessageData, pMsg->nMsgLength );
		GetParent()->SendMessage( WMU_SET_MESSAGE, (WPARAM)pMsg->szMsgCode, (LPARAM)(LPCTSTR)strMsg );		

		g_iXingAPI.ReleaseMessageData( lParam );
	}

	//-------------------------------------------------------------------------------------
	// Release Data�� ����
	else if( wParam == RELEASE_DATA )
	{
		g_iXingAPI.ReleaseRequestData( (int)lParam );
	}

	return 0L;
}

//--------------------------------------------------------------------------------------
// Timeout �߻�
//--------------------------------------------------------------------------------------
LRESULT CDlg_t1101::OnXMTimeoutData( WPARAM wParam, LPARAM lParam )
{
	g_iXingAPI.ReleaseRequestData( (int)lParam );

	return 0L;
}

void CDlg_t1101::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
}


void CDlg_t1101::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
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
