// Dlg_0H0.cpp : implementation file
//

#include "stdafx.h"
#include "XingAPI_Sample.h"
#include "Dlg_EH0.h"

#include "./packet/EH0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlg_0H0 dialog

IMPLEMENT_DYNCREATE(CDlg_EH0, CDialog)

CDlg_EH0::CDlg_EH0(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_EH0::IDD, pParent)
{

}


void CDlg_EH0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTBLOCK, m_ctrlOutBlock);
	DDX_Control(pDX, IDC_EDIT_CODE, m_code);
}


BEGIN_MESSAGE_MAP(CDlg_EH0, CDialog)
	//	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_MESSAGE(WM_USER + XM_RECEIVE_REAL_DATA, OnXMReceiveRealEH0)
END_MESSAGE_MAP()


// CDlg_EH0 message handlers


BOOL CDlg_EH0::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_code.SetWindowTextA("201M9312");
	m_strCode = "201M9312";
	// TODO:  Add extra initialization here
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlg_EH0::OnDestroy()
{
	UnadviseEH0();
	CDialog::OnDestroy();

	// TODO: Add your message handler code here


}


void CDlg_EH0::OnButtonRequest()
{
	// TODO: Add your control notification handler code here
	UnadviseEH0();
	AdviseEH0();
}

//--------------------------------------------------------------------------------------
// ��Ʈ�� �ʱ�ȭ
//--------------------------------------------------------------------------------------
void CDlg_EH0::InitCtrls()
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
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ��2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ��2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ������2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ������2");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ��3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ��3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ������3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ������3");
	m_ctrlOutBlock.InsertItem(nRow++, "�ŵ�ȣ���Ѽ���");
	m_ctrlOutBlock.InsertItem(nRow++, "�ż�ȣ���Ѽ���");
	m_ctrlOutBlock.InsertItem(nRow++, "�����ڵ�");
}

//--------------------------------------------------------------------------------------
// ������ Advise
//--------------------------------------------------------------------------------------
void CDlg_EH0::AdviseEH0()
{
	TCHAR	szTrCode[] = "EH0";

	//-----------------------------------------------------------
	// ������ ���
	CString strCode; GetDlgItemText(IDC_EDIT_CODE, strCode);

	//-----------------------------------------------------------
	// ������ ����
	BOOL bSuccess = g_iXingAPI.AdviseRealData(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_REAL_DATA ���� �´�.
		szTrCode,					// TR ��ȣ
		strCode,					// �����ڵ�
		strCode.GetLength()
		//sizeof(EH0_InBlock)		// �����ڵ� ����
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
void CDlg_EH0::UnadviseEH0()
{
	//-----------------------------------------------------------
	// ������ ����� ������ ���ٸ� Return�Ѵ�.
	if (m_strCode.IsEmpty())
	{
		return;
	}

	TCHAR	szTrCode[] = "EH0";

	//-----------------------------------------------------------
	// ������ ����
	BOOL bSuccess = g_iXingAPI.UnadviseRealData(
		GetSafeHwnd(),				// �����͸� ���� ������, XM_RECEIVE_REAL_DATA ���� �´�.
		szTrCode,					// TR ��ȣ
		m_strCode,					// �����ڵ�
		m_strCode.GetLength()
		//sizeof(EH0_InBlock)		// �����ڵ� ����
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
LRESULT CDlg_EH0::OnXMReceiveRealEH0(WPARAM wParam, LPARAM lParam)
{
	LPRECV_REAL_PACKET pRealPacket = (LPRECV_REAL_PACKET)lParam;

	if (strcmp(pRealPacket->szTrCode, "EH0") == 0)
	{

		LPEH0_OutBlock pOutBlock = (LPEH0_OutBlock)pRealPacket->pszData;
		int nRow = 0;
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->hotime, sizeof(pOutBlock->hotime), DATA_TYPE_STRING));    // ȣ���ð�
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho1, sizeof(pOutBlock->offerho1), DATA_TYPE_FLOAT, 2.2));    // �ŵ�ȣ��1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho1, sizeof(pOutBlock->bidho1), DATA_TYPE_FLOAT, 2.2));    // �ż�ȣ��1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem1, sizeof(pOutBlock->offerrem1), DATA_TYPE_LONG));    // �ŵ�ȣ������1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem1, sizeof(pOutBlock->bidrem1), DATA_TYPE_LONG));    // �ż�ȣ������1
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho2, sizeof(pOutBlock->offerho2), DATA_TYPE_FLOAT, 2.2));    // �ŵ�ȣ��2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho2, sizeof(pOutBlock->bidho2), DATA_TYPE_FLOAT, 2.2));    // �ż�ȣ��2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem2, sizeof(pOutBlock->offerrem2), DATA_TYPE_LONG));    // �ŵ�ȣ������2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem2, sizeof(pOutBlock->bidrem2), DATA_TYPE_LONG));    // �ż�ȣ������2
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerho3, sizeof(pOutBlock->offerho3), DATA_TYPE_FLOAT, 2.2));    // �ŵ�ȣ��3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidho3, sizeof(pOutBlock->bidho3), DATA_TYPE_FLOAT, 2.2));    // �ż�ȣ��3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->offerrem3, sizeof(pOutBlock->offerrem3), DATA_TYPE_LONG));    // �ŵ�ȣ������3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->bidrem3, sizeof(pOutBlock->bidrem3), DATA_TYPE_LONG));    // �ż�ȣ������3
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->totofferrem, sizeof(pOutBlock->totofferrem), DATA_TYPE_LONG));    // �ŵ�ȣ���Ѽ���
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->totbidrem, sizeof(pOutBlock->totbidrem), DATA_TYPE_LONG));    // �ż�ȣ���Ѽ���
		m_ctrlOutBlock.SetItemText(nRow++, 1, GetDispData(pOutBlock->optcode, sizeof(pOutBlock->optcode), DATA_TYPE_STRING));    // 
	}
	return 0L;
}