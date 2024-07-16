// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "XingAPI_Sample.h"

#include "ChildFrm.h"


#include "Dlg_JEKYLL.h"				// ������ȸ
// �ֽ�
#include "Dlg_t1101.h"				// �ֽ����簡ȣ����ȸ
#include "Dlg_t1301.h"				// �ֽĽð��뺰ü����ȸ
#include "Dlg_t1305.h"				// �Ⱓ���ְ�
#include "Dlg_t1452.h"				// �ŷ�������

#include "Dlg_H1_.h"
#include "Dlg_H2_.h"
#include "Dlg_h3_ELW.h"
#include "Dlg_h2_ELW.h"

#include "Dlg_CSPAT00600.h"			// ���������ֹ�
#include "Dlg_CSPAT00700.h"			// ���������ֹ�
#include "Dlg_CSPAT00800.h"			// ��������ֹ�

#include "Dlg_SC0.h"				// �ֽ��ֹ�����
#include "Dlg_SC1.h"				// �ֽ��ֹ�ü��
#include "Dlg_SC2.h"				// �ֽ��ֹ�����
#include "Dlg_SC3.h"				// �ֽ��ֹ����
#include "Dlg_SC4.h"				// �ֽ��ֹ��ź�

#include "Dlg_CSPAQ03700.h"			// �������� �ֹ�ü�᳻�� ��ȸ
#include "Dlg_CSPAQ02300.h"			// �������� �ܰ��� ��ȸ
#include "Dlg_CSPAQ02200.h"			// �������� ������/�ֹ����ɱݾ�/���� ��ȸ
#include "Dlg_CSPBQ00200.h"			// �������� ���űݷ��� �ֹ����ɼ��� ��ȸ

// �����ɼ�
#include "Dlg_FC0.h"				// ����ü��
#include "Dlg_FH0.h"				// ����ȣ��
#include "Dlg_OC0.h"				// �ɼ�ü��
#include "Dlg_OH0.h"				// �ɼ�ȣ��
#include "Dlg_OH1.h"				// �ɼ�ȣ��2
#include "Dlg_EH0.h"				// �ɼ�ȣ��(�߰�)
#include "Dlg_t8415.h"              // ����/�ɼ���Ʈ

#include "Dlg_CFOAT00100.h"			// �����ɼ� �����ֹ�
#include "Dlg_CFOAT00200.h"			// �����ɼ� �����ֹ�
#include "Dlg_CFOAT00300.h"			// �����ɼ� ����ֹ�

#include "Dlg_CFOAQ00600.h"			// �����ɼ� �����ֹ�ü�᳻�� ��ȸ
#include "Dlg_CFOFQ02400.h"			// �����ɼ� �̰���������Ȳ
#include "Dlg_CFOAQ10100.h"			// �����ɼ� �ֹ����ɼ���
#include "Dlg_CEXAQ21200.h"			// ������ �ֹ����ɼ���
#include "Dlg_night.h"				// ������ �ü���ȸ



// ���� CME
#include "Dlg_CCEAT00100.h"			// ���� CME �����ֹ�
#include "Dlg_CCEAT00200.h"			// ���� CME �����ֹ�
#include "Dlg_CCEAT00300.h"			// ���� CME ����ֹ�

// �ֽļ���
#include "Dlg_JC0.h"

// �����ں�
#include "Dlg_t1601.h"				// �����ں�����
#include "Dlg_t1602.h"				// �����ڸŸ����� ��

#include "Dlg_BMT.h"
#include "Dlg_BM_.h"

// ��Ÿ
#include "Dlg_t9942.h"				// API�� ELW ��������ȸ
#include "Dlg_t9943.h"				// API�� �������� ��������ȸ

