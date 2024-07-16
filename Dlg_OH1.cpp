// Dlg_0H1.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Dlg_OH1.h"

#include "./packet/OH0.h"
#include<mutex>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlg_0H1 dialog

IMPLEMENT_DYNCREATE(CDlg_OH1, CDialog)

int nColumn;
mutex mtx;

CDlg_OH1::CDlg_OH1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_OH1::IDD, pParent)
{

}


void CDlg_OH1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTBLOCK, m_ctrlOutBlock);
	DDX_Control(pDX, IDC_EDIT_CODE, m_code);
}


BEGIN_MESSAGE_MAP(CDlg_OH1, CDialog)
	//	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealOH0)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST24, &CDlg_OH1::OnBnClickedButtonRequest24)
END_MESSAGE_MAP()


// CDlg_OH1 message handlers


BOOL CDlg_OH1::OnInitDialog()
{
	CDialog::OnInitDialog();
	nColumn = 1;
	//m_strCode = "201MA322";
	//m_code.SetWindowTextA(m_strCode);
	// TODO:  Add extra initialization here
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlg_OH1::OnDestroy()
{
	//UnadviseOH0();
	CDialog::OnDestroy();

	UnadviseOH0("201N6330");
	UnadviseOH0("301N6305");
	// TODO: Add your message handler code here


}



//--------------------------------------------------------------------------------------
// ��Ʈ�� �ʱ�ȭ
//--------------------------------------------------------------------------------------
void CDlg_OH1::InitCtrls()
{
	//-------------------------------------------------------------------------
	// OutBlock
	m_ctrlOutBlock.InsertColumn(0, "�ʵ�  ", LVCFMT_LEFT, 150);
	m_ctrlOutBlock.InsertColumn(1, "������", LVCFMT_LEFT, 200);

	int nRow = 0;
	m_ctrlOutBlock.InsertItem(nRow++, "ȣ���ð�");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ��1");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ��1");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ������1");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ������1");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ���Ǽ�1");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ���Ǽ�1");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ��2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ��2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ������2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ������2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ���Ǽ�2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ���Ǽ�2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ��3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ��3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ������3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ������3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ���Ǽ�3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ���Ǽ�3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ��4");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ��4");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ������4");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ������4");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ���Ǽ�4");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ���Ǽ�4");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ��5");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ��5");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ������5");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ������5");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ���Ǽ�5");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ���Ǽ�5");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ���Ѽ���");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ���Ѽ���");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ���ѰǼ�");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ���ѰǼ�");
	m_ctrlOutBlock.InsertItem(nRow++, "�����ڵ�");
	m_ctrlOutBlock.InsertItem(nRow++, "���ϰ�ȣ������");
	m_ctrlOutBlock.InsertItem(nRow++, "������뱸��");
}

//--------------------------------------------------------------------------------------
// ������ Advise
//--------------------------------------------------------------------------------------
void CDlg_OH1::AdviseOH0(CString strCode)
{
	TCHAR	szTrCode[] = "OH0";

	//-----------------------------------------------------------
	// ������ ���
	//CString strCode; GetDlgItemText(IDC_EDIT_CODE, strCode);

	//-----------------------------------------------------------
	// ������ ����
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_REAL_DATA ���� �´�.
		szTrCode,					// TR ��ȣ
		strCode,					// �����ڵ�
		strCode.GetLength()
		//sizeof(OH0_InBlock)		// �����ڵ� ����
		);

	//-----------------------------------------------------------
	// ����üũ
	if (bSuccess == FALSE)
	{
		MessageBox("��ȸ����", "����", MB_ICONSTOP);
	}
	else
	{
		m_strCode = strCode;
	}
}

//--------------------------------------------------------------------------------------
// ������ Unadvise
//--------------------------------------------------------------------------------------
void CDlg_OH1::UnadviseOH0(CString strCode)
{
	//-----------------------------------------------------------
	// ������ ����� ������ ���ٸ� Return�Ѵ�.
	m_strCode = strCode;
	if (m_strCode.IsEmpty())
	{
		return;
	}

	TCHAR	szTrCode[] = "OH0";

	//-----------------------------------------------------------
	// ������ ����
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_REAL_DATA ���� �´�.
		szTrCode,					// TR ��ȣ
		m_strCode,					// �����ڵ�
		m_strCode.GetLength()
		//sizeof(OH0_InBlock)		// �����ڵ� ����
		);

	//-----------------------------------------------------------
	// ����üũ
	if (bSuccess == FALSE)
	{
		MessageBox("��ȸ����", "����", MB_ICONSTOP);
	}
	else
	{
		m_strCode.Empty();
	}

}

