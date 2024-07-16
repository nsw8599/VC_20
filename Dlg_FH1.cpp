// Dlg_FH1.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Dlg_FH1.h"
#include "afxdialogex.h"

#include "./packet/FH0.h"


// CDlg_FH1 dialog

IMPLEMENT_DYNAMIC(CDlg_FH1, CDialog)

CDlg_FH1::CDlg_FH1(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_FH1, pParent)
{

}

CDlg_FH1::~CDlg_FH1()
{
}

void CDlg_FH1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTBLOCK, m_ctrlOutBlock);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
}


BEGIN_MESSAGE_MAP(CDlg_FH1, CDialog)
//	ON_WM_ACTIVATE()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_BUTTON_REQUEST, &CDlg_FH1::OnBnClickedButtonRequest)
ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealData)
END_MESSAGE_MAP()


// CDlg_FH1 message handlers


BOOL CDlg_FH1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlg_FH1::OnDestroy()
{
	UnadviseData();
	CDialog::OnDestroy();

	// TODO: Add your message handler code here


}


void CDlg_FH1::OnBnClickedButtonRequest()
{
	// TODO: Add your control notification handler code here
	UnadviseData();
	AdviseData();
}

//--------------------------------------------------------------------------------------
// ��Ʈ�� �ʱ�ȭ
//--------------------------------------------------------------------------------------
void CDlg_FH1::InitCtrls()
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
void CDlg_FH1::AdviseData()
{
	TCHAR	szTrCode[] = "FH0";

	//-----------------------------------------------------------
	// ������ ���
	CString strCode; GetDlgItemText(IDC_EDIT_CODE, strCode);

	//-----------------------------------------------------------
	// ������ ����
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_REAL_DATA ���� �´�.
		szTrCode,					// TR ��ȣ
		strCode,					// �����ڵ�
		sizeof(FH0_InBlock)		// �����ڵ� ����
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
void CDlg_FH1::UnadviseData()
{
	//-----------------------------------------------------------
	// ������ ����� ������ ���ٸ� Return�Ѵ�.
	if (m_strCode.IsEmpty())
	{
		return;
	}

	TCHAR	szTrCode[] = "FH0";

	//-----------------------------------------------------------
	// ������ ����
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_REAL_DATA ���� �´�.
		szTrCode,					// TR ��ȣ
		m_strCode,					// �����ڵ�
		sizeof(FH0_InBlock)		// �����ڵ� ����
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
LRESULT CDlg_FH1::OnXMReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;

	if (strcmp(pRealPacket->szTrCode, "FH0") == 0)
	{
		LPFH0_OutBlock pOutBlock = (LPFH0_OutBlock)pRealPacket->pszData;
		int nRow = 0;
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->hotime, sizeof(pOutBlock->hotime), DATA_TYPE_STRING));    // ȣ���ð�
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_FLOAT_DOT,2));    // �ŵ�ȣ��1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_FLOAT_DOT,2));    // �ż�ȣ��1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));    // �ŵ�ȣ������1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));    // �ż�ȣ������1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offercnt1, sizeof(pOutBlock->offercnt1), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidcnt1, sizeof(pOutBlock->bidcnt1), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�1

		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho2, sizeof(pOutBlock->offerho2), DATA_TYPE_FLOAT_DOT, 2));    // �ŵ�ȣ��2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho2, sizeof(pOutBlock->bidho2), DATA_TYPE_FLOAT_DOT, 2));    // �ż�ȣ��2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem2, sizeof(pOutBlock->offerrem2), DATA_TYPE_LONG));    // �ŵ�ȣ������2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem2, sizeof(pOutBlock->bidrem2), DATA_TYPE_LONG));    // �ż�ȣ������2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offercnt2, sizeof(pOutBlock->offercnt2), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidcnt2, sizeof(pOutBlock->bidcnt2), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�2

		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho3, sizeof(pOutBlock->offerho3), DATA_TYPE_FLOAT_DOT, 2));    // �ŵ�ȣ��3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho3, sizeof(pOutBlock->bidho3), DATA_TYPE_FLOAT_DOT, 2));    // �ż�ȣ��3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem3, sizeof(pOutBlock->offerrem3), DATA_TYPE_LONG));    // �ŵ�ȣ������3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem3, sizeof(pOutBlock->bidrem3), DATA_TYPE_LONG));    // �ż�ȣ������3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offercnt3, sizeof(pOutBlock->offercnt3), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidcnt3, sizeof(pOutBlock->bidcnt3), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�3

		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho4, sizeof(pOutBlock->offerho4), DATA_TYPE_FLOAT_DOT, 2));    // �ŵ�ȣ��4
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho4, sizeof(pOutBlock->bidho4), DATA_TYPE_FLOAT_DOT, 2));    // �ż�ȣ��4
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem4, sizeof(pOutBlock->offerrem4), DATA_TYPE_LONG));    // �ŵ�ȣ������4
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem4, sizeof(pOutBlock->bidrem4), DATA_TYPE_LONG));    // �ż�ȣ������4
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offercnt4, sizeof(pOutBlock->offercnt4), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�4
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidcnt4, sizeof(pOutBlock->bidcnt4), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�4

		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho5, sizeof(pOutBlock->offerho5), DATA_TYPE_FLOAT_DOT, 2));    // �ŵ�ȣ��5
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho5, sizeof(pOutBlock->bidho5), DATA_TYPE_FLOAT_DOT, 2));    // �ż�ȣ��5
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem5, sizeof(pOutBlock->offerrem5), DATA_TYPE_LONG));    // �ŵ�ȣ������5
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem5, sizeof(pOutBlock->bidrem5), DATA_TYPE_LONG));    // �ż�ȣ������5
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offercnt5, sizeof(pOutBlock->offercnt5), DATA_TYPE_LONG));    // �ŵ�ȣ���Ǽ�5
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidcnt5, sizeof(pOutBlock->bidcnt5), DATA_TYPE_LONG));    // �ż�ȣ���Ǽ�5

		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->totofferrem, sizeof(pOutBlock->totofferrem), DATA_TYPE_LONG));    // �ŵ�ȣ���Ѽ���
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->totbidrem, sizeof(pOutBlock->totbidrem), DATA_TYPE_LONG));    // �ż�ȣ���Ѽ���
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->totoffercnt, sizeof(pOutBlock->totoffercnt), DATA_TYPE_LONG));    // �ŵ�ȣ���ѰǼ�
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->totbidcnt, sizeof(pOutBlock->totbidcnt), DATA_TYPE_LONG));    // �ż�ȣ���ѰǼ�

		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->futcode, sizeof(pOutBlock->futcode), DATA_TYPE_STRING));    // ȣ���ð�
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->danhochk, sizeof(pOutBlock->danhochk), DATA_TYPE_STRING));    // ȣ���ð�
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->alloc_gubun, sizeof(pOutBlock->alloc_gubun), DATA_TYPE_STRING));    // ȣ���ð�
	}

	return 0L;
}