static TR_WINDOW_TABLE s_tblTrWindow[] = 
{
	//---------------------------------------------------------------------------------------------
	// �ֽ�/ELW �ü�
	{ "����/�ɼ�" , "�ü�", "��ȸTR",   "t2105"     , RUNTIME_CLASS(CDlg_t1101     ), IDD_t1101     , "�ɼ� ���簡��ȸ(t2105)" },
	{ "������" , "�ü�", "��ȸTR",   "t2830"     , RUNTIME_CLASS(CDlg_night	), IDD_night     , "������ �ü���ȸ(t2830)" },
	{ "������", "�ɼǽü�", "�ǽð�TR", "EH0"       , RUNTIME_CLASS(CDlg_EH0),	IDD_EH0      , "�߰��ɼ�ü��" },
 	/*{ "�ֽ�/ELW" , "�ü�", "��ȸTR",   "t1301"     , RUNTIME_CLASS(CDlg_t1301     ), IDD_t1301     , "�ֽĽð��뺰ü����ȸ(t1301)" },
 	{ "�ֽ�/ELW" , "�ü�", "��ȸTR",   "t1305"     , RUNTIME_CLASS(CDlg_t1305     ), IDD_t1305     , "�Ⱓ���ְ�(t1305)" },
 	{ "�ֽ�/ELW" , "�ü�", "��ȸTR",   "t1452"     , RUNTIME_CLASS(CDlg_t1452     ), IDD_t1452     , "�ŷ�������(t1452)" },

	{ "�ֽ�/ELW" , "�ü�", "�ǽð�TR", "H1_"       , RUNTIME_CLASS(CDlg_H1_       ), IDD_H1_       , "KOSPI ȣ���ܷ�" },
	{ "�ֽ�/ELW" , "�ü�", "�ǽð�TR", "H2_"       , RUNTIME_CLASS(CDlg_H2_       ), IDD_H2_       , "KOSPI �ð���ȣ���ܷ�" },
	{ "�ֽ�/ELW" , "�ü�", "�ǽð�TR", "h3_"       , RUNTIME_CLASS(CDlg_h3_ELW    ), IDD_h3_ELW    , "ELW ȣ���ܷ�" },
	{ "�ֽ�/ELW" , "�ü�", "�ǽð�TR", "h2_"       , RUNTIME_CLASS(CDlg_h2_ELW    ), IDD_h2_ELW    , "ELW �ð���ȣ���ܷ�" },
	//---------------------------------------------------------------------------------------------*/

	//---------------------------------------------------------------------------------------------
	// �ֽ�/ELW �ֹ�
	/*{ "�ֽ�/ELW" , "�ֹ�", "��ȸTR",   "CSPAT00600", RUNTIME_CLASS(CDlg_CSPAT00600), IDD_CSPAT00600, "���������ֹ�(CSPAT00600)" },
	{ "�ֽ�/ELW" , "�ֹ�", "��ȸTR",   "CSPAT00700", RUNTIME_CLASS(CDlg_CSPAT00700), IDD_CSPAT00700, "���������ֹ�(CSPAT00700)" },
 	{ "�ֽ�/ELW" , "�ֹ�", "��ȸTR",   "CSPAT00800", RUNTIME_CLASS(CDlg_CSPAT00800), IDD_CSPAT00800, "��������ֹ�(CSPAT00800)" },
	
	{ "�ֽ�/ELW" , "�ֹ�", "�ǽð�TR", "SC0"       , RUNTIME_CLASS(CDlg_SC0       ), IDD_SC0       , "�ֽ��ֹ�����" },
	{ "�ֽ�/ELW" , "�ֹ�", "�ǽð�TR", "SC1"       , RUNTIME_CLASS(CDlg_SC1       ), IDD_SC1       , "�ֽ��ֹ�ü��" },
	{ "�ֽ�/ELW" , "�ֹ�", "�ǽð�TR", "SC2"       , RUNTIME_CLASS(CDlg_SC2       ), IDD_SC2       , "�ֽ��ֹ�����" },
	{ "�ֽ�/ELW" , "�ֹ�", "�ǽð�TR", "SC3"       , RUNTIME_CLASS(CDlg_SC3       ), IDD_SC3       , "�ֽ��ֹ����" },
	{ "�ֽ�/ELW" , "�ֹ�", "�ǽð�TR", "SC4"       , RUNTIME_CLASS(CDlg_SC4       ), IDD_SC4       , "�ֽ��ֹ��ź�" },
	//---------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------
	// �ֽ�/ELW ����
	{ "�ֽ�/ELW" , "����", "��ȸTR"  , "CSPAQ03700", RUNTIME_CLASS(CDlg_CSPAQ03700), IDD_CSPAQ03700, "�������� �ֹ�ü�᳻�� ��ȸ" },
	{ "�ֽ�/ELW" , "����", "��ȸTR"  , "CSPAQ02300", RUNTIME_CLASS(CDlg_CSPAQ02300), IDD_CSPAQ02300, "�������� �ܰ��� ��ȸ" },
	{ "�ֽ�/ELW" , "����", "��ȸTR"  , "CSPAQ02200", RUNTIME_CLASS(CDlg_CSPAQ02200), IDD_CSPAQ02200, "�������� ������/�ֹ����ɱݾ�/���� ��ȸ" },
	{ "�ֽ�/ELW" , "����", "��ȸTR"  , "CSPBQ00200", RUNTIME_CLASS(CDlg_CSPBQ00200), IDD_CSPBQ00200, "�������� ���űݷ��� �ֹ����ɼ��� ��ȸ" },
	//---------------------------------------------------------------------------------------------*/

	//---------------------------------------------------------------------------------------------
	// ����/�ɼ� �ü�
	{ "����/�ɼ�", "�ü�", "�ǽð�TR", "FC0"       , RUNTIME_CLASS(CDlg_FC0       ), IDD_FC0       , "����ü��" },
	{ "����/�ɼ�", "�ü�", "�ǽð�TR", "FH0"       , RUNTIME_CLASS(CDlg_FH0		),	IDD_FH0      , "����ȣ��" },
	{ "����/�ɼ�", "�ü�", "�ǽð�TR", "OC0"       , RUNTIME_CLASS(CDlg_OC0		),	IDD_OC0      , "�ɼ�ü��" },
	{ "����/�ɼ�", "�ü�", "�ǽð�TR", "OH0"       , RUNTIME_CLASS(CDlg_OH0		),	IDD_OH0      , "�ɼ�ȣ��" },
	{ "����/�ɼ�", "�ü�", "�ǽð�TR", "OH1"       , RUNTIME_CLASS(CDlg_OH1		),	IDD_OH1      , "�ɼ�ȣ��" },
	
	//---------------------------------------------------------------------------------------------
	// ����/�ɼ� �ֹ�
	//{ "����/�ɼ�", "�ֹ�", "��ȸTR"  , "CFOAT00100", RUNTIME_CLASS(CDlg_CFOAT00100), IDD_CFOAT00100, "�����ɼ� �����ֹ�" },
	//{ "����/�ɼ�", "�ֹ�", "��ȸTR"  , "CFOAT00200", RUNTIME_CLASS(CDlg_CFOAT00200), IDD_CFOAT00200, "�����ɼ� �����ֹ�" },
	//{ "����/�ɼ�", "�ֹ�", "��ȸTR"  , "CFOAT00300", RUNTIME_CLASS(CDlg_CFOAT00300), IDD_CFOAT00300, "�����ɼ� ����ֹ�" },
	//---------------------------------------------------------------------------------------------
	
	//---------------------------------------------------------------------------------------------
	// ����/�ɼ� ����
	//{ "����/�ɼ�", "����", "��ȸTR"  , "CFOAQ00600", RUNTIME_CLASS(CDlg_CFOAQ00600), IDD_CFOAQ00600, "�����ɼ� �����ֹ�ü�᳻�� ��ȸ" },
	//{ "����/�ɼ�", "����", "��ȸTR"  , "CFOFQ02400", RUNTIME_CLASS(CDlg_CFOFQ02400), IDD_CFOFQ02400, "�����ɼ� �̰���������Ȳ" },
	{ "����/�ɼ�", "����", "��ȸTR"  , "CFOAQ10100", RUNTIME_CLASS(CDlg_CFOAQ10100), IDD_CFOAQ10100, "�����ɼ� �ֹ����ɼ���" },
	//{ "����/�ɼ�", "����", "��ȸTR"  , "CEXAQ21200", RUNTIME_CLASS(CDlg_CEXAQ21200), IDD_CEXAQ21200, "������ �ֹ����ɼ���" },
	//---------------------------------------------------------------------------------------------
	
	//---------------------------------------------------------------------------------------------
	// ���� CME �ֹ�
	/*{ "���� CME", "�ֹ�", "��ȸTR"  , "CCEAT00100", RUNTIME_CLASS(CDlg_CCEAT00100), IDD_CCEAT00100, "���� CME �����ֹ�" },
	{ "���� CME", "�ֹ�", "��ȸTR"  , "CCEAT00200", RUNTIME_CLASS(CDlg_CCEAT00200), IDD_CCEAT00200, "���� CME �����ֹ�" },
	{ "���� CME", "�ֹ�", "��ȸTR"  , "CCEAT00300", RUNTIME_CLASS(CDlg_CCEAT00300), IDD_CCEAT00300, "���� CME ����ֹ�" },
	//---------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------
	// �ֽļ��� �ü�
	{ "�ֽļ���" , "�ü�", "�ǽð�TR", "JC0"       , RUNTIME_CLASS(CDlg_JC0       ), IDD_JC0       , "����ü��" },
	//---------------------------------------------------------------------------------------------
	
	//---------------------------------------------------------------------------------------------
	// ���� �ü�
	//---------------------------------------------------------------------------------------------
	
	//---------------------------------------------------------------------------------------------*/
	// ������
	{ "������", "", "��ȸTR", "t1601", RUNTIME_CLASS(CDlg_t1601), IDD_t1601, "�����ں�����" },
	{ "������", "", "��ȸTR", "t1602", RUNTIME_CLASS(CDlg_t1602), IDD_t1602, "�����ں��Ÿ����̻�" },
	/*	{ "������", "", "�ǽð�TR", "BMT"  , RUNTIME_CLASS(CDlg_BMT), IDD_BMT, "�ð��뺰 �����ڸŸ�����" },
	{ "������", "", "�ǽð�TR", "BM_"  , RUNTIME_CLASS(CDlg_BM_), IDD_BM_, "�����ں� �����ں� �Ÿ���Ȳ" },
	//---------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------
	// ���α׷�
	//---------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------
	// ��������
	//---------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------*/
	// ��Ʈ
	{ "����/�ɼ�", "��Ʈ", "��ȸTR", "t8415"       , RUNTIME_CLASS(CDlg_t8415		),	IDD_t8415      , "�ɼ���Ʈ" },
	//---------------------------------------------------------------------------------------------
	/*
	//---------------------------------------------------------------------------------------------
	// ��Ÿ
	{ "��Ÿ", "", "��ȸTR", "t9942", RUNTIME_CLASS(CDlg_t9942), IDD_t9942, "ELW��������ȸAPI��(t9941)" },
	{ "��Ÿ", "", "��ȸTR", "t9943", RUNTIME_CLASS(CDlg_t9943), IDD_t9943, "����������������ȸAPI��(t9941)" },
	//---------------------------------------------------------------------------------------------*/

	{ "�����ֹ�" , "�ü�", "��ȸTR",   "����"     , RUNTIME_CLASS(CDlg_JEKYLL), IDD_JEKYLL     , "JEKYLL" },
};