//--------------------------------------------------------------------------------------
// �����͸� ����
//--------------------------------------------------------------------------------------
LRESULT CDlg_OH1::OnXMReceiveRealOH0(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;

	if (strcmp(pRealPacket->szTrCode, "OH0") == 0)
	{
		
		LPOH0_OutBlock pOutBlock = (LPOH0_OutBlock)pRealPacket->pszData;
		int nRow = 0;
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->hotime, sizeof(pOutBlock->hotime), DATA_TYPE_STRING));    // ȣ���ð�
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_FLOAT,2.2));    // �ŵ�ȣ��1
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_FLOAT, 2.2));    // �ż�ȣ��1
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));    // �ŵ�ȣ������1
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));    // �ż�ȣ������1
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offercnt1, sizeof(pOutBlock->offercnt1), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�1
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidcnt1, sizeof(pOutBlock->bidcnt1), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�1
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerho2, sizeof(pOutBlock->offerho2), DATA_TYPE_FLOAT, 2.2));    // �ŵ�ȣ��2
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidho2, sizeof(pOutBlock->bidho2), DATA_TYPE_FLOAT, 2.2));    // �ż�ȣ��2
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerrem2, sizeof(pOutBlock->offerrem2), DATA_TYPE_LONG));    // �ŵ�ȣ������2
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidrem2, sizeof(pOutBlock->bidrem2), DATA_TYPE_LONG));    // �ż�ȣ������2
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offercnt2, sizeof(pOutBlock->offercnt2), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�2
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidcnt2, sizeof(pOutBlock->bidcnt2), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�2
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerho3, sizeof(pOutBlock->offerho3), DATA_TYPE_FLOAT, 2.2));    // �ŵ�ȣ��3
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidho3, sizeof(pOutBlock->bidho3), DATA_TYPE_FLOAT, 2.2));    // �ż�ȣ��3
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerrem3, sizeof(pOutBlock->offerrem3), DATA_TYPE_LONG));    // �ŵ�ȣ������3
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidrem3, sizeof(pOutBlock->bidrem3), DATA_TYPE_LONG));    // �ż�ȣ������3
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offercnt3, sizeof(pOutBlock->offercnt3), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�3
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidcnt3, sizeof(pOutBlock->bidcnt3), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�3
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerho4, sizeof(pOutBlock->offerho4), DATA_TYPE_FLOAT, 2.2));    // �ŵ�ȣ��4
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidho4, sizeof(pOutBlock->bidho4), DATA_TYPE_FLOAT, 2.2));    // �ż�ȣ��4
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerrem4, sizeof(pOutBlock->offerrem4), DATA_TYPE_LONG));    // �ŵ�ȣ������4
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidrem4, sizeof(pOutBlock->bidrem4), DATA_TYPE_LONG));    // �ż�ȣ������4
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offercnt4, sizeof(pOutBlock->offercnt4), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�4
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidcnt4, sizeof(pOutBlock->bidcnt4), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�4
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerho5, sizeof(pOutBlock->offerho5), DATA_TYPE_FLOAT, 2.2));    // �ŵ�ȣ��5
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidho5, sizeof(pOutBlock->bidho5), DATA_TYPE_FLOAT, 2.2));    // �ż�ȣ��5
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offerrem5, sizeof(pOutBlock->offerrem5), DATA_TYPE_LONG));    // �ŵ�ȣ������5
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidrem5, sizeof(pOutBlock->bidrem5), DATA_TYPE_LONG));    // �ż�ȣ������5
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->offercnt5, sizeof(pOutBlock->offercnt5), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�5
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->bidcnt5, sizeof(pOutBlock->bidcnt5), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�5
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->totofferrem, sizeof(pOutBlock->totofferrem), DATA_TYPE_LONG));    // �ŵ�ȣ���Ѽ���
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->totbidrem, sizeof(pOutBlock->totbidrem), DATA_TYPE_LONG));    // �ż�ȣ���Ѽ���
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->totoffercnt, sizeof(pOutBlock->totoffercnt), DATA_TYPE_LONG));    // �ŵ�ȣ���ѰǼ�
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->totbidcnt, sizeof(pOutBlock->totbidcnt), DATA_TYPE_LONG));    // �ż�ȣ���ѰǼ�
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->optcode, sizeof(pOutBlock->optcode), DATA_TYPE_STRING));    // 
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->danhochk, sizeof(pOutBlock->danhochk), DATA_TYPE_STRING));    // 
		m_ctrlOutBlock.SetItemText(nRow++, nColumn, GetDispData(pOutBlock->alloc_gubun, sizeof(pOutBlock->alloc_gubun), DATA_TYPE_STRING));    //
	}
	return 0L;
}

//UINT MyThreadProc(LPVOID Param)
//{
//	AdviseOH0("301N6305");
//	if (stopNow==FALSE) {
//		UnadviseOH0("301N6305");
//	}
//	return TRUE;
//}

void CDlg_OH1::OnButtonRequest()
{
	// TODO: Add your control notification handler code here
	//mtx.lock();
	//AdviseOH0("201N6330");
	//mtx.unlock();
	//Sleep(1000);
	//nColumn = 2;
	AdviseOH0("301N6305");
}

void CDlg_OH1::OnBnClickedButtonRequest24()
{
	// TODO: Add your control notification handler code here
	//UnadviseOH0("201N6330");
	UnadviseOH0("301N6305");
}