int GetTRWindowTableCount()
{
	return sizeof( s_tblTrWindow ) / sizeof( TR_WINDOW_TABLE );
}

LPTR_WINDOW_TABLE GetTRWindowTableData()
{
	return s_tblTrWindow;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
		ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
		ON_WM_SETFOCUS()
		ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
void CChildFrame::OnFileClose() 
{
	// To close the frame, just send a WM_CLOSE, which is the equivalent
	// choosing close from the system menu.

	SendMessage(WM_CLOSE);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	return 0;
}

void CChildFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	m_wndView.SetFocus();
}

BOOL CChildFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	
	// otherwise, do default handling
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CChildFrame::SetTR( LPCTSTR pszTrCode )
{
	int nCount = sizeof( s_tblTrWindow ) / sizeof( TR_WINDOW_TABLE );
	for( int i=0; i<nCount; i++ )
	{
		if( strcmp( s_tblTrWindow[i].szTrCode, pszTrCode ) == 0 )
		{
			char szTitle[256] = { 0 };
			sprintf( szTitle, "[%s] %s", s_tblTrWindow[i].szTrCode, s_tblTrWindow[i].szDesc );
			SetWindowText( szTitle  );
			CDocument* pDocument = GetActiveDocument();
			if( pDocument )
			{
				pDocument->SetTitle( szTitle );
			}
			else
			{
				m_strTitle = szTitle;
			}
			m_wndView.SetTR( s_tblTrWindow[i].pRuntimeClass, s_tblTrWindow[i].uDlgID );
			return TRUE;
		}
	}

	CString strMsg;
	strMsg.Format( "%s �� Sample�� ã�� �� �����ϴ�.", pszTrCode );
	
	MessageBox( strMsg, "����", MB_ICONSTOP );

	SendMessage( WM_CLOSE );
	
	return FALSE;
}